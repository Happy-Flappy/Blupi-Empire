

std::vector<std::vector <bool>> groundmap;//map out pixels

void getGroundEdges(Image &ground)
{
	
	groundmap.resize(ground.getSize().x);
	
	
	for(int a=0;a<groundmap.size();a++)
	{
		groundmap[a].resize(ground.getSize().y);
	}
	
	
	for(int x=0;x<ground.getSize().x;x++)
	{
	
		for(int y = 0; y < ground.getSize().y; y++)
		{
			if(ground.getPixel(x,y)!=Color::Transparent)
			{
				groundmap[x][y]=true;
			}
			else
			{
				groundmap[x][y]=false;
			}
		}
	}
	
	
}










int groundedge(int x,int y)
{
	
	for(int y2 = y-5; y2 < groundmap[x].size(); y2++)
	{
		if(groundmap[x][y2])
		{
			return y2;
		}
	}		
	
	return groundmap[x].size() + 500;
	
}


int getRoof(int x,int y)
{
	
	for(int y2 = y+5; y2 > 0; y2--)
	{
		if(y2 < groundmap[x].size())
		{
	
			if(groundmap[x][y2])
			{
				std::cout << "top:" << y2 << "\n"; 
				return y2;
			
			}
		}
	}		
	
	return 0;	
}























int getGroundAngle(Image &ground, Vector2f now, float lastangle, int range = 10,bool resolve=true)
{
    if (now.x + (range / 2) >= ground.getSize().x)
        return 0;

    Vector2f center;
    Vector2f right;

    center.x = now.x;
    right.x = now.x + (range / 2);

    center.y = groundedge(now.x,now.y);
    right.y = groundedge(now.x + (range / 2),now.y);

    int opp = right.y - center.y;
    int adj = right.x - center.x;

    float rightangle = atan2(adj, opp) * (180 / 3.14);
    
    
    
    if(rightangle > 5)
    {
    	rightangle-=5;
	}
	else if(rightangle < -5)
	{
		rightangle+=5;
	}
    
    
    int targetAngle = -rightangle + 90;






	if(!resolve)
	{
		return targetAngle;
	}



    // Calculate the angle difference and ensure it's within -180 to 180 range
    float angleDifference = targetAngle - lastangle;
    if (angleDifference > 180)
        angleDifference -= 360;
    else if (angleDifference < -180)
        angleDifference += 360;

    // Linear interpolation
    float t = 0.1; // This is the interpolation factor; adjust as needed
    float newangle = lastangle + t * angleDifference;

    // Normalize newangle to keep within 0 to 360
    if (newangle >= 360)
        newangle -= 360;
    else if (newangle < 0)
        newangle += 360;

    return newangle;
}







