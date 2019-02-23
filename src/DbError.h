#ifndef DATABASE_DBERROR_H
#define DATABASE_DBERROR_H

#include <string>

using namespace std;

class DbError {
    string message;
public:
    // Build an error
    DbError(string msg);

    // get the message
    string getMessage();
};


#endif //DATABASE_DBERROR_H
