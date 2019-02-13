//
//  Record.cpp
//  
//
//  Created by Caleb Adeyemi on 2/13/19.
//

#include "Record.hpp"


int Record::size(){
    
    return this->content.size();
}

Record::Record(int newRecordSize){
    vector<string> newVec;
    newVec.resize(newRecordSize);
    content = newVec;
    cout << "Record constructor function" << endl;
}

string Record::operator[](int i) const
{
    cout << "Bracket operator function " << endl;
    return this->content[i];
}
string& Record::operator[](int i) 
{
    cout << "Bracket operator function " << endl;
    return this->content[i];
}

