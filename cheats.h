



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
			if(blupi[player[ME].selected].mod.type == "slowSpeed")
				blupi[player[ME].selected].mod.type = "none";
			else
			{
				blupi[player[ME].selected].mod.type = "slowSpeed";
				blupi[player[ME].selected].trailType = "smoke";
			}
			input = "";
		}
		
		if(input.find("speedy") != std::string::npos)
		{
			if(blupi[player[ME].selected].mod.type == "fastSpeed")
			{
				blupi[player[ME].selected].mod.type = "none";
			}
			else
			{
				blupi[player[ME].selected].mod.type = "fastSpeed";
				blupi[player[ME].selected].trailType = "sparkle";
			}
			input = "";
		}
		
		if(input.find("invincible") != std::string::npos)
		{
			if(blupi[player[ME].selected].mod.type == "invincible")
				blupi[player[ME].selected].mod.type = "none";
			else
				blupi[player[ME].selected].mod.type = "invincible";
			input = "";
		}
		
		if(input.find("alwaysfull") != std::string::npos)
		{
			if(blupi[player[ME].selected].mod.type == "alwaysfull")
				blupi[player[ME].selected].mod.type = "none";
			else
				blupi[player[ME].selected].mod.type = "alwaysfull";
			input = "";
		}
		
		if(input.find("givelife") != std::string::npos)
		{
			blupi[player[ME].selected].energy = 100;
			input = "";
		}
		
		
		
		
		
		
	}

}

#endif