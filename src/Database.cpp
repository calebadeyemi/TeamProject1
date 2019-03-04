#include <map>
#include <regex>
#include <sstream>
#include <fstream>
#include "Database.h"
#include "DbError.h"
#include "QueryParser.h"

Database::~Database() {
    for (auto table : tables) {
    }
}


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

        dbStore << "TABLE " << tableName;

        for (int i = 0; i < table->getSize(); i++) {
            Record* record = table->getRecord(i);
            dbStore << endl;
            for (int j = 0; j < record->size(); j++) {
                dbStore << record->operator[](j) << ",";
            }
        }
    }
    dbStore.close();
}

Database* Database::load(string fileName) {
    ifstream dbStore(fileName);
    string tableName;
    int size = 0;
    Database* loadedDb = new Database;

    while(dbStore.good()) {
        string line;
        getline(dbStore, line);

        // if this is new table, build the table
        regex r("TABLE (.*)");
        if (regex_match(line, r)) {
            tableName = regex_replace(line, r, "$2");
            Table* t = new Table;
            size = 0;
            loadedDb->add(tableName, t);

            // get attributes from next line
            getline(dbStore, line);
            char* lineCopy = new char[line.size() + 1];
            copy(line.begin(), line.end(), lineCopy);
            char* attribute = strtok(lineCopy, ",");
            while(attribute != nullptr) {
                t->addAttribute(attribute);
                attribute = strtok(nullptr, ",");
                size++;
            }
            delete[] lineCopy;
        } else {
            char* lineCopy = new char[line.size() + 1];
            copy(line.begin(), line.end(), lineCopy);
            char* attributes = strtok(lineCopy, ",");
            Record* record = new Record(size);
            // else populate a new record
            int index = 0;
            while (attributes != nullptr) {
                record->operator[](index) = string(attributes);
                attributes = strtok(nullptr, ",");
                index++;
            }
            loadedDb->getTable(tableName)->insert(record);
            delete[] lineCopy;
        }
    }
    dbStore.close();
    remove(fileName.c_str());
    return loadedDb;
}

vector<string> Database::getTableNames() {
    vector<string> tableNames;
    for (auto const &mapping : tables) {
        tableNames.push_back(mapping.first);
    }
    return tableNames;
}

vector<Table*> Database::getTables() {
    vector<Table*> tableList;
    for (auto const &mapping : tables) {
        tableList.push_back(mapping.second);
    }
    return tableList;
}

Table Database::query(string select, string from, string where) {
    Table* t = getTableFromQuery(from);
    vector<string> attributes = t->getAttributes();
    Table* newTable = new Table(attributes);

    vector<Record*> records = t->getRecords();
    QueryParser parser;

    for (auto record : records) {
        if (parser.eval(attributes, record, where)){
            newTable->insert(record);
        }
    }

    if (select == "*") {
        return *newTable;
    } else {
        vector<string> selectedAttributes;
        char* selectCopy = new char[select.size() + 1];
        std::copy(select.begin(), select.end(), selectCopy);
        selectCopy[select.size()] = '\0';

        char* tokens = strtok(selectCopy, ",");
        while (tokens != nullptr) {
            selectedAttributes.push_back(string(tokens));
            tokens = strtok(nullptr, ",");
        }

        Table *selectedTable = new Table(selectedAttributes);
        for (auto record : records) {
            Record* copyRecord = new Record(selectedAttributes.size());
            for (int i = 0; i < selectedAttributes.size(); i++) {
                copyRecord->operator[](i) = parser.getIndexOfAttribute(attributes, selectedAttributes.at(i));
            }
            selectedTable->insert(copyRecord);
        }
        return *selectedTable;
    }
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

Table* Database::getTableFromQuery(string &tableName) {
    if (tables.find(tableName) != tables.end()) {
        return tables[tableName];
    } else {
        throw DbError("requested table " + tableName + " not in the database");
    }
}

Table* Database::getTable(string tableName) {
    return tables[tableName];
}