

#ifndef SETUPSCREEN
#define SETUPSCREEN










class TextCanvas
{
	public:
		
	Text text;
	int maxwidth,maxheight;
	std::vector<std::vector<char>> canvas;
	
	TextCanvas()
	{
		text.setFont(textures.comic);
		text.setCharacterSize(18);
		text.setFillColor(Color::White);
		text.setOutlineThickness(1);
		text.setOutlineColor(Color::Blue);
		
		text.setString("A");
		int width,height;
		width = text.getGlobalBounds().width;
		height = text.getGlobalBounds().height;
		
		maxwidth = 200;
		maxheight = 200;
		
		
		canvas.resize(maxwidth,std::vector<char>(maxheight,' '));
		
		
		text.setPosition(2,3);

	}	
	
	
	
	
	
	
	
	
	void clear()
	{
		for(int x=0;x<canvas.size();x++)
		{
			for(int y=0;y<canvas[x].size();y++)
			{
				canvas[x][y]=' ';
			}
		}		
	}
	
	
	
	
	
	
	
	
	
	void draw(std::string str,int x,int y)
	{
		int y2=0;
		for(int i=0;i<str.length();i++)
		{
			
			if(x+i > maxwidth)
			{
				x=0;
				y2++;
			}
			if(y+y2 >= maxheight)
			{
				break;
			}
				
			canvas[y+y2][x+i]=str[i];
		}
	}
	
	
	
	
	void display(RenderWindow &window)
	{
		std::string s;
        for (int x = 0; x < maxwidth; ++x) 
		{
            for (int y = 0; y < maxheight; ++y) {
                s += canvas[x][y]; 
            }
            s += '\n'; // Add newline at the end of each row
        }
		text.setString(s);
		window.draw(text);
	
	}
		
}textCanvas;









class Typing
{
	public:
	
	Typing()
	{
	}
	
	
	
	std::string name;
	std::string typer="|";
	std::string keystring;
	std::string input;
	std::string output;
	
	float typertime = 0;
	bool get = true;
	bool released = true;
	bool firstdone = false;
	
	
	void update() 
	{
		if(get)
		{
		
			typertime += seconds(1.f/60.f).asSeconds();
			if(typertime>1)
			{
				if(typer=="|")
					typer=" ";
				else
					typer="|";	
				typertime=0;
			}
			
			
			
			
			
		


			
		
			output = input + typer;
		}
		else	
		{
			output = name;
			
		}
	}
		
		
}typing,leveltyping;















class SetupScreen
{
	public:
	
	RenderWindow window;
	View view;
	bool quitAll=false;
	Sprite decor;
	Sprite button1,button2;
	Time timesincelastupdate=Time::Zero;
	Time timeperframe=seconds(1.f/60.f);
	Clock clock;
	
	
	
	
	
