#include "meuinclude.h"

int slot (int x, int y)
{
	int slot;
	
	if (y >= 10 && y <= 234 )
	{
		if( x >= 10 && x <= 180 )
		{
			slot=0;
		}
		else if( x >= 190 && x <=360)
		{
			slot=1;
		}
		else if( x >= 370 && x <=540)
		{
			slot=2;
		}
		
	}
	else if( y >= 244 && y <= 468)
	{
		if( x >= 10 && x <= 180 )
		{
			slot=3;
		}
		else if( x >= 190 && x <=360)
		{
			slot=4;
		}
	}
				
	return slot;
}
