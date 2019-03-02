#ifndef TEAMDATABASE_DATABASE_H
#define TEAMDATABASE_DATABASE_H

#include <map>
#include <string>
#include <sstream>
#include "Table.h"

using namespace std;

class Database {
    map<string, Table*> tables;
    vector<string> getAttributesFromQuery(stringstream& query);
    Table getTableFromQuery(string &tableName);
    Table parseComparison(stringstream& comparisons, vector<string>* aggregator = nullptr);

public:
    // Adds a new table to the database
    void add(string tableName, Table *table);

    // Drops a table from the database (deletes it)
    void drop(string tableName);

    // Saves the database state
    void save(string fileName);

    // Retrieves a database from the disk
    Database load(string tableName);

    // Gets a list of the table names available
    vector<string> getTableNames();

    // Gets the tables from a database
    vector<Table> getTables();

    // Queries the database for records and returns a Table
    Table query(string select, string from, string where);
};

#endif //TEAMDATABASE_DATABASE_H
