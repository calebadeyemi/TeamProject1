//
//  Record.hpp
//  
//
//  Created by Caleb Adeyemi on 2/13/19.
//

#ifndef Record_hpp
#define Record_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
class Record{
    vector<string> content;
public:
    Record(int recordSize);
    int size();
    string operator[](int i) const;
    string& operator[](int i);
    
    
};

#endif /* Record_hpp */
