// Written in SFML 2.6.0

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Network.hpp>





class Player
{
	public:
	
	std::string name = "";
	std::string color = "yellow";
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	unsigned short port = 4000;
	int selected = -1;
		
};
Player self;



#include "wav.h"
#include "input.h"
using namespace sf;

Vector2f MPosition;

class Button
{
	public:
	std::string type;
	sf::IntRect icon;
	int time;
	int energy;
	
	Button(std::string type,sf::IntRect icon,int time,int energy)
	{
		this->type = type;
		this->icon = icon;
		this->time = time;
		this->energy = energy;
	}
	
};

std::vector<Button> buttons;

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




bool isServer = false;



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








#include "network.h"
#include <thread>
#include "cheats.h"


using namespace sf;


int getTopmostElementLayer(int layer)
{
	int topE = -1;
	for (int a = 0; a < element.size(); a++)
    {
    	
        if (!element[a].active || !element[a].exists || element[a].layer != layer)continue;
		
		// Adjusted bounds with 20px padding
        FloatRect bounds = element[a].sprite.getGlobalBounds();
        bounds.left += 20;
        bounds.width -= 40;
        bounds.top += 20;
        bounds.height -= 20;

        if (bounds.contains(MPosition) && MPosition.y < groundEdge[MPosition.x])
        {
        	if(topE < a)
				topE = a;
        }
			
	}
	
	return topE;
}



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
        if (!blupi[a].alive || blupi[a].color != self.color) 
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


	int topE = -1;
    // 2. Find topmost element 
    
	topE = getTopmostElementLayer(5);
	if(topE == -1)
		topE = getTopmostElementLayer(4);
	if(topE == -1)
		topE = getTopmostElementLayer(3);
	if(topE == -1)
		topE = getTopmostElementLayer(2);
	if(topE == -1)
		topE = getTopmostElementLayer(1);
		
	if(topE != -1)	
	{
		topElement.ID = topE;
        topElement.type = "element";	
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





#include <cctype> // For isdigit()

bool findNumberInString(const std::string& str,int &number) {
    std::string currentNumber;
    for (char c : str) {
        if (std::isdigit(c)) {
            currentNumber += c;
        } else {
            if (!currentNumber.empty()) {
                std::cout << "Found number: " << currentNumber << std::endl;
                currentNumber.clear(); // Reset for the next number
            }
        }
    }
    // Check for a number at the end of the string
    if (!currentNumber.empty()) 
	{
	    int n = -1;
		n = std::stoi(currentNumber);	
	    
	    if(n != -1 & n > 0)
	    {
	    	number = n;
	    	return true;
		}
		
    }
    return false;
}





int main()
{

	sf::Uint32 style = sf::Style::Default;
	int width = 960 + 100;
	int height = 540 + 100;
	
	
	std::ifstream settings;
	settings.open("Settings.txt"); 
	
	
	std::string line;
	
	while(getline(settings,line))
	{
		if(line.find("fullscreen") != std::string::npos)
		{
			if(line.find("true") != std::string::npos)
			{
				style = sf::Style::Fullscreen;
			}
		}
		
		if(line.find("width") != std::string::npos)
		{
			if(findNumberInString(line,width))
			{
				width = width + 100;
			}	
		}
		
		if(line.find("height") != std::string::npos)
		{
			if(findNumberInString(line,height))
			{
				height = height + 100;
			}	
		}
		
		
		if(line.find("server") != std::string::npos)
		{
			if(line.find("true")!=std::string::npos)
			{
				isServer = true;
			}
		}	
		
	}
	
	settings.close();


	map.loadMap("level0.txt");

	
	network.init();



	

	
	Time timesincelastupdate = Time::Zero;
	Time timeperframe = seconds(1.f/60.f);
	Clock clock;	
	

		
	if(isServer)
	{
		while(true)
		{
			timesincelastupdate += clock.restart();
			
			while(timesincelastupdate > timeperframe)
			{
				timesincelastupdate -= timeperframe;
			
			
			
				for(int a=0;a<blupi.size();a++)
				{
					if(!blupi[a].alive)
						continue;
					blupi[a].ID=a;
					blupi[a].update(map.iground);
				}			
								
			
				water.update(map.iground);


				for(int a=0;a < element.size();a++)
				{
				
					if(!element[a].exists)
						continue;
					element[a].ID=a;
					element[a].update(map.iground,"walk");
					element[a].displayNumber=0;
				
				}

						
				network.getData();
				network.sendData();
			}
		}
		return 0;
	}
	
	
	//,Style::Fullscreen
	RenderWindow window(VideoMode(width,height),"",style);
	View view;
	view.reset(FloatRect(0,0,width,height));
	window.setMouseCursorVisible(false);

	
	float parallax;
		
	
	while(window.isOpen())
	{
	
	
	
	
	
	
		Input::beginFrame();

		Event e;
		while(window.pollEvent(e))
		{
			if(e.type==Event::Closed)
				window.close();
				
			Input::update(e);
			
			Cheats::update(e);
		}		
		
		
		
		
		MPosition = window.mapPixelToCoords(Input::getPosition());
		
		
		
		timesincelastupdate += clock.restart();
		
		while(timesincelastupdate > timeperframe)
		{
		
		
			timesincelastupdate -= timeperframe;
		

		
			//game stuff
			
			
			
			
			

			
		
			if(Input::Key(Keyboard::Left)) 
			{
				if(view.getCenter().x > (view.getSize().x/2)) 
				{ 
					map.viewvelo=-6; 
					parallax-=map.parallaxspeed; 
				} 
			} 
			
			if(Input::Key(Keyboard::Right)) 
			{
			
				if(view.getCenter().x < map.tground.getSize().x - (view.getSize().x/2)-1) 
				{ 
					map.viewvelo=6; 
					parallax+=map.parallaxspeed; 
				} 
			} 
			
			if(Input::getPosition().x < window.getSize().x/32 && Input::getPosition().x >= 0) 
			{
				if(view.getCenter().x > (view.getSize().x/2)) 
				{ 
					map.viewvelo=-6; 
					parallax-=map.parallaxspeed; 
				} 
			} 
			
			if(Input::getPosition().x > window.getSize().x - (window.getSize().x/32) && Input::getPosition().x <= window.getSize().x) 
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
			
			
			
			
		
			if(self.selected==-1)
			{
				for(int a=0;a<blupi.size();a++)
				{
					if(blupi[a].color==self.color && blupi[a].alive)
					{
						self.selected = a;
						break;
					}
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
				element[a].update(map.iground,blupi[self.selected].locomotion);
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
		
		
		
		
		}
		
		
		
		
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
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		drawElements(window);


		
		
		water.draw(window);
		

		window.draw(map.ground);		



		for(int a=0;a<blupi.size();a++)//draw blupis of specific states on a background layer.
		{
			if(blupi[a].haven != -1)
			{
				//Is in haven
				//draw
				blupi[a].draw(window);
			}
		}



		for(int a=0;a<blupi.size();a++)
		{
			if(!blupi[a].alive)
				continue;	
			
			if(blupi[a].haven != -1)
			{
				//Is in haven
				//skip
				//Already drawn before
				continue;
			}

			
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
		
		
		
		
		
		
		wav.listen.setPosition(view.getCenter().x,0,0);
		
	}
	
}