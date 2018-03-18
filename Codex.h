//
// Created by Slayton on 11/21/2017.
//

#ifndef THECONLANGCOMPILER_CODEX_H
#define THECONLANGCOMPILER_CODEX_H

#include "Grammar.h"

class Codex {
/* Codex ----- The Codex is the most important class of the conlang compiler and
 * the class in which everything comes together. For now storage will be handled
 * here as well, though eventually storage will mainly be handled by the scrinvener
 * and the sql database which it will be connected to.
 */
private:
    string languageName;
    string languageType;
    string languageDescription;
    Scrivener scrivener;
    Grammar grammar;
    map<pair<string, string>, Word*> languageDictionary; // <sound, type>, Word
    map<string, Word*> translationDictionary;
public:
    // Constructors
    Codex();
    Codex(string scrivenerInput);
    ~Codex();

    // Standard Getters
    string getLangaugeName() const;
    string getLanguageType() const;
    string getLanguageDescription() const;
    Word* getWord(string soundInput, string typeInput);
    Scrivener getScrivener(); //const make const after proper testing
    Grammar* getGrammar(); //const make const after proper testing
    map<pair<string, string>, Word*> getDictionary(); //const make const after proper testing

    // Standard Setters
    void setName(string nameInput);
    void setDescription(string descriptionInput);

    // Initializer Methods
    void initializeScrivener();
    void initializeGrammar(string fileDestination);
    void initializeDictionary(string fileDestination);

    // Word Methods
    void createWord(string input);
    void createCompoundWord(); /*
 *  chooses a random word construction rule, then randomly selects stems from the
 *  language, presents their meaning to the user, and allows them to assign a
 *  meaning and stemtype to the new word.
 */
    vector<Word*> chooseWordsToCombine();
    void removeWord(string sound, string type);

    // Translation Method
    string translate(string translationInput);

    // Input/Output Methods
    void writeCodexToFile();
    void writeCodexToFile(string filepath);

    // Console Methods
    void printStatistics();
    void printDictionary();
};

#endif //THECONLANGCOMPILER_CODEX_H
