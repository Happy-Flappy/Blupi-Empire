



class Blupi
{
	public:
	
	Sprite sprite;
	
	
	//SHIFT MODES
	
	struct ShiftModes
	{
		
		
		ShiftData walkleft;
		ShiftData walkright;
		ShiftData idleleft;
		ShiftData idleright;
		ShiftData blinkleft;
		ShiftData blinkright;
		ShiftData blowup; 
		
		
		
		ShiftModes()
		{
			
			blinkleft.rect.push_back(IntRect(62*4,0,62,62));
			blinkleft.rect.push_back(IntRect(62*6,62*8,62,62));
			
			blinkright.rect.push_back(IntRect(0,0,62,62));
			blinkright.rect.push_back(IntRect(62*5,62*8,62,62));
			
			
			
			idleright.delay = 0.4;
			idleright.rect.push_back(IntRect(0,0,62,62));
			idleright.rect.push_back(IntRect(62*7,62,62,62));
			
			idleleft.delay = 0.4;
			idleleft.rect.push_back(IntRect(62*4,0,62,62));
			idleleft.rect.push_back(IntRect(62*8,62,62,62));
			
			
			
			walkright.delay = 0.1;

			walkright.rect.push_back(IntRect(62*10, 0+1, 62, 62));
			walkright.rect.push_back(IntRect(62*5, 0+1, 62, 62));
			walkright.rect.push_back(IntRect(62*6, 0+1, 62, 62));
			walkright.rect.push_back(IntRect(62*7, 0+1, 62, 62));
			walkright.rect.push_back(IntRect(62*8, 0+1, 62, 62));
			walkright.rect.push_back(IntRect(62*9, 0+1, 62, 62));

			
			

			walkleft.delay=0.1;
			walkleft.rect.push_back(IntRect(62*11,0,62,62));
			walkleft.rect.push_back(IntRect(62*12,0,62,62));
			walkleft.rect.push_back(IntRect(62*13,0,62,62));
			walkleft.rect.push_back(IntRect(62*14,0,62,62));
			walkleft.rect.push_back(IntRect(62*15,0,62,62));
			walkleft.rect.push_back(IntRect(0,62,62,62));
			
			
			
			
			
			
				
		}
		
		
		
		
		
		
		
		
		
		struct Jeep
		{
			ShiftData left;
			ShiftData turnleft;
			ShiftData turnright;
			ShiftData right;
			
			
			
			Jeep()
			{
				left.rect.push_back(IntRect(62*6, 62*7, 62, 62));
				left.rect.push_back(IntRect(62*7, 62*7, 62, 62));
				left.rect.push_back(IntRect(62*8, 62*7, 62, 62));
				left.rect.push_back(IntRect(62*7, 62*7, 62, 62));

				
				right.rect.push_back(IntRect(62*14, 62*6, 62, 62));
				right.rect.push_back(IntRect(62*15, 62*6, 62, 62));
				right.rect.push_back(IntRect(62*0, 62*7, 62, 62));
				right.rect.push_back(IntRect(62*15, 62*6, 62, 62));

				
				
				
				
			}
			
		}jeep;
		
		
		
		
		
		
		
		
		
			
	}shift;
	
	
	
	
	
	Vector2f now;
	
	int destination;
	float gravity = 0.2;
	Vector2f velocity;
	float speed;
	int ID;
	int haven=-1;
	int itemref = -1;
	bool busy = false;
	float idledelay = 0;
	std::string state = "right"; //direction
	std::string locomotion="walk"; //form of locomotion such as jeep,boat,walk
	
	Element carrying;
	std::string action="none"; // the action that blupi is currently trying to accomplish
	
	
	SoundBuffer say;
	
	
	
	
	
	
	
