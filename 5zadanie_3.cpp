// C++ код для сортировки большого объема числовых данных в файле с использованием битового массива

#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <ctime>


int main() {
    int start = clock();
    const int MAX_NUM = 10000000; // Максимальное число в наборе данных
    const int BIT_ARRAY_SIZE = MAX_NUM / 8 + 1; // Размер битового массива для охвата всех чисел

    std::bitset<MAX_NUM> bitArray; // Битовый массив для представления чисел
    bitArray.reset(); // Инициализация всех битов в 0

    // Чтение данных из входного файла и установка соответствующих битов в битовом массиве
    std::ifstream inputFile("/home/han/CLionProjects/SiAOD_51/input.txt");
    int num;
    while (inputFile >> num) {
        bitArray.set(num);
    }
    inputFile.close();

    // Запись отсортированных данных в выходной файл путем проверки битового массива
    std::ofstream outputFile("/home/han/CLionProjects/SiAOD_51/output.txt");
    for (int i = 0; i < MAX_NUM; ++i) {
        if (bitArray.test(i)) {
            outputFile << i << std::endl;
        }
    }
    int stop = clock();
    int res = stop - start;
    std::cout << bitArray.size()/(1024*1024*8) << "Mb\n";
    std::cout << res << "ms";
    outputFile.close();

    return 0;
}
