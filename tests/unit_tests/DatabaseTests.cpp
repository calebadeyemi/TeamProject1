#include "gtest/gtest.h"
#include "Database.h"
#include "DbError.h"

TEST(DatabaseTests, AddsTable) {
    Table t;
    Database d;
    d.add("table1", t);
    ASSERT_NO_THROW(d.getTables().at(0));
}

TEST(DatabaseTests, DropsTable) {
    Table t;
    Database d;
    d.add("t1", t);
    d.drop("t1");
    ASSERT_THROW(d.getTables().at(0), out_of_range);
}

TEST(DatabaseTests, GetsTableNames) {
    Table t;
    Database d;
    vector<string> tableNames = {"t1", "t2", "t3"};
    for (auto name : tableNames) {
        d.add(name, t);
    }

    vector<string> storedNames = d.getTableNames();
    for (int i = 0; i < tableNames.size(); i++) {
        ASSERT_EQ(tableNames[i], storedNames[i]);
    }
}

TEST(DatabaseTests, DoesQuery) {
    Database d;
    Table t;
    d.add("table1", t);
    Table result = d.query("*", "table1", "((age > rank) OR (this < that)) AND NOT those = them");
}
