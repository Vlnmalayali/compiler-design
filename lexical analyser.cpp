#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <unordered_map>

using namespace std;

// Function to tokenize the input string
vector<pair<string, string>> tokenize(const string& input_string, unordered_map<string, int>& token_count) {
    vector<pair<string, string>> tokens;

    // Remove comments from input string
    string processed_string = regex_replace(input_string, regex("/\\*.*?\\*/"), "");

    // Regular expression patterns for different token types
    vector<pair<string, string>> patterns = {
        {"NUMBER", "\\d+"},
        {"WORD", "\"[^\"]*\"|[a-zA-Z]+"},
        {"OPERATOR", "[\\+\\-]{2}|[\\+\\-\\*\\/\\!\\@\\#\\$\\%\\^\\&\\(\\)\\<\\>\\=\\_\\?\\,\\:\\.\\;]"}

    };

    // Combine patterns into a single regular expression
    string combined_pattern;
    for(const auto& pattern : patterns) {
        combined_pattern += "(" + pattern.second + ")|";
    }
    combined_pattern.pop_back(); // Remove the last '|' character

    // Tokenize processed input string
    regex token_regex(combined_pattern);
    auto words_begin = sregex_iterator(processed_string.begin(), processed_string.end(), token_regex);
    auto words_end = sregex_iterator();
    for (sregex_iterator it = words_begin; it != words_end; ++it) {
        for(size_t i = 1; i < it->size(); ++i) {
            if(!it->str(i).empty()) {
                tokens.emplace_back(patterns[i-1].first, it->str(i));
                token_count[patterns[i-1].first]++; // Increment token count for this identifier
                break;
            }
        }
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
    for(const auto& token : tokens) {
        cout << "\t" << token.first << ": " << token.second << endl;
    }
    cout << "Number of tokens: " << tokens.size() << endl;

    cout <<"Token counts:\n";
    for(const auto& pair : token_count) {
        cout << "\t" << pair.first << ": " << pair.second << endl;
    }

    return 0;
}
