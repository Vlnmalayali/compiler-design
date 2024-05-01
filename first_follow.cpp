#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

using namespace std;

class GrammarAnalyzer {
private:
    unordered_map<char, vector<string>> productions;

    unordered_set<char> first(char nonTerminal);

    unordered_set<char> follow(char nonTerminal);

public:
    void addProduction(char nonTerminal, const vector<string>& symbols);

    void computeFirstSets();

    void computeFollowSets();
};

void GrammarAnalyzer::addProduction(char nonTerminal, const vector<string>& symbols) {
    productions[nonTerminal] = symbols;
}

void GrammarAnalyzer::computeFirstSets() {
    cout << "First sets:\n";
    for (auto prod : productions) {
        cout << "First(" << prod.first << ") = ";
        unordered_set<char> firstSet = first(prod.first);
        for (char terminal : firstSet) {
            cout << terminal << " ";
        }
        cout << endl;
    }
}

void GrammarAnalyzer::computeFollowSets() {
    cout << "\nFollow sets:\n";
    for (auto prod : productions) {
        cout << "Follow(" << prod.first << ") = ";
        unordered_set<char> followSet = follow(prod.first);
        for (char terminal : followSet) {
            cout << terminal << " ";
        }
        cout << endl;
    }
}

unordered_set<char> GrammarAnalyzer::first(char nonTerminal) {
    unordered_set<char> result;
    if (!isupper(nonTerminal)) {
        result.insert(nonTerminal);
        return result;
    }
    for (string production : productions[nonTerminal]) {
        if (production[0] == nonTerminal) continue;
        unordered_set<char> temp = first(production[0]);
        result.insert(temp.begin(), temp.end());
    }
    return result;
}

unordered_set<char> GrammarAnalyzer::follow(char nonTerminal) {
    unordered_set<char> result;
    if (nonTerminal == 'S') result.insert('$');
    for (auto prod : productions) {
        for (string production : prod.second) {
            size_t found = production.find(nonTerminal);
            if (found != string::npos) {
                if (found == production.size() - 1) { // If non-terminal is the last symbol
                    if (prod.first != nonTerminal) { // To avoid infinite recursion
                        unordered_set<char> temp = follow(prod.first);
                        result.insert(temp.begin(), temp.end());
                    }
                } else { // If non-terminal is followed by a terminal or non-terminal
                    char nextSymbol = production[found + 1];
                    if (isupper(nextSymbol)) { // If next symbol is non-terminal
                        unordered_set<char> temp = first(nextSymbol);
                        if (temp.find('@') != temp.end()) { // If next symbol can derive epsilon
                            temp.erase('@');
                            unordered_set<char> followSet = follow(prod.first);
                            temp.insert(followSet.begin(), followSet.end());
                        }
                        result.insert(temp.begin(), temp.end());
                    } else { // If next symbol is terminal
                        result.insert(nextSymbol);
                    }
                }
            }
        }
    }
    return result;
}

int main() {
    GrammarAnalyzer analyzer;
    string input;
    cout << "Enter the grammar productions (Enter 'done' to finish):\n";
    while (true) {
        getline(cin, input);
        if (input == "done") break;

        stringstream ss(input);
        string production, arrow;
        char nonTerminal;

        ss >> nonTerminal >> arrow;
        vector<string> symbols;
        while (ss >> production) {
            symbols.push_back(production);
        }
        analyzer.addProduction(nonTerminal, symbols);
    }

    analyzer.computeFirstSets();
    analyzer.computeFollowSets();

    return 0;
}
