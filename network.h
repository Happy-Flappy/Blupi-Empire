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
