#include <stdio.h>
#include <stdlib.h>
#include <MQTTClient.h>
#include <unistd.h>
#include "mqtt_initializer.h"

// code main
MQTTClient client;
MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;


int main(int argc, char* argv[]) {

if(mqtt_initialize(&client, &conn_opts) == 0){
	printf("%s", "connected OK!\n");

	// this subscription contains shellyplug-s, TRVs etc..
	if(mqtt_subscribe(&client, "shellies/#") ==0){

		printf("subscribed OK\n");
	}
	else{
	
		printf("subscribed FAIL\n");
	}

}

else{

	printf("%s", "failed to connect!\n");

}

char c = 120;
while(c>0){
sleep(1);
c--;
}


mqtt_cleanup(&client);
printf("%s", "disconnected!\n");

    return EXIT_SUCCESS;
}

