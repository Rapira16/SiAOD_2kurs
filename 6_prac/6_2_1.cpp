#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>

// Функция для поиска слов, содержащих подстроку
// Эта функция принимает два параметра: input_text - входной текст и substring - подстрока для поиска
std::vector<std::string> find_words(const std::string& input_text, const std::string& substring) {
    // Вектор для хранения слов, найденных в входном тексте
    std::vector<std::string> words;
    // Переменная для хранения текущего слова
    std::string word;

    // Разбиваем входной текст на слова, проходя по каждому символу
    for (char c : input_text) {
        // Если встретили пробел, это означает конец слова
        if (std::isspace(c)) {
            // Если слово не пустое, добавляем его в вектор слов
            if (!word.empty()) {
                words.push_back(word);
                // Очищаем переменную word для хранения следующего слова
                word.clear();
            }
        } else {
            // Если не пробел, добавляем символ к текущему слову
            word += c;
        }
    }

    // Добавляем последнее слово в вектор, если оно не пустое
    if (!word.empty()) {
        words.push_back(word);
    }

    // Вектор для хранения результатов поиска
    std::vector<std::string> result;
    // Проходим по каждому слову в векторе слов
    for (const auto& word : words) {
        // Очищаем слово от неалфавитных символов, таких как знаки препинания
        std::string clean_word;
        for (char c : word) {
            // Проверяем, является ли символ алфавитным
            if (std::isalnum(c)) {
                // Если да, добавляем его к очищенному слову
                clean_word += c;
            }
        }

        // Проверяем, содержит ли очищенное слово подстроку
        if (clean_word.find(substring) != std::string::npos) {
            // Если да, добавляем его в вектор результатов
            result.push_back(clean_word);
        }
    }

    // Возвращаем вектор результатов
    return result;
}

int main() {
    // Входной текст для поиска
    std::string input_text = "Hello, world! This is a sample text.";
    // Подстрока для поиска
    std::string substring = "l";
    // Результат поиска
    std::vector<std::string> result = find_words(input_text, substring);

    // Выводим результат поиска
    for (const auto& word : result) {
        // Выводим каждое слово, содержащее подстроку
        std::cout << word << std::endl;
    }

    return 0;
}
