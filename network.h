#ifndef NETWORK_H
#define NETWORK_H

#include <SFML/Network.hpp>
#include <vector>
#include <iostream>





sf::IpAddress serverIP = sf::IpAddress("147.185.221.16");
unsigned short serverLocalPort = 5000;  // What the game binds to locally
unsigned short serverTunnelPort = 20821; // What playit.gg exposes to the internet
unsigned short clientLocalPort = 4000;  // What client binds to locally

class Client
{
	public:
	

	
	
	Client()
	{
		//init player hookup on both sides for testing
		self.color = "yellow";
		self.name = "Flappy";	
		self.ip = sf::IpAddress::getLocalAddress();
		self.port = clientLocalPort;	
	}



	void start(sf::UdpSocket &socket)
	{
        if(socket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
        {
            std::cerr << "Client failed to bind\n";
            return;
        }
        std::cerr << "Client bound to port " << socket.getLocalPort() << "\n";

	}


	
	void requestConnect(sf::Packet &packet)
	{
		//Send self to Server
		
		packet << "REQUEST_CONNECT";
		packet << self.color << self.name;
		
	}	
	
	
	
	void sendInput(sf::Packet &packet)
	{
		packet << "GAME_INPUT";
		
		packet << blupi.size();
		
		for(int a=0; a < blupi.size(); a++)
		{
			packet << a;
			blupi[a].sendInput(packet);
		}
	}
	
	
	
	void getGameState(sf::Packet &packet)
	{
		int blupiSize = 0;
		packet >> blupiSize;
		
		for(int a=0; a < blupiSize; a++)
		{
			int index = 0;
			packet >> index;
			
			while(blupiSize >= blupi.size()) // if not enough blupis in the vector then only use CreateBlupi for making new vector indices.
			{
				CreateBlupi();
			}
			
			//now there are enough vector indices and the proper indices mentioned by the host can be modified.
			
			blupi[index].getState(packet);
			
		}
		
		
		
		int elementSize = 0;
		packet >> elementSize;
		
		for(int a=0; a < elementSize; a++)
		{
			int index = 0;
			packet >> index;
			
			while(elementSize >= element.size()) //Same reason as done for blupi
			{
				CreateElement();
			}
			
			element[index].getState(packet);
			
		}
		
		
	}
	
	
	
	
	
	void sendAllPacket(sf::Packet &packet,sf::UdpSocket &socket)
	{
		packet.clear();
		// Send connection request to TUNNEL port
		requestConnect(packet);
		socket.send(packet,serverIP,serverTunnelPort);

		packet.clear();
		sendInput(packet);

		//send to already known server
		socket.send(packet,serverIP,serverTunnelPort);
	}
	
	bool getAllPacket(sf::Packet &packet,sf::UdpSocket &socket)
	{
		sf::IpAddress ip;
		unsigned short port;
		
		if(socket.receive(packet,ip,port) != sf::Socket::Done)
		{
			packet.clear();
			return false;
		}
//		sf::Packet empty;
//		while(socket.receive(empty,ip,port) != sf::Socket::Done)
//		{
//			//empty garbage data
//		}
//		
	    std::string type;
	    if(packet >> type)
	    {
	        if(type == "GAME_STATE")
	        {
	            getGameState(packet);
	            return true;
	        }
	    }
		
		return true;
	}
		
};


class Server
{
	public:
	
	
	
	
	std::vector<Player> players;
	
	
	
	Server()
	{
		
		
	}
	
	
	
	void start(sf::UdpSocket &socket)
	{
		if(socket.bind(serverLocalPort) != sf::Socket::Done)
		{
            std::cerr << "Failed to Start Server on port " << serverLocalPort << "!\n";
            system("pause");
			exit(0);
		}
		else
			std::cerr << "Server started on port " << serverLocalPort << "!\n";
		
	}
	
	
	
		
	void getRequest(Player player)
	{
		
		for(int a=0; a < players.size(); a++)
		{
			
			if(player.name == players[a].name)
			{
				return;
			}
			
		}
		
		
		players.push_back(player);

		std::cerr << "Connected to "<< player.name << "\n";
		
		
	}	
		
	
	void getInput(sf::Packet &packet)
	{
		
		int size = 0;
		packet >> size;
		for(int a=0; a < size; a++)
		{
			
			int index = 0;
			packet >> index;
			
			
			if(index < blupi.size())
				blupi[index].getInput(packet);
			else
			{
				Blupi dummy;
				dummy.getInput(packet);
			}	
				
		}
		
	}	
		
	
	void sendGameState(sf::Packet &packet)
	{
		packet << "GAME_STATE";
		
		//Clients dont need to know player count. 
		//Only elements and blupis and needed on client side.
		
		int blupiSize = static_cast<int>(blupi.size());
		
		packet << blupiSize;
		
		for(int a = 0; a < blupiSize; a++)
		{
			packet << a;
			blupi[a].sendState(packet);
		}
		
		int elementSize = static_cast<int>(element.size());
		
		packet << elementSize;
		
		for(int a = 0; a < elementSize; a++)
		{
			packet << a;
			element[a].sendState(packet);
		}
		
		
	
		
	}
	
	
	
	void sendAllPacket(sf::Packet &packet,sf::UdpSocket &socket)
	{

		sendGameState(packet);
			
		//send to all known clients
		
		for(int a=0; a < players.size(); a++)
		{
			socket.send(packet,players[a].ip,players[a].port);
		}
	}
	
	bool getAllPacket(sf::Packet &packet,sf::UdpSocket &socket)
	{
		
		sf::IpAddress ip;
		unsigned short port;
		while(socket.receive(packet,ip,port) == sf::Socket::Done)
		{
			std::string type;
			packet >>  type;
			
			if(type == "REQUEST_CONNECT")
			{
				std::string color,name;
				packet >> color >> name;
				getRequest({name,color,ip,port});
			}
			
			
			
			if(type == "GAME_INPUT")
			{
				getInput(packet);
			}
			
			packet.clear();
		}

		return true;
	}
	
		
};





class Network
{
	public:
		
		
	sf::UdpSocket socket;	
		
	Client client;
	Server server;
	
	
	//already connected to only client for now
	
	
	
	
	
	Network()
	{

	}


	


	void init()
	{
		socket.setBlocking(false);
		if(isServer)
			server.start(socket);
		else
			client.start(socket);
		
	}
	
	
	void getData()
	{
		sf::Packet packet;
		if(isServer)
		{
			//call server functions
			server.getAllPacket(packet,socket);
		}
		else
		{
			//call client functions
			client.getAllPacket(packet,socket);
		}
	}
	
	
	void sendData()
	{
		sf::Packet packet;
		if(isServer)
		{
			//call server functions
			server.sendAllPacket(packet,socket);
		}
		else
		{
			//call client functions
			client.sendAllPacket(packet,socket);
		}		
	}
	
	
	
}network;




#endif