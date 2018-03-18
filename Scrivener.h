//
// Created by Slayton on 11/21/2017.
//

#ifndef THECONLANGCOMPILER_SCRIVENER_H
#define THECONLANGCOMPILER_SCRIVENER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <direct.h>
#include <map>
using namespace std;

class Scrivener {
public:
    Scrivener();
    vector<string> readFileToStringVector(string fileName); /*
     * readFileToStringVector(string fileName) ----- takes in a string and checks
     *      if there exists a file in the local directory with that name, if so,
     *      copies the contents of the file to a string vector and returns it.\
     *
     < Requires: Filename with proper .txt and existing file.
     < Modifies: Nothing
     < Effects: Returns a string vector
     */
    void writeStringVectorToFile(string fileName, vector<string> rawLines);
    static vector<string> split(string line, char splitChar);
};


#endif //THECONLANGCOMPILER_SCRIVENER_H
