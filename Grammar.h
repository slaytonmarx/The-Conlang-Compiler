//
// Created by Slayton on 11/21/2017.
//

#ifndef THECONLANGCOMPILER_CONTEXTFREEGRAMMAR_H
#define THECONLANGCOMPILER_CONTEXTFREEGRAMMAR_H

#include <random>
#include <time.h>
#include "Scrivener.h"

// Symbols
// Word should be it's own thing.
// Constructing a word.
// Randomly selecting from a map
class Symbol {
/* Symbol ----- Abstract parent class to nonterminal symbol and preterminal symbol.
 *      name - the name of the symbol at hand, such as verb, composite noun, ect.
 *      productions - list of rules which turn the symbol to other symbols.
 */
protected:
    string name;
    int id;
    bool isTerminal;
public:
    // Constructors
    Symbol();
    Symbol(string nameInput, int idInput);

    // Standard Getters
    string getName() const;
    int getId() const;
    bool getTerminality() const;
    virtual bool getPreterminality() const;
    virtual vector<vector<Symbol*>> getProductions();

    // Standard Setters
    void setName(string nameInput);
    void setId(int idInput);
    virtual vector<Symbol*> addProduction(string stringInput, map<string, Symbol*>* symbolsInput);
    virtual void addProduction(Symbol *wordInput);

    // Evaluation Methods
    virtual vector<Symbol*> evaluate(int searchDepth);
    virtual Symbol* evalute();
    virtual bool searchProductions(vector<Symbol*> &sentance, int depth, int maximumDepth);

    // Input/Output Methods
    virtual void parseProductionsInput(string unparsedString, map<string, Symbol*>* symbolsInput);
    virtual string toIdentityOutputFormat();
    virtual string toProductionsOutputFormat();

    // Console Methods
    virtual string toString();
    virtual string bundleContents();
};
class Word : public Symbol {
private:
    string sound;
    string type;
    string meaning;
    vector<Word*> roots;
    map<pair<string, string>, Word*>* dictionary;
public:
    // Constructor
    Word();
    Word(string unparsedInput, map<pair<string, string>, Word*>* dictionaryInput);
    Word(string soundInput, string typeInput, string meaningInput,
         map<pair<string, string>, Word*>* dictionaryInput);

    // Standard Getter Methods
    string getSound() const;
    string getMeaning() const;
    string getType() const;
    vector<Word*> getRoots() const;

    // Standard Setter Methods
    void setSound(string soundInput);
    void setMeaning(string meaningInput);
    void setType(string typeInput);
    void setRoots(vector<Word*> rootsInput);

    // Input/Output Methods
    void readInputString(string unparsedString);
    string toIdentityOutputFormat() override;

    // Standard Console Methods
    string toString() override;
    string bundleContents() override;
    string toStemFormat();
    string toRootFormat();
    string printWord();
};
class NonterminalSymbol : public Symbol {
/* Nonterminal ----- Same as definition in context free grammar. Nonterminal symbols have a set
 * of rules called productions with which they can be nondeterministically converted into terminal
 * symbols. These are symbols like "complex noun," or "prefix noun," they're blueprints for making
 * sentences and words.
 */
private:
    vector<vector<Symbol*>> productions;
    vector<vector<Symbol*>> translationProductions;
    bool isPreterminal;
public:
    // Constructor
    NonterminalSymbol(string nameInput, int idInput, bool preterminalInput);

    // Standard Getters
    bool getPreterminality() const override;
    vector<vector<Symbol*>> getProductions() override;

    // Standard Setters
    vector<Symbol*> addProduction(string stringInput, map<string, Symbol*>* symbolsInput) override;
    void addProduction(Symbol *wordInput) override;

    // Evaluation Method
    vector<Symbol*> evaluate(int searchDepth) override;
    bool searchProductions(vector<Symbol *> &sentance, int depth, int maximumDepth) override;

    // Input/Output Methods
    void parseProductionsInput(string unparsedString, map<string, Symbol*>* symbolsInput) override;
    string toIdentityOutputFormat() override;
    string toProductionsOutputFormat() override;
    string productionToString(vector<Symbol*> production);

    // Console Methods
    string toString() override;
    string bundleContents() override;
};

class Grammar {
private:
    map<string, Symbol*> symbols;
    Scrivener* bart;
public:
    // Constructors
    Grammar();
    Grammar(Scrivener* scrivenerInput, string languageName);

    // Standard Getters
    map<string, Symbol*>* getSymbols();
    Symbol* getSymbol(string symbolName);

    // Word Parsing Methods [NOTE PARSEWORDTYPEFILE MUST BE CALLED FIRST]
    void parseWordtypeFile(string wordtypeInput); /*
 *  parses the wordtype file into a list of preterminal symbols and adds that
 *  list to the symbols map<string, vector<Symbol*>> to be used by other methods.
 *  This list's key is "preterminal."
 */
    void parseSentenceConstructionKit(string sentenceInput); /*
 *  parses the sentance file into a list of nonterminal symbols and adds that
 *  list to the symbols map<string, vector<Symbol*>> as "sentanceNonterminal."
 */
    void parseWordConstructionKit(string wordInput); /*
 *  parses the word file into a list of nonterminal symbols and adds that list
 *  to the symbols map<string, vector<Symbol*>> as "wordNonterminal."
 */

    // Word Methods
    void addSymbol(string nameInput, string symbolType);
    void addSymbol(Symbol* symbolInput);
    void assignWord(Word* word);

    // Sentance Methods
    string generateRandomStringFromSymbol(string nontermKey);
    vector<Word*> generateRandomWordVector(string nontermKey);

    // Console Methods
    void printSymbols();
    void printNonterminalsAndProductions();
    void printPreterminalsAndWords();
    void printSymbolsMap(string headingName, map<string, Symbol*>* symMap);
};

#endif //THECONLANGCOMPILER_CONTEXTFREEGRAMMAR_H

/*
 *
class PreterminalSymbol : public Symbol {
/* Preterminal ----- The stems of the grammar, these symbols are, for all intents and purposes
 * the terminal characters of the grammar, but because they're not the actual words they aren't
 * quite there yet, hence, preterminal. The each preterminal symbol is a stem type like noun,
 * verb, or prefix, which can be used to construct words or to construct sentences.
 /
private:
map<string, Word*> terminalSymbols;
public:
// Constructors
PreterminalSymbol(string nameInput, int idInput);
PreterminalSymbol(string nameInput, int idInput, map<string, vector<Word*>>* listInput);

// Standard Getters
map<string, Word*>* getTerminalSymbols();

// Evaluation Method
vector<Symbol*> evaluate(int searchDepth) override;
Symbol * evalute() override;
bool searchProductions(vector<Symbol *> &sentance, int depth, int maximumDepth) override;

// Input/Output Methods
void parseProductionsInput(string unparsedString, map<string, Symbol*>* input) override;
void addWord(Word* word);
string toIdentityOutputFormat() override;
string toProductionsOutputFormat() override;

// Console Methods
string toString() override;
string bundleContents() override;
};
 */