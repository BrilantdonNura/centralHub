#ifndef SHELLYPLUGS_H
#define SHELLYPLUGS_H
#include<stdbool.h>

typedef struct shellyplug_s{

	char* id; // Will get it from the topic
	double energy; // energy in watt/minute
        char *tableSchema ;
	char *dataEntry ;
	//double instantPower; // instant power in watts
	//bool state; // State of the device
	//double internalTemperature; // Internal temperature of the device
//	bool overTemperature; // Over temperature True - NOT OK, False - OK

}shellyplug_s;



/*
 * This function will handle the data for the shellyplug-s
 * product 
 * Parameters
 * 1. (char*) id that we'll get from the topic
 * 2. (char*) payload  message from the 
 * */
int shellyplug_s_handle(char*, char*);

#endif