	void failed()
	{
		action="none";
		Stop();
		//say "I can't do it!"
		
		int a = rand()%3;
		
		
		sound[0].stop();
		
		if(a==0)
			say.loadFromFile("ASSETS/say/sound056.wav");
		
		if(a==1)
			say.loadFromFile("ASSETS/say/sound057.wav");
		
		if(a==2)
			say.loadFromFile("ASSETS/say/sound058.wav");
		
		
		sound[0].setBuffer(say);
		sound[0].play();
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	Blupi()
	{
		sprite.setTexture(textures.blupiblue);
		sprite.setTextureRect(IntRect(202+1,185+1,32,49));
		destination = sprite.getPosition().x;
		sprite.setScale(1.5,1.5);
		sprite.setOrigin(sprite.getTextureRect().width/2,sprite.getTextureRect().height);
		
		speed=2;
	
		
	}	
	
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	void checkmove()
	{

	
		if (state.find("move")!=std::string::npos)
		{
		    if (abs(destination - now.x) <= 5)
		    {
		        velocity.x = 0;
		        if(state =="moveleft")
					state = "left";
				if(state =="moveright")
					state = "right";
					
				now.x = destination; // Ensure exact position
		        
		    }
		}

		
	}
	
	
	
	

	
	
	
	
	
	
	
	
	
	void setBoundsOfRoomSides(Image &ground)
	{
		
		while(now.x <= 0)
		{
			state="right";
			now.x+=1;
			velocity.x=0;
		}
		while(now.x >= ground.getSize().x)
		{
			state="left";
			now.x-=1;
			velocity.x=0;
		}
		
	}
	
	
	
	
	
	
	
	void Stop()
	{
		
		action = "none";
		destination = now.x; 
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	bool possible(int dest)
	{
		//check if path can currently be completed
		
		int increment;
		bool condition;
		
		
		std::string dir;
		

		if(now.x > dest)
		{
			condition = true;
			dir = "left";
			increment = -1;	
		}
		else if (now.x < dest)
		{
			condition = true;
			increment = 1;
			dir = "right";	
		}
		else
		{
			return false;
		}
		
		
		
	
		for(int x=now.x; condition; x += increment)
		{
		
			if(dir == "left")
			{
				condition = (x > dest);
			}
			else
			{
				condition = (x < dest);
			}

			//std::cout << x << "," << groundedge[x] << std::endl;
			
			
			if(water.image.getPixel(x,groundedge[x])!=Color::Transparent)
			{
				
				
				//get deepness
				
				int index=-1;
				for(int a=0; a < water.puddle.size(); a++)
				{
					int left = water.puddle[a].left;	
					int right = water.puddle[a].right;	
					
					if(x > left && x < right)
					{
						index = a;
						break;
					}	
				}
				
				if(index==-1)
				{
					std::cout <<"failed to get index"<<std::endl;
					break;
				}
				int deep = groundedge[x] - water.puddle[index].pos.y;
				
				std::cout << x << ":" << deep << std::endl; 
				
				
				
				
				
				
				if(deep > 40)
				{
					if(locomotion != "boat")
					{
						return false;
					}
				}
			}
			
			
			
			
			
			
			for(int a=0; a < element.size(); a++)
			{
				if(element[a].type == "wall" && element[a].now.x == x)
				{
					return false;
				}
			}
			
			
			
		}
		return true;

	}
	
	
	
	bool traveled()
	{
		
		
		
		if(destination == now.x)
			return true;
		
		return false;
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	int itemindex = -1;
	
	
	void doAction(Image &ground)
	{
		if(action=="none")
			return;
		
		
		
		
		
		if(action == "stop")
			Stop();
		
		
		
		
		
		
		if(traveled())
		{
		
		
			if(action=="haven")
			{
				if(locomotion=="walk")
				{
					if(!element[itemindex].burning)
					{
						haven=itemindex;
						element[itemindex].boolean[0]=true;
				
					}
					else
						failed();
					action="none";
				}
				else
					failed();
			}
			
			
			
			
			
			
			if(action=="drive")
			{
				if(!element[itemindex].burning)
				{
					locomotion = element[itemindex].type;
					element[itemindex].active=false;
					itemref = itemindex;
					speed = 5;
				}
				else
					failed();
					
				action="none";	
			}
			
			
			if(action=="stop drive")
			{
				element[itemref].now = now;
				element[itemref].active=true;
				locomotion = "walk";	
				action="none";
				speed = 2;
			}
			
			
			
			
			
			if(action=="make shed")
			{
				Element newelement;
				element[itemindex] = newelement;
				
				element[itemindex].ID = itemindex;
				element[itemindex].type="shed";
				element[itemindex].sprite.setTextureRect(IntRect(0,438,127,95));
				
				
			}
			
			
			
			
			if(action=="pick up")
			{
				if(state=="moveleft")
					state="left";
				if(state=="moveright")
					state="right";
				
				
				busy=true;
				
				
				
				static bool bounceobject=false;
				
				if(state.find("move")!=std::string::npos)
				{
					
					if(!bounceobject)
					{
						//bounce item up
						
						if(checkGroundNow(ground,now))
						{
							if(velocity.y<=0)
								velocity.y=-5;
							else
							{
								velocity.y=0;
								bounceobject=true;
							}
							sprite.setTextureRect(IntRect(66,846,33,60));
						}
						else
						{
							sprite.setTextureRect(IntRect(108,91,37,43));
						}
					}
				}
			
				
			}
			
			
			if(action=="blow up")
			{
				//bring out hammer and slam bomb to detonate it.
			}
			
			
			
			if(action=="leave haven")
			{
				haven=-1;
				element[itemindex].boolean[0]=false;
			}
			
			action = "none";
		}
			
		
		
	}
	
	
	
	
	
	
	void Idle(ShiftData &idle,ShiftData &blink = emptyshift)
	{
		
		
		if(&blink != &emptyshift)
		{
			
		
		
			idledelay += seconds(1.f/60.f).asSeconds();
			
			if(idledelay > 5)
			{
				sprite.setTextureRect(Shift(blink));
				if(blink.ended)
				{
					idledelay=0;
					blink.ended = false;
				}
			}
			else
			{
				//fidget animation
				sprite.setTextureRect(Shift(idle));
				
			}	
		}
		else
		{
			//fidget animation
			sprite.setTextureRect(Shift(idle));
		}
		
	}
	
	
	

	void updateShifts()
	{
		
		if(locomotion=="walk")
		{
			if(state == "left")
				Idle(shift.idleleft,shift.blinkleft);
			else if(state == "right")
				Idle(shift.idleright,shift.blinkright);
			else
				idledelay = 0;
		
		
			if(state == "moveleft")
				sprite.setTextureRect(Shift(shift.walkleft));
			
			if(state == "moveright")
				sprite.setTextureRect(Shift(shift.walkright));
		
		}
		
		
		if(locomotion=="jeep")
		{
			if(state=="left" || state == "moveleft")
				sprite.setTextureRect(Shift(shift.jeep.left));
			
			if(state=="right"|| state == "moveright")
				sprite.setTextureRect(Shift(shift.jeep.right));
		
		
		
		}
		
		
		
		
		
		
		

		if(state == "blow up")
		{
			//Shift(shift.blowup);
		}
		
		
		
		
			
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	void checkSelfClicks(Image &ground)
	{
		
		if(sprite.getGlobalBounds().contains(MPosition))
		{
			static bool released=false;
			
			if(Mouse::isButtonPressed(Mouse::Left))
			{
				if(released)
				{
					
					if(toplayer.type=="blupi" && toplayer.ID == ID)
					{
					
						selected = toplayer.ID;
				
						int b = rand()%5;
						
						if(sound[0].getStatus()!=Sound::Status::Playing)
						{
							if(b == 0)
								say.loadFromFile("ASSETS/say/sound002.wav");
							if(b == 1)
								say.loadFromFile("ASSETS/say/sound003.wav");
							if(b == 2)
								say.loadFromFile("ASSETS/say/sound004.wav");
							if(b == 3)
								say.loadFromFile("ASSETS/say/sound005.wav");
							if(b == 4)
								say.loadFromFile("ASSETS/say/sound006.wav");
							sound[0].stop();
							sound[0].setBuffer(say);
							sound[0].play();
						}
			
					
					
					
						
					
						if(!busy)
						{
						
							if(locomotion!="walk")
							{
								if(!checkGroundNow(ground,now))
								{
									
								}
								else
								{
									iconrect.clear();
									buttons.clear();
									buttons.push_back("stop drive");
									
									
								}
							}
						}
					}
				}
				
				released=false;
			}
			else
				released=true;
			
		}
		
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	void update(Image &ground)
	{
		
	
		
		
		
		sprite.setOrigin(sprite.getTextureRect().width/2,sprite.getTextureRect().height/2);
		
		if(haven==-1)
		{
		
			sprite.setPosition(now.x,now.y - 35);
		
			
			Gravity(sprite,ground,velocity,now,gravity); // apply gravity and resolve collisions.
			
			
			
			
			sprite.setRotation(getGroundAngle(ground,now.x,sprite.getRotation() ,10));
		
			
		
			destination = (int)destination;
			
			if(checkGroundNow(ground,now))
			{
				
				if (!busy)
				{    
				    if (state.find("move") == std::string::npos)//if move not found
				    {
				        if (abs(destination - now.x) > 5)
				        {
				            if (destination < now.x)
				            {
				                velocity.x = -speed;
				                state = "moveleft";
				                action = "move";
				            }
				            else if (destination > now.x)
				            {
				                velocity.x = speed;
				                state = "moveright";
				                action = "move";
				            }
				        }
				    }        
				}
	
	
			}
			
			
			
			
			setBoundsOfRoomSides(ground);
			
			checkmove();
			
			
			updateShifts();
			
			
			
			
			
			
		
			
			
			
	
		}
		
		doAction(ground);
			
			
		checkSelfClicks(ground);	
			
			
//		if(liveitem==-1)
//		{
//			buttons.clear();
//			buttons.push_back("stop");
//		}	
		
	}
	
	void draw(RenderWindow &window)
	{
		
		if(selected == ID)
		{
			
		}
		
		if(haven==-1)
		{
		
			carrying.sprite.setPosition(sprite.getPosition().x,sprite.getPosition().y - (sprite.getTextureRect().height - (sprite.getTextureRect().height/16)));
			
			window.draw(sprite);
		}
		else
		{
			now = element[haven].now;
			
			destination = now.x;
			sprite.setRotation(element[haven].sprite.getRotation());
			sprite.setPosition(element[haven].now.x -15,element[haven].now.y - 62);
			sprite.setTextureRect(IntRect(137,8,29,27));
			
			window.draw(sprite);
		}
		
		
	}
	
};

std::vector<Blupi> blupi;