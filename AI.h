

#ifndef AI_CLASS
#define AI_CLASS

#include <cassert>



class AI
{
	public:
	bool active=false;
	int ID=-1;
	int soundChannel = -1;
	
	AI()
	{
		
	}
	
	
	
	
	
	
	
	
	
	int dangerousBlupiNear(int b)
	{
		for(int a=0;a<blupi.size();a++)
		{
			if(blupi[a].action == "blow up")
			{
				if(b!=a)
				{
					
					
	                int distance = abs(blupi[b].now.x - blupi[a].now.x);
	                if (distance < 300)
	                {
	                    return a;
	                }
					
				}
			}
			
			
			
		}
		return -1;
	}
	
	
	
	
	
	
	
	
	
	
    void runAwayFrom(int dangerX,int blupiIndex)
    {
    	assert(blupiIndex < blupi.size());
        Blupi& current = blupi[blupiIndex];
        current.action = "none";
        current.busy = false;

		int a = findChannel();
		if(a!=-1 && soundChannel!=-1)
		{
			sound[a].stop();
			current.say.loadFromFile("ASSETS/say/Sound049.wav");
			sound[a].setBuffer(current.say);
			sound[a].play();
		}


        int delta = dangerX - current.now.x;
        if (delta > 0) // Danger is to the right, move left
            current.destination.x = current.now.x - 300;
        else // Danger is to the left, move right
            current.destination.x = current.now.x + 300;
    }
	
	
	
	
	
	
	
	void update()
	{
		if(active && ID!=-1)
		{
		
			//get Conditions for all blupis
			
	        for (int a = 0; a < blupi.size(); a++)
	        {
	        
	        	
	            int currentBlupi = a;
				if (blupi[a].color == player[ID].color)
	            {
	            	
	                int danger = dangerousBlupiNear(a);
	                if (danger != -1)
	                {
	                	assert(danger < blupi.size());
	                    runAwayFrom(blupi[danger].now.x, currentBlupi);
	                }
	            }
	        }
	    }
		
		
		
		
	}
	
	
		
};






#endif