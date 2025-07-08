







class Taskbar
{
	public:
	Sprite sprite;
	Sprite icon;
	Sprite box;
	Sprite energyBar;
	RectangleShape gridguide;
	
	
	
	// Constants for base button 
    const std::vector<std::string> BASE_BUTTONS = {"menu"};
    const std::vector<IntRect> BASE_ICONS = {
    	  {0,560,40,40} //menu
//        {160,280,40,40},  // quit
//        {200,320,40,40},  // settings
//        {200,360,40,40}   // save
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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	void update(RenderWindow &window,Image &ground)
	{

		box.setPosition(window.getView().getCenter().x - (window.getView().getSize().x/2),540-5);
		window.draw(box);


	
		Vector2f boxpos;
		boxpos = box.getPosition();
		
		
		
		
		
		for(int a=0;a<BASE_BUTTONS.size();a++)
		{
			sprite.setScale(1,1);
			sprite.setTextureRect(IntRect(1,1,39,39));
			sprite.setPosition(boxpos.x + 20 +  ((sprite.getTextureRect().width * sprite.getScale().x) * a),boxpos.y + 55);
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
				
				
				if(buttons[a] == "stop")
				{

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
					iconrect.clear();
					break;	
				}




				if(buttons[a].find("exit") != std::string::npos)
				{
					blupi[player[ME].selected].action = buttons[a];
					blupi[player[ME].selected].itemindex = liveitem;
					blupi[player[ME].selected].initAction = true;
					blupi[player[ME].selected].sayObey();
					buttons.clear();
					iconrect.clear();			
					break;		
				}

			
				
				if(!blupi[player[ME].selected].busy)
				{
					if(!blupi[player[ME].selected].possible(element[liveitem].now))
					{
						blupi[player[ME].selected].sayFailed();
						buttons.clear();
						iconrect.clear();						
						break;
					}
					blupi[player[ME].selected].action = buttons[a];
					blupi[player[ME].selected].itemindex = liveitem;
					blupi[player[ME].selected].initAction = true;
					blupi[player[ME].selected].sayObey();
					buttons.clear();
					iconrect.clear();
					break;
				}
				else
				{
					
					blupi[player[ME].selected].sayFailed();
					buttons.clear();
					iconrect.clear();
					break;
				}

			}
		
			if(a < iconrect.size())
				icon.setTextureRect(iconrect[a]);
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
					iconrect.clear();
					liveitem=-1;
			
			
				}
			}
		}
		
	

		
		
		if(blupi[player[ME].selected].busy && buttons.size() == 0 && !blupi[player[ME].selected].startstop)
		{
			buttons.push_back("stop");
			iconrect.push_back({160,280,40,40});
	
		}
		
		if(!blupi[player[ME].selected].busy || blupi[player[ME].selected].startstop)
		{
			for(int a=0;a<buttons.size();a++)
			{
				if(buttons[a] == "stop")
				{
					buttons.erase(buttons.begin()+a);
					iconrect.erase(iconrect.begin()+a);
					break;
				}
			}
		}
		
		
		
		
		
		
		//draw energy bar <><><><><><><><><><><><><>
		
		energyBar.setPosition(boxpos.x + 22,boxpos.y+20);
		energyBar.setTexture(textures.bars);
		energyBar.setTextureRect({0,0,124,22});//empty
		window.draw(energyBar);
		
		
		int percent = 124 * (blupi[player[ME].selected].energy/100);
		
		
		energyBar.setTextureRect({0,22,percent,22});
		
		window.draw(energyBar);
		
		
		//draw progress bar<><><><>
		
		//.......placeholder......
		
		//////////////////////////
	}
	
	
	
}taskbar;