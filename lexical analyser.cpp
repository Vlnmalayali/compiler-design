#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <unordered_map>

using namespace std;

// Function to tokenize the input string
vector<pair<string, string>> tokenize(const string& input_string, unordered_map<string, int>& token_count) {
    vector<pair<string, string>> tokens;

    try {
        // Remove comments from input string
        string processed_string = regex_replace(input_string, regex("/\\*.*?\\*/"), "");
        processed_string = regex_replace(processed_string, regex("//.*"), "");

        // Regular expression patterns for different token types
        vector<pair<string, string>> patterns = {
            {"KEYWORD", "\\b(if|else|while|for|return|int|float|double|char|string|void|const|static|class|struct|union|enum)\\b"},
            {"IDENTIFIER", "\\b(?!(if|else|while|for|return|int|float|double|char|string|void|const|static|class|struct|union|enum)\\b)[a-zA-Z_][a-zA-Z0-9_]*\\b"},
            {"NUMBER", "\\b\\d+\\b"},
            {"STRING", "\"(\\\\.|[^\\\\\"])*\""},
            {"OPERATOR", "\\+\\+|\\-\\-|\\+|\\-|\\*|\\/|\\=|\\!|\\<|\\>|\\&|\\||\\^|\\%|\\~|\\?|\\:"},
            {"PUNCTUATION", "[\\(\\)\\{\\}\\[\\]\\;\\,\\.]"}
        };

        // Tokenize processed input string for each pattern separately
        for (const auto& pattern : patterns) {
            regex token_regex(pattern.second);
            auto words_begin = sregex_iterator(processed_string.begin(), processed_string.end(), token_regex);
            auto words_end = sregex_iterator();

            for (sregex_iterator it = words_begin; it != words_end; ++it) {
                smatch match = *it;
                tokens.emplace_back(pattern.first, match.str());
                token_count[pattern.first]++;
            }
        }

        // Sort tokens by their position in the original string
        stable_sort(tokens.begin(), tokens.end(), [&processed_string](const pair<string, string>& a, const pair<string, string>& b) {
            return processed_string.find(a.second) < processed_string.find(b.second);
        });

    } catch (const std::exception &e) {
        cerr << "Error tokenizing input string: " << e.what() << endl;
    }

    return tokens;
}

int main() {
    string input_string;
    cout << "Enter a string: ";
    getline(cin, input_string);

    unordered_map<string, int> token_count; // Map to store token identifiers and their counts

    vector<pair<string, string>> tokens = tokenize(input_string, token_count);

    cout << "Tokens found:\n";
    for (const auto& token : tokens) {
        cout << "\t" << token.first << ": " << token.second << endl;
    }
    cout << "Number of tokens: " << tokens.size() << endl;

    cout << "Token counts:\n";
    for (const auto& pair : token_count) {
        cout << "\t" << pair.first << ": " << pair.second << endl;
    }

    return 0;
}
