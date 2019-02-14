
#include "Table.h"
#include "Record.h"

int main() {
 Record r(3);
 cout << "RECORD SIZE " << r.size() << endl;
 r[2] = "John";

 string s = r[2];
 cout << s << endl;


 vector<string> attribute = {"id", "name", "birthdate", "university"};
 string attribute_name = "attribute name";
 string record = "record";
 string table1 = "table1";
 string table2 = "table2";

 Table t(attribute);

 t.delete_attribute(attribute_name);
 t.insert_attribute(record);

 t.add_attribute(attribute_name);
 t.get_attribute();
 t.get_size();

 t.individual_record(record);
 t.name_key(attribute_name);

 t.cross_join(table1, table2);
 t.natural_join(table1, table2);
 t.calculations(attribute_name);

 Table tt;

 return 0;
}