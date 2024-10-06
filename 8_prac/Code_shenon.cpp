#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

// Structure to represent a node in the Huffman tree
struct Node {
    char symbol;
    int frequency;
    Node* left;
    Node* right;
};

// Function to calculate the frequency of each symbol in the input string
map<char, int> calculateFrequencies(string input) {
    map<char, int> frequencies;
    for (char c : input) {
        frequencies[c]++;
    }
    return frequencies;
}

// Function to build the Huffman tree
Node* buildHuffmanTree(map<char, int> frequencies) {
    // Create a priority queue to store nodes
    priority_queue<Node*, vector<Node*>, std::function<bool(Node*, Node*)>> queue(
            [](Node* a, Node* b) { return a->frequency > b->frequency; });

    // Create leaf nodes for each symbol
    for (auto& pair : frequencies) {
        Node* node = new Node();
        node->symbol = pair.first;
        node->frequency = pair.second;
        node->left = node->right = nullptr;
        queue.push(node);
    }

    // Build the Huffman tree
    while (queue.size() > 1) {
        Node* left = queue.top();
        queue.pop();
        Node* right = queue.top();
        queue.pop();

        Node* parent = new Node();
        parent->frequency = left->frequency + right->frequency;
        parent->left = left;
        parent->right = right;
        queue.push(parent);
    }

    return queue.top();
}

// Function to generate Shannon-Fano codes
void generateCodes(Node* root, string code, map<char, string>& codes) {
    if (root == nullptr) {
        return;
    }

    if (root->left == nullptr && root->right == nullptr) {
        codes[root->symbol] = code;
    }

    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

// Function to encode the input string using Shannon-Fano codes
string encodeString(string input, map<char, string> codes) {
    string encodedString;
    for (char c : input) {
        encodedString += codes[c];
    }
    return encodedString;
}

// Function to decode the encoded string using Shannon-Fano codes
string decodeString(string encodedString, map<char, string> codes) {
    string decodedString;
    string tempCode;

    for (char c : encodedString) {
        tempCode += c;
        for (auto& pair : codes) {
            if (pair.second == tempCode) {
                decodedString += pair.first;
                tempCode.clear();
                break;
            }
        }
    }

    return decodedString;
}

int main() {
    string input = "Мой котёнок очень странный, Он не хочет есть сметану, К молоку не прикасался И от рыбки отказался.";
    map<char, int> frequencies = calculateFrequencies(input);
    Node* root = buildHuffmanTree(frequencies);
    map<char, string> codes;
    generateCodes(root, "", codes);

    cout << "Frequency of each symbol and its code:" << endl;
    for (auto& pair : frequencies) {
        cout << "Symbol: " << pair.first << ", Frequency: " << pair.second << ", Code: " << codes[pair.first] << endl;
    }

    string encodedString = encodeString(input, codes);
    cout << "Encoded string: " << encodedString << endl;

    string decodedString = decodeString(encodedString, codes);
    cout << "Decoded string: " << decodedString << endl;

    return 0;
}
