#include <iostream>
#include "Menu.h"
#include "headers.h"

void mainTerminal() {
    stack<Menu*> s;
    bool b;
    s.push(new MainMenu(&s));
    // Main loop of the program, depends on s having menus to continue
    while(!s.empty()) {
        b = s.top()->run();
        if(!b) {// run returns false if menu is quit
            s.pop(); // if a menu is quit it is popped, if none on stack, exit
        }
    }
}

int main() {
    srand(time(NULL));
    mainTerminal();
    return 0;
}

/*
    Codex* c = new Codex("Wiztalk");
    c->initializeScrivener();
    c->initializeGrammar("Wiztalk");
    c->initializeDictionary("Wiztalk");
    cout << c->getGrammar()->generateRandomStringFromSymbol("Sentence");
 */