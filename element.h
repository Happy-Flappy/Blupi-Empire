





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
	float scale = 1.5;//1.5
	bool burning=false;
	bool active = true;
	bool boolean[10];
	bool exists=true;
	bool taken=false;
	bool obeysRotation = true;
	int displayNumber=0;
	
	Text numberText;
	
	SoundBuffer buffer;
	int soundChannel = -1;
	int blupiIndex=-1;
	int boomID=-1;
	int textX=0;
	int layer = 5;
	sf::FloatRect bounds;
	
	
	
	
	void getState(sf::Packet &packet) //CLIENT FUNCTION THAT RECEIVES GAME STATE
	{
		packet >> type 
		>> color
		>> velocity.x 
		>> velocity.y
		>> now.x 
		>> now.y
		>> scale
		>> burning
		>> active
		>> boolean[0] 
		>> boolean[1]
		>> boolean[2]
		>> boolean[3]
		>> boolean[4]
		>> boolean[5]
		>> boolean[6]
		>> boolean[7]
		>> boolean[8]
		>> boolean[9]
		>> exists
		>> taken
		>> obeysRotation
		>> displayNumber
		>> soundChannel
		>> /*blupiIndex << boomID*/ textX
		>> layer
		>> bounds.left
		>> bounds.top
		>> bounds.width
		>> bounds.height;		
	}
	
	void sendState(sf::Packet &packet)//HOST FUNCTION THAT SENDS GAME STATE TO CLIENTS
	{
		packet << type 
		<< color
		<< velocity.x 
		<< velocity.y
		<< now.x 
		<< now.y
		<< scale
		<< burning
		<< active
		<< boolean[0] 
		<< boolean[1]
		<< boolean[2]
		<< boolean[3]
		<< boolean[4]
		<< boolean[5]
		<< boolean[6]
		<< boolean[7]
		<< boolean[8]
		<< boolean[9]
		<< exists
		<< taken
		<< obeysRotation
		<< displayNumber
		<< soundChannel
		<< /*blupiIndex << boomID*/ textX
		<< layer
		<< bounds.left
		<< bounds.top
		<< bounds.width
		<< bounds.height;
		
	}
	
	
	
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
		ShiftData energy;
		
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
			
			grow.rect.push_back(sf::IntRect(59,644 + 1,45 - 1,56+offset - 1));
			grow.rect.push_back(sf::IntRect(59+45,644 + 1,45 - 1,56+offset - 1));
			grow.rect.push_back(sf::IntRect(59+45+45,644 + 1,45 - 1,56+offset - 1));
			grow.rect.push_back(sf::IntRect(59+45+45+45,644 + 1,45 - 1,56+offset - 1));
			grow.rect.push_back(sf::IntRect(59+45+45+45+45,644 + 1,45 - 1,56+offset - 1));
			
			
			energy.delay = 0.15;
			int x1 = 328;
			int y1 = 644;
		    
			for(int a=0;a<6;a++)
				energy.rect.push_back({x1 + (77 * a),y1,77,73});
		    
			
		}
		
		
		
			
	}shift;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	void update(sf::Image &ground,std::string locomotion)
	{
		
		if(ground.getSize().x == 0 || ground.getSize().y == 0)
			return;
		
		bounds = sprite.getGlobalBounds();
        bounds.left += bounds.left/6;
        bounds.width -= bounds.width/6;
        bounds.top += bounds.top/5;
        bounds.height -= bounds.height/5;
        
        
        
        
		if(active && exists)
		{
		
		
			
		
		
		
			sprite.setScale(scale,scale);
			
			sprite.setOrigin(sprite.getTextureRect().width/2,sprite.getTextureRect().height/2);
			
			
			sprite.setPosition(now.x,now.y - (averageHeight - (averageHeight/3)));
			
			
			Gravity(ground,velocity,now,gravity);
			
			
			if(obeysRotation)
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
							sprite.setScale(-scale,scale);
						}
						else
						{
							now.x = water.puddle[index].left + width;
							now.y = water.puddle[index].linepos[width].y;
							sprite.setScale(scale,scale);
						}
					}
					
					
				}

			}
			
			
			if(type=="energy")
			{
				sprite.setTextureRect(Shift(shift.energy));
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
						int a = wav.findChannel();
						if(a!=-1)
						{
						
							soundChannel = a;
							if(a==-1)
								a=0;
							wav.playSound(100,now.x);
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
			
			

		}
		
	}
	void draw(RenderWindow &window)
	{
		if(active && exists)
		{
			window.draw(sprite);
			if(displayNumber > 1)
			{
	
		        // Get final position first
		        float textY = now.y - (averageHeight - (averageHeight/3)) - 70;
		        
		        // Set string once with final value
		        numberText.setString(std::to_string(displayNumber));

				FloatRect textBounds = numberText.getLocalBounds();
	    	    numberText.setOrigin(textBounds.width/2, textBounds.height/2);
	        
	    	    // Set final position
	    	    numberText.setPosition(textX, textY);
				window.draw(numberText);
			}
		}	
	}
};

std::vector <Element> element;



void drawElementLayer(int layer,sf::RenderWindow &window)
{
	for(int a=0;a<element.size();a++)
	{
		
		if(!element[a].exists)
			continue;
		if(element[a].layer != layer)
			continue;
	
		if(element[a].active)
		{
			element[a].draw(window);
		}
	}
}


void drawElements(sf::RenderWindow &window)
{

	drawElementLayer(1,window);
	drawElementLayer(2,window);
	drawElementLayer(3,window);
	drawElementLayer(4,window);
	drawElementLayer(5,window);
	

}