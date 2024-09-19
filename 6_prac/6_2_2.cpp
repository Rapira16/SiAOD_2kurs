#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void rabin_karp(const string& text, const string& pattern) {
    int d = 256;  // number of characters in the input alphabet
    int q = 101;  // a prime number
    int M = pattern.length();
    int N = text.length();
    int pattern_hash = 0;
    int text_hash = 0;
    int h = 1;
    int count = 0; // count of occurrences

    // calculate h value, h = d^(M-1) % q
    for (int i = 0; i < M - 1; i++) {
        h = (h * d) % q;
    }

    // calculate initial hash values for pattern and text
    for (int i = 0; i < M; i++) {
        pattern_hash = (d * pattern_hash + pattern[i]) % q;
        text_hash = (d * text_hash + text[i]) % q;
    }

    // slide the pattern over the text
    for (int i = 0; i <= N - M; i++) {
        if (pattern_hash == text_hash) {
            // check for a character-by-character match
            bool match = true;
            for (int j = 0; j < M; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                count++; // increment count of occurrences
            }
        }

        // calculate the hash value for the next window
        if (i < N - M) {
            text_hash = (d * (text_hash - text[i] * h) + text[i + M]) % q;
            if (text_hash < 0) {
                text_hash += q;
            }
        }
    }

    cout << "Pattern found " << count << " times." << endl;
}

int main() {
    ifstream file("/home/han/CLionProjects/SiAOD_2_5_2/input.txt"); // open the input file
    if (!file) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string pattern, text;
    getline(file, pattern); // read the pattern from the first line
    getline(file, text); // read the text from the second line

    file.close(); // close the file

    rabin_karp(text, pattern);

    return 0;
}
