//
// Created by Henning Futrell on 2019-02-23.
//

#include "DbError.h"

DbError::DbError(string msg) {
    message = msg;
}

string DbError::getMessage() {
    return "Database error: " + message;
}
