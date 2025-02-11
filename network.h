#include <chrono>
#include <windows.h>

class Network {

    public:
        UdpSocket udpsocket;
        IpAddress hostip;
        std::string pcname;
        std::string hostname = "MAX-PC";
        unsigned short hostport = 12345;
        bool hostknown=false;
		long long lastTimestamp=0;
	

        struct Client {
            IpAddress ip;
            unsigned short port;
            std::string color;

        };

        std::vector<Client> clients;


        Network() {

        }


















		void sendData() 
		{
	        if(isHost) 
	        {
	            Packet packet;
	            
				auto now = std::chrono::system_clock::now();
  		        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        		packet << timestamp;

				
				packet << playing;
	            
	            if(playing) 
	            {
	            	
		            packet << map.name;
	        	
	                packet << blupi.size();
	                
					
		            for (const auto& b : blupi) {
		                packet << b.color;
		                packet << b.now.x;
		                packet << b.now.y;
		                packet << b.velocity.x;
		                packet << b.velocity.y;
		                packet << b.state;
		                packet << b.rotation;
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
                
				
				auto now = std::chrono::system_clock::now();
  		        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        		packet << timestamp;
	            
				
				
				packet << UserColor;


	            if(playing) 
	            {

                    for(int a = 0; a < blupi.size(); a++) 
                    {
                        if(blupi[a].color == UserColor) 
                        {
                            packet << blupi[a].action;
                            packet << blupi[a].locomotion;
                            packet << blupi[a].destination;
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
		            
		            
		            
				            
		            long long timestamp;
		            packet >> timestamp;
		            
		            
		            
		            if(lastTimestamp > timestamp)
		            {
						return;
		        	}
		            
		            lastTimestamp = timestamp;
	
	                std::string color;
	                packet >> color;
	
		            if(playing) 
		            {
		                for(int a = 0; a < blupi.size(); a++) 
		                {
		                    if(blupi[a].color == color) 
		                    {
		                    	
		                        
		                        packet >> blupi[a].action;
		                        packet >> blupi[a].locomotion;
		                        packet >> blupi[a].destination;
								
								
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
		        	
		        	
		        	
		        	
		        	long long timestamp;
		            packet >> timestamp;
		            
		            
		            
		            if(lastTimestamp > timestamp)
		            {
		            	return;
		            }
		            lastTimestamp = timestamp;
		            
		        	
		        	
		        	
		        	
		        	
	        	
		            packet >> playing;
		                
		                
		                
		            
		            if(playing) 
		            {
		            
		                std::string level;
		                packet >> level;
		                
						
						
						
						if(map.name != level) 
		                {
		                	if(level!="")
		                	{
								map.loadMap(level);
		                	}
		                	
						}
		
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
			                
			                
			            }

		            }
				
		        }
		    }
		    
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		

} network;
