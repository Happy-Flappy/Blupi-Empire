

	
bool checkGroundResolve(Image &ground,Vector2f &future,Vector2f &resolve)
{
	
	if(future.x>=0 && future.x < ground.getSize().x && future.y >= 0 && future.y < ground.getSize().y)
	{
	
		if(future.y > groundedge(future.x,future.y))
		{
			//collision on bottom center
			resolve.y = groundedge(future.x,future.y)+1;
		
			return true;
		}
		
		
		
		
	}
	return false;
}










bool checkGroundNow(Image &ground,Vector2f now)
{
	Vector2f future;
	future = now;
	if(future.x>=0 && future.x < ground.getSize().x && future.y >= 0 && future.y < ground.getSize().y)
	{
	
		if(future.y > groundedge(future.x,now.y))
		{
			//collision on bottom center
			return true;
		}
		
		
		
		
	}
	return false;
}







void Gravity(Sprite &sprite,Image &ground,Vector2f &velocity,Vector2f &now,float gravity)
{
	
	
	
	Vector2f future;
	Vector2f resolve;
	
	future.x = now.x + velocity.x;
	future.y = now.y + velocity.y;
	

	
	
	

	
	
	if(checkGroundResolve(ground,future,resolve))
	{
		
		
		velocity.y=0;
		
		now = Vector2f(future.x,resolve.y);
		
	}
	else
	{
		
		velocity.y += gravity;
		
		now = Vector2f(future.x,future.y);
	}
	
	
		
}