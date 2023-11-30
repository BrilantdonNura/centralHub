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
	if(mqtt_subscribe(&client, "shellies/#") == 0){

		printf("subscribed shellies:  OK\n");
	}
	else{
	
		printf("subscribed shellies: FAIL\n");
	}


	if(mqtt_subscribe(&client, "shellyplusht-80646fc9ba80/#") == 0){

		printf("subscribed shellyplusht: OK\n");
	}
	else{
	
		printf("subscribed shellyplusht  FAIL\n");
	}



}

else{

	printf("%s", "failed to connect!\n");

}

int c = 40;
while(c>0){
sleep(1);
c--;
}


mqtt_cleanup(&client);
printf("%s", "disconnected!\n");

    return EXIT_SUCCESS;
}

