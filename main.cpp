
#include "Database.h"
#include "Table.h"
#include "Record.h"

int main() {

 //////////////////////////////////////////////////////////////////////////////////
 //
 // Record
 //
 //////////////////////////////////////////////////////////////////////////////////

 Record r(3);
 cout << "RECORD SIZE " << r.size() << endl;
 r[2] = "John";

 string s = r[2];
 cout << s << endl;

 vector<string> attributes = {"id", "name", "birthdate", "university"};
 string attribute_name = "attribute name";
 string record = "record";
 string table1 = "table1";
 string table2 = "table2";


 //////////////////////////////////////////////////////////////////////////////////
 //
 // Table
 //
 //////////////////////////////////////////////////////////////////////////////////

 Table t(attributes);

 string attribute = attributes[0];
 t.count(attribute);
 t.deleteAttribute(attribute);
 t.insert(&r);
 t.addAttribute(attribute_name);
 t.getAttributes();
 t.getSize();
 t.getRecords();
 t.makeKey(attribute_name);
 t.count(attribute);
 t.max(attribute);
 t.min(attribute);

 Table t1;
 Table t2;
 t.naturalJoin(&t1, &t2);
 t.crossJoin(&t1, &t2);


 //////////////////////////////////////////////////////////////////////////////////
 //
 // Database
 //
 //////////////////////////////////////////////////////////////////////////////////

 Database d;

 string tableName = "test_table";

 d.add(tableName, &t);
 d.save(tableName);
 d.load(tableName);
 d.getTableNames();
 d.getTables();
 d.query("*", "test_table", "this > bananas");
 d.drop(tableName);
}