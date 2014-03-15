#include "stdafx.h"
#include "Test.h"
#include <iostream>
#include "conio.h"


int main()
{
	try 
	{
		TestLevenshteinDestination();
	}
	catch (const std::exception& ex) 
	{
		std::cerr << "Exception: " << ex.what() << std::endl;
		return -1;
	}
	getch();
	return 0;
}
