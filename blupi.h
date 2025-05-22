



class Blupi
{
	public:
	
	Sprite sprite;
	Sprite carrying;
	
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
			
			
			
			blowup.delay = 0.15;
			blowup.rect.push_back(IntRect(0,1798,130,80));
			blowup.rect.push_back(IntRect(130,1798,130,80));
			blowup.rect.push_back(IntRect(130*2,1798,130,80));
			blowup.rect.push_back(IntRect(130*3,1798,130,80));
			blowup.rect.push_back(IntRect(130*4,1798,130,80));
			blowup.rect.push_back(IntRect(130*5,1798,130,80));
			
			
			
			
				
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
	float rotation = 0;
	float gravity = 0.2;
	Vector2f velocity;
	float speed;
	int maxjumpdist = -1;
	int jumpvelo = -10;
	int ID;
	int haven=-1;
	int itemref = -1;
	bool busy = false;
	bool alive = true;
	float idledelay = 0;
	std::string state = "right"; //direction
	std::string locomotion="walk"; //form of locomotion such as jeep,boat,walk
	std::string action="none"; // the action that blupi is currently trying to accomplish
	std::string keyinput="none";
	
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
		busy=false;
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
			return true;
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
						
						bool istrue = false;
						for(int a=0;a<element.size();a++)
						{
							if(element[a].type=="boat")
							{
								if(element[a].active)
								{
									istrue=true;
								}
							}
						}
						
						if(!istrue)
						{
							return false;
						}
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
		{
			return true;
		}
		return false;
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	int itemindex = -1;
	std::string liveAction="none";
	
