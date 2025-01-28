

std::vector <int> groundedge;

void getGroundEdge(Image &ground)
{
	int pos[ground.getSize().x];
	//get positions of edge pixels
	for(int x=0;x<ground.getSize().x;x++)
	{
	
		for(int y = ground.getSize().y-1; y > 0; y--)
		{
			if(ground.getPixel(x,y)==Color::Transparent)
			{
				pos[x]=y;
				break;
			}
		}
	}
	groundedge.resize(ground.getSize().x);
	
	
	for(int a=0;a<groundedge.size();a++)
	{
		groundedge[a]=pos[a];
	}
	
	
}









int getGroundAngle(Image &ground, int point, float lastangle, int range = 10,bool resolve=true)
{
    if (point + (range / 2) >= ground.getSize().x)
        return 0;

    Vector2f center;
    Vector2f right;

    center.x = point;
    right.x = point + (range / 2);

    center.y = groundedge[point];
    right.y = groundedge[point + (range / 2)];

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







