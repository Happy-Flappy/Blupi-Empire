#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Network.hpp>
using namespace sf;

Vector2f MPosition;
int selected=0;
std::vector <std::string> buttons;
std::vector <IntRect> iconrect;
int liveitem=0;

struct Layer
{
	int ID;
	std::string type;
	int layer;	
	
	
};

std::vector<Layer> layers; 
Layer toplayer;


void getTopHoveredLayer();



Sound sound[16];

bool isHost=false;

std::string UserColor="none";
bool playing;






#include <cmath>
#include <fstream> 
#include <sstream>
#include <iostream> 
#include "getgroundangle.h"
#include "gravity.h"
#include "waterphysics.h"
#include "textures.h"
#include "shift.h"
#include "element.h"
#include "blupi.h"
#include "cursor.h"
#include "taskbar.h"
#include "map.h"

#include "network.h"
#include <thread>

using namespace sf;








void getTopHoveredLayer()
{
	
	int topmost=-1;
	int topmostID = -1;
	std::string toptype;
	for(int a=0;a<layers.size();a++)
	{
		if(layers[a].type=="blupi")
		{
			FloatRect bounds = blupi[layers[a].ID].sprite.getGlobalBounds();
			
			bounds.left +=20;
			bounds.width -=40;
			bounds.top +=20;
			bounds.height -=20;
			
			if(bounds.contains(MPosition))
			{
				if(layers[a].layer > topmost)
				{
					topmost = layers[a].layer;
					topmostID = layers[a].ID;
					toptype="blupi";
				}
			}
		}
		if(layers[a].type=="element")
		{
			if(element[layers[a].ID].sprite.getGlobalBounds().contains(MPosition))
			{
				if(layers[a].layer > topmost)
				{
					topmost = layers[a].layer;
					topmostID = layers[a].ID;
					toptype = "element";
				}
			}
		}
		
	
	}
	
	
	
	
	
	
	if(topmostID!=-1)
	{
		toplayer.ID = topmostID;
		toplayer.type = toptype;
		toplayer.layer = topmost;
	}
	else
	{
		toplayer.ID=0;
		toplayer.layer=0;
		toplayer.type="none";
	}
}










































