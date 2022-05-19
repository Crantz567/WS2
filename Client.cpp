#include <iostream>
#include "Functions.h"
#include "WS2.h"

int main()
{
	WS2 ws(1111, "127.0.0.1");
	
	if (!ws.connectToServer())
	{
		std::getchar();
		return 1;
	}

	std::getchar();
	return 0;
}

