#include <iostream>
#include <vector>
#include <algorithm> // Для std::shuffle
#include <random>    // Для std::default_random_engine
#include <chrono>    // Для std::chrono::system_clock
#include <bitset>

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
int* bitSort(int *data, int size) {
    // Создаем битовый набор размером 256 бит
    bitset<256> bitmask = 0;
    // Вычисляем размер данных в битах
    int bitCount = sizeof(long long) * 32;
    // Создаем битовую маску
    bitset<256> mask;
    mask[255] = 1;
    int* resultArr = new int[bitCount];
    int index = bitCount - 1;
    // Устанавливаем биты в битовом наборе в соответствии с данными
    for (int i = 0; i < size; i++) {
        int shiftAmount = (bitCount - 1) - data[i];
        bitset<256> shiftedMask = mask >> shiftAmount;
        bitmask |= shiftedMask;
        resultArr[index--] = bitCount - i - 1;
    }
    return resultArr;
}

int main() {
    int arr[256];
    fillArrayRandomlyUnique(arr, 256);

    cout << "Исходный массив: \n";
    for (int i = 0; i < 256; i++) {
        cout << arr[i] << " ";
    }
    cout << endl << "Отсортированный массив: \n";

    int* out = bitSort(arr, 256);
    for (int i = 0; i < 256; i++) {
        cout << out[i] << " ";
    }
    return 0;
}
