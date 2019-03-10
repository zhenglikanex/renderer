#include <iostream>
#include "GLFW/glfw3.h"
#include "Config.h"

int main()
{
	aurora::Config config;
	config.Load("aurora.config");
	system("pause");
	return 0;
}