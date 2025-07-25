#include <iostream>
#include <string>
#include "ConsoleUI.h"

using namespace std;

int ConsoleUI::getIdInput(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        try {
            return InputValidator::validateId(input);
        }
        catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << ". Please try again." << endl;
        }
    }
}

string ConsoleUI::getDestinationInput(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        try {
            return InputValidator::validateDestination(input);
        }
        catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << ". Please try again." << endl;
        }
    }
}

string ConsoleUI::getTimeInput(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        try {
            return InputValidator::validateTime(input);
        }
        catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << ". Please try again." << endl;
        }
    }
}

int ConsoleUI::getGroupIdInput(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        try {
            return InputValidator::validateGroupId(input);
        }
        catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << ". Please try again." << endl;
        }
    }
}

FreightType ConsoleUI::getFreightTypeInput(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        try {
            return InputValidator::parseFreightType(input);
        }
        catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << ". Valid types: MiniMover, CargoCruiser, MegaCarrier" << endl;
        }
    }
}