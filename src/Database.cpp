#include <map>
#include <sstream>
#include <fstream>
#include "Database.h"
#include "DbError.h"

struct ComparisonStack {
    vector<string> equations;
    map<string, string> relations;
    map<string, string> comparisons;

    struct Comparison {
        string lhs;
        string rhs;
        char comparator;
        bool eval() {
        };
    };

    ComparisonStack() {
        relations["AND"] = '&';
        relations["OR"] = '|';
        relations["NOT"] = '!';
        comparisons[">"] = '>';
        comparisons[">="] = 'g';
        comparisons["<"] = '<';
        comparisons["<="] = 'l';
        comparisons["="] = '=';
        comparisons["("] = '(';
        comparisons[")"] = ')';
    }

    ComparisonStack(stringstream& ss) : ComparisonStack() {
        string currString;
        while (ss.good()) {
            ss >> currString;
            if (relations.find(currString) != relations.end()) {
                currString = relations[currString];
            } else if (comparisons.find(currString) != comparisons.end()) {
                currString = comparisons[currString];
            }

        }
        ss.clear();
    }
};

void Database::add(string tableName, Table table) {
    tables[tableName] = table;
    ComparisonStack c;
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
        Table table = tableMapping.second;
        auto attributes = table.getAttributes();
        dbStore << attributes.at(0);

        for (int i = 1; i < attributes.size() - 1; i++) {
            dbStore << " ," << attributes.at(i);
        }
        dbStore << endl;

        //for (Record record : table.getRecords()) {
        //    dbStore << record[0];
        //    for (int i = 1; i < attributes.size() - 1; i++) {
        //        dbStore << ", " << record[i];
        //    }
        //    dbStore << endl;
        //}
    }
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

Table Database::query(string select, string from, string where) {
    // get attribute list
    stringstream selectStream(select);
    vector<string> attributes;
    attributes = getAttributesFromQuery(selectStream);

    // get the proper table
    Table table = getTableFromQuery(from);

    // here we need to get the table and run the comparisons on it
    auto records = table.getRecords();

    // get all the (...) comparisons
    stringstream whereStream(where);
    ComparisonStack comp(whereStream);

    // generate a new table
    Table matchTable(attributes);
        // Apply comparisons on each record


        // if the record works, store in table

    return matchTable;
}

Table Database::parseComparison(stringstream& comparisons, vector<string>* aggregator) {
    // Every comparison will return a table, and subsequent comparisons will act on
    // that table. For example:
    //
    // Select * FROM table WHERE ((something > otherthing) AND ((this = that) OR NOT (this = 'bucket')))
    //
    // First returns a table where something > otherthing
    string lhs, comparator, rhs;
    comparisons >> lhs;

    // if open bracket, drop into another comparison. This will continue until fully resolved
    // (((this > that)))
    // (..
    //  (..
    //   (this > that)
    //              ..)
    //               ..)
    bool paren = false;
    if (lhs.at(0) == '(') {
        parseComparison(comparisons, aggregator);
        paren = true;
        // remove paren
        lhs.erase(0);
    }

    comparisons >> comparator;
    comparisons >> rhs;
    if (paren) {
        rhs.erase(rhs.size() - 1);
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

Table Database::getTableFromQuery(string &tableName) {
    if (tables.find(tableName) != tables.end()) {
        return tables[tableName];
    } else {
        throw DbError("requested table " + tableName + " not in the database");
    }
}
