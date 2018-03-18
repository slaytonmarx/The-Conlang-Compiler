//
// Created by Slayton on 11/21/2017.
//
#include "Scrivener.h"

Scrivener::Scrivener() {

}

vector<string> Scrivener::readFileToStringVector(string fileName) {
    string line;
    vector<string> fileVector;
    ifstream file(fileName);
    if(file.is_open()) {
        while(getline(file,line)) {
            fileVector.push_back(line);
        }
        file.close();
    }
    else
        cout << "Couldn't find file " + fileName + ", did you add .txt?";
    return fileVector;
}
void Scrivener::writeStringVectorToFile(string fileName, vector<string> rawLines) {
    ofstream file(fileName);
    string line;
    if(file.is_open()) {
        for(int i = 0; i < rawLines.size(); ++i) {
            file << rawLines.at(i) + "\n";
        }
        file.close();
    }
    else
        cout << "Unable to open the file";
}
vector<string> Scrivener::split(string line, char splitChar) {
    vector<string> sVector;
    int beginning = 0;
    int end = 0;
    for(int i = 0; i < line.size(); ++i) {
        end = i;
        if(line.at(i) == splitChar || i == line.size() - 1) {
            if(i == line.size() - 1)
                ++end;
            sVector.push_back(line.substr(beginning, end - beginning));
            beginning = end + 1;
        }
    }
    return sVector;
}
bool hasTxt(string fileName) {
    if(!(fileName.substr(fileName.size() - 4, 4) == ".txt")) {
        cout << "The language name you entered has no .txt at the end"
                "\n  it would be best, all things considered, to write that"
                "\n  .txt at the end of your fileName, otherwise it won't"
                "\n  be read.\nNew file name: ";
        return false;
    }
    else {
        cout << "\nChecks out, sounds good.\n";
        return true;
    }
}