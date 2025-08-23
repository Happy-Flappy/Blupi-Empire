

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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
    void runAwayFrom(float dangerX,int blupiIndex)
    {
    	
    	assert(blupiIndex < blupi.size());
        Blupi& current = blupi[blupiIndex];
        current.action = "none";
        current.busy = false;

		
		if(!current.running)
    	{
			soundChannel = wav.playSound(11,current.now.x);
			
		}

        if (dangerX > current.now.x) {
            // Danger is to the right, move left
            current.destination.x = current.now.x - 300;
        } else {
            // Danger is to the left, move right
            current.destination.x = current.now.x + 300;
        }
        
        current.running = true;
    }
	
	
	
	
	
	
	
	
	bool dangerousBlupiNear(int a)
	{
		Blupi &b = blupi[blupiByPos[a].ID];
		if(b.color!=player[ID].color) return false; //only control AI blupis
    	
    	
    	Blupi *leftb = nullptr;
    	Blupi *rightb = nullptr;
    	
    	if(a - 1 >= 0)
    	{
    		leftb = &blupi[blupiByPos[a-1].ID];
		}
		
    	if(a + 1 < blupiByPos.size())
    	{
    		rightb = &blupi[blupiByPos[a+1].ID];
		}
		
		
		
		
		
		if(leftb != nullptr)
		{
			
			
			
			if(leftb->action == "blow up")
			{
			
	        	if(b.now.x - leftb->now.x < 300)
	        	{
	        		if(!b.running)
	        			runAwayFrom(leftb->now.x, b.ID);
	        		return true;
				}
			}
		}
		if(rightb != nullptr)
		{
			if(rightb->action == "blow up")
			{
			
	        	if(rightb->now.x - b.now.x < 300)
	        	{
	        		
	        		if(!b.running)
	        			runAwayFrom(rightb->now.x, b.ID);
					return true;
				}
			}
		}
    	return false;
    	
	}
	
	
	
	
	
	
	
	void update()
	{
		if(!isHost || !active || ID == -1 || blupiByPos.empty()) return;
		
		
		//get Conditions for all blupis
		
        for (int a = 0; a < blupiByPos.size(); a++)
        {
        
        	Blupi &b = blupi[blupiByPos[a].ID];
        	
        	for(int p=0;p<4;p++)
        	{
        		if(player[p].color == b.color && !player[p].human)
        		{
		        			
		        	if(!dangerousBlupiNear(a))		
			        	b.running = false;
				}
			}
        	
        	
	        
        }
		
		
		
		
	}
	
	
		
};






#endif