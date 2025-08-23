







class Taskbar
{
	public:
	Sprite sprite;
	Sprite icon;
	Sprite box;
	Sprite energyBar;
	RectangleShape gridguide;
	
	
	
	// Constants for base button 
    const std::vector<std::string> BASE_BUTTONS = {"menu","quit","settings","save"};
    const std::vector<IntRect> BASE_ICONS = {
    	  {0,560,40,40}, //menu
        {160,280,40,40},  // quit
        {200,320,40,40},  // settings
        {200,360,40,40}   // save
    };

	
	
	
	
	
	
	Taskbar()
	{
		sprite.setTexture(textures.buttons);
		sprite.setScale(1.8,1.8);
		box.setTexture(textures.taskbox);
		gridguide.setSize(Vector2f(32,32));
		gridguide.setFillColor(Color::Transparent);
		gridguide.setOutlineThickness(1);
		gridguide.setOutlineColor(Color::Yellow);
		icon.setTexture(textures.buttons);
	}
	
	
	
	bool checkbutton()
	{
		if(sprite.getGlobalBounds().contains(MPosition))
		{
			if(Input::Mouse(Mouse::Left,true))
			{
				sprite.setTextureRect(IntRect(121,1,39,39));
				return true;
				
			}
			else
				sprite.setTextureRect(IntRect(81,1,39,39));
		}
		
		
		return false;

	}
	
	
	
	
	
	
	
	
	
	
	
