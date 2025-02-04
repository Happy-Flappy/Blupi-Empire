

class Network
{

	public:
	UdpSocket udpsocket;
	IpAddress hostip = IpAddress::None;
	unsigned short hostport;
	unsigned short clientport;
	
	struct Client
	{
		IpAddress ip;
		unsigned short port;
		std::string color;
		
	};
	
	std::vector<Client> clients;
	
	
	Network()
	{
		
	}
	
	
	
	
	
	
	
	
	
	void sendData()
	{
		
		
		
		//discover host
		if(hostip==IpAddress::None)
		{
			Packet packet;
			packet << "GET_HOST";
			udpsocket.send(packet,IpAddress::Broadcast,12345);
		}
		else
		{
			Packet packet;
			packet << "You are HOST";
			udpsocket.send(packet,hostip,hostport);
			if(clientport==0)
			{
				clientport = Socket::AnyPort;
				udpsocket.bind(clientport);
			}
			packet.clear();
		
		
			if(isHost)
			{
				
				
				
				
				Packet packet;
				
				
				
				
				packet << playing;
				
				packet << map.name; 
				
				
				if(playing)
				{
				
				
				
				
				
					packet << blupi.size();
					
					for(int a=0; a < blupi.size(); a++)
					{
						packet << blupi[a].velocity.x;
						packet << blupi[a].velocity.y;
						
					}
					
					
					
					udpsocket.send(packet, IpAddress::Broadcast, 12345);
				}
				
				
				
				
				
				
				
				
			}
			else
			{
				
				
				if(playing)
				{
					if(hostip!=IpAddress::None)
					{
								
						Packet packet;
						
						
						packet << UserColor;
						
						
						for(int a=0;a<blupi.size();a++)
						{
							if(blupi[a].color == UserColor)
							{
								packet << blupi[a].action;
								packet << blupi[a].state;
							}
						}
						
						udpsocket.send(packet,IpAddress::Broadcast,12345);
					}
				}
				else
				{
					if(hostip!=IpAddress::None)
					{
						Packet packet;
						packet << UserColor;
						udpsocket.send(packet,hostip,hostport);
					}
				}
				
				
			}
			
		
		}
		
		
		
		
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	void getData()
	{
		
		
		//discover host
		if(hostip==IpAddress::None)
		{
			Packet packet;
			udpsocket.receive(packet,hostip,hostport);//get host ip and port if a host is out there.
			
			std::string str;
			packet >> str;
			if(str == "You are HOST")
			{
				hostip = IpAddress::getLocalAddress();
				hostport = 12345;
				
				udpsocket.bind(hostport);
				udpsocket.setBlocking(false);
				isHost = true;
			}
			else
			{
				static float forcehost=0;
				forcehost+=seconds(1.f/60.f).asSeconds();
				packet.clear();
				
				
				if(forcehost >= 1)
				{
					
					std::cout<<"Now Host"<<"\n";
					hostip = IpAddress::getLocalAddress();
					std::cout<<hostip.toString()<<"\n";
					hostport = 12345;
					isHost=true;
					udpsocket.bind(hostport);
					udpsocket.setBlocking(false);
					forcehost=0;
					
				}
			}
		}
		else
		{
		
		
		
		
		
			if(isHost)
			{
				Packet packet;
				
				if(udpsocket.receive(packet,hostip,hostport)!=Socket::Done)
					return;
				
				
				
				
				if(playing)
				{
				
				
					std::string color;
					packet >> color;
						
					
					
					for(int a=0;a<blupi.size();a++)
					{
						
						if(blupi[a].color == color)
						{
							packet >> blupi[a].action;
							packet >> blupi[a].state;	
						}
						
					}
					
				}
				else
				{
					IpAddress ip;
					unsigned short port;
					
					udpsocket.receive(packet,ip,port);
					
					std::string color;
					packet >> color;
					
					bool known=false;
					for(int a=0;a<clients.size();a++)
					{
						if(clients[a].ip == ip)
						{
							known=true;
							break;
						}
					}
					
					if(!known)
					{
						Client newclient;
						newclient.ip=ip;
						newclient.port = port;
						newclient.color = color;
						clients.push_back(newclient);
					}
					
					
				}
				
				
				
				
				
				
				
				
				
				
				
			}
			else
			{
				
				
				
				if(playing)
				{
					
				
					Packet packet;
					
					
					if(udpsocket.receive(packet,hostip,hostport)!=Socket::Done)
						return;
					
					
					
					packet >> playing;
					
					std::string level;
					packet >> level;
					if(map.name!=level)
					{
						map.loadMap(level);
					}
					
					int size;
					
					packet >> size;
					
					blupi.resize(size);
					
					for(int a=0; a < blupi.size(); a++)
					{
						
						packet >> blupi[a].velocity.x;
						packet >> blupi[a].velocity.y;
						
						
					}
				}
				else
				{
					Packet packet;
					
					if(udpsocket.receive(packet,hostip,hostport)!=Socket::Done)
						return;
					
					
					packet >> playing; 
					
					
					
				}
				
				
				
				
				
				
				
				
				
			}
		
		}
		
		
	}
}network;
