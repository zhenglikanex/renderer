#include <iostream>
#include "MyApp.h"

int main()
{
	MyApp app;
	if (app.Create())
	{
		app.Run();
	}
	
	return 0;
}