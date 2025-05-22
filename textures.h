



class Textures
{
	public:
	Texture blupiblue;
	Texture blupiyellow;
	Texture blupigreen;
	Texture blupiorange; 
	Texture buttons;
	Texture taskbox;
	Texture pblupi;
	Texture element;
	Texture explo;
	Texture pelement;
	Texture decor016;
	Font comic;
	Font comicbd;
	Font comicz;
	
	
	void Clean(std::string dir,Texture &t)
	{
		Image image;
		image.loadFromFile(dir);
		
		for(int x=0;x<image.getSize().x;x++)
		{
			for(int y=0;y<image.getSize().y;y++)
			{
				if(image.getPixel(x,y)==Color::Blue || image.getPixel(x,y) == Color(0,38,255))
				{
					image.setPixel(x,y,Color::Transparent);
				}
			}
		}
		t.loadFromImage(image);
		
		
	}
	
	
	
	Textures()
	{
		Clean("ASSETS/blupiblue.png",blupiblue);
		
		Clean("ASSETS/blupiyellow.png",blupiyellow);
		
		Clean("ASSETS/blupigreen.png",blupigreen);
		
		Clean("ASSETS/blupiorange.png",blupiorange);
		
		
		
		buttons.loadFromFile("ASSETS/buttons.png");
		taskbox.loadFromFile("ASSETS/taskbox.png");
		Clean("ASSETS/pblupi.png",pblupi);
		Clean("ASSETS/element.png",element);
		Clean("ASSETS/explo.bmp",explo);
		blupiblue.setSmooth(true);
		blupiyellow.setSmooth(true);
		blupiorange.setSmooth(true);
		blupigreen.setSmooth(true);
		element.setSmooth(true);
		explo.setSmooth(true);
		decor016.loadFromFile("ASSETS/DECOR016.PNG");
		comic.loadFromFile("ASSETS/ComicMono.ttf");
		
	}
}textures;