





class Map
{
	public:
			
	Sprite ground;	
	Image iground;	
	Texture tground;
	Texture tbackground;
	Sprite background;
	Texture tforeground;
	Sprite foreground;
	Texture tfloater;
	Sprite floater;
	std::vector <std::string> key;
	Music music;
	Music atmosphere;
	std::string folder;
	std::string name;
	
	

		
		
		
		
		
		
	void loadMap(std::string levelname)
	{
		
		
		
		folder = "levels/";
		this->name = levelname;
		
		
		if(!iground.loadFromFile("levels/" + name +".png"))
		{
			iground.create(1920,540,Color::Transparent);
		}
		tground.loadFromImage(iground);
		ground.setTexture(tground);
		
		
		
		getGroundEdge(iground);
		
		
		
		
		
		
		
		std::ifstream file;
		file.open("levels/" + name + ".txt");
		
		
		if(file.is_open())
		{	
			std::string word;
			while(file >> word)
			{
				if(word!="END")
					key.push_back(word);
				else
				{
					obey();	
					key.clear();
				}	
			}
		} 
		file.close();
		
	}
	

	// Function to convert a string to an int safely
	int stringToInt(std::string str) 
	{
		int result=0;
	    std::stringstream ss(str);
	    ss >> result;
		return result;
	}
	

	
	
	Color color;
	
	
	
	void obey()
	{
		
		if(key[0]=="background")
		{
			tbackground.loadFromFile(folder + key[1]);
			background.setTexture(tbackground);
		}
		
		
		if(key[0]=="foreground")
		{
			tforeground.loadFromFile(folder + key[1]);
			foreground.setTexture(tforeground);
			
		}
		
		
		
		if(key[0]=="floater")
		{
			tfloater.loadFromFile(folder + key[1]);
			floater.setTexture(tfloater);
			floater.setPosition(0,-floater.getTextureRect().height);
		}
		
		
		if(key[0]=="atmosphere")
		{
			atmosphere.stop();
			atmosphere.openFromFile(folder + key[1]);
			atmosphere.setLoop(true);
			atmosphere.play();
		}
		
		if(key[0]=="music")
		{
			music.stop();
			music.openFromFile(folder + key[1]);
			music.setLoop(true);
			music.play();
		}
		
		
		
		
		
		
		
		
		
		if(key[1]=="blupi")
		{
			Blupi newblupi;
			newblupi.ID = blupi.size();
			newblupi.now=Vector2f(stringToInt(key[2]),stringToInt(key[3]));
			newblupi.Stop();
			newblupi.color = key[0];
			if(key[0]=="yellow")
				newblupi.sprite.setTexture(textures.blupiyellow);
			if(key[0]=="blue")
				newblupi.sprite.setTexture(textures.blupiblue);
			if(key[0]=="orange")
				newblupi.sprite.setTexture(textures.blupiorange);
			if(key[0]=="green")
				newblupi.sprite.setTexture(textures.blupigreen);
			
			
			
			
			blupi.push_back(newblupi);
		}
		
		
		
		if(key[0]=="wood")
		{
			Element newelement;
			newelement.type = "wood";
			//newelement.sprite.setTexture(textures.)
		}
		
		if(key[0]=="bomb")
		{
			Element newelement;
			newelement.type = "bomb";
			newelement.sprite.setTexture(textures.element);
			newelement.sprite.setTextureRect(IntRect(88,24,48,24));
			newelement.now = Vector2f(stringToInt(key[1]),stringToInt(key[2]));
			newelement.averageHeight = newelement.sprite.getTextureRect().height;
			element.push_back(newelement);
		}
		
		if(key[0]=="house")
		{
			//a house is a haven where any blupi can be protected from some enemies such as dozers but is not protected from things that can destroy the house such as fire and bombs.
			Element newelement;
			newelement.type = "house";
			newelement.sprite.setTexture(textures.explo);
			newelement.sprite.setTextureRect(IntRect(0,650,127,107));
			newelement.now = Vector2f(stringToInt(key[1]),stringToInt(key[2]));
			newelement.averageHeight = newelement.sprite.getTextureRect().height;
			element.push_back(newelement);
		}
		
		
		if(key[0]=="shed")
		{
			Element newelement;
			newelement.type = "shed";
			newelement.sprite.setTexture(textures.explo);
			newelement.sprite.setTextureRect(IntRect(0,438,127,95));
			newelement.now = Vector2f(stringToInt(key[1]),stringToInt(key[2]));
			newelement.averageHeight = newelement.sprite.getTextureRect().height;	
			element.push_back(newelement);
		}
		
		if(key[0]=="jeep")
		{
			Element newelement;
			newelement.type = "jeep";
			newelement.sprite.setTexture(textures.element);
			newelement.sprite.setTextureRect(IntRect(363,50,59,29));
			newelement.now = Vector2f(stringToInt(key[1]),stringToInt(key[2]));
			newelement.averageHeight = newelement.sprite.getTextureRect().height;	
			element.push_back(newelement);			
		}
		
		
		if(key[0]=="water")
		{
			Water::Puddle newdrop;
			newdrop.pos = Vector2i(stringToInt(key[1]),stringToInt(key[2]));
			water.puddle.push_back(newdrop);
			
		}
		
		
		
		
		
		
		
		
		
		
	
		
		
	}
}map;