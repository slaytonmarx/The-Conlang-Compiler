//
// Created by Slayton on 12/2/2017.
//

#include "Menu.h"

// MENU METHODS
Menu::Menu() {
    prompt = "Menu not properly constructed";
}
Menu::Menu(stack<Menu*>* menusInput) : menus(menusInput) {

}
Menu::Menu(stack<Menu*>* menusInput, Codex* codexInput) : menus(menusInput), codex(codexInput) {

}
void Menu::populateMenu(string promptInput, vector<pair<string, string>> optionsInput) {
    // used instead of constructor to allow for writing inside
    // the subclass, rather than putting unique text inside the initializer list.
    prompt = promptInput;
    options = optionsInput;
}
string Menu::ensureProperInput() {
    bool running = true;
    string userInput;
    while(running) {
        cout << prompt;
        for(int i = 0; i < options.size(); ++i) {
            cout << "\n\t" + options.at(i).first + ": " + options.at(i).second;
        }
        cout << "\ninput: ";
        cin >> userInput;
        for(int i = 0; i < options.size(); ++i) {
            if(userInput == options.at(i).first)
                return userInput;
        }
        if(userInput == "q")
            return "back";
        cout << "The input: <" + userInput + "> is not one of the options, repeating prompt\n";
    }
}
string Menu::ensureProperInput(string promptInput, vector<pair<string, string>> optionsInput) {
    bool running = true;
    string userInput;
    while(running) {
        cout << promptInput;
        for(int i = 0; i < optionsInput.size(); ++i) {
            cout << "\n\t" + optionsInput.at(i).first + ": " + optionsInput.at(i).second;
        }
        cout << "\ninput: ";
        cin >> userInput;
        for(int i = 0; i < optionsInput.size(); ++i) {
            if(userInput == optionsInput.at(i).first)
                return userInput;
        }
        if(userInput == "q")
            return "back";
        cout << "The input: <" + userInput + "> is not one of the options, repeating prompt\n";
    }
}
bool Menu::run() { // Will change to virtual when I put this in header

}
void Menu::halt() {
    string userInput;
    cout << "\nType 'c' to continue:";
    cin >> userInput;
}

// STATISTIC MENU METHODS
StatisticsMenu::StatisticsMenu(stack<Menu*>* menuInput, Codex* codexInput) : Menu(menuInput, codexInput) {
    populateMenu("Statistics of: " + codexInput->getLangaugeName(),
                 {make_pair("b", "Back to language menu")});
}
bool StatisticsMenu::run() {
    codex->printStatistics();
    string command = ensureProperInput();
    if(command == "b")
        return false;
    return true;
}

// GRAMMAR MENU METHODS
GrammarMenu::GrammarMenu(stack<Menu*>* menuInput, Codex* codexInput) : Menu(menuInput, codexInput) {
populateMenu("Grammar Menu of " + codexInput->getLangaugeName(),
             {make_pair("w", "View Word Types"),
              make_pair("p", "View Productions"),
              make_pair("at", "Add Word Type"),
              make_pair("ap", "Add Production"),
              make_pair("b", "Back to Language menu")});
    // Add remove wordtype and production type
}
bool GrammarMenu::run() {
    string input;
    string symbolName;
    string command = ensureProperInput();
    if(command == "b")
        return false;
    if(command == "w") {
        cout << "Displaying Symbols:\n";
        codex->getGrammar()->printSymbols();
    }
    if(command == "p") {
        cout << "Displaying Productions:\n";
        codex->getGrammar()->printNonterminalsAndProductions();
    }
    if(command == "at") {
        cout << "Type the name of your new wordtype (note the first letter must be uppercase):";
        cin >> command;
        if(command.at(0) > 91) {
            cout << "Sorry, the first letter must be uppercase\n";
            return true;
        }
        symbolName = command;
        command = ensureProperInput("Would you like the symbol to be preterminal?", {make_pair("y", "Make preterminal"), make_pair("n", "Make nonterminal")});
        if(command == "back")
            return true;
        if(command == "y")
            codex->getGrammar()->addSymbol(symbolName, "Preterminal");
        if(command == "n")
            codex->getGrammar()->addSymbol(symbolName, "Nonterminal");
        cout << "Symbol: " + symbolName + " created.\n";
    }
    if(command == "ap") {
        cout << "What symbol do you want to add a production to?: ";
        cin >> symbolName;
        Symbol* s = codex->getGrammar()->getSymbol(symbolName);
        if(s == nullptr) {
            cout << "Returning to grammar menu\n";
            return true;
        }
        else {
            input = "";
            while(command != "q") {
                cout << "Enter the name of a symbol to add to the production (or q to finish):";
                cin >> command;
                if(command != "q") {
                    if(input != "") {
                        input += ",";
                    }
                    input += command;
                    cout << "Production so far: " + input + "\n";
                }
            }
            codex->getGrammar()->getSymbol(symbolName)->addProduction(input, codex->getGrammar()->getSymbols());
            cout << "Production added\n";
        }
    }

    return true;
}

