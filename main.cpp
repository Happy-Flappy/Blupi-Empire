// Written in SFML 2.6.0

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Network.hpp>
#include "wav.h"
using namespace sf;

Vector2f MPosition;
std::vector <std::string> buttons;
std::vector <IntRect> iconrect;
int liveitem=0;



struct Boom
{
	int boomSpot=0;
	bool booming=false;
};


std::vector <Boom> boom;


struct Layer
{
	int ID=0;
	std::string type="none";
	int layer=0;	
	
	
};

Layer toplayer;
Layer topElement;
Layer topBlupi;


void getTopHoveredLayer();



Sound sound[16];


int findChannel()
{
	for(int a=0;a<16;a++)
	{
		if(sound[a].getStatus()!=Sound::Status::Playing)
		{
			return a;
		}
	}
	return -1;
}




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


int CreateElement()
{
	int index=-1;
	for(int a=0;a<element.size();a++)
	{
		if(!element[a].exists)
		{
			index=a;
			break;
		}
	}
	
	
	if(index!=-1)
	{
		element[index] = Element();
	}
	else
	{
		element.push_back(Element());
		index = element.size()-1;
	}
	element[index].ID = index;
	
	return index;
	
}





#include "blupi.h"






int CreateBlupi()
{
	int index=-1;
	for(int a=0;a<blupi.size();a++)
	{
		if(!blupi[a].alive)
		{
			index=a;
			break;
		}
	}
	
	
	if(index!=-1)
	{
		blupi[index] = Blupi();
	}
	else
	{
		blupi.push_back(Blupi());
		index = blupi.size()-1;
	}
	blupi[index].ID = index;
	
	return index;
	
}





struct BlupiByPos
{
	int ID;
	int position;	
};
std::vector<BlupiByPos> blupiByPos;
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
    // Reset both top layers
    topBlupi.ID = -1;
    topBlupi.type = "none";
    topElement.ID = -1;
    topElement.type = "none";

    // 1. Find topmost blupi (last in vector = highest rendered)
    for (int a = blupi.size() - 1; a >= 0; a--)
    {
        if (!blupi[a].alive || blupi[a].color != UserColor) 
            continue;

        // Adjusted bounds with 20px padding
        FloatRect bounds = blupi[a].sprite.getGlobalBounds();
        bounds.left += 20;
        bounds.width -= 40;
        bounds.top += 20;
        bounds.height -= 20;

        if (bounds.contains(MPosition))
        {
            topBlupi.ID = blupi[a].ID;
            topBlupi.type = "blupi";
            
            break; // Stop at topmost blupi
        }
    }

    // 2. Find topmost element (last in vector = highest rendered)
    for (int a = element.size() - 1; a >= 0; a--)
    {
        if (!element[a].active || !element[a].exists)continue;// || 
  //          (element[a].color != UserColor && element[a].color != "any"))
  //          continue;

        // Adjusted bounds with 20px padding
        FloatRect bounds = element[a].sprite.getGlobalBounds();
        bounds.left += 20;
        bounds.width -= 40;
        bounds.top += 20;
        bounds.height -= 20;

        if (bounds.contains(MPosition))
        {
            topElement.ID = element[a].ID;
            topElement.type = "element";
            break; // Stop at topmost element
        }
    }

    // 3. Determine overall top layer (blupi > element in rendering order)
    if (topBlupi.ID != -1)
        toplayer = topBlupi;
    else
        toplayer = topElement;
        
         
}






























struct GridComparator {
    int gridX;  // The grid coordinate we're searching for
    GridComparator(int x) : gridX(x) {}
    
