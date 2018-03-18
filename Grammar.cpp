//
// Created by Slayton on 11/21/2017.
//

#include <random>
#include "Grammar.h"

// ==================== BEGIN ==================== //
// =============== SYMBOL METHODS ================ //
// Constuctors
Symbol::Symbol() {

}
Symbol::Symbol(string nameInput, int idInput) : name(nameInput), id(idInput) {

}

// Evaluation Method
vector<Symbol*> Symbol::evaluate(int depth) {}
Symbol * Symbol::evalute() {}
bool Symbol::searchProductions(vector<Symbol *> &sentance, int depth, int maximumDepth) {}

// Standard Getters
string Symbol::getName() const {
    return name;
}
int Symbol::getId() const {
    return id;
}
bool Symbol::getTerminality() const {
    return isTerminal;
}
bool Symbol::getPreterminality() const {
}
vector<vector<Symbol*>> Symbol::getProductions() {}

// Standard Setters
void Symbol::setName(string nameInput) {
    name = nameInput;
}
void Symbol::setId(int idInput) {
    id = idInput;
}
vector<Symbol*> Symbol::addProduction(string stringInput, map<string, Symbol*>* symbolsInput) {

}
void Symbol::addProduction(Symbol *wordInput) {

}

// Input/Output Methods [ALL VIRTUAL METHODS]
void Symbol::parseProductionsInput(string unparsedString, map<string, Symbol *>* symbolsInput) {

} // Used by nonterm
string Symbol::toIdentityOutputFormat() {
}
string Symbol::toProductionsOutputFormat() {
}

// Console Methods
string Symbol::toString() {
    return "";
}
string Symbol::bundleContents() {}
// ===================== END ===================== //
// =============== SYMBOL METHODS ================ //



// ==================== BEGIN ==================== //
// ================ WORD METHODS ================= //
// Constructors
Word::Word() {
    sound = "unused";
    meaning = "unused";
    type = "error";
    isTerminal = true;
}
Word::Word(string unparsedInput, map<pair<string, string>, Word*>* dictionaryInput) {
    dictionary = dictionaryInput;
    isTerminal = true;
    readInputString(unparsedInput);
}
Word::Word(string soundInput, string typeInput, string meaningInput,
           map<pair<string, string>, Word*>* dictionaryInput) : sound(soundInput),
                                                    type(typeInput), meaning(meaningInput), dictionary(dictionaryInput) {
    isTerminal = true;
}

// Standard Getter Methods
string Word::getSound() const {
    return sound;
}
string Word::getMeaning() const {
    return meaning;
}
string Word::getType() const {
    return type;
}
vector<Word*> Word::getRoots() const {
    return roots;
}

// Standard Setter Methods
void Word::setSound(string soundInput) {
    sound = soundInput;
}
void Word::setMeaning(string meaningInput) {
    meaning = meaningInput;
}
void Word::setType(string typeInput) {
    type = typeInput;
}
void Word::setRoots(vector<Word *> rootsInput) {
    roots = rootsInput;
}

// Input/Output Methods
void Word::readInputString(string unparsedString) {
    vector<string> wordAndRoots = Scrivener::split(unparsedString, '|');
    vector<string> parse = Scrivener::split(wordAndRoots.at(0), '-');
    vector<Word*> rootsTemp;
    Word* temp;
    sound = parse.at(0);
    type = parse.at(1);
    meaning = parse.at(2);
    // Handles root words, but only runs if the word does have roots
    for(int i = 1; i < wordAndRoots.size(); ++i) {
        parse = Scrivener::split(wordAndRoots.at(i), '-');
        temp = dictionary->at(make_pair(parse.at(0), parse.at(1)));
        rootsTemp.push_back(temp);
    }
    roots = rootsTemp;
}
string Word::toIdentityOutputFormat() {
    string line = toStemFormat();
    for(int i = 0; i < roots.size(); ++i) {
        line += "|" + roots.at(i)->getSound() + "-" + roots.at(i)->getType();
    }
    return line;
}

