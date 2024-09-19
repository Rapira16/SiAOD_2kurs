#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iostream>

// Функция для поиска слов, содержащих подстроку
// Эта функция принимает два параметра: input_text - входной текст и substring - подстрока для поиска
std::vector<std::string> find_words(const std::string& input_text, const std::string& substring) {
    // Вектор для хранения слов, найденных в входном тексте
    std::vector<std::string> words;
    // Поток для разбиения входного текста на слова
    std::istringstream iss(input_text);
    // Переменная для хранения текущего слова
    std::string word;

    // Разбиваем входной текст на слова, используя поток iss
    while (iss >> word) {
        // Добавляем слово в вектор слов
        words.push_back(word);
    }

    // Вектор для хранения результатов поиска
    std::vector<std::string> result;
    // Проходим по каждому слову в векторе слов
    for (const auto& word : words) {
        // Проверяем, содержит ли слово подстроку
        // Мы используем сравнение строк, начиная с конца слова, чтобы найти подстроку
        if (word.size() >= substring.size() &&
            word.compare(word.size() - substring.size(), substring.size(), substring) == 0) {
            // Если да, добавляем его в вектор результатов
            result.push_back(word);
        }
    }

    // Возвращаем вектор результатов
    return result;
}

int main() {
    // Входной текст для поиска
    std::string input_text = "Hello, world! This is a sample text.";
    std::cout << input_text;
    // Подстрока для поиска
    std::string substring = "is";
    // Результат поиска
    std::vector<std::string> result = find_words(input_text, substring);

    // Выводим результат поиска
    for (const auto& word : result) {
        // Выводим каждое слово, содержащее подстроку
        std::cout << word << std::endl;
    }

    return 0;
}
