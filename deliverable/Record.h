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

public:

    explicit Record(int recordSize);

    int size();

    string operator[](int index) const;

    string& operator[](int index);
};

#endif /* Record_hpp */
