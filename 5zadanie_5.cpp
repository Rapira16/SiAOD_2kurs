#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

int linearSearch(const std::vector<int>& numbers, int key) {
    for (int i = 0; i < numbers.size(); ++i) {
        if (numbers[i] == key) {
            return i; // Возвращаем индекс, если ключ найден
        }
    }
    return -1; // Возвращаем -1, если ключ не найден
}

int main() {
    std::ifstream file("/home/han/CLionProjects/SiAOD_2_5_2/input100.bin", std::ios::binary);

    if (file) {
        std::vector<int> numbers;
        std::vector<std::string> restOfLines;

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            int number;
            ss >> number;
            std::string rest = line.substr(6); // Отделяем первый символ

            numbers.push_back(number);
            restOfLines.push_back(rest);
        }

        file.close();

        // Вывод чисел

        int key; // Пример ключа для поиска
        std::cout << "Enter key: ";
        std::cin >> key;
        int index = linearSearch(numbers, key);
        if (index != -1) {
            std::cout << "Key " << key << " found at index " << index << std::endl;
            std::cout << "Information in: " << restOfLines[index];
        } else {
            std::cout << "Key " << key << " not found" << std::endl;
        }

    } else {
        std::cerr << "Ошибка открытия файла." << std::endl;
    }

    return 0;
}