	void doAction(Image &ground)
	{
		if(action=="none")
			return;
		
		
		
		
		
		if(action == "stop")
			Stop();
		
		
		
		
		
		
		if(traveled())
		{
		
			
			
			if(action == "grow")
			{
				busy=true;
				
				
				
				//steps in growing tomatoes
				
				//1: blupi is busy
				//2: goto position
				//3: choose position slightly beside blupi on a random side.
				//4: create "plant" element
				//5: itemIndex becomes reference to the newly created element. 
				//6: use growing tomato Shift Mode for blupi (digging,then watering)
				//7: use growing tomato Shift Mode for element (stages of growth(includes preparing ground))
				//8: both blupi and tomato animate using Shift Modes at the same time
				//9: When tomato reaches last frame, blupi is no longer busy and tomato is of type "tomato"
				
				
				growDirect = 0;
				growLeftPath=true;
				growRightPath=true;
				liveAction = action;

			}
			
			
			if(action=="haven")
			{
				if(locomotion=="walk" && haven==-1 && element[itemindex].boolean[0]!=true)
				{
					if(!element[itemindex].burning)
					{
						locomotion="house";
						speed=0;
						haven=itemindex;
						element[itemindex].boolean[0]=true;
						element[itemindex].blupiIndex = ID;
						sayDone();
					}
					else
						failed();
					action="none";
				}
				else
					failed();
				
			}
			
			
			
			if(action=="leave haven")
			{
				locomotion="walk";
				speed=2;
				element[haven].boolean[0]=false;
				element[haven].blupiIndex=-1;
				haven=-1;
				sayDone();
			}
			
			
			
			
			if(action=="drive")
			{
				if(!element[itemindex].burning)
				{
					locomotion = element[itemindex].type;
					element[itemindex].active=false;
					itemref = itemindex;
					speed = 5;
					sayDone();
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
				sayDone();
			}
			
			
			
			
			
			if(action=="make shed")
			{
				Element newelement;
				element[itemindex] = newelement;
				
				element[itemindex].ID = itemindex;
				element[itemindex].type="shed";
				element[itemindex].sprite.setTextureRect(IntRect(0,438,127,95));
				
				//for things that take time once blupi is there, have a busy status while working on it.
				sayDone();
			}
			
			
			
			
			if(action=="pick up")
			{
				liveAction = action;			
			}
			
			if(action == "drop")
			{
				element[carryref].active=true;
				element[carryref].now = carrying.getPosition();
				element[carryref].velocity.y = jumpvelo/(jumpvelo*0.90);
				Sprite newsprite;
				carrying = newsprite;
				action = "none";
			}
			
			if(action=="blow up")
			{
				//bring out hammer and slam bomb to detonate it.
				if(now.x != element[itemindex].now.x)
				{
					state = "blow up";
					
					//for things that take time once blupi is there, have a busy status while working on it.
					
					
				}
				else
				{
					
					if(now.x - 50 > 0)
					{
						destination.x = now.x-50;
					}
					else
					{
						destination.y = now.x+50;
					}
					busy=true;
					return;
				}
			}
			
			action = "none";
		}
			
		
		
	}
	
	
	
	
	
	

	

	
	
	
	int firstGrab = 0;
	int carryref = 0;
	int setupGrowth = 0;
	int growDirect = -1;
	bool growLeftPath = true;
	bool growRightPath = true;
	
	void UpdateActions(sf::Image &ground)
	{
		if(liveAction == "grow")
		{
		
		
		
			if(traveled() || destination.x == now.x)
			{
	
				if(setupGrowth == 0)
				{
					
					if(growDirect == 0)
					{
					
						int direct = rand()%100;
						
						if(direct < 50)
						{
							growDirect = -1;
						}
						else
						{
							growDirect = 1;
						}
					}
	
					destination.x = now.x + (growDirect * 50);


					setupGrowth = 1;
					
					return;
				}	
				
				if(setupGrowth == 1)
				{
					
					int x=now.x;
					
					x = now.x + (element[itemindex].sprite.getTextureRect().width * growDirect);
					
					if(x < 0)
					{
						growDirect = !growDirect;
						growLeftPath=false;
						return;
					}
					if(x >= ground.getSize().x)
					{
						growRightPath=false;
						growDirect = !growDirect;
						return;
					}
					
					int index = water.getPuddleIndex(x);
					if(index!=-1)
					{
						if(growDirect == -1)
							growLeftPath = false;
						else
							growRightPath = false;
						growDirect = !growDirect;
						
						return;
					}
					
					
					if(!growLeftPath && !growRightPath)
					{
						failed();
						Stop();
						return;
					}







					


					
					
					for(int a=0;a<element.size();a++)
					{
						if(element[a].type == "tomato" || element[a].type == "bomb" || element[a].type == "wood")
						{
						
							if(element[a].sprite.getGlobalBounds().contains(x,element[a].sprite.getPosition().y))
							{
								destination.x = now.x - (50 * growDirect);	
								return;
							}
						}
					}
					
					Element newelement;
					
					newelement.type = "plant";
					newelement.sprite.setTexture(textures.element);
					
					newelement.sprite.setTextureRect(newelement.shift.grow.rect[0]);
					newelement.averageHeight = newelement.sprite.getTextureRect().height;

					element.push_back(newelement);
					
					itemindex = element.size()-1;
					
					element[itemindex].now = sf::Vector2f(x + (growDirect * 50),now.y);
					if(element[itemindex].now.x > now.x)
						state = "right";
					else
						state = "left";	
					setupGrowth = 2;
				}

				element[itemindex].sprite.setTextureRect(Shift(element[itemindex].shift.grow));
				int size = element[itemindex].shift.grow.rect.size();
				if(element[itemindex].sprite.getTextureRect() == element[itemindex].shift.grow.rect[size-1])
				{
					element[itemindex].type = "tomato"; 
					element[itemindex].sprite.setTextureRect(IntRect(67,153,51,39)); //tomato rect
					element[itemindex].averageHeight = element[itemindex].sprite.getTextureRect().height;
					itemindex=-1;					
					setupGrowth = 0;
				}
			}
			

				
		}
		
		if(liveAction == "pick up")
		{
			if(locomotion == "walk")
			{
				if(firstGrab == 0)
				{
					
					velocity.y = jumpvelo/2;
					firstGrab++;
				}
				else
				{
					if(checkGroundNow(ground,now) && checkGroundNow(ground,element[itemindex].now))
					{
						if(element[itemindex].velocity.y >=0)
						{
							firstGrab++;
							element[itemindex].velocity.y = jumpvelo/1.2;
						}
					}
			
					if(firstGrab == 2)
					{
						if(element[itemindex].now.y < now.y - sprite.getTextureRect().height)
						{
							firstGrab++;
						}
					}
					if(firstGrab == 3)
					{
						if(element[itemindex].now.y >= now.y - sprite.getTextureRect().height)
						{
							firstGrab = 0;
							element[itemindex].active = false;
							carrying = element[itemindex].sprite;
							action = "none";
							liveAction = "none";
							carryref = itemindex;
				
						}
					}
			
				}	
				
				
			}
			else if(carrying.getTextureRect().width==0)
			{
				firstGrab = 0;
				carryref = 0;
			}
			
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
			
			bool faceLeft = false;
			if(element[itemindex].now.x < now.x)
				faceLeft = true;
			
			sprite.setTextureRect(Shift(shift.blowup));
			
			
			if(faceLeft)
				sprite.setScale(-1.5,1.5);
			else
				sprite.setScale(1.5,1.5);
					
			
			if(shift.blowup.ended)
			{
				busy=false;
				element[itemindex].boolean[0]=true;
				alive = false;
				sayDone();
				buttons.clear();
				iconrect.clear();
			}
		}
		
		
		
		
			
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	void checkSelfClicks(Image &ground)
	{
	
		FloatRect bounds = sprite.getGlobalBounds();
		
		bounds.left +=20;
		bounds.width -=40;
		bounds.top +=20;
		bounds.height -=20;
		
		
		if(bounds.contains(MPosition))
		{
			static bool released=false;
			
			if(Mouse::isButtonPressed(Mouse::Left))
			{
				if(released)
				{
					
					
					if(color!=UserColor)
					{
						say.loadFromFile("ASSETS/say/sound075.wav");
						sound[0].stop();
						sound[0].setBuffer(say);
						sound[0].play();
					}
					
					if(topBlupi.ID == ID)
					{
						
						if(color==UserColor)
						{
						
							
							player[ME].selected = ID;
					
							int b = rand()%3;
							
							
								
								
							
							if(b == 0)
								say.loadFromFile("ASSETS/say/sound002.wav");
							if(b == 1)
								say.loadFromFile("ASSETS/say/sound003.wav");
							if(b == 2)
								say.loadFromFile("ASSETS/say/sound004.wav");
							sound[0].stop();
							sound[0].setBuffer(say);
							sound[0].play();
						
						
						
						
							
						
							
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
	
	
	
	
	
	
	
	
	void sayDone()
	{
		if(color == UserColor)
		{
		
			int b = rand()%3;
			
			
				
				
			if(sound[0].getStatus()!=Sound::Status::Playing)
			{
				if(b == 0)
					say.loadFromFile("ASSETS/say/sound008.wav");
				if(b == 1)
					say.loadFromFile("ASSETS/say/sound009.wav");
				if(b == 2)
					say.loadFromFile("ASSETS/say/sound010.wav");
				sound[0].stop();
				sound[0].setBuffer(say);
				sound[0].play();
			}
		}
	}
	
	
	
	
	
	
	void sayObey()
	{
		if(color == UserColor)
		{
		
			int b = rand()%3;
			
			
				
				
			if(sound[0].getStatus()!=Sound::Status::Playing)
			{
				if(b == 0)
					say.loadFromFile("ASSETS/say/sound005.wav");
				if(b == 1)
					say.loadFromFile("ASSETS/say/sound006.wav");
				if(b == 2)
					say.loadFromFile("ASSETS/say/sound007.wav");
				sound[0].stop();
				sound[0].setBuffer(say);
				sound[0].play();
			}
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
					
						
						for(int a=0;a<element.size();a++)
						{
							if(element[a].type=="boat")
							{
								if(element[a].active)
								{
								
									int width = (element[a].sprite.getTextureRect().width * 0.85);
									
									if(element[a].now.x==water.puddle[index].left + width)
									{
										locomotion = "boat";
										element[a].active=false;
										speed = 3;
										itemref = a;
										now.x = element[a].now.x;
										break;
									}
								}
							}
						}
						
						
						
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


			if(ID==player[ME].selected)
			{
				if(keyinput=="up")
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
				int width = (element[itemref].sprite.getTextureRect().width * 0.85);
				element[itemref].now.x = now.x + width;
				element[itemref].active=true;
				speed = 2;
				itemref=-1;
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
		
			
			
			
			if(Keyboard::isKeyPressed(Keyboard::Up))
			{
				keyinput="up";
			}
			else
			{
				keyinput="none";
			}
			
			
			
			
			
			
		
			if(isHost)
			{
			
				updatePhysics(ground);
			
			
				Vector2f carryLocalPos(30,2);
				Vector2f carryWorldPos = sprite.getTransform().transformPoint(carryLocalPos);
				carrying.setPosition(carryWorldPos);
				carrying.setRotation(rotation);
				
			
			
			
			
			
			
			
			
			
				
				
				
				
				
				
				
				
				

		        // Check if destination is far enough to start moving
		        if (std::abs(destination.x - now.x) > 5) // Adjust threshold as needed
		        {
		            if (destination.x < now.x)
		            {
		            	state = "moveleft";
						velocity.x = -speed;
					
		            }
		            else if (destination.x > now.x)
		            {
	            		state = "moveright";
						velocity.x = speed;
				    
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
			
	
		UpdateActions(ground);
		
		
		
		bool dropfound=false;
		for(int z=0;z<buttons.size();z++)
		{
			if(buttons[z]=="drop")
			{
				dropfound=true;
				break;
			}
		}
		
		if(!dropfound && carrying.getTextureRect().width!=0)
		{
			buttons.push_back("drop");
			iconrect.push_back(sf::IntRect(42,240,40,40));			
		}
		
	}
	
	void draw(RenderWindow &window)
	{
		
		if(player[ME].selected == ID)
		{
			
		}
		
		if(haven==-1)
		{
		
			
			window.draw(sprite);
			
			
			window.draw(carrying);
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