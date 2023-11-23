#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* extractDeviceID(const char *source) {
    const char *start = strchr(source, '/');
    const char *end = strchr(start + 1, '/');

    if (start != NULL && end != NULL) {
        // Calculate the length of the substring between the slashes
        size_t length = end - (start + 1);

        // Allocate memory for the destination buffer
        char *destination = (char*)malloc(length + 1);

        if (destination != NULL) {
            // Copy the substring to the destination buffer
            strncpy(destination, start + 1, length);

            // Null-terminate the destination string
            destination[length] = '\0';
        } else {
            // Handle memory allocation failure
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        return destination;
    } else {
        // Set the destination to an empty string if the pattern is not found
        char *destination = (char*)malloc(1);
        if (destination != NULL) {
            destination[0] = '\0';
            return destination;
        } else {
            // Handle memory allocation failure
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
}



int shellyplug_s_handle(char* topic , char* payload){
	if(strstr(topic, "energy") !=NULL ){
	char* id =extractDeviceID(topic); 
	printf("\nid: %s\n", id);
	printf("\ndata: %s\n", payload);

	free(id);


	}
	return 1;
}





