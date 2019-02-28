//
// Created by Henning Futrell on 2019-02-27.
//

#include "gtest/gtest.h"
#include "Table.h"
#include "Record.h"

TEST(TableTests, CrossJoins) {
    vector<string> vans = {"make", "model"};
    vector<string> interiors = {"seats", "paint"};
    Table table1(vans);
    Record dodge(2);
    dodge[0] = "dodge";
    dodge[1] = "caravan";
    table1.insert(&dodge);

    Record ford(2);
    ford[0] = "ford";
    ford[1] = "windstar";
    table1.insert(&ford);

    Table table2(interiors);
    Record i1(2);
    i1[0] = "cloth";
    i1[1] = "standard";
    table2.insert(&i1);

    Record i2(2);
    i2[0] = "leather";
    i2[1] = "standard";
    table2.insert(&i2);

    Record i3(2);
    i3[0] = "leather";
    i3[1] = "premium";
    table2.insert(&i3);

    vector<string> e = {"make", "model", "seats", "paint"};
    Table expected(e);
    auto dodge1 = dodge;
    auto dodge2 = dodge;
    auto dodge3 = dodge;

    auto ford1 = ford;
    auto ford2 = ford;
    auto ford3 = ford;

    dodge1.addAttribute("cloth");
    dodge1.addAttribute("standard");
    ford1.addAttribute("cloth");
    ford1.addAttribute("standard");

    dodge2.addAttribute("leather");
    dodge2.addAttribute("standard");
    ford2.addAttribute("leather");
    ford2.addAttribute("standard");

    dodge3.addAttribute("leather");
    dodge3.addAttribute("premium");
    ford3.addAttribute("leather");
    ford3.addAttribute("premium");

    expected.insert(&dodge1);
    expected.insert(&dodge2);
    expected.insert(&dodge3);
    expected.insert(&ford1);
    expected.insert(&ford2);
    expected.insert(&ford3);

    auto actual = table1.crossJoin(&table1, &table2);

    for (int i = 0; i < actual->getSize(); i++) {
        ASSERT_TRUE(expected.getRecord(i)->operator[](2) == actual->getRecord(i)->operator[](2)) ;
    }
}

TEST(TableTests, NaturalJoins) {
    vector<string> students = {"name", "school"};
    vector<string> schools = {"school", "city"};
    Table table1(students);
    Record joe(2);
    joe[0] = "Joe Smith";
    joe[1] = "Rice";
    table1.insert(&joe);

    Record jill(2);
    jill[0] = "Jill Smith";
    jill[1] = "LSU";
    table1.insert(&jill);

    Record sam(2);
    sam[0] = "Sam Jones";
    sam[1] = "TAMU";
    table1.insert(&sam);

    Record sue(2);
    sue[0] = "Sue Jones";
    sue[1] = "Rice";
    table1.insert(&sue);

    Table table2(schools);
    Record tamu(2);
    tamu[0] = "TAMU";
    tamu[1] = "College Station";
    table2.insert(&tamu);

    Record rice(2);
    rice[0] = "Rice";
    rice[1] = "Houston";
    table2.insert(&rice);

    Record lsu(2);
    lsu[0] = "LSU";
    lsu[1] = "Baton Rouge";
    table2.insert(&lsu);

    vector<string> e = {"name", "school", "city"};
    Table expected(e);

    joe.addAttribute("Houston");
    jill.addAttribute("Baton Rouge");
    sam.addAttribute("College Station");
    sue.addAttribute("Houston");
    expected.insert(&joe);
    expected.insert(&jill);
    expected.insert(&sam);
    expected.insert(&sue);

    table2.makeKey("school");
    auto actual = table1.naturalJoin(&table1, &table2);

    for (int i = 0; i < actual->getSize(); i++) {
        ASSERT_TRUE(expected.getRecord(i)->operator[](2) == actual->getRecord(i)->operator[](2)) ;
    }
}

