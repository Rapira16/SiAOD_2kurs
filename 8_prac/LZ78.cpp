#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// Структура для хранения узлов кода
struct CodeNode {
    int prefix; // префикс
    char symbol; // символ
};

// Словарь для хранения кодов
unordered_map<string, int> dictionary;

/**
 * Функция для кодирования строки по алгоритму LZ78
 * @param phrase строка для кодирования
 */
void LZ78encode(const string& phrase) {
    // Очистка словаря
    dictionary.clear();
    // Добавление пустой строки в словарь
    dictionary[""] = 0;
    int dictSize = 1; // размер словаря

    string w = ""; // текущая строка
    // Обход строки по символам
    for (char c : phrase) {
        // Создание новой строки, добавляя текущий символ к текущей строке
        string wc = w + c;
        // Если новая строка уже есть в словаре, то обновляем текущую строку
        if (dictionary.find(wc) != dictionary.end()) {
            w = wc;
        } else {
            // Если новая строка не найдена в словаре, то выводим код и добавляем новую строку в словарь
            cout << "<" << dictionary[w] << "," << c << "> ";
            dictionary[wc] = dictSize++;
            w = ""; // обнуляем текущую строку
        }
    }
    // Если текущая строка не пустая, то выводим код
    if (!w.empty()) {
        cout << "<" << dictionary[w] << "," << w.back() << "> ";
    }
}

string LZ78decode(const string& phrase) {
    unordered_map<int, string> dictionary; // словарь для хранения строк
    dictionary[0] = ""; // добавление пустой строки в словарь
    int dictSize = 1; // размер словаря

    string result = ""; // раскодированная строка
    size_t pos = 0; // позиция в строке с кодами

    while (pos < phrase.size()) {
        // Извлечение номера текущей строки и текущего символа из кода
        size_t commaPos = phrase.find(',', pos);
        int prefix = stoi(phrase.substr(pos, commaPos - pos));
        char symbol = phrase[commaPos + 1];

        // Извлечение строки из словаря по номеру
        string w = dictionary[prefix];

        // Добавление строки и текущего символа к раскодированной строке
        result += w + symbol;

        // Добавление новой строки в словарь
        dictionary[dictSize++] = w + symbol;

        // Обновление позиции в строке с кодами
        pos = commaPos + 3; // +3, потому что "<" и ">" не учитываются
    }

    return result;
}

int main() {
    string phrase; // строка для кодирования
    phrase = "sarsalsarsanlasanl33";
    // Кодирование строки по алгоритму LZ78
    LZ78encode(phrase);
    return 0;
}
