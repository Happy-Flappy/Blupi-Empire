




#ifndef WATER_H
#define WATER_H











class Water
{
	
	public:
	
	Image image;	
	Texture texture;
	Sprite sprite;
	int width,height;
	int depthlimit = 20;
	
	
	
	
	
	
	Water()
	{
		
		
		
		
	}
	
	
	
	
	struct Puddle
	{
		int left=-1;
		int right;
		int lefty=0;
		Vector2i pos;
		Vector2i last;
		
		std::vector<Vector2i> linepos;
		
	};
	
	std::vector <Puddle> puddle;
	
		
	
	
	
	void getClamp(Image &ground,Puddle &group)
	{
		if(groundmap.size()!=0)
		{
		
			
			Vector2i pos = group.pos;
		
		
			int mostleft=pos.x;
			int mostright=pos.x;
			
		
			
			for(int z=pos.y; z < ground.getSize().y-1;z++)
			{
				int left=0;
				for(int x = pos.x; x > 0; x--)
				{
					
					if(groundmap[x][z])
					{
						left = x;
						break;
					}
				}
				
				int right = ground.getSize().x-1;
				for(int x = pos.x; x < ground.getSize().x-1; x++)
				{
					
					if(groundmap[x][z])
					{
						right = x;
						break;
					}
				}
				
				if(right - left > 0)
				{
					if(mostleft > left)
					{
						mostleft = left;
					}
					if(mostright < right)
					{
						mostright = right;
					}
					group.lefty = z;
					
					
				}
				
			}
			
			
			
			
			//Right side
			for(int z=pos.y; z < ground.getSize().y-1;z++)
			{
				
				int right = ground.getSize().x-1;
				for(int x = mostright; x < ground.getSize().x-1; x++)
				{
					
					if(groundmap[x][z])
					{
						right = x;
						break;
					}
				}
				
				if(right - mostleft > 0)
				{
					if(mostright < right)
					{
						mostright = right;
					}
					
				}
				
			}
			
			
			
			
			
			for(int z=pos.y; z < ground.getSize().y-1;z++)
			{
				int left=0;
				for(int x = mostleft; x > 0; x--)
				{
					
					if(groundmap[x][z])
					{
						left = x;
						break;
					}
				}
				
				if(mostright - left > 0)
				{
					if(mostleft > left)
					{
						mostleft = left;
					}
					
				}
				
			}
			
			
			
			
			group.left = mostleft;
			group.right = mostright;
		}
		
		
		
	}
	
	
	
	
	
	
	
	
	
	int getPuddleIndex(int x)
	{
		
		
		for(int a=0; a < puddle.size(); a++)
		{
			int left = puddle[a].left;	
			int right = puddle[a].right;	
			
			if(x > left && x < right)
			{
				return a;
			}	
		}
		
		
		
		return -1;
	}
	
	
	
	
	
	
	
	void update(Image &ground)
	{
		



		if(image.getSize().x==0) //create line
		{
			image.create(1,ground.getSize().y,Color::Transparent);
			int hue=0;
			for(int y=0;y < ground.getSize().y;y++)
			{
				hue++;
				
				
				if(hue < 20)
					image.setPixel(0,y,Color(0,142,212,80));
				if(hue >= 20 && hue < 60)
					image.setPixel(0,y,Color(0,45,145,80));
				if(hue >= 60)
					image.setPixel(0,y,Color(0,5,212,80));
				
			}
			
			
			texture.loadFromImage(image);
			sprite.setTexture(texture);
		}

		width = ground.getSize().x;
		height = ground.getSize().y;



		



		for(int a=0;a<puddle.size();a++)
		{
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
		
			
			float speed = 0.1;	
			

			if(puddle[a].left==-1)
			{
				getClamp(ground,puddle[a]);
				puddle[a].last = puddle[a].pos;
			}
			else
			{
				if(puddle[a].pos.y != puddle[a].last.y || puddle[a].pos.x != puddle[a].last.x)
				{
					puddle[a].last = puddle[a].pos;
					getClamp(ground,puddle[a]);
				}
			}
			
			
			
			
			
			float amplitude=5;
			float frequency=0.02;
			
			
			
			
			static float offset=0;
			
			
			if(puddle[a].right - puddle[a].left > 0)
			{
			
			
				if(puddle[a].linepos.size() != puddle[a].right - puddle[a].left)
					puddle[a].linepos.resize(puddle[a].right - puddle[a].left);	
				
				for(int x=0; x < puddle[a].linepos.size(); x++)	
				{
					
					float wave = amplitude * std::sin((frequency * x) + offset);
					wave+=amplitude;
					
					int y = puddle[a].pos.y + wave; 
					
					
					puddle[a].linepos[x] = Vector2i(puddle[a].left + x,y);
					
					
				}
					
			}
				
			
			
			offset += speed;
			
			
				
		}
		
		
		

		
	}
	
	
	
	
	
	
	void draw(RenderWindow &window)
	{
		for(int a=0;a<puddle.size();a++)
		{
			for(int b=0;b<puddle[a].linepos.size();b++)
			{
				
				int height = groundedge(puddle[a].linepos[b].x,puddle[a].lefty+5) - puddle[a].linepos[b].y;
				if(height > 0)
				{	
					sprite.setTextureRect(IntRect(0,0,1,height+1));
					sprite.setPosition(puddle[a].linepos[b].x,puddle[a].linepos[b].y);
					window.draw(sprite);
				}
				
			}
		}
	}
	
	
	
}water;











#endif