#include"pocket.h"
#include"table.h"

int pocket::pocketIndexCnt = 0;

void pocket::Initialise(void)
{
	//work out pocket position
	if(index == 0)
	{
		position(0) = -TABLE_X;
		position(1) = TABLE_Z;
	}
	else if(index == 1)
	{
		position(0) = TABLE_X;
		position(1) = TABLE_Z;
	}
	else if (index == 2)
	{
		position(0) = TABLE_X;
		position(1) = 0;
	}
	else if (index == 3)
	{
		position(0) = TABLE_X;
		position(1) = -TABLE_Z;
	}
	else if (index == 4)
	{
		position(0) = -TABLE_X;
		position(1) = -TABLE_Z;
	}
	else if (index == 5)
	{
		position(0) = -TABLE_X;
		position(1) = 0;
	}
	return;
}