#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "motion.h"
#include "db_handler.h"
#include <cJSON.h>
#include <time.h>

char* extractMotionID(const char* source){

	const char *start = strchr(source, '/');
	const char *end = strchr(start + 1, '/');

	if(start != NULL && end != NULL){
		size_t length = end - (start + 1);
		char *destination = (char*)malloc(length + 1);
		if (destination != NULL) {
 			strncpy(destination, start + 1, length);
			destination[length] = '\0';

		}else{

			fprintf(stderr, "Memory allocation failed\n");
			exit(EXIT_FAILURE);
		}

		return destination;
	}else{

		char *destination = (char*)malloc(1);
	        if (destination != NULL) {
			destination[0] = '\0';
		      return destination;
		}
		else {

	            fprintf(stderr, "Memory allocation failed\n");
		    exit(EXIT_FAILURE);

		}
}

}



int motion_handle(char* topic, char* payload){


	if(strstr(topic,"status")!=NULL && strstr(topic, "read")==NULL){
	char* id = extractMotionID(topic);

		printf("\nid: %s\n", id);
		printf("\ndata: %s\n", payload);

		cJSON *root = cJSON_Parse(payload);

    		if (root == NULL) {
        	// Handle error, cJSON_Parse failed
        		printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        		return 0;
    		}


    		cJSON* motion = cJSON_GetObjectItem(root, "motion");
   		cJSON* timestamp = cJSON_GetObjectItem(root, "timestamp");
    		cJSON* active = cJSON_GetObjectItem(root, "active");
    		cJSON* vibration = cJSON_GetObjectItem(root, "vibration");
    		cJSON* lux = cJSON_GetObjectItem(root, "lux");
    		cJSON* bat = cJSON_GetObjectItem(root, "bat");
    		cJSON* tmp = cJSON_GetObjectItem(root, "tmp");
    		cJSON* tmp_value = cJSON_GetObjectItem(tmp, "value");
    		cJSON* tmp_units = cJSON_GetObjectItem(tmp, "units");
    		cJSON* tmp_is_valid = cJSON_GetObjectItem(tmp, "is_valid");


		char* motionDetected = cJSON_IsTrue(motion) ? "true" : "false";
    		int motionTimestamp =  timestamp->valueint;
    		char* motionActive =  cJSON_IsTrue(active) ? "true" : "false";
    		char* vibrationDetected =  cJSON_IsTrue(vibration) ? "true" : "false";
    		int luxIntensity =  lux->valueint;
    		int batteryLevel = bat->valueint;
    		double tempSensor = tmp_value->valuedouble; 
		char* tempAvailable = cJSON_IsTrue(tmp_is_valid) ? "true" : "false";

		time_t dateTime = (time_t) motionTimestamp;
    		struct tm *local_time = localtime(&dateTime);
		char time_str[20];
		strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local_time);








    printf("\n-----before %s-----\n", "insert_data_sql_format");

		const char* insert_data_sql_format = "INSERT INTO motion (id, motion, motion_time, motion_active, vibration, lux, battery, temperature, temp_available) VALUES ('%s', '%s', '%s', '%s','%s', %d, %d, %lf, '%s');";

		int size = snprintf(NULL, 0, insert_data_sql_format, id, motionDetected, time_str, motionActive, vibrationDetected, luxIntensity, batteryLevel, tempSensor, tempAvailable);
		char *insert_data_sql = malloc(size + 1);
		snprintf(insert_data_sql, size+1, insert_data_sql_format, id, motionDetected, time_str, motionActive, vibrationDetected, luxIntensity, batteryLevel, tempSensor, tempAvailable);



printf("\n-----after %s-----\n", "insert_data_sql_format");


		motion_t motionData = {
		
		.tableSchema = "CREATE TABLE IF NOT EXISTS motion ("
			       "id TEXT,"
			       "timestamp DATE DEFAULT (datetime('now','localtime')),"
			       "motion TEXT,"
			       "motion_time TEXT,"
			       "motion_active TEXT,"
			       "vibration TEXT,"
			       "lux INTEGER,"
			       "battery INTEGER,"
			       "temperature REAL,"
			       "temp_available TEXT);",
		.dataEntry = insert_data_sql,
		.operation = 'W'		
		
		};

        	sqlite3* key = connect_open_db("myDB");
        	if (write_to_db(key, &motionData)==1){

		free(id);
		free(insert_data_sql);
		printf("\n### free heap after writing in db motion ####\n");
		cJSON_Delete(root);
		}


	}



	return 1;

}







