




class Wav
{
	public:
	sf::Sound sound[16];
	sf::SoundBuffer buffer[200];


	int findChannel()
	{
		for(int a=0;a<16;a++)
		{
			if(sound[a].getStatus()!=sf::Sound::Status::Playing)
			{
				return a;
			}
		}
		return -1;
	}
	
	Wav()
	{
		buffer[0].loadFromFile("ASSETS/say/sound056.wav");
		buffer[1].loadFromFile("ASSETS/say/sound057.wav");
		buffer[2].loadFromFile("ASSETS/say/sound058.wav");
		
		buffer[4].loadFromFile("ASSETS/say/sound075.wav");
		buffer[5].loadFromFile("ASSETS/say/sound002.wav");
		buffer[6].loadFromFile("ASSETS/say/sound003.wav");
		buffer[7].loadFromFile("ASSETS/say/sound004.wav");	
		buffer[8].loadFromFile("ASSETS/say/sound008.wav");
		buffer[9].loadFromFile("ASSETS/say/sound009.wav");
		buffer[10].loadFromFile("ASSETS/say/sound010.wav");	
		buffer[11].loadFromFile("ASSETS/say/sound049.wav");	
			

		buffer[100].loadFromFile("ASSETS/miscSound/boom.wav");
		buffer[101].loadFromFile("ASSETS/miscSound/en/sound050.wav");
		
	}
}wav;