	void addButtons()
	{
		for(int a=0;a<element.size();a++)
		{
			if((toplayer.type=="element" && toplayer.ID == a) || (toplayer.type=="blupi" && player[ME].selected == toplayer.ID && topElement.ID == a))
			{
				
				
				std::string type = element[a].type;
				
				if(Input::Mouse(Mouse::Left))
				{

					buttons.clear();

					if(type=="bomb" || type=="wood"||type=="tomato") //pickup
					{
						
						if(blupi[player[ME].selected].carrying.getTextureRect().width==0)
						{
							liveitem = a;
							buttons.push_back(Button("pick up",sf::IntRect(1,239,40,40),2,0));
						}
						
						
					}

					if(type=="tomato")
					{
						liveitem = a;
						
						
						buttons.push_back(Button("eat",sf::IntRect(80,241,40,40),4,0));
						
					}


					if(type=="bomb")
					{
						buttons.push_back(Button("blow up",sf::IntRect(200,280,40,40),1,0));
					}
					
					if(type=="house")
					{
						
						liveitem = a;
						
						if(element[a].blupiIndex!=-1)
						{
							player[ME].selected = element[a].blupiIndex;
						}
						
						
						if(element[a].blupiIndex==player[ME].selected || element[a].blupiIndex == -1)
						{
						
							if(element[a].boolean[0]==true)
							{
								buttons.push_back(Button("exit haven",sf::IntRect(0,0,0,0),0.5,0));
							}
							
						}
						
						if(element[a].boolean[0]==false)
						{
							buttons.push_back(Button("enter haven",sf::IntRect(0,0,0,0),0.5,0));
						}
						
						
					}
					
					
					
					
					if(type=="shed")
					{
						liveitem = a;
						
						
						buttons.push_back(Button("grow",sf::IntRect(161,200,40,40),8,2));
						
					}
					
					
					
					
					if(type=="jeep")
					{
						liveitem = a;
						
						
						
						
						
						
						if(blupi[player[ME].selected].locomotion=="walk")
						{
							buttons.push_back(Button("enter jeep",sf::IntRect(0,0,0,0),0.5,0));
						}
					}
						
						
			
				}
			}
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	void update(RenderWindow &window,Image &ground)
	{

		addButtons();



		box.setPosition(window.getView().getCenter().x - (window.getView().getSize().x/2),540-5);
		window.draw(box);


	
		Vector2f boxpos;
		boxpos = box.getPosition();
		
		
		
		
		
		for(int a=0;a<BASE_BUTTONS.size();a++)
		{
			
			sf::Vector2f pos;
			
			
			if(a == 0)//top left
			{
				pos.x = boxpos.x + 190 - 39 - 4 -1;
				pos.y = boxpos.y + 55 - 39 + 2;
			}
			
			if(a == 1)//top right
			{
				pos.x = boxpos.x + 190 - 3 + 1 -1;
				pos.y = boxpos.y + 55 - 39 + 2;
			}
			
			if(a == 2)//bottom left
			{
				pos.x = boxpos.x + 190 - 3 - 39 - 1 -1;
				pos.y = boxpos.y + 55 + 4;
			}
			
			
			if(a == 3)//bottom right
			{
				pos.x = boxpos.x + 190 - 3 + 1 - 1;
				pos.y = boxpos.y + 55 + 4;
			}
			
			
			
			
			
			
			
			
			sprite.setScale(1,1);
			sprite.setTextureRect(IntRect(1,1,39,39));
			sprite.setPosition(pos);
			icon.setTextureRect(BASE_ICONS[a]);
			icon.setPosition(sprite.getPosition());
			icon.setScale(sprite.getScale());
			
			
			
			
			if(checkbutton())
			{
				if(BASE_BUTTONS[a] == "menu")
				{
					
					
					//open menu that contains "quit" "settings" and "save"
					
					
					exit(0);
				}
				
				
			}
			
			
			window.draw(sprite);
			window.draw(icon);
		}
	
		for(int a=0;a<buttons.size();a++)
		{
			
			

			sprite.setScale(1.8,1.8);
			sprite.setTextureRect(IntRect(1,1,39,39));
			sprite.setPosition(boxpos.x + 250 +  ((sprite.getTextureRect().width * sprite.getScale().x) * a),boxpos.y + 20);
			icon.setPosition(sprite.getPosition());
			icon.setScale(sprite.getScale());



			
			bool pressed=false;
			if((Input::Key(Keyboard::Num1,true) && a == 1)||(Input::Key(Keyboard::Num2,true) && a == 2)||(Input::Key(Keyboard::Num3,true) && a == 3)||(Input::Key(Keyboard::Num4,true) && a == 4)||(Input::Key(Keyboard::Num5,true) && a == 5))
			{
				pressed=true;
			}			
					
			
			if(checkbutton() || pressed)
			{
				
				
				if(buttons[a].type == "stop")
				{

					blupi[player[ME].selected].actionTime = 0;
					blupi[player[ME].selected].actionEnergy = 0;

					if(!blupi[player[ME].selected].traveled())
					{
						blupi[player[ME].selected].sayObey();
						blupi[player[ME].selected].Stop();
					}
					else
					{		
						blupi[player[ME].selected].startstop=true;
						blupi[player[ME].selected].sayObey();
					}
					
					buttons.clear();
					break;	
				}




				if(buttons[a].type.find("exit") != std::string::npos)
				{
					blupi[player[ME].selected].action = buttons[a].type;
					blupi[player[ME].selected].itemindex = liveitem;
					blupi[player[ME].selected].initAction = true;
					blupi[player[ME].selected].actionTime = buttons[a].time;
					blupi[player[ME].selected].actionEnergy = buttons[a].energy;					
					blupi[player[ME].selected].sayObey();
					buttons.clear();
					break;		
				}

			
				
				if(!blupi[player[ME].selected].busy)
				{
					if(!blupi[player[ME].selected].possible(element[liveitem].now))
					{
						blupi[player[ME].selected].sayFailed();
						buttons.clear();						
						break;
					}
					blupi[player[ME].selected].action = buttons[a].type;
					blupi[player[ME].selected].itemindex = liveitem;
					blupi[player[ME].selected].initAction = true;
					blupi[player[ME].selected].actionTime = buttons[a].time;
					blupi[player[ME].selected].actionEnergy = buttons[a].energy;
					blupi[player[ME].selected].sayObey();
					buttons.clear();
					break;
				}
				else
				{
					
					blupi[player[ME].selected].sayFailed();
					buttons.clear();
					break;
				}

			}
		
			if(buttons[a].icon != sf::IntRect(0,0,0,0))
				icon.setTextureRect(buttons[a].icon);
			else
				icon.setTextureRect(IntRect(39*15,39*2,39,39));
			
		
		
		
		
			
			
			


			
			
			window.draw(sprite);
			window.draw(icon);
			
		}
	
	
	
		

		

		
		
		
		
		
		
		
		if(window.hasFocus() && MPosition.y < ground.getSize().y && MPosition.x < ground.getSize().x && MPosition.x >=0 && MPosition.y >=0)
		{
			gridguide.setPosition(int(MPosition.x/32)*32,int(MPosition.y/32)*32);
			window.draw(gridguide);
			
			
			
			if(checkGroundNow(ground,MPosition))
			{
				
			
				static bool released=false;
				if(Input::Mouse(Mouse::Left,true))
				{
					if(!blupi[player[ME].selected].busy && blupi[player[ME].selected].possible(MPosition) && blupi[player[ME].selected].haven==-1)
					{
						
						if(toplayer.type!="element")
						{
						
						
						
						
							bool skip=false;
							if(toplayer.ID!=player[ME].selected && toplayer.type=="blupi")
							{
								skip=true;
							}
							
							if(!skip)
							{
							
								if(blupi[player[ME].selected].state=="moveleft")
									blupi[player[ME].selected].state="left";
								if(blupi[player[ME].selected].state=="moveright")
									blupi[player[ME].selected].state="right";
								
								
								blupi[player[ME].selected].destination = MPosition;
								
								blupi[player[ME].selected].action="none";
								
							}
						}
						
					}
					else
					{
						
						if(blupi[player[ME].selected].busy)
						{
							if(!blupi[player[ME].selected].traveled())
							{
								blupi[player[ME].selected].sayObey();
								blupi[player[ME].selected].Stop();
							}
							
						}
						else
						{
							if(!blupi[player[ME].selected].possible(MPosition))
								blupi[player[ME].selected].failed();
								
						}
						
					}
					
					buttons.clear();
					liveitem=-1;
			
			
				}
			}
		}
		
	

		
		
		if(blupi[player[ME].selected].busy && buttons.size() == 0 && !blupi[player[ME].selected].startstop)
		{
			buttons.push_back(Button("stop",sf::IntRect(160,280,40,40),blupi[player[ME].selected].actionTime,0));
	
		}
		
		if(!blupi[player[ME].selected].busy || blupi[player[ME].selected].startstop)
		{
			for(int a=0;a<buttons.size();a++)
			{
				if(buttons[a].type == "stop")
				{
					buttons.erase(buttons.begin()+a);
					break;
				}
			}
		}
		
		
		
		
		
		
		//draw energy bar <><><><><><><><><><><><><>
		
		energyBar.setPosition(boxpos.x + 20,boxpos.y+20);
		energyBar.setTexture(textures.bars);
		energyBar.setTextureRect({0,0,124,22});//empty
		window.draw(energyBar);
		
		
		int percent = 124 * (blupi[player[ME].selected].energy/100);
		
		
		energyBar.setTextureRect({0,22 + 22,percent,22});
		
		window.draw(energyBar);
		
		
		//draw progress bar<><><><>
		
		energyBar.setPosition(boxpos.x + 20,boxpos.y+20 + 25);
		energyBar.setTexture(textures.bars);
		energyBar.setTextureRect({0,0,124,22});//empty
		window.draw(energyBar);
		
		if(blupi[player[ME].selected].actionTime != 0 && blupi[player[ME].selected].progressTime.getElapsedTime().asSeconds() != 0)
			percent = 124 * (blupi[player[ME].selected].progressTime.getElapsedTime().asSeconds()/blupi[player[ME].selected].actionTime);
		else
			percent = 0;
			
		
		energyBar.setTextureRect({0,22 * 3,percent,22});
		
		window.draw(energyBar);
		
		//////////////////////////
		
		
		
		
		
		
	}
	
	
	
}taskbar;