    bool operator()(const Element& el) const {
        return static_cast<int>(el.now.x) / 32 == gridX;
    }
};









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
			
			
			
			
		
			if(player[ME].selected==-1)
			{
				for(int a=0;a<blupi.size();a++)
				{
					if(blupi[a].color==UserColor && blupi[a].alive)
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
			
			
			for(int a=0;a<blupi.size();a++)
			{
				if(!blupi[a].alive)
					continue;
				blupi[a].ID=a;
				blupi[a].update(map.iground);
			}
			
			
			blupiByPos.resize(blupi.size());
			
			
			for(int a=0;a<blupi.size();a++)
			{
				blupiByPos[a].ID = a;
				blupiByPos[a].position = blupi[a].now.x;
			}
		
			
			std::sort(blupiByPos.begin(),blupiByPos.end(),[](BlupiByPos &a,BlupiByPos &b){
				
				return a.position < b.position;
				
			});
		
			
			for(int a=0;a < element.size();a++)
			{
				
				
		
			
					
				if(!element[a].exists)
					continue;
				element[a].ID=a;
				element[a].update(map.iground,blupi[player[ME].selected].locomotion);
				element[a].displayNumber=0;
			
			
				
			
			
			}
				
			
			
			
			
			
			
			
			
			
			
			
			std::map<std::pair<std::string, int>, std::vector<int>> gridGroups;
			
			
			
			// Build grid groups
			for (int a = 0; a < element.size(); a++) {
			    if (!element[a].exists || !element[a].active) continue;
			    
			    int gridX = static_cast<int>(element[a].now.x) / 32;
			    auto key = std::make_pair(element[a].type, gridX);
			    gridGroups[key].push_back(a);
			}
			
			// Process groups
			for (auto& group : gridGroups) {
			    if (group.second.size() <= 1) continue;
			
			    // Find leftmost element
			    auto leftIt = std::min_element(group.second.begin(), group.second.end(),
			        [&](int a, int b) { return element[a].now.x < element[b].now.x; });
			    
			    // Find rightmost element
			    auto rightIt = std::max_element(group.second.begin(), group.second.end(),
			        [&](int a, int b) { return element[a].now.x < element[b].now.x; });
			
			    float diff = element[*rightIt].now.x - element[*leftIt].now.x;
			    element[*rightIt].displayNumber = group.second.size();
			    element[*rightIt].textX = element[*rightIt].now.x - diff / 2;
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
		
		
		MPosition = window.mapPixelToCoords(Mouse::getPosition(window));
		getTopHoveredLayer();
		
		//render
		
		
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
			
			if(!element[a].exists)
				continue;
			

			if(element[a].active)
			{
				element[a].draw(window);
			}
		}




		
		
		water.draw(window);
		

		window.draw(map.ground);		



		for(int a=0;a<blupi.size();a++)
		{
			if(!blupi[a].alive)
				continue;	
			

			
			blupi[a].draw(window);
		}
		
		
		
		
		
		//explosions update

		for(int a=0;a<element.size();a++)
		{
			
			
			
			
			if(!element[a].exists)
				continue;
			
			
			
//			if (element[a].active && element[a].exists) {
//		        RectangleShape rect;
//		        sf::Vector2f size = sf::Vector2f(element[a].sprite.getTextureRect().width*element[a].sprite.getScale().x,element[a].sprite.getTextureRect().height*element[a].sprite.getScale().y);
//		        
//		        rect.setSize(size);
//		        rect.setPosition(element[a].sprite.getPosition().x - (size.x/2),element[a].sprite.getPosition().y - (size.y/2));
//		        rect.setFillColor(Color(0, 0, 0, 0));
//		        rect.setOutlineColor(Color::Red);
//		        rect.setOutlineThickness(1);
//		        window.draw(rect);
//		    }
			
			
			
			
			for(int b=0;b<boom.size();b++)
			{
				if(element[a].now.x > boom[b].boomSpot - 500 && element[a].now.x < boom[b].boomSpot + 500)
				{
					if(!(element[a].type=="bomb" && element[a].boolean[0]))
						element[a].exists = false;
				}
			}
			
			
			
		}

		for(int a=0;a<blupi.size();a++)
		{
			
			if(!blupi[a].alive)
				continue;
			
			for(int b=0;b<boom.size();b++)
			{
				if(blupi[a].now.x > boom[b].boomSpot - 500 && blupi[a].now.x < boom[b].boomSpot + 500)
				{
					blupi[a].alive = false;
				}
			}
			
		}		
			
		boom.clear();
			
			
			
			
			
			
		if(map.foreground.getTextureRect().width > 0)	
			window.draw(map.foreground);
		
		if(map.overlay.getFillColor() != Color(0,0,0,0))
			window.draw(map.overlay);
		
				
		taskbar.update(window,map.iground);
		
		
		cursor.draw(window);
		
		
		
		window.display();
		
		
		
		
		
		
		//wav.listen.setPosition(view.getCenter().x,0,0);
		
	}
	
}