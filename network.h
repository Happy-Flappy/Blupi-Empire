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

        



        Network() {

        }



		
		
		
		
		
		
		
//		void sendFile(sf::TcpSocket& socket, const std::string& filePath) 
//		{
//		    sf::Packet packet;
//		    std::ifstream inFile(map.folder + filePath, std::ios::binary);
//		    std::vector<char> fileData((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
//		
//		    
//		    // Send the file path
//		    
//		    
//		    packet << filePath;
//		    socket.send(packet);
//		
//		    // Send the file data
//		    packet.clear();
//		    packet.append(fileData.data(), fileData.size());
//		    socket.send(packet);
//		    
//		
//		}
//		
//		
//		
//		
//		std::string receiveFile(sf::TcpSocket& socket, const std::string& folder) {
//		    sf::Packet packet;
//		    std::string filedir;
//		    std::vector<char> fileData;
//		
//		    // Receive the file name
//		    socket.receive(packet);
//		    packet >> filedir;
//		
//		    // Receive the file data
//		    packet.clear();
//		    socket.receive(packet);
//		    fileData.resize(packet.getDataSize());
//		    memcpy(fileData.data(), packet.getData(), packet.getDataSize());
//
//
//
//
//			
//			size_t pos = filedir.find_last_of('/');
//			
//			std::string path = filedir.substr(0,pos+1);
//			
//			std::string fileName =  filedir.substr(pos+1);
//
//
//
//			std::filesystem::create_directories(folder + path);
//
//						
//				
//
//		    std::ofstream outFile(folder + path + fileName, std::ios::binary);
//		    outFile.write(fileData.data(),fileData.size());
//		    outFile.close();
//		    
//		    
//		    return path + fileName;
//		}
//		
//		
//		
//		
//		
//		void sendLevel(const sf::IpAddress& clientIp, unsigned short clientPort)
//		{
//			
//		    sf::TcpSocket socket;
//			socket.connect(clientIp,clientPort);
//			
//			Packet packet;
//			packet << map.filepaths.size();//that number includes the script file since filepath size is more than literal size by 1.
//			socket.send(packet);
//			
//			system("cls");
//			std::cout << "Sending Level Data to clients> ";
//			
//			std::cout << ".";
//			sendFile(socket,map.name);//send script file
//			
//			for(int a=0;a<map.filepaths.size();a++)
//			{
//				std::cout << ".";
//				sendFile(socket,map.filepaths[a]);
//			}
//			
//			
//			system("cls");
//		}
//		
//		
//		
//		
//		
//		void getLevel(unsigned short clientPort)
//		{
//
//			if(map.folder!="ClientData/")
//			{
//			
//			//Empty if existing folder
//			std::string folder = "ClientData";
//			
//			if (std::filesystem::exists(folder)) 
//			{
//		        std::filesystem::remove_all(folder);
//			}
//			else
//				std::filesystem::create_directory(folder);
//		    
//		    folder = "ClientData/";
//		    
//		    
//		    
//
//
//		    sf::TcpListener listener;
//		    if (listener.listen(clientPort) != sf::Socket::Done) {
//		        std::cout << "Error listening on port " << clientPort << std::endl;
//		        return;
//		    }
//		
//		    sf::TcpSocket socket;
//		    if (listener.accept(socket) != sf::Socket::Done) {
//		        std::cout << "Error accepting connection on port " << clientPort << std::endl;
//		        return;
//		    }
//		    
//
//
//		    
//		    
//		    
//		    Packet packet;
//		    socket.receive(packet);
//		    
//		    
//		    
//		    
//		    int files;
//		    packet >> files;
//		    packet.clear();
//		    
//		    
//		    system("cls");
//		    
//		    
//		    int percent;
//		    
//			percent = 100 * static_cast<double>(1) / files;
//		    
//			loadPercent = percent;	
//		    
//		    receiveFile(socket,folder);
//		    
//		   
//		    
//		    std::vector<std::string> filename;
//		    for(int a=0;a<files;a++)
//		    {
//				percent = 100 * static_cast<double>(a + 1) / files;
//		    	
//		    	
//				loadPercent = percent;	
//		    
//				filename.push_back(receiveFile(socket,folder));
//
//			}
//			
//			if(percent==100)
//			{
//				loadPercent=200;
//			}
//			
//			map.folder = folder;
//		    
//		    
//		    if(!map.loadMap(filename[0]))
//		    {
//		    	loadPercent=-1;
//			}
//		    
//		    
//			}
//			
//			system("cls");
//
//		}
//		
//		













		void sendData() 
		{
			
			
			
	        if(isHost) 
	        {
	            Packet packet;
	            

				
				
				packet << map.name; 
    	
				packet << allLoaded;
				packet << playing;
	            
	            if(playing) 
	            {
	            	
	        	
	                
					
		            for (const auto& b : blupi) {
		                packet << b.color;
		                packet << b.now.x;
		                packet << b.now.y;
		                packet << b.velocity.x;
		                packet << b.velocity.y;
		                packet << b.state;
		                packet << b.rotation;
		                packet << b.locomotion;	
		                
		                packet << b.alive;
						packet << b.haven;
						sf::IntRect r = b.carrying.getTextureRect();
			            packet << r.left << r.top << r.width << r.height;
			                
			                
		                packet << b.itemref;
		                packet << b.running;
		               		
							
		            }
		            
		            
	            
					for(int a=0;a<element.size();a++)
					{
						packet << element[a].exists;
						packet << element[a].burning;
						packet << element[a].active;
						packet << element[a].blupiIndex;
						packet << element[a].boomID;
						for(int b=0;b<10;b++)
						{
							packet << element[a].boolean[b];
						}
						packet << element[a].now.x;
						packet << element[a].now.y;
						packet << element[a].type;
						packet << element[a].color;
						
					}		            
		            
		            
		            
	            }
	            
	            
	            
  
	            
	            
	        	for(int a=0;a<4;a++)
	            {
	            	if(player[a].ip != IpAddress::None)
	            	{
	            		player[a].human=true;
	            		player[a].participating=true;
					}
				}
	            
	            
	            
	            
	            
	            //send awareness of other clients.
	            
	            
	            for(int a=0;a<4;a++)
	            {
	            	packet << player[a].name;
					packet << player[a].color;
	            	packet << player[a].loadedLevel;
	            	packet << player[a].human;
		            packet << player[a].participating;
		            
				}
	            
	            
	            
	            
  				for(int a=0;a<4;a++)
		        {
		            udpsocket.send(packet, player[a].ip, player[a].port);
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
							packet << blupi[a].running;
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
						
						selfIP = IpAddress::getPublicAddress();	
						
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
						for(int a = 0; a < 4; a++) 
		                {
		                    if(player[a].ip == ip) 
		                    {
		                    	player[a].loadedLevel=false;
		                    	break;
		                    }
		                }
					}
					if(level!="")
					{
						for(int a = 0; a < 4; a++) 
		                {
		                    if(player[a].ip == ip) 
		                    {
		                    	player[a].loadedLevel=true;
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
		                for(int a = 0; a < 4; a++) 
		                {
		                    if(player[a].ip == ip) 
		                    {
		                    	if(player[a].known)
		                    	{
									known = true;
			                       	ID=a;
			                       	
			                       	if(player[a].ip==selfIP)
			                       		ME=a;	
									
			                       	
			                       	break;
			                    }
		                    }
		                }
		
		
		
						if(!known)
						{
							for(int a=0;a<4;a++)
							{
								if(player[a].ip==IpAddress::None)
								{
									ID=a;
									break;
								}
							}
						}
		
		
		
		                if(!known) 
		                {
		                	player[ID].participating = true;
		                	player[ID].human=true;
		                	player[ID].ip = ip;
		                	player[ID].port = port;
		                	player[ID].color = color;
		                	player[ID].known=true;
		                }
		                else
		                {
		                	player[ID].color = color;
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
		        	
		        	
		        	
					std::string mapname;
					packet >> mapname;
		        	
		        	if(mapname!="" && map.name=="")
		        	{
		        		map.loadMap(mapname);
					}
					
	        		packet >> allLoaded;
		            packet >> playing;
		                
		                
		                
		            
		            if(playing) 
		            {
		            
		                
						
						
						
						
		
		            
			            for (auto& b : blupi) {
			                
							
							
							packet >> b.color;
			                packet >> b.now.x;
			                packet >> b.now.y;
			                packet >> b.velocity.x;
			                packet >> b.velocity.y;
			                packet >> b.state;
				            packet >> b.rotation;
				            packet >> b.locomotion;
			                
			                packet >> b.alive;
							packet >> b.haven;
							int left,top,width,height;
			                packet >> left >> top >> width >> height;
			                
			                
			                packet >> b.itemref;
			                
			                if(sf::IntRect(left,top,width,height) != b.carrying.getTextureRect())
			                {
			                	b.carrying = element[b.itemref].sprite;
							}
							packet >> b.running;
							
							
			            }

						for(int a=0;a<element.size();a++)
						{
							packet >> element[a].exists;
							packet >> element[a].burning;
							packet >> element[a].active;
							packet >> element[a].blupiIndex;
							packet >> element[a].boomID;
							for(int b=0;b<10;b++)
							{
								packet >> element[a].boolean[b];
							}
							packet >> element[a].now.x;
							packet >> element[a].now.y;
							packet >> element[a].type;
							packet >> element[a].color;
							
						}


		            }
		            
		            
		            
		            
		            for(int a=0;a<4;a++) // copy list of clients from host to this client
		            {
		            	std::string color;
		            	bool loaded;
		            	bool human;
		            	bool participating;
		            	std::string name;
		            	packet >> name;
		            	packet >> color;
		            	packet >> loaded;
		            	packet >> human;
		            	packet >> participating;
		            	
		            	
		            	player[a].name = name;
		            	player[a].color = color;
		            	player[a].loadedLevel = loaded;
		            	player[a].human = human;
		            	player[a].participating = participating;
		            	
		            	
		            	
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
