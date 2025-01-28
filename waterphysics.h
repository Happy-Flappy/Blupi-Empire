




#ifndef WATER_H
#define WATER_H











class Water
{
	
	public:
	
	
	Image image;	
	Texture texture;
	Sprite sprite;
	
	
	
	
	
	
	Water()
	{
	}
	
	
	
	
	struct Puddle
	{
		int left=-1;
		int right;
		Vector2i pos;	
	};
	
	std::vector <Puddle> puddle;
	
		
	
	
	
	void getClamp(Image &ground,Puddle &group)
	{
		int left=0;
		Vector2i pos = group.pos;
		for(int x = pos.x; x > 0; x--)
		{
			if(ground.getPixel(x,pos.y)!=Color::Transparent)
			{
				left = x;
				break;
			}
		}
		
		int right = ground.getSize().x-1;
		for(int x = pos.x; x < ground.getSize().x-1; x++)
		{
			if(ground.getPixel(x,pos.y)!=Color::Transparent)
			{
				right = x;
				break;
			}
		}
		
		
		group.left = left;
		group.right = right;
		
		
		
		
	}
	
	
	Image empty;
	
	void update(Image &ground)
	{
		
		
		
		if(image.getSize().x==0)
		{
			image.create(ground.getSize().x,ground.getSize().y,Color::Transparent);
			empty = image;
		}
	
		



		image = empty;
		


		static float offset=0;	
		float speed = 0.1;	
		
		for(int a=0;a<puddle.size();a++)
		{
			if(puddle[a].left==-1)
				getClamp(ground,puddle[a]);
			
			
			
			float amplitude=5;
			float frequency=0.02;
			
			if(puddle[a].right - puddle[a].left > 0)
			{
				
				for(int x=puddle[a].left; x < puddle[a].right; x++)	
				{
					
					float wave = amplitude * std::sin((frequency * x) + offset);
					wave+=amplitude;
					
					int hue = 0; 
					for(int y = puddle[a].pos.y + wave; y < image.getSize().y; y++)
					{	
						hue++;
						
						if(ground.getPixel(x,y)!=Color::Transparent)
						{
							break;
						}
						else
						{
							if(hue < 20)
							{
								image.setPixel(x,y,Color(0,142,212,80));
								
							}
							if(hue >= 20 && hue < 60)
							{
								
								image.setPixel(x,y,Color(0,45,145,80));
							}
							if(hue >= 60)
							{
								
								image.setPixel(x,y,Color(0,5,212,80));
							}
							
							
							
						}
						
						
					}
					
				}
					
			}
			else
				break;
			
			
		}
		
		offset += speed;
		
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	
		
	}
	
	
	
	void draw(RenderWindow &window)
	{
		window.draw(sprite);
		
	}
	
	
	
	
}water;











#endif