int main()
{


	
	
	float parallax;
	

	
	Time timesincelastupdate = Time::Zero;
	Time timeperframe = seconds(1.f/60.f);
	Clock clock;
	
	bool settingUp = true;
	
	
	while(settingUp)
	{

		std::cout << "\nHostPcName:";
		std::cin >> network.hostname;
		std::cout << "\nUserColor:";
		std::cin >> UserColor;
		
			
			
		if(!network.getData())
		{
			if(!network.hostknown)
			{
				std::cout << "\nFAILED: Could not find Host Identity.";
				continue;
			}
			else
			{
				//normal behavior. There are checks to make sure no attempts are made to load data when a socket fails to receive a packet because the packet was never sent.These checks return false if no data was sent to the clients to be received.
			}
		}
		network.sendData();
		
		if(isHost)
		{
		
			network.allLoaded=true;
			for(int a=0;a<network.clients.size();a++)
			{
				if(!network.clients[a].loadedLevel)
				{
					network.allLoaded=false;
				}
			}
		}		
		
		
		
		if(isHost && network.hostknown && map.name=="")
		{
			std::cout << "\nLevelScriptFile:";
			std::cin >> map.name;
			
			if(!map.loadMap(map.name))
			{
				map.name="";
				std::cout << "\n FAILED! Level could not be loaded sucessfully.";
				
				network.allLoaded=false;
				settingUp=true;
				continue;
			}
			else
			{
				std::cout << "\nPress Enter When You Are Ready To Play";
				std::string s;
				std::cin >> s;
				playing=true;
			}
			
		}
		
		
		if(network.allLoaded)
		{
			settingUp=false;
		}
	}
	




	//,Style::Fullscreen
	RenderWindow window(VideoMode(960+100,540+100),"");
	View view;
	view.reset(FloatRect(0,0,960+100,540+100));
	window.setMouseCursorVisible(false);

	
	
	
	while(window.isOpen())
	{
	
		MPosition = window.mapPixelToCoords(Mouse::getPosition(window));
	
		timesincelastupdate += clock.restart();
		
		while(timesincelastupdate > timeperframe)
		{
		
		
			timesincelastupdate -= timeperframe;
		
			Event e;
			while(window.pollEvent(e))
			{
				if(e.type==Event::Closed)
					window.close();
			}
		
			//game stuff
			
			
			
			
			if(Keyboard::isKeyPressed(Keyboard::Left))
			{
				if(isHost)
				{
					playing=true;
					if(map.name=="")
						map.loadMap("level0/level0.txt");
				}
			}
			
			

			
			
			if(network.allLoaded)
			{
			
				if(Keyboard::isKeyPressed(Keyboard::Left)) 
				{
					if(view.getCenter().x > (view.getSize().x/2)) 
					{ 
						view.move(-map.viewspeed,0); 
						parallax-=map.parallaxspeed; 
					} 
				} 
				
				if(Keyboard::isKeyPressed(Keyboard::Right)) 
				{
				
					if(view.getCenter().x < map.tground.getSize().x - (view.getSize().x/2)-1) 
					{ 
						view.move(map.viewspeed,0); 
						parallax+=map.parallaxspeed; 
					} 
				} 
				
				if(Mouse::getPosition(window).x < window.getSize().x/32 && Mouse::getPosition(window).x >= 0) 
				{
					if(view.getCenter().x > (view.getSize().x/2)) 
					{ 
						view.move(-map.viewspeed,0); 
						parallax-=map.parallaxspeed; 
					} 
				} 
				
				if(Mouse::getPosition(window).x > window.getSize().x - (window.getSize().x/32) && Mouse::getPosition(window).x <= window.getSize().x) 
				{ 
					if(view.getCenter().x < map.tground.getSize().x - (view.getSize().x/2)) 
					{ 
						view.move(map.viewspeed,0); 
						parallax+=map.parallaxspeed; 
					} 
				}
				
				
				
				
				
				
				
				
				
				if(view.getCenter().x < view.getSize().x/2)
				{
					view.setCenter(view.getSize().x/2,view.getCenter().y);
					parallax += map.parallaxspeed;
				}
				
				
				if(view.getCenter().x > map.iground.getSize().x-(view.getSize().x/2)-1)
				{
					view.setCenter(map.iground.getSize().x-(view.getSize().x/2)-1,view.getCenter().y);
					parallax -= map.parallaxspeed;
				}
				
				
				
				
				
				
				
				
				
				map.background.setPosition(view.getCenter().x-(view.getSize().x/2)-int(parallax),0);
				
				
				
				getTopHoveredLayer();
				
				
				for(auto& b : blupi)
					b.update(map.iground);
			
				
				for(int a=0;a < element.size();a++)
				{
					element[a].ID=a;
					element[a].update(map.iground,blupi[selected].locomotion);
				}
				
				map.floater.move(0,-1);
	
				water.update(map.iground);
				

				
				
					
			}
			
			
			
			network.getData();
			network.sendData();
			
			
			
			
		
			if(UserColor=="none")
			{
				if(Keyboard::isKeyPressed(Keyboard::Y))
					UserColor = "yellow";
				if(Keyboard::isKeyPressed(Keyboard::B))
					UserColor = "blue";
					
			}
			
		
			
			
			cursor.update(window);
		
		}
		
		//render
		layers.clear();
		
		window.setView(view);
		
		window.clear(Color::Cyan);
		
		if(network.allLoaded)
		{
		
		
		
		
			
			
			
		
		
			if(map.background.getTextureRect().width > 0)	
				window.draw(map.background);
			
			
			
			if(map.floater.getTextureRect().width > 0)
			{
				
				if(map.floater.getPosition().y + map.floater.getTextureRect().height + 5 < 0)
				{
					map.floater.setPosition(rand() % map.iground.getSize().x,map.iground.getSize().y + 50);
				}
				
				
				
				
				window.draw(map.floater);
			}
			
			for(int a=0;a<element.size();a++){
				Layer newlayer;
				newlayer.ID = a;
				newlayer.layer = layers.size(); 
				newlayer.type = "element";
				if(element[a].active)
				{
					layers.push_back(newlayer);
					element[a].draw(window);
				}
			}
	
			
			
			water.draw(window);
			
			
			window.draw(map.ground);
	
	
	
			for(int a=0;a<blupi.size();a++)
			{
				Layer newlayer;
				newlayer.ID = a;
				newlayer.layer = layers.size(); 
				newlayer.type = "blupi";
				layers.push_back(newlayer);
				
				blupi[a].draw(window);
			}
			
				
			if(map.foreground.getTextureRect().width > 0)	
				window.draw(map.foreground);
			
			if(map.overlay.getFillColor() != Color(0,0,0,0))
				window.draw(map.overlay);
			
					
			taskbar.update(window,map.iground);
			
			
		}
		
		cursor.draw(window);
		
		
		
		window.display();
	}
	
}