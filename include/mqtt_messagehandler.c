#include <MQTTClient.h>
#include <cJSON.h>
#include <string.h>
#include "db_handler.h"
#include "shellyplug-s.h"
/*
 *
 * the mqtt_messagehandler.c has the duty to classify the messages coming from 
   the devices or mobile app using their topic names. After filtering it will
   send the messages to the db_handler.c to save the in the sqlite database
 *
 *
*/

//This function handles the incoming messages from the devices or mobile app
// by checking their topic.
int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: %.*s\n", message->payloadlen, (char*)message->payload);


    // check if shellyplug-s is available in the topic's message
    if(strstr(topicName,"shellyplug-s") != NULL){

	    /*Now here we need to handle the shelly plug's message 
	    //pack it in a structure and send it's memory address
	    //to the db_handler's function to save it
	    */

	    //-- Test Here--
	   //printf("%s", (char*)message->payload);

           //printf("--%s--", "it contains!!");
   shellyplug_s_handle(topicName , (char*)message->payload);



    }


    // Attempt to parse the received message as JSON
    cJSON *root = cJSON_Parse((char*)message->payload);

    if (root != NULL) {
        printf("Valid JSON!\n");

        // Additional processing with the cJSON structure can be done here if needed

        cJSON_Delete(root); // Clean up cJSON structure
    } else {
        printf("Not a valid JSON.\n");
    }



    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}


void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    if (cause)
        printf("     cause: %s\n", cause);
}
