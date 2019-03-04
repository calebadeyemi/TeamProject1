#include "gtest/gtest.h"
#include "Database.h"
#include "DbError.h"

TEST(DatabaseTests, AddsTable) {
    Table* t = new Table;
    Database d;
    d.add("table1", t);
    ASSERT_NO_THROW(d.getTables().at(0));
}

TEST(DatabaseTests, DropsTable) {
    Table* t = new Table;
    Database d;
    d.add("t1", t);
    d.drop("t1");
    ASSERT_THROW(d.getTables().at(0), out_of_range);
}

TEST(DatabaseTests, GetsTableNames) {
    Database d;
    vector<string> tableNames = {"t1", "t2", "t3"};
    for (auto name : tableNames) {
        Table* t = new Table;
        d.add(name, t);
    }

    vector<string> storedNames = d.getTableNames();
    for (int i = 0; i < tableNames.size(); i++) {
        ASSERT_EQ(tableNames[i], storedNames[i]);
    }
}

TEST(DatabaseTests, DoesQuery) {
    Database d;
    Table* t = new Table;
    d.add("table1", t);
    Table result = d.query("*", "table1", "((age > rank) OR (this < that)) AND NOT those = them");
}

TEST(DatabaseTests, StoresDb) {
    Database d;
    Table* t = new Table;
    for (int i = 0; i < 3; i++) {
        Record* r = new Record(4);
        for (int j = 0; j < 4; j++) {
            r->operator[](j) = "something" + to_string(j);
        }
        t->insert(r);
    }
    d.add("table1", t);
    d.save("testdb");
    Database* d2 = d.load("testdb");
    d2->save("otherTestDb");
}
