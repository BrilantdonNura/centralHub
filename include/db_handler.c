#include<sqlite3.h>
#include <stdlib.h>
#include <stdio.h>
sqlite3* connect_open_db(const char* dbName){
sqlite3 *db = NULL;
int rc = sqlite3_open("test.db", &db);

return db;
}

int write_to_db(sqlite3* db , const char* tableName){
int rc = 0;
// SQL query to create the EnergyMeter table
    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS EnergyMeter ("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,"
                                   "variable1 INTEGER,"
                                   "variable2 TEXT,"
                                   "variable3 REAL);";

    // Execute the SQL query to create the table
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    } else {
        printf("Table created successfully\n");
    }


// Sample values for variables
    int variable1Value = 42;
    const char *variable2Value = "Sample Text";
    double variable3Value = 123.45;

    // SQL query template with placeholders
    const char *insert_data_sql_format = "INSERT INTO EnergyMeter (variable1, variable2, variable3) VALUES (%d, '%s', %f);";

    // Calculate the size needed for the formatted SQL query
    int size = snprintf(NULL, 0, insert_data_sql_format, variable1Value, variable2Value, variable3Value);


    // Allocate memory for the formatted SQL query
    char *insert_data_sql = malloc(size + 1);

    // Format the SQL query with the variable values
    snprintf(insert_data_sql, size + 1, insert_data_sql_format, variable1Value, variable2Value, variable3Value);

    // Execute the SQL query
    rc = sqlite3_exec(db, insert_data_sql, 0, 0, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Data inserted successfully\n");
    }

    // Free the allocated memory
    free(insert_data_sql);

    // Close the database
    sqlite3_close(db);

}