// Standard Console Methods
string Word::toString() {
    return "Word: " + sound + ", meaning: " + meaning + ", type: " + type;
}
string Word::bundleContents() {
    string line;
    for(int i = 0; i < roots.size(); ++i) {
        line += "\n\t" + roots.at(i)->toString();
    }
    return line;
}
string Word::toStemFormat() {
    return sound + "-" + type + "-" + meaning;
}
string Word::toRootFormat() {
    return sound + "-" + type;
}
string Word::printWord() {
    cout << toString();
}
// ===================== END ===================== //
// ================ WORD METHODS ================= //



// ==================== BEGIN ==================== //
// ========== NONTERMINAL SYMBOL METHODS ========= //
// Constructor
NonterminalSymbol::NonterminalSymbol(string nameInput, int idInput, bool preterminalInput) : Symbol(nameInput, idInput) {
    isTerminal = false;
    isPreterminal = preterminalInput;
}

// Standard Getters
vector<vector<Symbol*>> NonterminalSymbol::getProductions() {
    return productions;
}
bool NonterminalSymbol::getPreterminality() const {
    return isPreterminal;
}

// Standard Setters
vector<Symbol*> NonterminalSymbol::addProduction(string input, map<string, Symbol*>* symbolsInput) {
    vector<string> symbolLines;
    vector<Symbol*> tempProduction;
    Symbol* temp;
    symbolLines = Scrivener::split(input, ',');
    for(int j = 0; j < symbolLines.size(); ++j) {
        if(symbolsInput->count(symbolLines.at(j)) != 0) {
            temp = symbolsInput->at(symbolLines.at(j));
            tempProduction.push_back(temp);
        }
    }
    productions.push_back(tempProduction);
    return tempProduction;
}
void NonterminalSymbol::addProduction(Symbol *wordInput) {
    vector<Symbol*> container;
    container.push_back(wordInput);
    productions.push_back(container);
}

// Evaluation Method
vector<Symbol*> NonterminalSymbol::evaluate(int searchDepth) {
    vector<Symbol*> sentance;
    int trial = 0;
    bool success = searchProductions(sentance, 0, searchDepth);
    while(!success) {
        cout << "Production did not evaluate at this length\n";
        sentance.clear();
        success = searchProductions(sentance, 0, searchDepth);
        if(trial > 100) {
            break;
        }
        trial += 1;
    }
    if(success)
        return sentance;
    cout << "The symbol [" + name + "] was not able to evaluate in time.";
    sentance.clear();
    return sentance;
}
bool NonterminalSymbol::searchProductions(vector<Symbol*> &sentance, int depth, int maximumDepth) {
    int chanceCounter = rand() % productions.size();
    vector<Symbol*> evaluatedProduction;
    evaluatedProduction = productions.at(chanceCounter);
    Symbol* tempSymbol;
    bool continueFlag = true;
    if(isPreterminal) {
        tempSymbol = evaluatedProduction.at(0);
        sentance.push_back(tempSymbol);
        return true;
    }
    if(depth >= maximumDepth)
        return false;
    for(int i = 0; i < evaluatedProduction.size(); ++i) {
        continueFlag = evaluatedProduction.at(i)->searchProductions(sentance, depth + 1, maximumDepth);
    }
    return continueFlag;
}

// Input/Output Methods
void NonterminalSymbol::parseProductionsInput(string unparsedString, map<string, Symbol*>* symbolsInput) {
    vector<string> productionLines = Scrivener::split(unparsedString, '|');
    vector<string> symbolLines;
    for (int i = 0; i < productionLines.size(); ++i) {
        addProduction(productionLines.at(i), symbolsInput);
    }
}
string NonterminalSymbol::toIdentityOutputFormat() {
    if(isPreterminal)
        return name + "-Preterminal";
    return name + "-Nonterminal";
}
string NonterminalSymbol::toProductionsOutputFormat() {
    string line;
    if(productions.size() == 0)
        return name + " has no productions";
    line = name + "-" + productionToString(productions.at(0));
    for(int i = 1; i < productions.size(); ++i) {
        line += "|" + productionToString(productions.at(i));
    }
    return line;
}
string NonterminalSymbol::productionToString(vector<Symbol*> production) {
    string line;
    for(int i = 0; i < production.size(); ++i) {
        line += production.at(i)->getName();
        if(i != production.size() - 1)
            line += ",";
    }
    return line;
}