	SetupScreen()
	{
		window.create(VideoMode(960,540),"",Style::Fullscreen);
		view.reset(FloatRect(0,0,960,540));
		window.setMouseCursorVisible(false);
		decor.setTexture(textures.decor016);
		button1.setTexture(textures.buttons);	
		button2.setTexture(textures.buttons);	
		button1.setPosition(378,410);
		button1.setScale(1.3,1.3);
		button2.setPosition(535,410);
		button2.setScale(1.3,1.3);
		
		button1.setTextureRect(IntRect(1,1,39,39));
		button2.setTextureRect(IntRect(1,1,39,39));
		
		
		
	}
	
	
	
	
	
	
	
	
	bool checkbutton(Sprite &sprite)
	{
		if(sprite.getGlobalBounds().contains(MPosition))
		{
			if(Mouse::isButtonPressed(Mouse::Left))
			{
				sprite.setTextureRect(IntRect(81,1,39,39));	
				if(cursor.released)
				{
					return true;

				}
				
				cursor.released=false;
			}
			else
				sprite.setTextureRect(IntRect(121,1,39,39));
		
			
		}
		else
			sprite.setTextureRect(IntRect(1,1,39,39));
		return false;

	}
	
	
	
	
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	void loop()
	{
		while(window.isOpen())
		{
			
			
			MPosition = window.mapPixelToCoords(Mouse::getPosition(window));
			Event e;
			while(window.pollEvent(e))
			{
				if(e.type==Event::Closed)
				{
					window.close();
					quitAll=true;
				}
				
				if(e.type == sf::Event::TextEntered)
		        {
		            if(e.text.unicode == '\b')
		            {
		            	if(!typing.input.empty())
		            		typing.input.pop_back();
		            		
		            	if(!leveltyping.input.empty())
		            		leveltyping.input.pop_back();
		            		
					}
				    else if (e.text.unicode >= 32 && e.text.unicode < 128) // Printable ASCII range
				    {
				        typing.input += static_cast<char>(e.text.unicode); // Append the character
				        
				        leveltyping.input += static_cast<char>(e.text.unicode); // Append the character
				    }
					
		        } 
				
				
				
			}
			
			
			
			
			
			
			
			
			timesincelastupdate += clock.restart();
			
			while(timesincelastupdate > timeperframe)
			{
				timesincelastupdate -= timeperframe;
				
				
				
				
				
				typing.update();
				if(isHost && network.hostknown)
					leveltyping.update();
				
				if(typing.get)
				{
					if(Keyboard::isKeyPressed(Keyboard::Return))
					{
						typing.get=false;
						typing.name=typing.input;
						network.hostname = typing.name;
						network.hostip = IpAddress(network.hostname);
						if(network.hostip==IpAddress::None)
						{
							network.hostname="";
							network.hostip=IpAddress::None;
							typing.get=true;
						}
					}
					leveltyping.input="";
					leveltyping.output="";
				}
				
				if(leveltyping.get)
				{
					if(Keyboard::isKeyPressed(Keyboard::Return))
					{
						leveltyping.get=false;
						leveltyping.name=leveltyping.input;
						
						if(!map.loadMap(leveltyping.name))
						{
							leveltyping.name="";
							leveltyping.get=true;
						}
						else
						{
							
							player[0].loadedLevel=true;
							
							//initialize AI to take place of missing players
							
							for(int a=1;a<map.availableColors.size(); a++)
							{
								if(!player[a].human)
								{
									player[a].known=true;
									player[a].participating=true;
									
									if(a==0)
										player[a].color = "yellow";
									if(a==1)
										player[a].color = "blue";
									if(a==2)
										player[a].color = "orange";
									if(a==3)
										player[a].color = "green";
										
									ai[a].active=true;
									ai[a].ID = a;
								}
							}
							
							
							
						}
						
					}
				}
				
				
				cursor.update(window);
				
			}
			
			
			
			window.setView(view);
			window.clear();
			window.draw(decor);
			
			
			//clear text canvas
			textCanvas.clear();			
			
			
			//draw to text canvas
			
			std::string hostn;
			hostn = "Host:"+ typing.output;
			textCanvas.draw(hostn,33,5);
			
			network.getData();
			network.sendData();
			
			if(isHost && network.hostknown)
			{
				textCanvas.draw("You are the Host!",33,7);
			}
		
			for(int a=0;a<4;a++)
			{
				if(player[a].participating && player[a].human)
				{
					textCanvas.draw(player[a].name+" is Connected!",33,7+a+1);
				}
				if(player[a].participating && !player[a].human)
				{
					textCanvas.draw("AI " + player[a].name + " is Connected!",33,7+a+1);
				}
				
				
			}
			
			textCanvas.draw("Players Ready:",33,8+4);
			
			
			if(isHost && network.hostknown)
			{
				if(map.name!="")
					textCanvas.draw("Host is ready.",33,8+4+1);
			}
			
			if(!isHost && network.hostknown)
			{
				if(map.name=="")
				{
					if(network.loadPercent==-1)
						textCanvas.draw("Self: Failed to load Level!",33,8+4+1);
					else
						textCanvas.draw("Self: Loading Level...",33,8+4+1);
				
				}
				else
					textCanvas.draw("Self: Ready",33,8+4+1);
			}
			
			
			
			for(int a=0;a<4;a++)
			{
				if(player[a].loadedLevel)
					textCanvas.draw(player[a].name + " is Ready.",33,8+4+a+1+1);
			}
		
		
		
			if(isHost && network.hostknown)
			{
				textCanvas.draw("Level Script:"+leveltyping.output,33,18);
			}
			
			
			static bool start=false;
			static float startTime=0;
			startTime+=seconds(1.f/60.f).asSeconds();			
			
			
			
			if(isHost && network.hostknown)
			{
			
				if(start)
				{
					
					bool nocolor=false;
					if(UserColor=="none")
					{
						textCanvas.draw("No color selected for host!",33,3);
						nocolor=true;
					}
					for(int a=0;a<map.availableColors.size();a++)
					{
						if(player[a].color=="none")
						{
							textCanvas.draw("No color selected for " + player[a].name + "!",33,3);
							nocolor=true;
						}
					}
					
					if(!nocolor)
					{
						if(map.name=="")
						{
							textCanvas.draw("Level not selected!",33,3);
						}
						else
						{
							playing=true;
							window.close();
						}
					}
				}
			}
			
			
			
			
			if(startTime > 3)
			{
				start=false;
				startTime=0;
			}
			
			
			
			static bool btnr1=true;
			if(checkbutton(button1))
			{
				if(btnr1)
				{
					if(UserColor=="none")
						UserColor = "yellow";
					else if(UserColor=="yellow")
						UserColor = "blue";
					else if(UserColor=="blue")
						UserColor = "orange";
					else if(UserColor=="orange")
						UserColor = "green";
					else if(UserColor=="green")
						UserColor = "yellow";
					btnr1=false;
					
					//replace with player[ME].color  = UserColor
					player[0].color = UserColor;
				}
					
			}
			else
				btnr1=true;
			
			if(isHost && network.hostknown)
			{
			
				if(checkbutton(button2))
				{
					start=true;
					startTime=0;
				
				}
			}
				
			
			window.draw(button1);
			
			textCanvas.draw("Color:"+UserColor,34,19);
			
			if(isHost&&network.hostknown)
			{
				window.draw(button2);
				textCanvas.draw("Play",54,21);
			}
			
			
			
			
			
			//display text canvas
			textCanvas.display(window);
							
			cursor.draw(window);
			
			
			window.display();
			
			
			if(playing)
			{
				window.close();
			}
			
		}
	}
	
		
};


#endif





