#include <iostream>
#include <vector>
#include <algorithm> // Для std::shuffle
#include <random>    // Для std::default_random_engine
#include <chrono>    // Для std::chrono::system_clock

using namespace std;

void fillArrayRandomlyUnique(int arr[], int size) {
    // Создаем вектор с последовательностью чисел
    std::vector<int> numbers;
    for (int i = 0; i < size; i++) {
        numbers.push_back(i);
    }

    // Получаем случайное время для инициализации генератора
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));

    // Копируем первые 'size' элементов в массив
    for (int i = 0; i < size; i++) {
        arr[i] = numbers[i];
    }
}
// Функция для сортировки массива с использованием битовой маски
void bitSort(int *data, int size, int *result, int &resultSize) {
    unsigned int bitmask = 0;       // Начальное значение битовой маски (long long для 2б)
    int bitCount = sizeof(int) * 8; // Вычисление размера битовой маски в битах (sizeof (long long))
    unsigned mask = 1 << bitCount - 1; // Инициализация маски с единственной единицей в старшем бите

    // Заполнение битовой маски на основе элементов массива
    for (int i = 0; i < size; i++) {

        // Сдвиг mask на ((bitCount - 1) - data[i]) позиций
        int shiftAmount = (bitCount - 1) - data[i];
        int shiftedMask = mask >> shiftAmount;
        // Применение побитовой операции "ИЛИ" к bitmask и shiftedMask
        bitmask |= shiftedMask; // Установка соответствующего бита в 1
    }

    resultSize = 0; // Инициализация размера результата

    // Проверка установленных битов и добавление соответствующих индексов в результат
    for (int i = 0; i < bitCount; i++) {
        if ((bitmask & (1 << i))) {
            result[resultSize++] = i; // Добавление индекса установленного бита
        }
    }
}

int main() {
    int arr[64]; // Исходный массив ([64])
    /*int size;
    cout << "Enter size: " << endl;
    cin >> size;
    cout << "Enter up to 8 numbers (0 - 7): " << endl;
    for (int i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }*/
    int result[256]; // Массив для хранения результата
    int resultSize; // Размер результата

    fillArrayRandomlyUnique(arr, 64);
    for (int i = 0; i < 64; ++i) {
        cout << arr[i] << " ";
    }

    bitSort(arr, 64, result, resultSize); // Вызов функции сортировки

    // Вывод отсортированного массива
    cout << "\nSorted: ";
    for (int i = 0; i < resultSize; i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}
