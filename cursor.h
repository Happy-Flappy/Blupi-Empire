




class Cursor
{
	public:
		
	Sprite sprite;
	bool released;	
	
	Cursor()
	{
		sprite.setTexture(textures.pblupi);
		sprite.setTextureRect(IntRect(437,1334,23,26));
	}
	
	
	void update(RenderWindow &window)
	{
		
		sprite.setPosition(MPosition);
		
		
		if(!Mouse::isButtonPressed(Mouse::Left))
		{
			released=true;
		}
	}
	
	
	void draw(RenderWindow &window)
	{
		window.draw(sprite);
	}
	
		
}cursor;