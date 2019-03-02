#include <map>
#include <regex>
#include <sstream>
#include <fstream>
#include "Database.h"
#include "DbError.h"

void Database::add(string tableName, Table* table) {
    tables[tableName] = table;
}

void Database::drop(string tableName) {
    auto i = tables.find(tableName);
    tables.erase(i);
}

void Database::save(string fileName) {
    // serialize and write to a file
    ofstream dbStore(fileName, ios::trunc);

    // add headers
    for (auto const &tableMapping : tables) {
        string tableName = tableMapping.first;
        Table* table = tableMapping.second;

        dbStore << "TABLE " << tableName << endl;

        for (int i = 0; i < table->getSize(); i++) {
            Record* record = table->getRecord(i);
            for (int j = 0; j < record->size(); j++) {
                dbStore << record->operator[](j) << ",";
            }
            dbStore << endl;
        }
    }
}

Database Database::load(string fileName) {
    ifstream dbStore(fileName);
    string tableName;
    int size = 0;
    while(dbStore.good()) {
        char* line;
        dbStore.getline(line, RLIM_INFINITY, '\n');

        regex r("TABLE *");
        // if this is new table, build the table
        if (regex_match(line, r)) {
            tableName = regex_replace(line, r, "TABLE *-$2");
            Table* t = new Table;
            size = 0;
            tables[tableName] = t;

            // get attributes from next line
            dbStore.getline(line, RLIM_INFINITY, '\n');
            char* attributes = strtok(line, ",");
            while(attributes != nullptr) {
                t->addAttribute(string(attributes));
                attributes = strtok(nullptr, ",");
                size++;
            }
            continue;
        }

        char* attributes = strtok(line, ",");
        Record* record = new Record(size);
        // else populate a new record
        int index = 0;
        while(attributes != nullptr) {
            record->operator[](index) = string(attributes);
            attributes = strtok(nullptr, ",");
            index++;
        }
    }
}

vector<string> Database::getTableNames() {
    vector<string> tableNames;
    for (auto const &mapping : tables) {
        tableNames.push_back(mapping.first);
    }
    return tableNames;
}

vector<Table> Database::getTables() {
    vector<Table> tableList;
    for (auto const &mapping : tables) {
        tableList.push_back(*mapping.second);
    }
    return tableList;
}

Table Database::query(string select, string from, string where) {

}

vector<string> Database::getAttributesFromQuery(stringstream &query) {
    vector<string> attributes;
    string select, attribute;

    while (query.good()) {
        query >> attribute;
        attributes.push_back(attribute);
    }

    // If no attributes, there is a problem
    if (attributes.empty()) {
        throw DbError("no attributes given.");
    }
    // else carry on
    return attributes;
}

Table Database::getTableFromQuery(string &tableName) {
    if (tables.find(tableName) != tables.end()) {
        return *tables[tableName];
    } else {
        throw DbError("requested table " + tableName + " not in the database");
    }
}