// DICTIONARY MENU METHODS
DictionaryMenu::DictionaryMenu(stack<Menu*>* menuInput, Codex* codexInput) : Menu(menuInput, codexInput) {
    populateMenu("Dictionary Menu of " + codexInput->getLangaugeName(),
                 {make_pair("v", "View All Words"),
                  make_pair("s", "Search Language"),
                  make_pair("a", "Add to Language"),
                  make_pair("sen", "Sentence Functions"),
                  make_pair("b", "Back to Language menu")});
}
bool DictionaryMenu::run() {
    string soundInput;
    string typeInput;
    string command = ensureProperInput();
    if(command == "v") {
        codex->printDictionary();
    }
    if(command == "s") {
        cout << "What is the sound of the word you're looking for: ";
        cin >> soundInput;
        cout << "What is the type of the word you're looking for: ";
        cin >> typeInput;
        cout << codex->getWord(soundInput, typeInput)->toString() + "\n";
    }
    if(command == "a") {
        menus->push(new AddWordMenu(menus, codex));
    }
    if(command == "sen") {
        menus->push(new SentanceMenu(menus, codex));
    }
    if(command == "r") {
        cout << "Input the sound of the word you want to erase: ";
        cin >> soundInput;
        cout << "Input the type of the word you want to erase: ";
        cin >> typeInput;
        codex->removeWord(soundInput, typeInput);
    }
    if(command == "b")
        return false;
    return true;
}

// ADD WORD MENU METHODS
AddWordMenu::AddWordMenu(stack<Menu*>* menuInput, Codex* codexInput) : Menu(menuInput, codexInput) {
    populateMenu("Add Word Menu of " + codexInput->getLangaugeName(),
                 {make_pair("m", "Manually Add a Word to the Language"),
                  make_pair("r", "Randomly Generate a Word to Add"),
                  make_pair("b", "Back to Dictionary menu")});
}
bool AddWordMenu::run() {
    string command = ensureProperInput();
    string formattedWordString;
    vector<Word*> list;
    string wordSound;
    string wordType;
    string wordMeaning;
    if(command == "m") {
        cout << "Manually creating words:\n";
        while(command != "q") {
            cout << "Enter the c to continue or q to quit";
            cin >> command;
            if(command == "c") {
                cout << "Enter the sound of the word (must be all lowercase): ";
                cin >> wordSound;
                cout << "Enter the type of the word (first letter must be uppercase): ";
                cin >> wordType;
                cout << "Enter the meaning of the word: ";
                cin >> wordMeaning;
                formattedWordString = wordSound + "-" + wordType + "-" + wordMeaning;
                codex->createWord(formattedWordString);
            }
        }
        cout << "Completed manually entering words\n";
    }
    if(command == "r") {
        cout << "Randomly generating words";
        while(command != "q") {
            cout << "Enter the c to continue or q to quit: ";
            cin >> command;
            if(command == "c") {
                wordSound = "";
                formattedWordString = "";
                list = codex->chooseWordsToCombine();
                for(int i = 0; i < list.size(); ++i) {
                    wordSound += list.at(i)->getSound();
                }
                cout << "The new word [" + wordSound + "] is composed of: \n";
                for(int i = 0; i < list.size(); ++i) {
                    cout << list.at(i)->toString() + "\n";
                }
                cout << "Meanings in a row: ";
                for(int i = 0; i < list.size(); ++i) {
                    cout << list.at(i)->getMeaning() + ", ";
                }
                cout << "\nEnter the type of the word (first letter must be uppercase): ";
                cin >> wordType;
                cout << "Enter the meaning of the word: ";
                cin >> wordMeaning;
                formattedWordString = wordSound + "-" + wordType + "-" + wordMeaning;
                for(int i = 0; i < list.size(); ++i) {
                    formattedWordString += "|" + list.at(i)->toRootFormat();
                }
                cout << formattedWordString + "\n";
                codex->createWord(formattedWordString);
            }
        }
    }
    if(command == "b")
        return false;
    return true;
}

