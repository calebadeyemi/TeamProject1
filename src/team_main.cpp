//
//  team_main.cpp
//  
//
//  Created by Caleb Adeyemi on 2/13/19.
//

#include <stdio.h>
#include "Record.hpp"


int main(){
    Record r(3);
    cout << "RECORD SIZE " << r.size() << endl;
    r[2] = "John";
    
    string s = r[2];
    cout << s << endl;
    
    
    return 0;
}
