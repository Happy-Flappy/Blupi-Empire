// Written in SFML 2.6.0

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Network.hpp>
using namespace sf;

Vector2f MPosition;
std::vector <std::string> buttons;
std::vector <IntRect> iconrect;
int liveitem=0;

struct Layer
{
	int ID=0;
	std::string type="none";
	int layer=0;	
	
	
};

std::vector<Layer> layers; 
Layer toplayer;


void getTopHoveredLayer();



Sound sound[16];

bool isHost=false;

bool playing;








int ME=0;
std::string UserColor = "none";
IpAddress selfIP;

struct Player
{
	bool participating=false;
	bool human=false;
	bool loadedLevel=false;
	bool known=false;
	IpAddress ip;
	unsigned short port;
	std::string color="none";
	std::string name;
	int selected = -1;
	
}player[4];


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







#include "AI.h"
AI ai[4];

#include "network.h"
#include <thread>
#include "SetupScreen.h"


using namespace sf;








void getTopHoveredLayer()
{
	
	int topmost=-1;
	int topmostID = 0;
	std::string toptype="none";
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
					if(blupi[layers[a].ID].color==UserColor)
					{
					
						topmost = layers[a].layer;
						topmostID = layers[a].ID;
						toptype="blupi";
					}
				}
			}
		}
		if(layers[a].type=="element")
		{
			if(element[layers[a].ID].sprite.getGlobalBounds().contains(MPosition))
			{
				if(layers[a].layer > topmost)
				{
					if(element[layers[a].ID].color==UserColor || element[layers[a].ID].color == "any")
					{
					
						topmost = layers[a].layer;
						topmostID = layers[a].ID;
						toptype = "element";
					}
				}
			}
		}
		
	
	}
	
	
	
	
	toplayer.ID = topmostID;
	toplayer.type = toptype;
	toplayer.layer = topmost;
	

}










































int main()
{

	//init self as a player
	player[0].human = true;
	player[0].ip = IpAddress::None;
	player[0].known=true;
	player[0].participating=true;
	player[0].port = network.udpsocket.getLocalPort();
	player[0].selected = 0;
	player[0].color = "yellow";
	


	//initialize first names until player chooses otherwise.
	
	
	player[0].name = "Player 1";
	player[1].name = "Player 2";
	player[2].name = "Player 3";
	player[3].name = "Player 4";
	
	
	
	
	
	
	
	float parallax;
	

	
	Time timesincelastupdate = Time::Zero;
	Time timeperframe = seconds(1.f/60.f);
	Clock clock;
	
	
	SetupScreen setup;
	
	setup.loop();
	
	if(setup.quitAll)
		return 0;



	//,Style::Fullscreen
	RenderWindow window(VideoMode(960+100,540+100),"",Style::Fullscreen);
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
				if(view.getCenter().x > (view.getSize().x/2)) 
				{ 
					map.viewvelo=-6; 
					parallax-=map.parallaxspeed; 
				} 
			} 
			
			if(Keyboard::isKeyPressed(Keyboard::Right)) 
			{
			
				if(view.getCenter().x < map.tground.getSize().x - (view.getSize().x/2)-1) 
				{ 
					map.viewvelo=6; 
					parallax+=map.parallaxspeed; 
				} 
			} 
			
			if(Mouse::getPosition(window).x < window.getSize().x/32 && Mouse::getPosition(window).x >= 0) 
			{
				if(view.getCenter().x > (view.getSize().x/2)) 
				{ 
					map.viewvelo=-6; 
					parallax-=map.parallaxspeed; 
				} 
			} 
			
			if(Mouse::getPosition(window).x > window.getSize().x - (window.getSize().x/32) && Mouse::getPosition(window).x <= window.getSize().x) 
			{ 
				if(view.getCenter().x < map.tground.getSize().x - (view.getSize().x/2)) 
				{ 
					map.viewvelo=6;
					parallax+=map.parallaxspeed; 
				} 
			}
			
			
			
			
			view.move(map.viewvelo,0);
			map.viewvelo=0;
			
			
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
			
		
			if(player[ME].selected==-1)
			{
				for(int a=0;a<blupi.size();a++)
				{
					if(blupi[a].color==UserColor)
					{
						player[ME].selected = a;
						break;
					}
				}
				if(player[ME].selected==-1)
				{
					//no blupis of that color exist. This could mean that the player has lost the game because all of his blupis have died.
				}
			}
			
			
			for(auto& b : blupi)
				b.update(map.iground);
		
		
		
			
			
			
			for(int a=0;a < element.size();a++)
			{
				element[a].ID=a;
				element[a].getNumberOfOverlap(element,element[a]);
				element[a].update(map.iground,blupi[player[ME].selected].locomotion);
			
			}
			
			map.floater.move(0,-1);

			water.update(map.iground);
			

			
			
					
			
		
			
			network.getData();
			network.sendData();
			
			
			
		
			
			
			cursor.update(window);
		
			for(int a=0;a<4;a++)
			{
				if(playing && !player[a].human)
					ai[a].update();
				
			}
		
		
		
		}
		
		//render
		
		layers.clear();
		
		window.setView(view);
		
		window.clear(Color::Cyan);
		

		
		
			
			
		
	
	
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
		
		
		cursor.draw(window);
		
		
		
		window.display();
	}
	
}