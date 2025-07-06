


std::vector<int> groundEdge;


void getGroundEdges(Image &ground)
{
	
	groundEdge.resize(ground.getSize().x);
	
	for(int x=0;x<ground.getSize().x;x++)
	{
	
		for(int y = 0; y < ground.getSize().y; y++)
		{
			if(ground.getPixel(x,y)!=Color::Transparent)
			{
				groundEdge[x] = y;				
				break;	
			}
		}
	}
	
	
}













int getGroundAngle(Image &ground, Vector2f now, float lastangle, int range = 10,bool resolve=true)
{
    if (now.x + (range / 2) >= ground.getSize().x)
        return 0;

    Vector2f center;
    Vector2f right;

    center.x = now.x;
    right.x = now.x + (range / 2);

    center.y = groundEdge[now.x];
    right.y = groundEdge[now.x + (range / 2)];

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







