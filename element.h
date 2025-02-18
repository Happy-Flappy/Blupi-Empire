





class Element
{
	public:
	Sprite sprite;
	std::string type="";
	int ID=-1;
	int averageHeight;
	Vector2f velocity;
	Vector2f now;
	float gravity = 0.2;
	bool burning=false;
	bool active = true;
	
	bool boolean[10];
	
	
	Element()
	{
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	void update(Image &ground,std::string locomotion)
	{
		
		
		if(active)
		{
		
			sprite.setScale(1.5,1.5);
			
			sprite.setOrigin(sprite.getTextureRect().width/2,sprite.getTextureRect().height/2);
			
			sprite.setPosition(now.x,now.y - (averageHeight - (averageHeight/3)));
			
			
			Gravity(sprite,ground,velocity,now,gravity);
			
			
			sprite.setRotation(getGroundAngle(ground,now, sprite.getRotation() , sprite.getTextureRect().width/2 ));
			
			
			
			
			
			
			if(type=="boat")
			{
				
				
				sprite.setRotation(0);
				
				
				int index = water.getPuddleIndex(now.x);
				
				if(index!=-1)
				{
					if(water.puddle[index].linepos.size()>now.x)
					{
						now.y = water.puddle[index].linepos[50].y;
					}
					if(water.puddle[index].left!=-1)
					{
					
						int middle = water.puddle[index].left + ((water.puddle[index].right-water.puddle[index].left)/2/*width*/);//left + half-width
						
						
						int width = sprite.getTextureRect().width * 0.85;
						
						if(now.x > middle)
						{
							now.x = water.puddle[index].right - width;
							now.y = water.puddle[index].linepos[water.puddle[index].linepos.size()-width].y;
							//sprite.setScale(-1,1);
						}
						else
						{
							now.x = water.puddle[index].left + width;
							now.y = water.puddle[index].linepos[width].y;
							//sprite.setScale(1,1);
						}
					}
					
					
				}

			}
			
			
			
			
			
			
			
			
			
			
		
			if(sprite.getGlobalBounds().contains(MPosition) && toplayer.type=="element" && toplayer.ID == ID)
			{
			
				static bool released=true;
				if(Mouse::isButtonPressed(Mouse::Left))
				{
					if(released)
					{
						
						if(type=="bomb")
						{
							liveitem = ID;
							
							buttons.clear();
							iconrect.clear();
							
							buttons.push_back("pick up");
							iconrect.push_back(IntRect(1,239,40,40));
							buttons.push_back("blow up");
							iconrect.push_back(IntRect(200,280,40,40));
							
						}
						
						if(type=="house")
						{
							liveitem = ID;
							
							buttons.clear();
							iconrect.clear();
							if(boolean[0]==true)
							{
								buttons.push_back("leave haven");
								
							}
							else
							{
								buttons.push_back("haven");
							}
						}
						
						
						
						if(type=="jeep")
						{
							liveitem = ID;
							
							
							
							
							
							
							buttons.clear();
							iconrect.clear();
							if(locomotion=="walk")
							{
								buttons.push_back("drive");
							}
						}
						
			
						
						released=false;
					}
				}
				else
					released=true;
			}
		}
		
	}
	void draw(RenderWindow &window)
	{
		if(active)
			window.draw(sprite);
	}
};

std::vector <Element> element;