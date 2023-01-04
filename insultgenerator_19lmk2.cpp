//Lucas Krayacich 2022
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include "insultgenerator_19lmk2.h"

using namespace std;

FileException::FileException(const string &message) : message(message) {}
string& FileException::what() {return message;}


NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string &message): message(message) {}
string& NumInsultsOutOfBounds::what() {return message;}


InsultGenerator::InsultGenerator() {
    //instantiate
}

//read text file InsultsSource.txt into string vectors
// If the file cannot be read, the method should throw an exception.
void InsultGenerator::initialize()
{
    ifstream inputFile("/Users/lucas/CLionProjects/CMPE320/InsultsSource.txt");
    if(inputFile.fail()) {
        throw FileException("File failed to open.");
    }
    else if (inputFile.is_open()){
        string fileString;

            while (getline(inputFile, fileString)) {

                istringstream iss(fileString);
                vector<string> column123;
                string singleLine;

                while (getline(iss, singleLine, '\t'))
                    column123.push_back(singleLine);

                column1.push_back(column123[0]);
                column2.push_back(column123[1]);
                column3.push_back(column123[2]);

                srand(time(0));// figure out how to get this to return different values every time its called
            }

    }

}

//generates a single random insult by selecting strings from each column's vector
string InsultGenerator::talkToMe(){
    int col1Index = rand() % 49;
    int col2Index = rand() % 49;
    int col3Index = rand() % 49;

    string col1String = column1[col1Index];
    string col2String = column2[col2Index];
    string col3String = column3[col3Index];

    string fullInsult = "Thou " + col1String + " " + col2String + " " + col3String + "!";
    return fullInsult;

}
    //generate the requested number of insults by iteratively calling talkToMe() and checking for duplicates
    //throws an error if insultCount is out of boundaries
vector<string> InsultGenerator::generate(int insultCount){

    if (insultCount < 1 || insultCount > 10000) {
        throw NumInsultsOutOfBounds("Insult Count not within bounds");
    }
    vector<string> allInsults;

        for (int i = 0; i < insultCount; i++) {
            string currentInsult = talkToMe();
            int duplicateCounter = 0;
            allInsults.push_back(currentInsult);

            for (int j = 0; j < allInsults.size(); j++){
                if (currentInsult == allInsults[j]){
                    duplicateCounter++;
                }
            }
            if (duplicateCounter > 1){
                allInsults.pop_back();
                insultCount++;
            }
        }
        return allInsults;

}

//generate the requested number of insults and save them to a text file
//throws an exception if out of boundaries
vector<string> InsultGenerator:: generateAndSave(string filename, int insultCount){

    if (insultCount < 1 || insultCount > 10000) {
        throw NumInsultsOutOfBounds("Insult Count not within bounds");
    }
    //throws an exception if file cannot be read
    ofstream outputFile(filename);
    if (outputFile.fail()){
        throw FileException("File failed to open during generate and save");
    }
    vector<string> allInsults = generate(insultCount);
        for (int i = 0; i < allInsults.size(); i++){
            string currentInsult = allInsults[i];
            outputFile << currentInsult;
            outputFile << "\n";
        } //end while

    return allInsults;
}




