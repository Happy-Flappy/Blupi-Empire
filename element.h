





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
	bool deleteThis=false;
	Text numberText;
	SoundBuffer buffer;
	int soundChannel = -1;
	
	Element()
	{
		numberText.setFillColor(Color::Green);
		numberText.setOutlineThickness(1);
		numberText.setCharacterSize(20);
		numberText.setFont(textures.comic);
		
		for(int a=0;a<10;a++)
			boolean[a]=false;
		
		
	}
	
	
	
	
	
	
	
	
	struct ShiftMode
	{
		ShiftData blowup;
		
		ShiftMode()
		{
			blowup.rect.push_back(IntRect(157,0,32,28));
			blowup.rect.push_back(IntRect(253,132,58,61));
			blowup.rect.push_back(IntRect(0,451,107,104));
			blowup.rect.push_back(IntRect(345,649,113,112));
			blowup.rect.push_back(IntRect(113,877,117,116));
			blowup.rect.push_back(IntRect(0,761,116,113));
			blowup.rect.push_back(IntRect(127,437,110,98));
			blowup.rect.push_back(IntRect(206,541,113,107));
			blowup.rect.push_back(IntRect(224,342,111,95));
			blowup.rect.push_back(IntRect(304,259,115,83));
			blowup.rect.push_back(IntRect(0,259,123,71));
			blowup.rect.push_back(IntRect(128,74,112,51));
		}
			
	}shift;
	
	
	
	
	
	
	
	
	
	
	
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
			
			
			
			
			
			
			if(type=="bomb")
			{
				if(boolean[0]==true)
				{
					//blowup!
					sprite.setScale(5,5);
					sprite.setTexture(textures.explo);
					sprite.setTextureRect(Shift(shift.blowup));
					
					if(soundChannel==-1)
					{
						int a = findChannel();
						if(a!=-1)
						{
						
							soundChannel = a;
							sound[a].stop();
							buffer.loadFromFile("ASSETS/miscSound/boom.wav");
							sound[a].setBuffer(buffer);
							sound[a].play();
						}
				
					}
					
					
					if(shift.blowup.ended)
					{	
						deleteThis=true;
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