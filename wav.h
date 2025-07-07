




class Wav
{
	public:
	sf::Sound sound[16];
	sf::SoundBuffer buffer[200];
	sf::Listener listen;

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
	
	sf::Clock cooldown;
	int playSound(int bufferID,int x)
	{
		
        if(cooldown.getElapsedTime().asMilliseconds() > 500) // 500ms cooldown
        {
	        	
			int a = findChannel();
			if(a!=-1)
			{
				sound[a].stop();
				sound[a].setBuffer(buffer[bufferID]);
				sound[a].setPosition(x,0,0);
				sound[a].setMinDistance(400.f);
	        	sound[a].setAttenuation(5);
				sound[a].play();
			}			
			cooldown.restart();
			
			return a;
        }

		
		return -1;
	}
	
	
	Wav()
	{
		// buffer[0] is skipped because I accidentally id'd the paths starting from 1 
		
		std::string paths[] = {"ASSETS\\say\\sound002.wav",//1
"ASSETS\\say\\sound003.wav",//2
"ASSETS\\say\\sound004.wav",//3
"ASSETS\\say\\sound005.wav",//4
"ASSETS\\say\\sound006.wav",//5
"ASSETS\\say\\sound007.wav",//6
"ASSETS\\say\\sound008.wav",//7
"ASSETS\\say\\sound009.wav",//8
"ASSETS\\say\\sound010.wav",//9
"ASSETS\\say\\sound014.wav",//10
"ASSETS\\say\\sound017.wav",//11
"ASSETS\\say\\sound018.wav",//12
"ASSETS\\say\\sound019.wav",//13
"ASSETS\\say\\sound027.wav",//14
"ASSETS\\say\\sound033.wav",//15
"ASSETS\\say\\sound037.wav",//16
"ASSETS\\say\\Sound049.wav",//17
"ASSETS\\say\\sound056.wav",//18
"ASSETS\\say\\sound057.wav",//19
"ASSETS\\say\\sound058.wav",//20
"ASSETS\\say\\sound059.wav",//21
"ASSETS\\say\\sound060.wav",//22
"ASSETS\\say\\sound061.wav",//23
"ASSETS\\say\\sound062.wav",//24
"ASSETS\\say\\sound063.wav",//25
"ASSETS\\say\\sound064.wav",//26
"ASSETS\\say\\sound065.wav",//27
"ASSETS\\say\\sound066.wav",//28
"ASSETS\\say\\sound067.wav",//29
"ASSETS\\say\\sound068.wav",//30
"ASSETS\\say\\sound069.wav",//31
"ASSETS\\say\\sound070.wav",//32
"ASSETS\\say\\sound071.wav",//33
"ASSETS\\say\\sound072.wav",//34
"ASSETS\\say\\sound073.wav",//35
"ASSETS\\say\\sound074.wav",//36
"ASSETS\\say\\sound075.wav"};//37			

		
		for(int a=1;a<=sizeof(paths)/sizeof(paths[0]);a++)
		{	
			buffer[a].loadFromFile(paths[a-1]);
		}
		
			
		
		
		
		
		buffer[100].loadFromFile("ASSETS/miscSound/boom.wav");
		buffer[101].loadFromFile("ASSETS/miscSound/en/sound050.wav");
		
		
		
		
		listen.setGlobalVolume(100);
		
		
		
	}
}wav;