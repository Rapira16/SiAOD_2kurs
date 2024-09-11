#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm> // Include for sort function

using namespace std;

struct TableEntry {
    int key;
    string value;
    // Add a comparison operator to sort by key
    bool operator<(const TableEntry& other) const {
        return key < other.key;
    }
};

TableEntry readEntryByIndex(const string& filename, int index) {
    ifstream file(filename);
    TableEntry entry;
    if (!file.is_open()) {
        cerr << "Unable to open file." << endl;
        return entry;
    }

    string line;
    int currentIndex = 0;
    while (getline(file, line)) {
        if (currentIndex == index) {
            stringstream ss(line);
            ss >> entry.key;
            getline(ss, entry.value);
            break;
        }
        currentIndex++;
    }

    file.close();
    return entry;
}

// Binary search function to find the value by key
string binarySearch(const vector<TableEntry>& table, int searchKey) {
    int low = 0;
    int high = table.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (table[mid].key == searchKey) {
            return table[mid].value;
        } else if (table[mid].key < searchKey) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return "Key not found";
}

int main() {
    vector<TableEntry> table;

    ifstream file("/home/han/CLionProjects/SiAOD_2_5_2/input100.bin");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            TableEntry entry;
            stringstream ss(line);
            ss >> entry.key;
            getline(ss, entry.value);
            table.push_back(entry);
        }
        file.close();
    } else {
        cout << "Unable to open file." << endl;
        return 1;
    }

    // Sort the entries by key before using binary search 
    sort(table.begin(), table.end());

    // Example usage of binary search function
    int keyToSearch = 31893; // Example key to search
    //string value = binarySearch(table, keyToSearch);
    //cout << "Key: " << keyToSearch << ", Value: " << (value.empty() ? "Not Found" : value.substr(1)) << endl;
    int index = 2;
    TableEntry entry = readEntryByIndex("/home/han/CLionProjects/SiAOD_2_5_2/input100.bin", index);
    cout << "Read by index " << index << ": Key: " << entry.key << ", Value: " << entry.value.substr(1) << endl;
    return 0;
}