// Console Methods
string NonterminalSymbol::toString() {
    if(isPreterminal)
        return name + ", Preterminal";
    return name + ", Nonterminal";
}
string NonterminalSymbol::bundleContents() {
    string line;
    if(isPreterminal) {
        line += name;
        for(int i = 0; i < productions.size(); ++i) {
            line +="\n\t" + ((Word*)productions.at(i).at(0))->toString();
        }
        return line;
    }
    return toProductionsOutputFormat();
}
// ===================== END ===================== //
// ========== NONTERMINAL SYMBOL METHODS ========= //



// ==================== BEGIN ==================== //
// =============== GRAMMAR METHODS =============== //
// Constructors
Grammar::Grammar() {

}
Grammar::Grammar(Scrivener *scrivenerInput, string languageName) : bart(scrivenerInput) {
    parseWordtypeFile(languageName + "\\Wordtypes.txt");
    cout << "Wordtypes Loaded\n";
    parseSentenceConstructionKit(languageName + "\\Productions.txt");
    cout << "Productions Loaded\n";
    //parseWordConstructionKit(languageName + "\\WordConstruction.txt");
    //cout << "Constructions Loaded\n";
}

//Standard Getters
map<string, Symbol*>* Grammar::getSymbols() {
    return &symbols;
}
Symbol* Grammar::getSymbol(string symbolName) {
    Symbol* s;
    if(symbols.count(symbolName) == 0) {
        cout << "No such symbol exists\n";
        return s;
    }
    else
        return symbols.at(symbolName);
}

// Word Parsing Methods [NOTE PARSEWORDTYPEFILE MUST BE CALLED FIRST]
void Grammar::parseWordtypeFile(string wordtypeInput) {
    vector<string> lines = bart->readFileToStringVector(wordtypeInput);
    vector<string> parsedLine;
    Symbol* newWordType;
    for(int i = 0; i < lines.size(); ++i) {
        parsedLine = Scrivener::split(lines.at(i), '-');
        if (parsedLine.at(1) == "Nonterminal") {
            newWordType = new NonterminalSymbol(parsedLine.at(0), symbols.size(), false);
        }
        else {
            newWordType = new NonterminalSymbol(parsedLine.at(0), symbols.size(), true);
        }
        symbols.insert(make_pair(parsedLine.at(0), newWordType));
        parsedLine.clear();
    }
}
void Grammar::parseSentenceConstructionKit(string sentenceInput) {
    vector<string> lines;
    vector<string> keyLine;
    string symbolKey;
    bool isTerminal;
    lines = bart->readFileToStringVector(sentenceInput);
    for(int i = 0; i < lines.size(); ++i) {
        keyLine = Scrivener::split(lines.at(i), '-');
        symbolKey = keyLine.at(0);
        if(symbols.count(symbolKey) != 0) {
            symbols.at(symbolKey)->parseProductionsInput(keyLine.at(1), &symbols);
        }
    }
}
void Grammar::parseWordConstructionKit(string wordInput) {

}

// Word Methods
void Grammar::addSymbol(string nameInput, string symbolType) {
    Symbol* newWordType;
    if (symbolType == "Nonterminal") {
        newWordType = new NonterminalSymbol(nameInput, symbols.size(), false);
    }
    else {
        newWordType = new NonterminalSymbol(nameInput, symbols.size(), true);
    }
    symbols.insert(make_pair(nameInput, newWordType));
}
void Grammar::addSymbol(Symbol* symbolInput) {
    symbols.insert(make_pair(symbolInput->getName(), symbolInput));
}
void Grammar::assignWord(Word* word) {
    if(symbols.count(word->getType()) != 0) {
        (symbols.at(word->getType()))->addProduction(word);
        // God I hate this, so much, why even have polymorphism if we're forced to reduce ourself to this.
        // At the same time though, this will allow us to make Word a child of symbol and save some headaches
        // elsewhere. It really is a cliche but this is an example of the give and take.
        // A better third solution definitely exists, just not in my timescale.
    }
}

