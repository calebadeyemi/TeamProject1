//
//  Record.hpp
//  
//
//  Created by Caleb Adeyemi on 2/13/19.
//

#ifndef Record_h
#define Record_h

#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Record{
    vector<string> content;
    vector<string> attributes;

public:

    Record();
    explicit Record(int recordSize);

    int size();

    string operator[](int index) const;

    string& operator[](int index);

    string& operator[](string attribute);

    void deleteAttribute(int index);
    
    void addAttribute(string attribute);

    void addAttribute();
};

#endif /* Record_hpp */
