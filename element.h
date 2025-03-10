





class Element
{
	public:
	Sprite sprite;
	std::string type="";
	std::string color = "any";
	int ID=-1;
	int averageHeight;
	Vector2f velocity;
	Vector2f now;
	float gravity = 0.2;
	bool burning=false;
	bool active = true;
	bool boolean[10];
	Text numberText;
	
	
	Element()
	{
		numberText.setFillColor(Color::Green);
		numberText.setOutlineThickness(1);
		numberText.setCharacterSize(20);
		numberText.setFont(textures.comic);
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	void getNumberOfOverlap(std::vector<Element> &element,Element &e)
	{
		
		
		
		std::string type;
		
		Vector2f position;
		type = e.type;
		position = e.now;
		
		int total=0;
		for(int a=0;a<element.size();a++)
		{
			
			if(element[a].type==type && element[a].active)
			{
				
				for(int b=0;b<element.size();b++)
				{
					if(element[b].type==type && element[a].active)
					{
						if(element[a].sprite.getGlobalBounds().contains(element[b].now))
						{
						
							if(abs(element[a].now.x) - abs(element[b].now.x) < 10)
							{
								if(a!=b)
								{
									total++;
								}
							}
						}
					}
				}
			}
		}
		e.numberText.setString(std::to_string(total+1));
		e.numberText.setPosition(e.now.x,e.now.y - 40);
		if(total == 0)
		{
			e.numberText.setString("");
		}
	
	}
	
	
	
	
	
	
	
	
	
	
	void update(Image &ground,std::string locomotion)
	{
		
		
		if(active)
		{
		
			sprite.setScale(1.5,1.5);
			
			sprite.setOrigin(sprite.getTextureRect().width/2,sprite.getTextureRect().height/2);
			
			sprite.setPosition(now.x,now.y - (averageHeight - (averageHeight/3)));
			
			
			Gravity(sprite,ground,velocity,now,gravity);
			
			
			sprite.setRotation(getGroundAngle(ground,now, sprite.getRotation() , 10 ));
			
			
			
			
			
			
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
							sprite.setScale(-1.5,1.5);
						}
						else
						{
							now.x = water.puddle[index].left + width;
							now.y = water.puddle[index].linepos[width].y;
							sprite.setScale(1.5,1.5);
						}
					}
					
					
				}

			}
			
			
			
			
			
			
			
		
			if(toplayer.type=="element" && toplayer.ID == ID)
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
		{
			window.draw(sprite);
			window.draw(numberText);
		}	
	}
};

std::vector <Element> element;