//
// Lucas Krayacich 20201392
//

#ifndef INSULTGENERATOR_19LMK2_INSULTGENERATOR_19LMK2_H
#define INSULTGENERATOR_19LMK2_INSULTGENERATOR_19LMK2_H

#include <vector>
#include <iostream>
#include <string>

using namespace std;

//initializing class and associated methods
class InsultGenerator {
public:
    InsultGenerator();
    void initialize();
    string talkToMe();
    vector<string> generate(int insultCount);
    vector<string> generateAndSave(string filename, int insultCount);
    vector<string> column123, column1, column2, column3;
};

class FileException{
public:
    FileException(const string& message);
    string& what();
private:
    string message;
};

class NumInsultsOutOfBounds{
public:
    NumInsultsOutOfBounds(const string& message);
    string& what();
private:
    string message;
};


#endif //INSULTGENERATOR_19LMK2_INSULTGENERATOR_19LMK2_H


