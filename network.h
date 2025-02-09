#include <chrono>


class Network {

    public:
        UdpSocket udpsocket;
        IpAddress hostip = IpAddress("MAX-PC");
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
			    if (hostip != IpAddress::None)
			    {
			        // Get the local machine's IP address
			        IpAddress localIp = IpAddress::getLocalAddress();
			        bool sameComputer = (localIp == hostip);
			
			        if (sameComputer)
			        {
			            std::cout << "Running in host mode (same computer)" << std::endl;
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
		        	
		            packet >> playing;
		                
		                
		                
		            
		            if(playing) 
		            {
		            
		                std::string level;
		                packet >> level;
		                
						
						
						
						if(map.name != level) 
		                {
		                    map.loadMap(level);
		                }
		
		                int size;
		                packet >> size;
		                blupi.resize(size);

			            for (auto& b : blupi) {
			                
							
							
							packet >> b.color;
			                packet >> b.now.x;
			                packet >> b.now.y;
			                packet >> b.velocity.x;
			                packet >> b.velocity.y;
			                packet >> b.state;
			                
			                
			                
			            }

		            } 
		        }
		    }
		    
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		

} network;
