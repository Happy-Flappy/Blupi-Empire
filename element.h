





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
	bool exists=true;
	bool displayNumber=false;
	Text numberText;
	SoundBuffer buffer;
	int soundChannel = -1;
	int blupiIndex=-1;
	int boomID=-1;
	
	
	Element()
	{
		numberText.setFillColor(Color::Green);
		numberText.setOutlineThickness(1);
		numberText.setCharacterSize(20);
		numberText.setFont(textures.comic);
		
		FloatRect textBounds = numberText.getLocalBounds();
    	numberText.setOrigin(textBounds.width/2, textBounds.height/2);
		
		for(int a=0;a<10;a++)
			boolean[a]=false;
		
		
	}
	
	
	
	
	
	
	
	
	struct ShiftMode
	{
		ShiftData blowup;
		ShiftData grow;
		
		ShiftMode()
		{
			blowup.delay = 0.1;
			blowup.rect.push_back(IntRect(156,1,31,27));
			blowup.rect.push_back(IntRect(254,133,57,60));
			blowup.rect.push_back(IntRect(128,438,109,97));
			blowup.rect.push_back(IntRect(346,650,112,111));
			blowup.rect.push_back(IntRect(114,878,116,115));
			blowup.rect.push_back(IntRect(1,762,115,112));
			blowup.rect.push_back(IntRect(128,438,109,97));
			blowup.rect.push_back(IntRect(207,542,112,106));
			blowup.rect.push_back(IntRect(225,343,110,94));
			blowup.rect.push_back(IntRect(305,260,114,82));
			blowup.rect.push_back(IntRect(1,260,122,70));
			blowup.rect.push_back(IntRect(129,75,111,50));
			
			
			grow.delay = 2;
			int offset=10;
			grow.rect.push_back(sf::IntRect(59,644,45,56+offset));
			grow.rect.push_back(sf::IntRect(59+45,644,45,56+offset));
			grow.rect.push_back(sf::IntRect(59+45+45,644,45,56+offset));
			grow.rect.push_back(sf::IntRect(59+45+45+45,644,45,56+offset));
			grow.rect.push_back(sf::IntRect(59+45+45+45+45,644,45,56+offset));
			
		}
		
		
		
			
	}shift;
	
	
	
	
	
	
	
	
	
	
		
	void getNumberOfOverlap(std::vector<Element> &element)
	{
	    int total = 1;
	    displayNumber = false; // Reset every frame
	
	    for (int a = 0; a < element.size(); a++)
	    {
	        if (element[a].ID == ID || 
	            !element[a].exists || 
	            !element[a].active || 
	            element[a].type != type) 
	            continue;
	
	        // Adjusted bounds with 20px padding
	        FloatRect bounds = sprite.getGlobalBounds();
	        bounds.left += 20;
	        bounds.width -= 40;
	        bounds.top += 20;
	        bounds.height -= 20;
	        
	        // Adjusted bounds with 20px padding
	        FloatRect bounds2 = element[a].sprite.getGlobalBounds();
	        bounds2.left += 20;
	        bounds2.width -= 40;
	        bounds2.top += 20;
	        bounds2.height -= 20;
	        
	        
	
	        if (bounds.intersects(bounds2))
	        {
	        	
	            total++;
	            element[a].displayNumber = false; // Disable others
	            displayNumber = true; // Enable for this element
	        }
	    }
	
	    // Update text only when needed
	    if (displayNumber && total > 1 && exists && active)
	    {
	        // Get final position first
	        float textY = now.y - (averageHeight - (averageHeight/3)) - 40;
	        
	        // Set string once with final value
	        numberText.setString(std::to_string(total));
	        
	        // Update origin AFTER string is set
	        FloatRect textBounds = numberText.getLocalBounds();
	        numberText.setOrigin(textBounds.width/2, textBounds.height/2);
	        
	        // Set final position
	        numberText.setPosition(now.x, textY);
	    }
	    else
	    {
	        numberText.setString("");
	        displayNumber = false;
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
						if(water.puddle[index].linepos.size()>50)
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
					sprite.setScale(9,9);
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
					
					
					if(shift.blowup.currentframe == int(shift.blowup.rect.size()/2))
					{
						Boom newboom;
						newboom.boomSpot=now.x;
						boom.push_back(newboom);	
					}
					
					
					if(shift.blowup.ended)
					{	
						exists=false;
					}
					
					
					
				}
			}
			
			
			
			
			
		
			if((toplayer.type=="element" && toplayer.ID == ID) || (toplayer.type=="blupi" && player[ME].selected == toplayer.ID && topElement.ID == ID))
			{
				static bool released=true;
				if(Mouse::isButtonPressed(Mouse::Left))
				{
					if(released)
					{

						if(type=="bomb" || type=="wood"||type=="tomato")
						{
							liveitem = ID;
							
							buttons.clear();
							iconrect.clear();
							
							buttons.push_back("pick up");
							iconrect.push_back(IntRect(1,239,40,40));
						}

						if(type=="bomb")
						{

							buttons.push_back("blow up");
							iconrect.push_back(IntRect(200,280,40,40));
							
						}
						
						if(type=="house")
						{
							
							liveitem = ID;
							
							buttons.clear();
							iconrect.clear();
							
							if(blupiIndex!=-1)
							{
								player[ME].selected = blupiIndex;
							}
							
							
							if(blupiIndex==player[ME].selected || blupiIndex == -1)
							{
							
								if(boolean[0]==true)
								{
									buttons.push_back("leave haven");
								}
								
							}
							
							if(boolean[0]==false)
							{
								buttons.push_back("haven");
							}
							
							
						}
						
						
						
						
						if(type=="shed")
						{
							liveitem = ID;
							
							buttons.clear();
							iconrect.clear();
							
							buttons.push_back("grow");
							iconrect.push_back(IntRect(161,200,40,40));	
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
			if(displayNumber)
				window.draw(numberText);
		}	
	}
};

std::vector <Element> element;