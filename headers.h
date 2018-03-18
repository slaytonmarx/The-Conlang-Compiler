//
// Created by Slayton on 11/30/2017.
//

#ifndef THECONLANGCOMPILER_HEADERS_H
#define THECONLANGCOMPILER_HEADERS_H

void mainTerminal();
void textSetter(string input);


/*
string fileExists(bool newLang) {
    /* fileExists ----- this ended up being a very important function, and too much of a hassle to
     * cover completely in the run function (hence the additional function). If the language already
     * exists it needs to make sure that the file for it exists, and if the language does not exist
     * it needs to make sure that the user doesn't accidentally write over one of their languages.

    string consolePrompt = "existing";
    ifstream file;
    string fileName;
    string userInput;
    vector<vector<string>> backup;
    string backupFileName;
    bool finished = false;
    if(newLang)
        consolePrompt = "new";
    consolePrompt = "Now write the file name of your <" + consolePrompt + "> conlang, remember that\n"
            "  language files are in .txt format so make sure to have .txt at the end of your file\n"
            "  you can also write 'q' to quit if you like.\nInput: ";
    cout << consolePrompt;
    // Checks both that an entered file has .txt and that the file exists.
    while(!finished) {
        cin >> userInput;
        if(userInput == "q")
            return "quit";
        while(!hasTxt(userInput))
            cin >> userInput;
        if(userInput == "q")
            return "quit";
        fileName = userInput;
        if(!newLang) {
            ifstream file(fileName);
            if(file.is_open()) {
                file.close();
                // Writes a backup
                backup = readFileToDictionary(fileName);
                backupFileName = fileName.substr(0,fileName.size() - 4) + "backup.txt";
                writeDictionaryToFile(backupFileName, backup);
                cout << "\nA backup of the dictionary called " + backupFileName + " has been saved to your local directory.\n";
                return fileName;
            }
            else {
                cout << "File: " + fileName + " could not be found, please enter a new file name\n";
            }
        }
        else {
            ifstream file(fileName);
            if(file.is_open()) {
                consolePrompt = "There's already a file of the name " + fileName + ", are you sure\n"
                        "  you want to write a new language over it? While there may be a backup file\n"
                        "  any changes to that language from the most recent section will be deleted\n"
                        "Input {y/n}: ";
                userInput = ensureProperInput(consolePrompt, {"y","n"});
                if(userInput == "y") {
                    file.close();
                    return fileName;
                }
                else
                    cout << "\nNew File Name: ";
            }
            else {
                file.close();
                return fileName;
            }
        }
    }
}
*/

#endif //THECONLANGCOMPILER_HEADERS_H
