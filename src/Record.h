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

    string operator[](int i) const;

    string& operator[](int i);
};

#endif /* Record_hpp */
