//
// Created by Slayton on 11/21/2017.
//

#include "Codex.h"
// Constructors
Codex::Codex() {

}
Codex::Codex(string scrivenerInput) {
    languageName = scrivenerInput;
}

// Standard Getters
string Codex::getLangaugeName() const {
    return languageName;
}
string Codex::getLanguageType() const {
    return languageType;
}
string Codex::getLanguageDescription() const {
    return languageDescription;
}
Word* Codex::getWord(string soundInput, string typeInput) {
    pair<string, string> p = make_pair(soundInput, typeInput);
    if(languageDictionary.count(p) == 0) {
        cout << "No word of sound " + soundInput + " exists in the dictionary\n";
        return nullptr;
    }
    else
        return languageDictionary.at(p);
}
Scrivener Codex::getScrivener() {
    return scrivener;
}
Grammar* Codex::getGrammar() {
    return &grammar;
}
map<pair<string, string>, Word*> Codex::getDictionary() {
    return languageDictionary;
}

// Standard Setters
void Codex::setName(string nameInput) {
    languageName = nameInput;
}
void Codex::setDescription(string descriptionInput) {
    languageDescription = descriptionInput;
}

// Initializer Methods
void Codex::initializeScrivener() {
    scrivener = Scrivener();
    languageDescription = scrivener.readFileToStringVector(languageName + "\\Description.txt").at(0);
    cout << "Scrivener Initialized and Description Loaded\n";
}
void Codex::initializeGrammar(string fileDestination) {
    grammar = Grammar(&scrivener, fileDestination);
}
void Codex::initializeDictionary(string fileDestination) { // must be called after initgrammar
    vector<string> lines = scrivener.readFileToStringVector(fileDestination + "\\Words.txt");
    vector<string> parse;
    string line;
    int count = 0;

    vector<string> compoundWords;
    // Ensures that compound words are created after their stems
    for(int i = 0; i < lines.size(); ++i) {
        if(Scrivener::split(lines.at(i), '|').size() > 1) {
            line = lines.at(i);
            compoundWords.push_back(line);
        }
        else {
            createWord(lines.at(i));
        }
    }
    if(compoundWords.size() != 0) {
        for(int i = 0; i < compoundWords.size(); ++i) {
            createWord(compoundWords.at(i));
        }
    }
    cout << "Dictionary Loaded\n";
}

// Word Methods
void Codex::createWord(string input) {
    Word* word;
    word = new Word(input, &languageDictionary);
    pair<string, string> p = make_pair(word->getSound(), word->getType());

    // Checking for format
    if(word->getSound().at(0) < 97) {
        cout << "Word sound [" + word->getSound() + "] not lowercase,"
                                                            " and thus could be confused"
                                                            " with a nonterminal character, aborting.\n";
        return;
    }
    if(grammar.getSymbols()->count(word->getType()) == 0) {
        cout << "Word's type [" + word->getType() + "] is not present in symbols, aborting\n";
    }
    if(languageDictionary.count(p) != 0) {
        cout << "A word with this sound and type already exists within the dictionary, not adding\n";
        return;
    }
    grammar.assignWord(word);
    languageDictionary.insert(make_pair(p, word));
    translationDictionary.insert(make_pair(word->getMeaning(), word));
}
vector<Word*> Codex::chooseWordsToCombine() {
    return grammar.generateRandomWordVector("New_Word");
}
void Codex::createCompoundWord() {

}
void Codex::removeWord(string sound, string type) {
    map<pair<string, string>, Word*>::iterator crawler;
    if(languageDictionary.at(make_pair(sound, type)) == 0) {
        cout << "No word of sound " + sound + " exists in the dictionary\n";
    }
    else {
        for(crawler = languageDictionary.begin(); crawler != languageDictionary.end(); ++crawler) {
            if(crawler->second->getSound() == sound && crawler->second->getType() == type) {
                languageDictionary.erase(crawler);
            }
        }
        cout << "Word: " + sound + " has been removed from the dictionary\n";
    }
}

// Translation Method
string Codex::translate(string translationInput) {
    vector<string> script = Scrivener::split(translationInput, ' ');
    string langLine;
    string engLine;
    vector<pair<Symbol*, Word*>> symbolLine;
    vector<Word*> wordLine;
    map<string, Symbol*>* symbols = grammar.getSymbols();
    Word* temp;
    int placementCounter = 0;
    Word* w;
    for(int i = 0; i < script.size(); ++i) {
        if(translationDictionary.count(script.at(i)) == 0)
            return "One of the words wasn't in the dictionary";
        w = translationDictionary.at(script.at(i));
        wordLine.push_back(w);
    }
    while(placementCounter < wordLine.size() - 1) {
        if(wordLine.at(placementCounter)->getType() == "Adjective" && wordLine.at(placementCounter + 1)->getType() == "Noun") {
            temp = wordLine.at(placementCounter);
            wordLine.at(placementCounter) = wordLine.at(placementCounter + 1);
            wordLine.at(placementCounter + 1) = temp;
            ++placementCounter;
        }
        ++placementCounter;
    }
    for(int i = 0; i < wordLine.size(); ++i) {
        engLine += wordLine.at(i)->getMeaning() + " ";
        langLine += wordLine.at(i)->getSound() + " ";
    }
    cout << "Sentence in English: " + translationInput << endl;
    cout << "Sentence in Grammar of Language: " + engLine << endl;
    cout << "Sentence in Language: " + langLine << endl;
}

// Input/Output
void Codex::writeCodexToFile() {
    writeCodexToFile(languageName);
}
void Codex::writeCodexToFile(string filepath) {
    vector<string> wordLines;
    vector<string> wordtypeLines;
    vector<string> productionsLines;
    map<pair<string, string>, Word*>::iterator wordCrawler;
    map<string, Symbol*>::iterator typeCrawler;
    map<string, Symbol*>::iterator productionsCrawler; // made a duplicate for clarity of code
    for(wordCrawler = languageDictionary.begin(); wordCrawler != languageDictionary.end(); ++wordCrawler) {
        wordLines.push_back(wordCrawler->second->toIdentityOutputFormat());
    }
    for(typeCrawler = grammar.getSymbols()->begin(); typeCrawler != grammar.getSymbols()->end(); ++typeCrawler) {
        if(!typeCrawler->second->getTerminality()) {
            wordtypeLines.push_back(typeCrawler->second->toIdentityOutputFormat());
        }
    }
    for(productionsCrawler = grammar.getSymbols()->begin(); productionsCrawler != grammar.getSymbols()->end(); ++productionsCrawler) {
        if(!productionsCrawler->second->getTerminality()) {
            if(!productionsCrawler->second->getPreterminality())
                productionsLines.push_back(productionsCrawler->second->toProductionsOutputFormat());
        }
    }
    scrivener.writeStringVectorToFile(filepath + "\\Words.txt", wordLines);
    scrivener.writeStringVectorToFile(filepath + "\\Wordtypes.txt", wordtypeLines);
    scrivener.writeStringVectorToFile(filepath + "\\Productions.txt", productionsLines);
}

// Console Methods
void Codex::printStatistics() {
    cout << "Language Name: " + languageName + "\n";
    cout << "Language Description:\n\t" + languageDescription + "\n";
    cout << "Total Number of Words: " << languageDictionary.size() << "\n";
}
void Codex::printDictionary() {
    map<pair<string, string>, Word*>::iterator crawler;
    for(crawler = languageDictionary.begin(); crawler != languageDictionary.end(); ++crawler) {
        cout << crawler->second->toString() + "\n";
    }
}