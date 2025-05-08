







class Taskbar
{
	public:
	Sprite sprite;
	Sprite icon;
	Sprite box;
	RectangleShape gridguide;
	
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
			if(Mouse::isButtonPressed(Mouse::Left))
			{
				sprite.setTextureRect(IntRect(121,1,39,39));
				
				if(cursor.released)
				{
					return true;

				}
				
				cursor.released=false;
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
		
		
		
		
	
		for(int a=0;a<buttons.size();a++)
		{
			sprite.setTextureRect(IntRect(1,1,39,39));
			sprite.setPosition(boxpos.x + 250 +  ((sprite.getTextureRect().width * sprite.getScale().x) * a),boxpos.y + 20);
			icon.setPosition(sprite.getPosition());
			icon.setScale(sprite.getScale());
			
			
			bool pressed=false;
			if((Keyboard::isKeyPressed(Keyboard::Num1) && a == 0)||(Keyboard::isKeyPressed(Keyboard::Num2) && a == 1)||(Keyboard::isKeyPressed(Keyboard::Num3) && a == 3)||(Keyboard::isKeyPressed(Keyboard::Num4) && a == 4)||(Keyboard::isKeyPressed(Keyboard::Num5) && a == 5))
			{
				pressed=true;
			}
			
			
			
			if(checkbutton() || pressed)
			{
				if(!blupi[player[ME].selected].busy && blupi[player[ME].selected].possible(element[liveitem].now))
				{
					
					blupi[player[ME].selected].action = buttons[a];
					blupi[player[ME].selected].itemindex = liveitem;
					
					
					
					if(buttons[a]!="stop drive" && buttons[a]!="drop")
					{
						blupi[player[ME].selected].destination = element[liveitem].now;
						if(blupi[player[ME].selected].now.x < element[liveitem].now.x)
						{
							blupi[player[ME].selected].state = "moveright";
						}
						if(blupi[player[ME].selected].now.x > element[liveitem].now.x)
						{
							blupi[player[ME].selected].state = "moveleft";
						}
					}
					
					blupi[player[ME].selected].sayObey();
				}
				else
				{
					blupi[player[ME].selected].failed();
				}
				buttons.clear();
				iconrect.clear();

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
				if(Mouse::isButtonPressed(Mouse::Left))
				{
					if(released)
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
									blupi[player[ME].selected].pickup=false;
									
								}
							}
							
						}
						else
						{
							blupi[player[ME].selected].failed();
						}
						
						buttons.clear();
						iconrect.clear();
						liveitem=-1;
						
						
						
					
						
					}
					released=false;
				}
				else
					released=true;
			}
		}
		
		
		if(blupi[player[ME].selected].busy && buttons.size() == 0)
		{
			buttons.push_back("stop");
			iconrect.push_back(IntRect(160,280,40,40));
						
		}
		
		
	}
	
	
	
}taskbar;