// ADD WORD MENU METHODS
SentanceMenu::SentanceMenu(stack<Menu*>* menuInput, Codex* codexInput) : Menu(menuInput, codexInput) {
    populateMenu("Add Word Menu of " + codexInput->getLangaugeName(),
                 {make_pair("g", "Generate a Sentance Randomly"),
                  make_pair("w", "Write a Sentance and have it Translated"),
                  make_pair("b", "Back to Dictionary menu")});
}
bool SentanceMenu::run() {
    char input[50];
    string command = ensureProperInput();
    if(command == "g") {
        cout << "\n" + codex->getGrammar()->generateRandomStringFromSymbol("Sentence") + "\n";
        return true;
    }
    if(command == "w") {
        cout << "Note, you may only use the words already in the language, those being:\n";
        codex->printDictionary();
        cout << "If your sentence is grammatically incorrect it may be rejected.\nInput your sentence here:";
        cin.clear();
        fflush(stdin);
        cin.getline(input,sizeof(input));
        cout << endl;
        codex->translate(input);
        cout << endl;
        return true;
    }
    if(command == "b")
        return false;
    return true;
}

// LANGUAGE MENU METHODS
LanguageMenu::LanguageMenu(stack<Menu*>* menuInput, Codex* codexInput) : Menu(menuInput, codexInput) {
    populateMenu("Language Menu of: " + codexInput->getLangaugeName(),
                 {make_pair("s", "View Language Statistics"),
                  make_pair("g", "Load Grammar Options"),
                  make_pair("d", "Load Dictionary Options"),
                  make_pair("f", "Save Language to File"),
                  make_pair("b", "Back to main menu")});
}
bool LanguageMenu::run() {
    string command = ensureProperInput();
    if(command == "b")
        return false;
    if(command == "s") {
        menus->push(new StatisticsMenu(menus, codex));
    }
    if(command == "g") {
        menus->push(new GrammarMenu(menus, codex));
    }
    if(command == "d") {
        menus->push(new DictionaryMenu(menus, codex));
    }
    if(command == "f") {
        command = ensureProperInput("What do you want the folder to be called:",
                                    {make_pair("a", "Save to Folder with Language Name"),
                                     make_pair("b", "Save to Folder Inputted")});
        if(command == "a")
            codex->writeCodexToFile(codex->getLangaugeName());
        if(command == "b") {
            cout << "Input the name of the folder: ";
            cin >> command;
            codex->writeCodexToFile(command);
        }
        cout << "Language has been saved";
    }
    return true;
}

// MAIN MENU METHODS
MainMenu::MainMenu(stack<Menu*>* menuInput) : Menu(menuInput) {
    populateMenu("Main Menu", {make_pair("n", "Create New Language"),
                               make_pair("l", "Load Existing Language from File"),
                               make_pair("q", "Exit")});
}
bool MainMenu::run() {
    string command = ensureProperInput();
    if(command == "q")
        return false;
    if(command == "n") {
        codex = createNewLanguage();
        menus->push(new LanguageMenu(menus, codex));
    }
    if(command == "l") {
        codex = loadExistingLanguage();
        menus->push(new LanguageMenu(menus, codex));
    }
    return true;
}
Codex* MainMenu::createNewLanguage() { //INCOMPLETE
    /* Walks user through the steps of creating a new language [giving it a name,
     * choosing a language type, and giving a description] and then creates a codex
     * with the specifications and returns it.
     */
    char input[50];
    Codex* c = new Codex();
    string line;
    cout << "What is the name of this new language: ";
    cin >> line;
    cout << "Give a brief description: ";
    c->setName(line);
    cin.clear();
    fflush(stdin);
    cin.getline(input,sizeof(input));
    c->setDescription(input);
    return c;
}
Codex* MainMenu::loadExistingLanguage() {
    /* Allows the user to type in the name of a language text file and uses the files
     * in it to create a language. Tells them if they're missing a specific file or if
     * the files were corrupted in a specific way.
     */
    string line;
    cout << "What is the language called: ";
    cin >> line;
    codex = new Codex(line);
    codex->initializeScrivener();
    codex->initializeGrammar(line);
    codex->initializeDictionary(line);
    return codex;
}