// Sentance Methods
string Grammar::generateRandomStringFromSymbol(string nontermKey) {
    string line;
    string lineTwo;
    vector<Symbol*> sentence = symbols.at(nontermKey)->evaluate(10);
    cout << ((Word*)sentence.at(0))->getName();
    for(int i = 0; i < sentence.size(); ++i) {
        Word* w = (Word*)sentence.at(i);
        line += w->getSound() + " ";
        lineTwo += w->getMeaning() + " ";
    }
    return "In Language: " + line + "\nIn English: " + lineTwo + "\n";
}
vector<Word*> Grammar::generateRandomWordVector(string nontermKey) {
    vector<Word*> sentance;
    vector<Symbol*> sentanceTemp = symbols.at(nontermKey)->evaluate(5);
    for(int i = 0; i < sentanceTemp.size(); ++i) {
        sentance.push_back((Word*)sentanceTemp.at(i));
    }
    return sentance;
}

// Console Methods
void Grammar::printSymbols() {
    printSymbolsMap("Nonterminal", &symbols);
}
void Grammar::printNonterminalsAndProductions() {
    map<string, Symbol*>::iterator crawler;
    for(crawler = symbols.begin(); crawler != symbols.end(); ++crawler) {
        if(!crawler->second->getPreterminality()) {
            cout << crawler->second->bundleContents() + "\n";
        }
    };
}
void Grammar::printPreterminalsAndWords() {
    map<string, Symbol*>::iterator crawler;
    for(crawler = symbols.begin(); crawler != symbols.end(); ++crawler) {
        if(crawler->second->getPreterminality()) {
            cout << crawler->second->bundleContents() + "\n";
        }
    }
}
void Grammar::printSymbolsMap(string headingName, map<string, Symbol*>* symMap) {
    map<string, Symbol*>::iterator crawler;
    cout << headingName + " Symbols\n";
    for(crawler = symMap->begin(); crawler != symMap->end(); ++crawler) {
        cout << "\t" + crawler->second->toString() + "\n";
    };
}
// ===================== END ===================== //
// =============== GRAMMAR METHODS =============== //

/*
 *


// ==================== BEGIN ==================== //
// ========== PRETERMINAL SYMBOL METHODS ========= //
//Constructors
PreterminalSymbol::PreterminalSymbol(string nameInput, int idInput) : Symbol(nameInput, idInput) {

}
PreterminalSymbol::PreterminalSymbol(string nameInput, int idInput, map<string, vector<Word*>>* listInput) : Symbol(nameInput, idInput) {
    vector<Word*> preterminalWords;
    listInput->insert(make_pair(name, preterminalWords));
}

// Standard Getters
map<string, Word*>* PreterminalSymbol::getTerminalSymbols() {
    return &terminalSymbols;
};

// Evaluation Method THREAD
vector<Symbol*> PreterminalSymbol::evaluate(int searchDepth) {
    vector<Symbol*> temp;
    temp.push_back(this);
    return temp;
}
Symbol* PreterminalSymbol::evalute() {
    int chanceCounter = rand() % terminalSymbols.size();
    map<string, Word*>::iterator crawler = terminalSymbols.begin();
    for(int i = 0; i < chanceCounter; ++i)
        ++crawler;
    return crawler->second;
}
bool PreterminalSymbol::searchProductions(vector<Symbol *> &sentance, int depth, int maximumDepth) {
    sentance.push_back(this);
    return true;
}

// Input/Output Methods
void PreterminalSymbol::parseProductionsInput(string unparsedString, map<string, Symbol*>* nonterm, map<string, Symbol*>* preterm) {
    cout << "[" + name + "] cannot parse productions as it is a preterminal symbol\n";
}
void PreterminalSymbol::addWord(Word* word) {
    terminalSymbols.insert(make_pair(word->getSound(), word));
}
string PreterminalSymbol::toIdentityOutputFormat() {
    return name + "-Terminal";
}
string PreterminalSymbol::toProductionsOutputFormat() {
    return "[" + name + "] has no productions as it is a preterminal symbol\n";
}

// Console Methods
string PreterminalSymbol::toString() {
    return name + ", Preterminal";
}
string PreterminalSymbol::bundleContents() {
    string line;
    map<string, Word*>::iterator crawler;
    for(crawler = terminalSymbols.begin(); crawler != terminalSymbols.end(); ++crawler) {
        line += "\t" + crawler->second->toString() + "\n";
    };
    return line;
}
// ===================== END ===================== //
// ========== PRETERMINAL SYMBOL METHODS ========= //



 */
