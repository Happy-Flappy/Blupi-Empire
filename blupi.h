



class Blupi
{
	public:
	
	Sprite sprite;
	Sprite carrying;
	Sprite icon;
	Sprite energyBar;
	
	
	
	
	//SHIFT MODES
	
	struct ShiftModes
	{
		
		
		ShiftData walkleft;
		ShiftData walkright;
		ShiftData idleleft;
		ShiftData idleright;
		ShiftData blinkleft;
		ShiftData blinkright;
		ShiftData tiredidleleft;
		ShiftData tiredidleright;
		ShiftData tiredwalkleft;
		ShiftData tiredwalkright;
		
		
		ShiftData blowup; 
		ShiftData water;
		ShiftData eatL,eatR;
		
		
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
			
			
			
			
			
			
			
			//tired animations
			
			
			tiredwalkleft.delay = 0.15;
			tiredwalkleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});
			tiredwalkleft.rect.push_back({0 + (60 * 1),1798 + (60 * 3),60,60});
			tiredwalkleft.rect.push_back({0 + (60 * 2),1798 + (60 * 3),60,60});
			tiredwalkleft.rect.push_back({0 + (60 * 3),1798 + (60 * 3),60,60});
			
			tiredwalkright.delay = 0.15;
			tiredwalkright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredwalkright.rect.push_back({0 + (60 * 1),1798 + (60 * 4),60,60});
			tiredwalkright.rect.push_back({0 + (60 * 2),1798 + (60 * 4),60,60});
			tiredwalkright.rect.push_back({0 + (60 * 3),1798 + (60 * 4),60,60});	
			


			tiredidleleft.delay = 0.1;
			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 3),60,60});

			tiredidleleft.rect.push_back({0 + (60 * 0),1798 + (60 * 0),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 1),1798 + (60 * 0),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 2),1798 + (60 * 0),60,60});
			tiredidleleft.rect.push_back({0 + (60 * 3),1798 + (60 * 0),60,60});


			tiredidleright.delay = 0.1;
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 4),60,60});
						
			tiredidleright.rect.push_back({0 + (60 * 0),1798 + (60 * 1),60,60});
			tiredidleright.rect.push_back({0 + (60 * 1),1798 + (60 * 1),60,60});
			tiredidleright.rect.push_back({0 + (60 * 2),1798 + (60 * 1),60,60});
			tiredidleright.rect.push_back({0 + (60 * 3),1798 + (60 * 1),60,60});
			
			
			
			//<><>><><><><><><><><
			
			
			
			
			
			
			
			
			
			
			
			
			blowup.delay = 0.15;
			blowup.rect.push_back(IntRect(0,1798,130,80));
			blowup.rect.push_back(IntRect(130,1798,130,80));
			blowup.rect.push_back(IntRect(130*2,1798,130,80));
			blowup.rect.push_back(IntRect(130*3,1798,130,80));
			blowup.rect.push_back(IntRect(130*4,1798,130,80));
			blowup.rect.push_back(IntRect(130*5,1798,130,80));
			
			
			water.rect.push_back(IntRect(240,1798,62,62));
			water.rect.push_back(IntRect(240+62,1798,62,62));





			eatR.delay = 0.15;
			eatR.rect.push_back({62*1,62*2,62,62});
			eatR.rect.push_back({62*2,62*2,62,62});
			eatR.rect.push_back({62*3,62*2,62,62});
			eatR.rect.push_back({62*2,62*2,62,62});
			eatR.rect.push_back({62*3,62*2,62,62});
			eatR.rect.push_back({62*2,62*2,62,62});
			eatR.rect.push_back({62*3,62*2,62,62});
			eatR.rect.push_back({62*2,62*2,62,62});
			eatR.rect.push_back({62*3,62*2,62,62});
			


			eatL.delay = 0.15;
			eatL.rect.push_back({62*4,62*2,62,62});
			eatL.rect.push_back({62*5,62*2,62,62});
			eatL.rect.push_back({62*6,62*2,62,62});
			eatL.rect.push_back({62*5,62*2,62,62});
			eatL.rect.push_back({62*6,62*2,62,62});
			eatL.rect.push_back({62*5,62*2,62,62});
			eatL.rect.push_back({62*6,62*2,62,62});
			eatL.rect.push_back({62*5,62*2,62,62});
			eatL.rect.push_back({62*6,62*2,62,62});
			

				
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
	bool startstop = false;
	bool alive = true;
	bool running = true;
	float idledelay = 0;
	float scale = 1.5;//1.5
	float energy = 100;
	float workEnergyLoss = 0.02;
	double walkEnergyLoss = 0.01;
	std::string state = "right"; //direction
	std::string locomotion="walk"; //form of locomotion such as jeep,boat,walk
	std::string action="none"; // the action that blupi is currently trying to accomplish
	std::string keyinput="none";
	
	
	
	
	





	void sayFailed()
	{
	
		
		int a = rand()%4;
		
		
		a+=18;//so that it will find the correct index
		
		
		wav.playSound(a,now.x);
		
	}





	void failed()
	{
		Stop();
		sayFailed();
	}
	
	
	
	
	
	
	
	
	
	
	
	
	Blupi()
	{
		sprite.setTexture(textures.blupiblue);
		sprite.setTextureRect(IntRect(202+1,185+1,32,49));
		destination = sprite.getPosition();
		sprite.setScale(scale,scale);
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
		action="none";
		destination.x = now.x; 
		destination.y = now.y;
	}
	
	
	
	
	
	
	float processTime = 0;
	
	
	bool enoughEnergy(float time,float energyLossPerFrame)
	{
		
		float lossPerSecond = energyLossPerFrame * 60;
		
		float lossAmount = lossPerSecond * time;
		return (lossAmount < energy);
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
				deep = groundEdge[x] - water.puddle[index].pos.y;
			
				
				
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
		
		if(locomotion == "sick" || locomotion == "tired")
		{
		
			//averageDistancePerFrame: speed;
			float totalFrames = abs(destination.x - now.x)/speed;    
			
			float timePerFrame = 1.f/60.f;
			
			float totalSeconds = totalFrames * timePerFrame;
			
			if(!enoughEnergy(totalSeconds,walkEnergyLoss))
				return false;
			
			
			
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
	int plantindex = -1;
	bool initAction=true;
	int firstGrab = 0;
	int carryref = 0;
	int channel = -1;
		
	void doAction(Image &ground) //the initialization function for starting actions
	{
		if(action=="none")
			return;
		
		
		
		
		
		
		if(initAction)
		{
			busy=true;
			startstop=false;
			
		}
		
		
		
		
		
		
		
		
		if(action!="stop drive"&&action!="drop" && action!="eat"&&itemindex!=-1)
		{
			if(initAction)
			{
			
				destination = element[itemindex].now;
				if(now.x < element[itemindex].now.x)
				{
					state = "moveright";
				}
				if(now.x > element[itemindex].now.x)
				{
					state = "moveleft";
				}
			}
		}
		
		
		
		
		
		
		if(action == "eat")
		{
			if(initAction)
			{
				
				
				int right = element[itemindex].now.x - ((element[itemindex].sprite.getTextureRect().width/2) * element[itemindex].scale);
				int left = element[itemindex].now.x - ((element[itemindex].sprite.getTextureRect().width/2) * element[itemindex].scale);
				
				
				destination = element[itemindex].now;
				if(now.x < element[itemindex].now.x)
				{
					state = "moveright";
					destination.x = left;
				}
				if(now.x >= element[itemindex].now.x)
				{
					state = "moveleft";
					destination.x = right;
				}				
			}
		}
		
		
		
		
		
		
		
		
		
		
		bool usesEnergy = false;
		
		if(action == "grow")
		{
			usesEnergy = true;
		}
		
		if(locomotion == "sick" || locomotion == "tired")
		{
			if(usesEnergy)
			{	
				if(!traveled())
				{
					failed();
				}
				else
					startstop = true;
			}
		}
		
		
		
		
		
		
		
	
		
		
		
		if(traveled())
		{
		
		
		
		
		
		
		
		
		
		
			if(action == "grow")
			{
				initAction=false;	
				
				
				if(plantindex!=-1)
				{
					
					
					
					
					
					
					energy -= workEnergyLoss;
					
					
					sprite.setTextureRect(Shift(shift.water));
					element[plantindex].sprite.setTextureRect(Shift(element[plantindex].shift.grow));
					int size = element[plantindex].shift.grow.rect.size();
					
					
					
					
					
				
					
					if(element[plantindex].sprite.getTextureRect() == element[plantindex].shift.grow.rect[size-1])
					{
						element[plantindex].type = "tomato"; 
						element[plantindex].sprite.setTextureRect(IntRect(67,153,51,39)); //tomato rect
						element[plantindex].averageHeight = element[plantindex].sprite.getTextureRect().height;
						plantindex=-1;	
						if(startstop)
						{
							action="none";
							busy=false;
							startstop=false;
						}
					}
					
					
				}			
				else
				{
				
				
				
					
					processTime = element[itemindex].shift.grow.rect.size() * element[itemindex].shift.grow.delay;
					
					
					if(!enoughEnergy(processTime,workEnergyLoss))
					{
						failed();
					}
					else
					{
					
					
						state = "right";
						
						
						plantindex = CreateElement();
						
						element[plantindex].type = "plant";
						element[plantindex].sprite.setTexture(textures.element);
						
						element[plantindex].sprite.setTextureRect(element[plantindex].shift.grow.rect[0]);
						element[plantindex].averageHeight = element[plantindex].sprite.getTextureRect().height;
		
						
						element[plantindex].now = sf::Vector2f(now.x + 60,now.y);
		
						
						wav.playSound(101,now.x);			
					
					}
				}				
				
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			if(action=="enter haven")
			{
				if(initAction)
				{
				
					if(locomotion=="walk" && element[itemindex].boolean[0]!=true)
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
					initAction=false;
				}
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			if(action=="enter jeep" || action == "enter (placeholder)")
			{
				if(initAction)
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
					busy=true;
					initAction = false;
				}
			}			
			
			
			
			
			
			
			
			
			
			
			
			if(action=="pick up")
			{
				if(locomotion == "walk")
				{
					element[itemindex].taken=true;
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
								element[itemindex].taken=true;
								carrying = element[itemindex].sprite;
								carryref = itemindex;
								busy=false;
								action = "none";
								
							}
						}
				
					}	
					
				}
				else if(carrying.getTextureRect().width==0)
				{
					firstGrab = 0;
					carryref = 0;
					action="none";
					busy=false;
					failed();
				}						
			}
			
			
			
			










			if(action == "eat")
			{
				if(initAction)
				{
				
					if(state=="left" || state == "moveleft")
						state = "eatleft";
					if(state=="right"|| state == "moveright")
						state = "eatright";
					
					
					initAction = false;
				}
				
				
				if(energy < 100)
				{
					energy+=0.3;
					element[itemindex].taken=true;
					
					if(channel == -1)
						channel = wav.playSound(13,now.x,false);
					if(channel != -1)
					{
						wav.playSound(13,now.x,true,channel);
					}
				}
				else
				{
					energy = 100;
					element[itemindex].exists = false;
					channel = -1;
					action="none";
					busy=false;
					
					
					if(state=="eatleft")
						state = "left";
					if(state=="eatright")
						state = "right";
					
				}
			}


	




			
			
		}
		
		
		if(action=="exit haven")
		{
			if(initAction)
			{
			
				locomotion="walk";
				speed=2;
				element[haven].boolean[0]=false;
				element[haven].blupiIndex=-1;
				haven=-1;
				sayDone();
				action="none";
				busy=false;
				initAction=false;
			}
		}
		
		
		
		

		
		
		if(action=="exit jeep")
		{
			element[itemref].now = now;
			element[itemref].active=true;
			locomotion = "walk";	
			speed = 2;
			sayDone();
			busy=false;
			action="none";
		}
		
		
		
		
		
		
		
		
		
		
		if(action=="blow up")
		{
			if(traveled())
			{
				
				if(initAction)
				{
				
					busy=true;
					
					if(now.x - 50 > 0)
					{
						destination.x = now.x-50;
					}
					else
					{
						destination.x = now.x+50;
					}
					initAction=false;
				}
				else
				{
					state = "blow up";
					
				}
			}
			
			
		}

		
		
		
		
		
		
		
		
		
		if(action == "drop")
		{
			element[carryref].active=true;
			element[carryref].now = carrying.getPosition();
			element[carryref].velocity.y = jumpvelo/(jumpvelo*0.90);
			element[carryref].taken=false;
			Sprite newsprite;
			carrying = newsprite;
			action = "none";
			busy=false;
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
		



		if(locomotion=="tired" && (state == "moveleft" || state == "moveright" || state == "left" || state == "right") && action == "none" && !busy)
		{
			
			
			if(state == "left")
				sprite.setTextureRect(Shift(shift.tiredidleleft));
			else if(state == "right")
				sprite.setTextureRect(Shift(shift.tiredidleright));
			
		
		
			if(state == "moveleft")
				sprite.setTextureRect(Shift(shift.tiredwalkleft));
			
			if(state == "moveright")
				sprite.setTextureRect(Shift(shift.tiredwalkright));
		
		}








		if(locomotion == "sick")
		{
			sprite.setColor(sf::Color(0,0,0,255));
		}
		else
		{
		
			int percent = 225 * (energy/100);
	    	
	    	percent = percent - 225;
	    	
	        sprite.setColor(sf::Color(255, 255+percent, 255+percent));
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
				sprite.setScale(-scale,scale);
			else
				sprite.setScale(scale,scale);
					
			
			if(shift.blowup.ended)
			{
				busy=false;
				action="none";
				element[itemindex].boolean[0]=true;
				alive = false;
				sayDone();
				buttons.clear();
				iconrect.clear();
			}
		}
		
		
		
		
		
		
		
		
		
		
		
		if(state == "eatleft")
		{
			sprite.setTextureRect(Shift(shift.eatL));
		}
		if(state == "eatright")
		{
			sprite.setTextureRect(Shift(shift.eatR));
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
			
			if(Input::Mouse(Mouse::Left))
			{
				if(released)
				{
					
					
					if(color!=UserColor)
					{
						
						wav.playSound(37,now.x);
					}
					
					if(topBlupi.ID == ID)
					{
						
						if(color==UserColor)
						{
						
							
							player[ME].selected = ID;
					
							int b = rand()%3;
							
							
							
							wav.playSound(b+1,now.x);
						
						
						
						
							
						
							
							if(locomotion!="walk")
							{
								if(!checkGroundNow(ground,now))
								{
									
								}
								else
								{
									iconrect.clear();
									buttons.clear();
									buttons.push_back("exit jeep");
									
									
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
			
			
				
				
			if(wav.sound[0].getStatus()!=Sound::Status::Playing)
			{
				wav.playSound(b+7,now.x);
			}
		}
	}
	
	
	
	
	
	
	void sayObey()
	{
		if(color == UserColor)
		{
		
			int b = rand()%3;
			
			wav.playSound(b+4,now.x);
		}
	}
	
	
	
	
	void updatePhysics(Image &ground)
	{
		if(locomotion=="walk" || locomotion == "tired" || locomotion == "sick")
		{
			
			
			if(locomotion == "tired" || locomotion == "sick")
			{
				speed = 0.5;
			}
			else
			{
				speed = 2;
			}
			
			if(velocity.x != 0)
			{
				energy-=walkEnergyLoss;
			}
			
			gravity = 0.2;
			
			int x = now.x;
			int index = water.getPuddleIndex(x);
			
			if(index!=-1)
			{
				
				
				
				
				int deep=0;
				if(x >= 0 && x < water.width)
					deep = groundEdge[x] - water.puddle[index].pos.y;
				
				
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
			
			Gravity(ground,velocity,now,gravity); // apply gravity and resolve collisions.
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
					deep = groundEdge[x] - water.puddle[index].pos.y;
			
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
			
			sprite.setPosition(now.x,now.y - 40);//35
			
			
			
			if(Input::Key(Keyboard::Up))
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
				
			
			
			
			
			
			
			
				float damper = 0;
			
			
				//get the opposing angle to the current direction.
				
				if(state == "moveleft")
				{
					if(sprite.getRotation() > 180+90)//uphill
					{
						damper = (360-sprite.getRotation())/20;
					}
					if(sprite.getRotation() < 180+90)//downhill
					{
						if(sprite.getRotation() > 180)
						{
							damper = (sprite.getRotation() - 180)/20;
							damper = -damper;
						}
						else
						{
							damper = 0;
						}
					}
				}
				
				if(state == "moveright")
				{
					if(sprite.getRotation() < 90)//uphill
					{
						damper = sprite.getRotation()/20;
					}
					if(sprite.getRotation() > 90)//downhill
					{
						if(sprite.getRotation() < 180)
						{
						
							damper = (sprite.getRotation() - 90)/20;
							damper = -damper;
						}
						else
						{
							damper = 0;
						}
					}
				}				
				
				
				
				

		        // Check if destination is far enough to start moving
		        if (std::abs(destination.x - now.x) > 5) // Adjust threshold as needed
		        {
		            if (destination.x < now.x)
		            {
		            	state = "moveleft";
						velocity.x = -speed - damper;
					
		            }
		            else if (destination.x > now.x)
		            {
	            		state = "moveright";
						velocity.x = speed + damper;
				    
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
		
		
		if(player[ME].color == color)
		{
		
			energyBar.setTexture(textures.bars);
			
			energyBar.setPosition(sprite.getPosition().x - (123/2),sprite.getPosition().y - ((sprite.getTextureRect().height/2)*scale) - carrying.getTextureRect().height - 10);
			
			
			
			energyBar.setTextureRect({1,100,123,10});
			window.draw(energyBar);
			
			
			
			int percent = 123 * (energy/100);
			
			if(percent <= 25)
			{
				locomotion = "tired";
			}
			else
			{
				if(locomotion == "tired")
				{
					locomotion = "walk";
					
				}
			}
			
			
			
			energyBar.setTextureRect({1,90,percent,10});
			window.draw(energyBar);
			
		}
		
		
		
		
	}
	
};

std::vector<Blupi> blupi;