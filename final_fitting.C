// imports
#include "math_functions.h"
#include "main_functions.h"
#include <iostream> 
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <string>

void final_fitting(){

	// casting values from txt file to arrays //

	// need to make a value high enough that it's able to contain the info
	const int nmax = 2000;
	// storing values
	int xs[nmax]={0};
	int ys[nmax]={0};
	int sigmas[nmax]={0};
	int lasts[nmax]={0};

	castdata("data.txt",xs,ys,sigmas,lasts);
	
	eventloop(xs,ys,sigmas,lasts);
	
}
