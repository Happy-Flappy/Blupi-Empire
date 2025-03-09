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
        std::string hostname = "";
        unsigned short hostport = 12345;
        bool hostknown=false;
		bool allLoaded = false;
		int loadPercent=0;

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
			
			system("cls");
			std::cout << "Sending Level Data to clients> ";
			
			std::cout << ".";
			sendFile(socket,map.name);//send script file
			
			for(int a=0;a<map.filepaths.size();a++)
			{
				std::cout << ".";
				sendFile(socket,map.filepaths[a]);
			}
			
			
			system("cls");
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
		    
		    
		    system("cls");
		    
		    
		    int percent;
		    
			percent = 100 * static_cast<double>(1) / files;
		    
			loadPercent = percent;	
		    
		    receiveFile(socket,folder);
		    
		   
		    
		    std::vector<std::string> filename;
		    for(int a=0;a<files;a++)
		    {
				percent = 100 * static_cast<double>(a + 1) / files;
		    	
		    	
				loadPercent = percent;	
		    
				filename.push_back(receiveFile(socket,folder));

			}
			
			if(percent==100)
			{
				loadPercent=200;
			}
			
			map.folder = folder;
		    
		    
		    if(!map.loadMap(filename[0]))
		    {
		    	loadPercent=-1;
			}
		    
		    
			}
			
			system("cls");

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


				packet << allLoaded;
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
	            
	            
	            
  
	            
	            
	            //send awareness of other clients.
	            
	            
	            packet << clients.size(); 
	            
	            for(int a=0;a<clients.size();a++)
	            {
	            	packet << clients[a].color;
	            	packet << clients[a].loadedLevel;
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
							packet << blupi[a].keyinput;
						}
                    }
 	            } 
	            
	            
	        	
	            
				udpsocket.send(packet, hostip, hostport);
               
                
	        }
	
		}
































		bool getData() 
		{
		   
			if (!hostknown)
			{
				if(hostname!="")
				{
					hostip = IpAddress(hostname);
					
					
					
					if(hostip != IpAddress::None)
					{
					
			            char pc[MAX_COMPUTERNAME_LENGTH + 1];
					    DWORD size = sizeof(pc) / sizeof(pc[0]);
					
					    if (GetComputerName(pc, &size))
						{
							std::string str(pc);
							pcname = str;
						}
						
						
						
						if(pcname==hostname)
						{
				            // Try to bind to host port
				            if (udpsocket.bind(hostport) != Socket::Done)
				            {
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
						    // Client mode - bind to any available port
				            isHost = false;
				            if (udpsocket.bind(Socket::AnyPort) != Socket::Done)
				            {
				                return false;
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
	        	    	return false;
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
								packet >> blupi[a].keyinput;
								
		                    }
		                }
		                
	
		                
		                
		            } 
		            else 
		            {
		
		                bool known = false;
						int ID=-1;
		                for(int a = 0; a < clients.size(); a++) 
		                {
		                    if(clients[a].ip == ip) 
		                    {
		                        known = true;
		                        ID=a;
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
		                    
							std::cout << "\nClient "<< clients.size() << " Joined!";
			
		                }
		                else
		                {
		                	clients[ID].color = color;
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
	        	    	return false;
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
		        	
		        	
	        		packet >> allLoaded;
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
		            
		            
		            
		            int clientsize;
		            packet >> clientsize;
		            
		            for(int a=0;a<clientsize;a++)
		            {
		            	std::string color;
		            	bool loaded;
		            	packet >> color;
		            	packet >> loaded;
		            	
						if(clientsize > clients.size())
						{
							Client newc;
		            		newc.color=color;
		            		newc.loadedLevel=loaded;
		            		clients.push_back(newc);
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
		    return true;
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		

} network;
