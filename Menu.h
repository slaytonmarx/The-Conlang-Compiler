//
// Created by Slayton on 12/2/2017.
//

#include <ctime>
#include <stack>
#include "Codex.h"

#ifndef THECONLANGCOMPILER_MENU_H
#define THECONLANGCOMPILER_MENU_H

class Menu {
protected:
    stack<Menu*>* menus;
    Codex* codex;
    string prompt;
    vector<pair<string, string>> options;
public:
    Menu();
    Menu(stack<Menu*>* menusInput);
    Menu(stack<Menu*>* menusInput, Codex* codexInput);
    void populateMenu(string promptInput, vector<pair<string, string>> optionsInput);
    string ensureProperInput();
    string ensureProperInput(string promptInput, vector<pair<string, string>> optionsInput);
    virtual bool run();

    void halt();
};
class StatisticsMenu : public Menu {
public:
    StatisticsMenu(stack<Menu*>* menuInput, Codex* codexInput);
    bool run() override;
};
class GrammarMenu : public Menu {
public:
    GrammarMenu(stack<Menu*>* menuInput, Codex* codexInput);
    bool run() override;
};
class DictionaryMenu : public Menu {
public:
    DictionaryMenu(stack<Menu*>* menuInput, Codex* codexInput);
    bool run() override;
};
class AddWordMenu : public Menu {
public:
    AddWordMenu(stack<Menu*>* menuInput, Codex* codexInput);
    bool run() override;
};
class SentanceMenu : public Menu {
public:
    SentanceMenu(stack<Menu*>* menuInput, Codex* codexInput);
    bool run() override;
};
class MainMenu : public Menu {
public:
    MainMenu(stack<Menu*>* menuInput);
    bool run() override;

    // Main Menu Specific Methods
    Codex* createNewLanguage();
    Codex* loadExistingLanguage();
};
class LanguageMenu : public Menu {
public:
    LanguageMenu(stack<Menu*>* menuInput, Codex* codexInput);
    bool run() override;
};

#endif //THECONLANGCOMPILER_MENU_H
