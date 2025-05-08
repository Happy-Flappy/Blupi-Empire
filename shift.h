




class ShiftData
{
	public:
	int currentframe=0;
	float delay = 0.15;
	float totaltime=0;
	bool ended = false;
	std::vector <IntRect> rect;
};


ShiftData emptyshift; // for Idle function in blupi.h 

IntRect Shift(ShiftData &shift)
{
	shift.totaltime += seconds(1.f/60.f).asSeconds();
	
	if(shift.totaltime >= shift.delay)
	{
		
		shift.currentframe++;
		shift.totaltime=0;
			
		if(shift.currentframe >= shift.rect.size())
		{
			shift.currentframe=0;
			shift.ended = true;
		}
	}
	return shift.rect[shift.currentframe];
	
}