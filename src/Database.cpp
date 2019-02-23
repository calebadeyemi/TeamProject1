#include <sstream>
#include "Database.h"
#include "DbError.h"

void Database::add(string tableName, Table table) {
    tables[tableName] = table;
}

void Database::drop(string tableName) {
    auto i = tables.find(tableName);
    tables.erase(i);
}

void Database::save(string fileName) {

}

Database Database::load(string tableName) {
    return Database();
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
        tableList.push_back(mapping.second);
    }
    return tableList;
}

Table Database::query(string query) {
    stringstream queryStream(query);

    vector<string> attributes;
    attributes = getAttributesFromQuery(queryStream);
    Table table = getTableFromQuery(queryStream);

    return Table();
}

vector<string> Database::getAttributesFromQuery(stringstream &query) {
    vector<string> attributes;
    string select, attribute;

    query >> select;
    query >> attribute;

    while (attribute != "FROM" || attribute != "from") {
        attributes.push_back(attribute);
        query >> attribute;
    }

    // last attribute _should_ be "from"
    attributes.pop_back();
    // move back the stream caret for next call
    query.unget();

    // If no attributes, there is a problem
    if (attributes.empty()) {
        throw DbError("no attributes given.");
    }
    // else carry on
    return attributes;
}

Table Database::getTableFromQuery(stringstream &query) {
    string from, tableName;

    query >> from;
    query >> tableName;

    if (tables.find(tableName) != tables.end()) {
        return tables[tableName];
    } else {
        throw DbError("requested table " + tableName + " not in the database");
    }
}
