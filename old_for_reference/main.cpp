
#include "HighNoon.hpp"

int main()
{
	HighNoon m_highNoon = HighNoon();

	bool keep_running = true;
	while(keep_running){
		keep_running = m_highNoon.GameCycle();
	}

	return 0;
}