#ifndef TEAMDATABASE_DATABASE_H
#define TEAMDATABASE_DATABASE_H

#include <string>
#include "Table.h"

using namespace std;

class Database {
public:
    // Adds a new table to the database
    void add(string tableName, Table table);

    // Drops a table from the database (deletes it)
    void drop(string tableName);

    // Saves the database state
    void save(string fileName);

    // Retrieves a database from the disk
    Database load(string tableName);

    // Gets a list of the table names available
    vector<string> getTableNames(Database database);

    // Gets the tables from a database
    vector<Table> getTables(Database database);

    // Queries the database for records
    void query(string query);
};

#endif //TEAMDATABASE_DATABASE_H
