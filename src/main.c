#include <stdio.h>
#include <stdlib.h>
#include <MQTTClient.h>
#include <unistd.h>
#include "mqtt_initializer.h"

// code
MQTTClient client;
MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;


int main(int argc, char* argv[]) {

if(mqtt_initialize(&client, &conn_opts) == 0){
	printf("%s", "connected OK!\n");


	if(mqtt_subscribe(&client, "hello") ==0){

		printf("subscribed OK\n");
	}


}

else{

	printf("%s", "failed to connect!\n");

}



while(1){


}




mqtt_cleanup(&client);
printf("%s", "disconnected!\n");

    return EXIT_SUCCESS;
}

