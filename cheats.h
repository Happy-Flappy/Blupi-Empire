



#ifndef Cheats_h
#define Cheats_h

namespace Cheats
{

	std::string input = "";
	void update(sf::Event &e)
	{
		if(e.type == sf::Event::TextEntered)
		{
		    if (e.text.unicode >= 32 && e.text.unicode < 128) // Printable ASCII range
		    {
		        input += static_cast<char>(e.text.unicode); // Append the character
		    }	
		}
		
		if(input.find("slowpoke") != std::string::npos)
		{
			if(blupi[self.selected].mod.type == "slowSpeed")
				blupi[self.selected].mod.type = "none";
			else
			{
				blupi[self.selected].mod.type = "slowSpeed";
				blupi[self.selected].trailType = "smoke";
			}
			input = "";
		}
		
		if(input.find("speedy") != std::string::npos)
		{
			if(blupi[self.selected].mod.type == "fastSpeed")
			{
				blupi[self.selected].mod.type = "none";
			}
			else
			{
				blupi[self.selected].mod.type = "fastSpeed";
				blupi[self.selected].trailType = "sparkle";
			}
			input = "";
		}
		
		if(input.find("invincible") != std::string::npos)
		{
			if(blupi[self.selected].mod.type == "invincible")
				blupi[self.selected].mod.type = "none";
			else
				blupi[self.selected].mod.type = "invincible";
			input = "";
		}
		
		if(input.find("alwaysfull") != std::string::npos)
		{
			if(blupi[self.selected].mod.type == "alwaysfull")
				blupi[self.selected].mod.type = "none";
			else
				blupi[self.selected].mod.type = "alwaysfull";
			input = "";
		}
		
		if(input.find("givelife") != std::string::npos)
		{
			blupi[self.selected].energy = 100;
			input = "";
		}
		
		
		
		
		
		
	}

}

#endif