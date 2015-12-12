//
//  main.cpp
//  dbtest
//
//  Created by Matthew Thorne on 28/03/2014.
//  Copyright (c) 2014 Matthew Thorne. All rights reserved.
//

#include <iostream>
#include <sqlite3.h>

#define DATABASE "/Users/matt/Documents/Projects/CPP/dbtest/xyz.db"

static int callback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
    for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int executeStatement(std::string sqlStatement)
{
    sqlite3 *db;
    int ret = 1;
    char *zErrMsg = 0;
    const char* data = "Callback function called";
    
    if (sqlite3_open(DATABASE, &db)==0){
        ret = sqlite3_exec(db, sqlStatement.c_str(), callback, (void*)data, &zErrMsg);
        std::cout << ret << "\n";
        if (ret>0) std::cerr << zErrMsg << "\n";
    }
    
    sqlite3_close(db);
    
    return ret;
}



int main(int argc, const char * argv[])
{

    // insert code here...
    std::cout << "Hello, World!\n";
    
    if (executeStatement("CREATE TABLE COMPANY2(ID INTEGER PRIMARY KEY AUTOINCREMENT, NAME TEXT, AGE INT, ADDRESS CHAR(50),SALARY REAL);")==0){
        std::cout << "Table created!\n";
    }
    
    if (executeStatement("insert into company2 (NAME, AGE, ADDRESS, SALARY) values ('Matt', 35, 'Test', 0);")==0){
        std::cout << "Data inserted!\n";
    }
    
    if (executeStatement("SELECT * FROM COMPANY2 WHERE AGE='35';")==0){
        std::cout << "Data!\n";
    }
    
    return 0;
}

