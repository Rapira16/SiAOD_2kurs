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

int main() {
    string phrase; // строка для кодирования
    phrase = "sarsalsarsanlasanl33";
    // Кодирование строки по алгоритму LZ78
    LZ78encode(phrase);
    return 0;
}
