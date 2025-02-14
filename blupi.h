



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
		
		
		
		
		
		struct Boat
		{
			ShiftData left;
			ShiftData right;
			ShiftData exit;
			ShiftData enter;
			
			
			
			Boat()
			{
				
				
				
				left.delay = 0.25;
				left.rect.push_back(IntRect(62*13,62*27,62,62));
				left.rect.push_back(IntRect(62*14,62*27,62,62));
				left.rect.push_back(IntRect(62*15,62*27,62,62));
				left.rect.push_back(IntRect(62*14,62*27,62,62));
				
				
				right.delay = 0.25;
				right.rect.push_back(IntRect(62*7,62*27,62,62));
				right.rect.push_back(IntRect(62*8,62*27,62,62));
				right.rect.push_back(IntRect(62*9,62*27,62,62));
				right.rect.push_back(IntRect(62*8,62*27,62,62));
				
				
				
		
				
			}
			
			
			
		}boat;
		
		
		
			
	}shift;
	
	
	
	
	
	Vector2f now;
	
	std::string color;
	
	Vector2f destination;
	Vector2f ldestination;
	float rotation = 0;
	float gravity = 0.2;
	Vector2f velocity;
	Vector2f lvelocity;
	float speed;
	int maxjumpdist = -1;
	int jumpvelo = -10;
	int ID;
	int haven=-1;
	int itemref = -1;
	bool busy = false;
	float idledelay = 0;
	std::string state = "right"; //direction
	std::string lstate;
	std::string locomotion="boat"; //form of locomotion such as jeep,boat,walk
	std::string llocomotion;
	Element carrying;
	std::string action="none"; // the action that blupi is currently trying to accomplish
	std::string laction;
	
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
		destination = sprite.getPosition();
		sprite.setScale(1.5,1.5);
		sprite.setOrigin(sprite.getTextureRect().width/2,sprite.getTextureRect().height);
		
		speed=2;
	
		
	}	
	
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	void checkmove()
	{

	
		if (state.find("move")!=std::string::npos)
		{
		    if (abs(destination.x - now.x) <= 5)
		    {
		        velocity.x = 0;
		        if(state =="moveleft")
					state = "left";
				if(state =="moveright")
					state = "right";
					
				now.x = destination.x; // Ensure exact position
		        
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
		destination.x = now.x; 
		destination.y = now.y;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	bool possible(Vector2f dest)
	{
		//check if path can currently be completed
		
		int increment;
		bool condition;
		
		
		std::string dir;
		

		if(now.x > dest.x)
		{
			condition = true;
			dir = "left";
			increment = -1;	
		}
		else if (now.x < dest.x)
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
				condition = (x > dest.x);
			}
			else
			{
				condition = (x < dest.x);
			}

			
			
		
				
			
			//get deepness
			
			int index = water.getPuddleIndex(x);
			
			if(index==-1)
			{
				break;
			}
			
			int deep=0;
			if(x >= 0 && x < water.width)
				deep = groundedge(x,water.puddle[index].pos.y) - water.puddle[index].pos.y;
			
				
				
			float destwidth = water.puddle[index].right - water.puddle[index].left;	
				
				
				
			if(deep > 20)
			{
				if(locomotion=="walk")
				{
					if(destwidth > maxjumpdist)
					{
						return false;
					}
				}
				else
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
		
		
		
		if(destination.x == now.x)
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
		
		
		if(locomotion=="boat")
		{
			if(state=="left" || state == "moveleft")
				sprite.setTextureRect(Shift(shift.boat.left));
			
			if(state=="right"|| state == "moveright")
				sprite.setTextureRect(Shift(shift.boat.right));
			
			
		
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
						if(color!=UserColor)
						{
							say.loadFromFile("ASSETS/say/sound056.wav");
							sound[0].stop();
							sound[0].setBuffer(say);
							sound[0].play();
						}
						else
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
				}
				
				released=false;
			}
			else
				released=true;
			
		}
		
	}
	
	
	
	
	
	
	
	
	
	
	void updatePhysics(Image &ground)
	{
		if(locomotion=="walk")
		{
			gravity = 0.2;
			
			int x = now.x;
			int index = water.getPuddleIndex(x);
			
			if(index!=-1)
			{
				
				
				
				
				int deep=0;
				if(x >= 0 && x < water.width)
					deep = groundedge(x,now.y) - water.puddle[index].pos.y;
				
				
				if(deep > water.depthlimit)
				{
				
					if(now.y > water.puddle[index].pos.y-20)
					{
					
				
						if(water.puddle[index].left!=-1)
						{
						
							int middle = water.puddle[index].left + ((water.puddle[index].right-water.puddle[index].left)/2/*width*/);//left + half-width
							
							if(now.x > middle)
							{
								now.x += (water.puddle[index].right - now.x)/20;
								Stop();
							}
							else
							{
								Stop();
								now.x -= (now.x - water.puddle[index].left)/20;
							}
						}
					}
				}
				
			}


			if(ID==selected)
			{
				if(Keyboard::isKeyPressed(Keyboard::Up))
				{
					if(checkGroundNow(ground,now))
					{	
						velocity.y = jumpvelo;
					}
				}
			}
			
			Gravity(sprite,ground,velocity,now,gravity); // apply gravity and resolve collisions.
			if(checkGroundNow(ground,now))
				rotation = getGroundAngle(ground,now,sprite.getRotation() ,10);
			










			//get distance of a jump
			if(maxjumpdist==-1)
			{
				Vector2f v;
				Vector2f p;
				v.x=speed;
				v.y=jumpvelo;
				p.x=0;
				p.y=0;
				
				for(int future=0;future < 1000; future++)
				{
					
					
					p.y+=v.y;
					p.x+=v.x;
					v.y+=gravity;
					
					if(p.y >= 0)
					{
						maxjumpdist = p.x;
						break;
					}
						
				}
			}




			
			
		}
		if(locomotion=="boat")
		{
			now.x += velocity.x;
			
			
			int x = now.x;
			int index = water.getPuddleIndex(x);
			
			
			if(index==-1)
			{
				locomotion="walk";
				//leave boat there
				//element[itemref].now.x = now.x;
				//element[itemref].active=true;
				
			}
			else
			{
				
				int deep=0;
				if(x >= 0 && x < water.width)
					deep = groundedge(x,water.puddle[index].pos.y) - water.puddle[index].pos.y;
			
				int x2 = now.x - water.puddle[index].left;
				
				if(x2 >= 0 && x2 < water.puddle[index].linepos.size())
				{
					now.y = water.puddle[index].linepos[x2].y;
				}
				
				
				
			}
			
			rotation = -velocity.x*3;
				
		}
		
		
		
		
		
	}
	
	
	
	
	
	void update(Image &ground)
	{
		
	
		
		
		sprite.setOrigin(sprite.getTextureRect().width/2,sprite.getTextureRect().height/2);
		
		if(haven==-1)
		{
		
			sprite.setPosition(now.x,now.y - 35);
		
		
		
			if(isHost)
			{
			
				updatePhysics(ground);
			
			
			
			
			
			
			
			
			
			
			
				
				
				
				
				
				
				
				
				

			    if (!busy)
			    {
			        // Check if destination is far enough to start moving
			        if (std::abs(destination.x - now.x) > 5) // Adjust threshold as needed
			        {
			            if (destination.x < now.x)
			            {
			            	state = "moveleft";
							action = "move";
							velocity.x = -speed;
						
			            }
			            else if (destination.x > now.x)
			            {
		            		state = "moveright";
							action = "move";
							velocity.x = speed;
					    
			            }
			        }
			    }			
				
			
			
				setBoundsOfRoomSides(ground);
					
				checkmove();	
			
			}
			
			sprite.setRotation(rotation);
			
			
			updateShifts();
			
			
			
		
			
			
			
	
		}
		
		doAction(ground);
			
		checkSelfClicks(ground);	
			
	
		
		
		
		
		
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
			
			destination.x = now.x;
			sprite.setRotation(element[haven].sprite.getRotation());
			sprite.setPosition(element[haven].now.x -15,element[haven].now.y - 62);
			sprite.setTextureRect(IntRect(137,8,29,27));
			
			window.draw(sprite);
		}
		
		
	}
	
};

std::vector<Blupi> blupi;