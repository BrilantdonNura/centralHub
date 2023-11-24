#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "shellyplug-s.h"
#include "db_handler.h"

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

	char *endptr;

	double energySpent = strtod(payload, &endptr);
	    // Check for conversion errors
	      if (*endptr != '\0') {
	      fprintf(stderr, "Conversion error: Not a valid double\n");
	               
	         }
/////////////////////////

    // SQL query template with placeholders
const char *insert_data_sql_format = "INSERT INTO shellyplugs (id, energy) VALUES ('%s', %lf);";

    // Calculate the size needed for the formatted SQL query
    int size = snprintf(NULL, 0, insert_data_sql_format, id, energySpent);


    // Allocate memory for the formatted SQL query
    char *insert_data_sql = malloc(size + 1);

    //Format the SQL query with the variable values
    snprintf(insert_data_sql, size + 1, insert_data_sql_format, id, energySpent);


   shellyplug_s plugsData = {
        .id = id,          // Initialize to appropriate values
        .energy = energySpent,       // Initialize to appropriate values
        .tableSchema = "CREATE TABLE IF NOT EXISTS shellyplugs ("
                        "id TEXT,"
			"timestamp DATE DEFAULT (datetime('now','localtime')),"
                       // timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,"
                        "energy REAL);",
        .dataEntry = insert_data_sql
    };



	printf("\n---from struct %s, %lf---\n", plugsData.id, plugsData.energy);	

	sqlite3* key = connect_open_db("myDB");
	if (write_to_db(key, &plugsData)==1){

	free(id);
        free(insert_data_sql);
} 


	}
	return 1;
}





