#include<sqlite3.h>
#include <stdlib.h>
#include <stdio.h>
#include "shellyplug-s.h"
sqlite3* connect_open_db(const char* dbName){
sqlite3 *db = NULL;
int rc = sqlite3_open("test.db", &db);

return db;
}


int write_to_db(sqlite3* db , void* dataStruct){
int rc = 0;

shellyplug_s* dataFromDevice = (shellyplug_s *) dataStruct;

printf("\n------db_handler.c-----\n");
printf("%s", dataFromDevice->id);
printf("\n------------------\n");

// SQL query to create the EnergyMeter table
    const char *create_table_sql = dataFromDevice->tableSchema;
    char *insert_data_sql = dataFromDevice->dataEntry;
    // Execute the SQL query to create the table
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    } else {
        printf("Table created successfully\n");
    }



    // Execute the SQL query
    rc = sqlite3_exec(db, insert_data_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Data inserted successfully\n");
   }

    // Free the allocated memory
    //free(insert_data_sql);

    // Close the database
    sqlite3_close(db);

    return  1;
}

