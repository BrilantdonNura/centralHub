#include<MQTTClient.h>
#include <cJSON.h>


int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: %.*s\n", message->payloadlen, (char*)message->payload);


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
