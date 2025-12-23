







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
			if((toplayer.type=="element" && toplayer.ID == a) || (toplayer.type=="blupi" && self.selected == toplayer.ID && topElement.ID == a))
			{
				
				std::string type = element[a].type;
				
				if(Input::Mouse(Mouse::Left))
				{

					buttons.clear();

					if(type=="bomb" || type=="wood"||type=="tomato" || ((type == "boat") && !element[a].taken)  || type == "energy") //pickup
					{
						
						if(blupi[self.selected].carrying.getTextureRect().width==0)
						{
							liveitem = a;
							buttons.push_back(Button("pick up",sf::IntRect(1,239,40,40),2,0));
						}
						
						
					}
					
					
					
					
					if(type == "boat")
					{
						if(!element[a].taken)//is on ground
						{
							liveitem = a;
							
							buttons.push_back(Button("scoot left",sf::IntRect(40*2,40*9,40,40),0,0));
							buttons.push_back(Button("scoot right",sf::IntRect(40*3,40*9,40,40),0,0));
						}
					}
					
					
					
					
					
					if(type == "wood")
					{
						liveitem = a;
						buttons.push_back(Button("make house",sf::IntRect(40*3,40*14,40,40),6,4));
						
						buttons.push_back(Button("make shed",sf::IntRect(40*1,40*4,40,40),6,4));
						
						buttons.push_back(Button("make boat",sf::IntRect(40*4,40*10,40,40),6,4));
						
						
						
						
					}
					

					if(type=="tomato" || type == "energy")
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
							self.selected = element[a].blupiIndex;
						}
						
						
						if(element[a].blupiIndex==self.selected || element[a].blupiIndex == -1)
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
						
						
						buttons.push_back(Button("grow tomato",sf::IntRect(161,200,40,40),8,2));
						
						buttons.push_back(Button("grow pine",sf::IntRect(40*2,40*2,40,40),8,2));
						
						buttons.push_back(Button("grow palm",sf::IntRect(40*4,40*2,40,40),8,2));
						
					}
					
					
					
					
					if(type=="jeep")
					{
						liveitem = a;
						
						
						
						
						
						
						if(blupi[self.selected].locomotion=="walk")
						{
							buttons.push_back(Button("enter jeep",sf::IntRect(0,0,0,0),0.5,0));
						}
					}
						
						
						
					if(type=="pine" || type == "palm")
					{
						liveitem = a;
						if(blupi[self.selected].locomotion=="walk")
						{
							buttons.push_back(Button("fell tree",sf::IntRect(40*4,40*4,40,40),6,4));
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
				


				//Make a request no matter the situation and let the host determine the action. The host will send acknowledgement if the action is possible.
			    
			    blupi[self.selected].makeRequest(
			        buttons[a].type,
			        element[liveitem].now,
			        liveitem,
			        buttons[a].time,
			        buttons[a].energy
			    );
			    
			    buttons.clear();
			    break;
			
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
			    if(Input::Mouse(Mouse::Left,true))
			    {
			        if(self.selected >= 0 && self.selected < blupi.size()) {
			            Blupi& selectedBlupi = blupi[self.selected];
			            
			            selectedBlupi.request.destination = MPosition;
			            std::cerr << "Request Move>>>>\n";
			            
						selectedBlupi.sayObey();
						
						buttons.clear();
			        	liveitem=-1;
			        }

			    }
			}
		}
		
	

		
		
		
		
		
		
		
		
		//draw energy bar <><><><><><><><><><><><><>
		
		energyBar.setPosition(boxpos.x + 20,boxpos.y+20);
		energyBar.setTexture(textures.bars);
		energyBar.setTextureRect({0,0,124,22});//empty
		window.draw(energyBar);
		
		
		int percent = 124 * (blupi[self.selected].energy/100);
		
		
		energyBar.setTextureRect({0,22 + 22,percent,22});
		
		window.draw(energyBar);
		
		
		//draw progress bar<><><><>
		
		energyBar.setPosition(boxpos.x + 20,boxpos.y+20 + 25);
		energyBar.setTexture(textures.bars);
		energyBar.setTextureRect({0,0,124,22});//empty
		window.draw(energyBar);
		
		if(blupi[self.selected].actionTime != 0 && blupi[self.selected].progressTime.getElapsedTime().asSeconds() != 0)
			percent = 124 * (blupi[self.selected].progressTime.getElapsedTime().asSeconds()/blupi[self.selected].actionTime);
		else
			percent = 0;
			
		
		energyBar.setTextureRect({0,22 * 3,percent,22});
		
		window.draw(energyBar);
		
		//////////////////////////
		
		
		
		
		
		
	}
	
	
	
}taskbar;