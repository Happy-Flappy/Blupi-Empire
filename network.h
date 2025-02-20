#include <chrono>
#include <windows.h>
#include <fstream>
#include <filesystem>
#include <cstring>
class Network {

    public:
        UdpSocket udpsocket;
        IpAddress hostip;
        std::string pcname;
        std::string hostname = "MAX-PC";
        unsigned short hostport = 12345;
        bool hostknown=false;
		bool loadingLevel = false;
	

        struct Client {
            IpAddress ip;
            unsigned short port;
            std::string color;
            bool loadedLevel=false;

        };

        std::vector<Client> clients;


        Network() {

        }



		
		
		
		
		
		
		
		void sendFile(sf::TcpSocket& socket, const std::string& filePath) 
		{
		    sf::Packet packet;
		    std::ifstream inFile(map.folder + filePath, std::ios::binary);
		    std::vector<char> fileData((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
		
		    
		    // Send the file path
		    
		    
		    packet << filePath;
		    socket.send(packet);
		
		    // Send the file data
		    packet.clear();
		    packet.append(fileData.data(), fileData.size());
		    socket.send(packet);
		
		}
		
		
		
		
		std::string receiveFile(sf::TcpSocket& socket, const std::string& folder) {
		    sf::Packet packet;
		    std::string filedir;
		    std::vector<char> fileData;
		
		    // Receive the file name
		    socket.receive(packet);
		    packet >> filedir;
		
		    // Receive the file data
		    packet.clear();
		    socket.receive(packet);
		    fileData.resize(packet.getDataSize());
		    memcpy(fileData.data(), packet.getData(), packet.getDataSize());




			
			size_t pos = filedir.find_last_of('/');
			
			std::string path = filedir.substr(0,pos+1);
			
			std::string fileName =  filedir.substr(pos+1);



			std::filesystem::create_directories(folder + path);
			std::cout <<"Create directory ("<<folder + path + fileName<< ")\n";

						
				

		    // Save the file to the new folder
		    std::cout <<"Output file("<< folder + path + fileName << ")\n";
		    std::ofstream outFile(folder + path + fileName, std::ios::binary);
		    outFile.write(fileData.data(),fileData.size());
		    outFile.close();
		    
		    
		    return path + fileName;
		}
		
		
		
		
		
		void sendLevel(const sf::IpAddress& clientIp, unsigned short clientPort)
		{
			
		    sf::TcpSocket socket;
			socket.connect(clientIp,clientPort);
			
			Packet packet;
			packet << map.filepaths.size();//that number includes the script file since filepath size is more than literal size by 1.
			socket.send(packet);
			
			sendFile(socket,map.name);//send script file
			
			for(int a=0;a<map.filepaths.size();a++)
			{
			
				sendFile(socket,map.filepaths[a]);
			}
			
		}
		
		
		
		
		
		void getLevel(unsigned short clientPort)
		{

			if(map.folder!="ClientData/")
			{
			
			//Empty if existing folder
			std::string folder = "ClientData";
			
			if (std::filesystem::exists(folder)) 
			{
		        std::filesystem::remove_all(folder);
			}
			else
				std::filesystem::create_directory(folder);
		    
		    folder = "ClientData/";
		    
		    
		    


		    sf::TcpListener listener;
		    if (listener.listen(clientPort) != sf::Socket::Done) {
		        std::cout << "Error listening on port " << clientPort << std::endl;
		        return;
		    }
		
		    sf::TcpSocket socket;
		    if (listener.accept(socket) != sf::Socket::Done) {
		        std::cout << "Error accepting connection on port " << clientPort << std::endl;
		        return;
		    }
		    


		    
		    
		    
		    Packet packet;
		    socket.receive(packet);
		    
		    
		    
		    
		    int files;
		    packet >> files;
		    packet.clear();
		    
		    
		    receiveFile(socket,folder);
		    
		    
		    std::vector<std::string> filename;
		    for(int a=0;a<files;a++)
		    {
				filename.push_back(receiveFile(socket,folder)); 
				std::cout << "Received File ("<<filename[filename.size()-1]<<")\n";
			}
			
			
			
			map.folder = folder;
		    
		    
		    
		    map.loadMap(filename[0]);
		    
			}
		}
		
		













		void sendData() 
		{
			
			
			
	        if(isHost) 
	        {
	            Packet packet;
	            


				bool found=false;
  				for(const auto& client : clients)
		        {
		        	if(!client.loadedLevel && map.name!="")
		        	{
		        		
		        		found=true;
		        		packet << "getLevel";
		        		sendLevel(client.ip,client.port);
		        		break;
					}
		        }
		        if(!found)
					packet << "noLoadLevel";


				
				packet << playing;
	            
	            if(playing) 
	            {
	            	
	        	
	                packet << blupi.size();
	                
					
		            for (const auto& b : blupi) {
		                packet << b.color;
		                packet << b.now.x;
		                packet << b.now.y;
		                packet << b.velocity.x;
		                packet << b.velocity.y;
		                packet << b.state;
		                packet << b.rotation;
		                packet << b.locomotion;	
		            }
	            }
	            
	            
	            
  
	            
	            
  				for(const auto& client : clients)
		        {
		            udpsocket.send(packet, client.ip, client.port);
		        }
	           		
	        } 
	        else 
	        {
        
		        Packet packet;
                
				
				packet << map.name;
				
				
				packet << UserColor;


	            if(playing) 
	            {

                    for(int a = 0; a < blupi.size(); a++) 
                    {
                        if(blupi[a].color == UserColor) 
                        {
                    		packet << blupi[a].action;	
							packet << blupi[a].destination.x;
							packet << blupi[a].destination.y;	
						
						}
                    }
 	            } 
	            
	            
	        	
	            
				udpsocket.send(packet, hostip, hostport);
               
                
	        }
	
		}
































		void getData() 
		{
		   
			if (!hostknown)
			{
				if(hostname!="")
				{
					hostip = IpAddress(hostname);
					
					if(hostip == IpAddress::None)
					{
//				    	Message("Failed: Unable to access the PC IP address.");
						
						return;
					}
					
					
					if(hostip != IpAddress::None)
					{
					
			            char pc[MAX_COMPUTERNAME_LENGTH + 1];
					    DWORD size = sizeof(pc) / sizeof(pc[0]);
					
					    if (GetComputerName(pc, &size))
						{
							std::string str(pc);
							pcname = str;
						}
						
						
						
						std::cout << pcname;
						std::cout << hostname;
						if(pcname==hostname)
						{
				            std::cerr << "Running in host mode (same computer)" << std::endl;
				            // Try to bind to host port
				            if (udpsocket.bind(hostport) != Socket::Done)
				            {
				                std::cerr << "Failed to bind host port, falling back to client mode" << std::endl;
				                isHost = false;
				                udpsocket.bind(Socket::AnyPort);
				            }
				            else
				            {
				                isHost = true;
				            }							
						}
						else
						{
						    std::cout << "Running in client mode (different computer)" << std::endl;
				            // Client mode - bind to any available port
				            isHost = false;
				            if (udpsocket.bind(Socket::AnyPort) != Socket::Done)
				            {
				                std::cerr << "Failed to bind client port" << std::endl;
				                return;
				            }	
						}
						
				        hostknown = true;
				        udpsocket.setBlocking(false);
				    }
				}
			}
		   	else
		   	{
		
		        if(isHost) 
		        {
		            Packet packet;
		            IpAddress ip;
		            unsigned short port;
		            
	        	    Socket::Status status = udpsocket.receive(packet, ip, port);
    				if(status == Socket::NotReady)
	        	    {
	        	    	return;
					}    
		            
		            
		            std::string level;
				    packet >> level;
				    
				    if(level=="" && playing && map.name!="")
					{
						for(int a = 0; a < clients.size(); a++) 
		                {
		                    if(clients[a].ip == ip) 
		                    {
		                    	clients[a].loadedLevel=false;
		                    	break;
		                    }
		                }
					}
					if(level!="")
					{
						for(int a = 0; a < clients.size(); a++) 
		                {
		                    if(clients[a].ip == ip) 
		                    {
		                    	clients[a].loadedLevel=true;
		                    	break;
		                    }
		                }
					}
					
	
	                std::string color;
	                packet >> color;
	
		            if(playing) 
		            {
		                for(int a = 0; a < blupi.size(); a++) 
		                {
		                    if(blupi[a].color == color) 
		                    {
		                        packet >> blupi[a].action;
	                        	packet >> blupi[a].destination.x;
	                        	packet >> blupi[a].destination.y;
							
								
		                    }
		                }
		                
	
		                
		                
		            } 
		            else 
		            {
		
		                bool known = false;
		                for(int a = 0; a < clients.size(); a++) 
		                {
		                    if(clients[a].ip == ip) 
		                    {
		                        known = true;
		                        break;
		                    }
		                }
		
		                if(!known) 
		                {
		                    Client newclient;
		                    newclient.ip = ip;
		                    newclient.port = port;
		                    newclient.color = color;
		                    clients.push_back(newclient);
		                }
		                
		                
	
		                
		            }
		            
		            
		            bool clearold=true;
		                
	                while(clearold)
	                {
						packet.clear();
		                
		        	    Socket::Status status = udpsocket.receive(packet, ip, port);
	    				if(status == Socket::NotReady)
		        	    {
		        	    	clearold=false;
						}
					}
		        } 
		        else 
		        {
	        	 
		            Packet packet;
		            IpAddress ip;
		            unsigned short port;
	        	    
	        	    
	        	    Socket::Status status = udpsocket.receive(packet, ip, port);
    				if(status == Socket::NotReady)
	        	    {
	        	    	return;
					}
		        	
		        	
		        	
					std::string loadID;
					packet >> loadID;
					if(loadID=="getLevel" && !isHost)
		        	{
		        		//load the level
		        		unsigned short cport;
		        		cport = udpsocket.getLocalPort();
		        		getLevel(cport);
					}
		        	
		        	
	        	
		            packet >> playing;
		                
		                
		                
		            
		            if(playing) 
		            {
		            
		                
						
						
						
						
		
		                int size;
		                packet >> size;
		                if(size!=blupi.size())
		                	blupi.resize(size);

			            for (auto& b : blupi) {
			                
							
							
							packet >> b.color;
			                packet >> b.now.x;
			                packet >> b.now.y;
			                packet >> b.velocity.x;
			                packet >> b.velocity.y;
			                packet >> b.state;
				            packet >> b.rotation;
				            packet >> b.locomotion;
			                
			                
			            }

		            }
		            
		            
		            bool clearold=true;
		                
	                while(clearold)
	                {
						packet.clear();
		                
		        	    Socket::Status status = udpsocket.receive(packet, ip, port);
	    				if(status == Socket::NotReady)
		        	    {
		        	    	clearold=false;
						}
					}
		            
				
		        }
		    }
		    
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		

} network;
