

#include <sstream>



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
	RectangleShape overlay;
	std::vector <std::string> key;
	Music music;
	Music atmosphere;
	std::string folder = "levels/";
	std::string name;
	float parallaxspeed = 0.1;
	float viewspeed = 0.5;
	float viewvelo = 0;
	sf::Vector2i size;
	std::vector<std::string> filepaths;
	std::vector<std::string> availableColors;
		
		
		
		
		
	bool loadMap(std::string levelname)
	{
		
		
		
		filepaths.clear();
		
		
		this->name = levelname;
		
		
		
		
		std::ifstream file;
		file.open(folder + name);
		
		
		
		
		
		
		
		if(file.is_open())
		{
		
		
			filepaths.push_back(name);
		
			
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
		else
		{
			//fail message
			return false;
		} 
		file.close();
		
		return true;
		
	}
	
	
	

	

	// Function to convert a string to an int safely
	int stringToInt(std::string str) 
	{
		int result=0;
	    std::stringstream ss(str);
	    ss >> result;
		return result;
	}
	
	
	// Function to convert a string to a float safely
	int stringToFloat(std::string str) 
	{
		float result=0;
	    std::stringstream ss(str);
	    ss >> result;
		return result;
	}
	
	

	
	
	Color color;
	
	
	
	void obey()
	{
		
		
		
		if(key[0]=="ground")
		{
			if(iground.getSize().x==0)
			{
			
				if(!iground.loadFromFile(folder + key[1]))
				{
					iground.create(1920,540,Color::Transparent);
				}
				filepaths.push_back(key[1]);
			}
			tground.loadFromImage(iground);
			ground.setTexture(tground);
			
			getGroundEdges(iground);
			
			size = sf::Vector2i(iground.getSize().x,iground.getSize().y);
		}
		
		
		if(key[0]=="background")
		{
			if(tbackground.getSize().x==0)
				tbackground.loadFromFile(folder + key[1]);
			
			filepaths.push_back(key[1]);
			background.setTexture(tbackground);
			tbackground.setRepeated(true);
			background.setTextureRect(IntRect(0,0,iground.getSize().x,iground.getSize().y));
			
			if(key.size()>3)
			{
				if(key[2]=="scroll%")
				{
					parallaxspeed = viewspeed*(stringToFloat(key[3])*0.01);
				}
			}
		}
		
		
		if(key[0]=="foreground")
		{
			if(tforeground.getSize().x==0)
				tforeground.loadFromFile(folder + key[1]);
			
			filepaths.push_back(key[1]);
			foreground.setTexture(tforeground);
			
		}
		
		
		
		if(key[0]=="floater")
		{
			if(tfloater.getSize().x==0)
				tfloater.loadFromFile(folder + key[1]);
			
			filepaths.push_back(key[1]);
			floater.setTexture(tfloater);
			floater.setPosition(0,-floater.getTextureRect().height);
		}
		
		
		if(key[0]=="atmosphere")
		{
			atmosphere.stop();
			if(atmosphere.getStatus()!=Sound::Status::Playing)
			{
			
				atmosphere.openFromFile(folder + key[1]);
				atmosphere.setLoop(true);
				atmosphere.play();
				
				
				filepaths.push_back(key[1]);
			}
		}
		
		if(key[0]=="music")
		{
			if(music.getStatus()!=Sound::Status::Playing)
			{
			
				music.stop();
				music.openFromFile(folder + key[1]);
				music.setLoop(true);
				music.play();
				
				
				filepaths.push_back(key[1]);
			}
		}
		
		
		
		
		
		
		
		
		
		if(key[1]=="blupi")
		{
			
			int index = CreateBlupi();
			
			blupi[index].now=Vector2f(stringToInt(key[2]),stringToInt(key[3]));
			blupi[index].Stop();
			blupi[index].color = key[0];
			if(key[0]=="yellow")
				blupi[index].sprite.setTexture(textures.blupiyellow);
			if(key[0]=="blue")
				blupi[index].sprite.setTexture(textures.blupiblue);
			if(key[0]=="orange")
				blupi[index].sprite.setTexture(textures.blupiorange);
			if(key[0]=="green")
				blupi[index].sprite.setTexture(textures.blupigreen);
			
			
			
			
			bool exists=false;
			for(int a=0; a<availableColors.size();a++)
			{
				if(availableColors[a]==key[0])
				{
					exists=true;
					break;
				}
				
			}
			if(!exists)
			{
				availableColors.push_back(key[0]);
			}			
			
			
		}
		
		
		
		if(key[0]=="wood")
		{
			int index = CreateElement();
			element[index].type = "wood";
			//element[index].sprite.setTexture(textures.)
		}
		
		if(key[0]=="bomb")
		{
			int index = CreateElement();
			
			element[index].type = "bomb";
			element[index].sprite.setTexture(textures.element);
			element[index].sprite.setTextureRect(IntRect(88,25,44,22));
			element[index].now = Vector2f(stringToInt(key[1]),stringToInt(key[2]));
			element[index].averageHeight = element[index].sprite.getTextureRect().height;
			
		}

		if(key[0]=="tomato")
		{
			int index = CreateElement();
			
			element[index].type = "tomato";
			element[index].sprite.setTexture(textures.element);
			element[index].sprite.setTextureRect(sf::IntRect(67,153,51,39));
			element[index].now = Vector2f(stringToInt(key[1]),stringToInt(key[2]));
			element[index].averageHeight = element[index].sprite.getTextureRect().height;
			
		}



		
		if(key[0]=="house")
		{
			//a house is a haven where any blupi can be protected from some enemies such as dozers but is not protected from things that can destroy the house such as fire and bombs.
			int index = CreateElement();
			element[index].type = "house";
			element[index].sprite.setTexture(textures.explo);
			element[index].sprite.setTextureRect(IntRect(0,650,127,107));
			element[index].now = Vector2f(stringToInt(key[1]),stringToInt(key[2]));
			element[index].averageHeight = element[index].sprite.getTextureRect().height;
			
		}
		
		
		if(key[0]=="shed")
		{
			int index = CreateElement();
			element[index].type = "shed";
			element[index].sprite.setTexture(textures.explo);
			element[index].sprite.setTextureRect(IntRect(0,438,127,95));
			element[index].now = Vector2f(stringToInt(key[1]),stringToInt(key[2]));
			element[index].averageHeight = element[index].sprite.getTextureRect().height;	
			
		}
		
		
		
		if(key[0] == "tree")
		{
			int index = CreateElement();
			element[index].type = "tree";
			element[index].sprite.setTexture(textures.explo);
			element[index].obeysRotation = false;
			element[index].now = Vector2f(stringToInt(key[1]),stringToInt(key[2]));			
			element[index].layer = 1;		
			
			if(key[3] == "palm")
			{
				int random = -1;
				if(key[4] == "random")
				{
					random = rand()%3;
				}
				if(key[4] == "1" || random == 0)
					element[index].sprite.setTextureRect(sf::IntRect(124,1486,126,126));
				if(key[4] == "2" || random == 1)
					element[index].sprite.setTextureRect(sf::IntRect(0,995,127,118));
				if(key[4] == "3" || random == 2)
					element[index].sprite.setTextureRect(sf::IntRect(336,1361,126,125));
					
			}
			if(key[3] == "pine")
			{
				int random = -1;
				if(key[4] == "random")
				{
					random = rand()%3;
				}				
				if(key[4] == "1" || random == 0)
					element[index].sprite.setTextureRect(sf::IntRect(0,1361,92,125));
				if(key[4] == "2" || random == 1)
					element[index].sprite.setTextureRect(sf::IntRect(250,1486,126,126));
				if(key[4] == "3" || random == 2)
					element[index].sprite.setTextureRect(sf::IntRect(368,1116,125,121));
				
				
			}
			
			element[index].averageHeight = element[index].sprite.getTextureRect().height/2;	
			
		}
		
		
		
		if(key[0]=="jeep")
		{
			int index = CreateElement();
			element[index].type = "jeep";
			element[index].sprite.setTexture(textures.element);
			element[index].sprite.setTextureRect(IntRect(363,50,59,29));
			element[index].now = Vector2f(stringToInt(key[1]),stringToInt(key[2]));
			element[index].averageHeight = element[index].sprite.getTextureRect().height;	
						
		}
		
		
		if(key[0]=="boat")
		{
			int index = CreateElement();
			element[index].type = "boat";
			element[index].sprite.setTexture(textures.element);
			element[index].sprite.setTextureRect(IntRect(0,645,58,27));
			element[index].now = Vector2f(stringToInt(key[1]),stringToInt(key[2]));
			element[index].averageHeight = element[index].sprite.getTextureRect().height;	
						
			
		}
		
		
		if(key[0]=="water")
		{
			Water::Puddle newdrop;
			newdrop.pos = Vector2i(stringToInt(key[1]),stringToInt(key[2]));
			water.puddle.push_back(newdrop);
			
		}
		
		
		

		
		if(key[0]=="overlay")
		{
			if(overlay.getSize().x==0)
			{
			
				//RGBA
				overlay.setSize(Vector2f(iground.getSize().x,iground.getSize().y));
				overlay.setPosition(0,0);
				overlay.setFillColor(Color(stringToInt(key[1]),stringToInt(key[2]),stringToInt(key[3]),stringToInt(key[4])));
			}
		}
		
		
	
		
		
	}
}map;