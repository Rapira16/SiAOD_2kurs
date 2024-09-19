#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

// Структура для хранения данных
struct Data {
    string phoneNumber; // номер телефона
    string address; // адрес
};

// Класс хеш-таблицы
class HashTable {
private:
    vector<Data> data; // массив для хранения данных
    vector<int> hashTable; // хеш-таблица для хранения индексов
    int size; // текущий размер хеш-таблицы
    // максимальный размер хеш-таблицы

    // Функция хеширования с открытым адресованием и квадратичным пробированием
    int hashFunction(string key) {
        // вычисляем хеш-значение ключа
        int hash = 0;
        for (char c : key) {
            hash += c;
        }
        // возвращаем хеш-значение по модулю capacity
        return hash % capacity;
    }

    // Функция квадратичного пробирования
    int probe(int index) {
        // возвращаем следующий индекс по модулю capacity
        return (index + 1) % capacity;
    }

public:
    // Конструктор хеш-таблицы
    HashTable(int initialCapacity) : capacity(initialCapacity) {
        // инициализируем размер хеш-таблицы
        size = 0;
        // инициализируем массив данных
        data.resize(capacity);
        // инициализируем хеш-таблицу с -1
        hashTable.resize(capacity, -1);
    }

    // Вставка нового элемента данных
    void insert(string phoneNumber, string address) {
        // создаем новый элемент данных
        Data newData = {phoneNumber, address};
        // вычисляем индекс для вставки
        int index = hashFunction(phoneNumber);
        // пробуем вставить элемент данных
        while (hashTable[index] != -1) {
            // если индекс занят, пробуем следующий индекс
            index = probe(index);
        }
        // вставляем элемент данных
        data[index] = newData;
        // обновляем хеш-таблицу
        hashTable[index] = index;
        // увеличиваем размер хеш-таблицы
        size++;

        // если коэффициент загрузки превышает 0.7, перераспределяем и рехешируем хеш-таблицу
        if ((double)size / capacity > 0.7) {
            resize();
        }
    }

    // Поиск элемента данных по номеру телефона
    Data* search(string phoneNumber) {
        // вычисляем индекс для поиска
        int index = hashFunction(phoneNumber);
        // пробуем найти элемент данных
        while (hashTable[index] != -1) {
            // если элемент данных найден, возвращаем его
            if (data[index].phoneNumber == phoneNumber) {
                return &data[index];
            }
            // если элемент данных не найден, пробуем следующий индекс
            index = probe(index);
        }
        // если элемент данных не найден, возвращаем nullptr
        return nullptr;
    }

    // Удаление элемента данных по номеру телефона
    void remove(string phoneNumber) {
        // вычисляем индекс для удаления
        int index = hashFunction(phoneNumber);
        // пробуем удалить элемент данных
        while (hashTable[index] != -1) {
            // если элемент данных найден, удаляем его
            if (data[index].phoneNumber == phoneNumber) {
                // сбрасываем элемент данных
                data[index] = Data();
                // обновляем хеш-таблицу
                hashTable[index] = -1;
                // уменьшаем размер хеш-таблицы
                size--;
                return;
            }
            // если элемент данных не найден, пробуем следующий индекс
            index = probe(index);
        }
    }

    // Печать всех элементов данных
    void print() {
        // пробуем печать всех элементов данных
        for (int i = 0; i < capacity; i++) {
            // если элемент данных найден, печатаем его
            if (hashTable[i] != -1) {
                cout << "Phone Number: " << data[i].phoneNumber << ", Address: " << data[i].address << endl;
            }
        }
    }

    // Перераспределение и рехеширование хеш-таблицы
    void resize() {
        // увеличиваем размер хеш-таблицы в два раза
        capacity *= 2;
        // создаем новый массив данных
        vector<Data> newData(capacity);
        // создаем новую хеш-таблицу
        vector<int> newHashTable(capacity, -1);
        // пробуем перераспределить и рехешировать элементы данных
        for (int i = 0; i < size; i++) {
            // вычисляем индекс для перераспределения
            int index = hashFunction(data[i].phoneNumber);
            // пробуем перераспределить элемент данных
            while (newHashTable[index] != -1) {
                // если индекс занят, пробуем следующий индекс
                index = probe(index);
            }
            // перераспределяем элемент данных
            newData[index] = data[i];
            // обновляем хеш-таблицу
            newHashTable[index] = index;
        }
        // обновляем массив данных и хеш-таблицу
        data = newData;
        hashTable = newHashTable;
    }

    int capacity;
};

int main() {
    // создаем хеш-таблицу с начальным размером 10
    HashTable hashTable(10);

    // автоматически заполняем таблицу 5-7 записями
    hashTable.insert("1234567890", "Rilski Kongres, 101");
    hashTable.insert("9876543210", "Crniche, 45");
    hashTable.insert("5551234567", "Ilinden, 12");
    hashTable.insert("5559876543", "Skupi, 5");
    hashTable.insert("5555555555", "Vostanichka, 65");
    hashTable.insert("5551234567", "Kavalska, 43"); // тест на коллизию

    // пробуем выполнить команды
    while (true) {
        cout << "Enter command (insert, search, remove, print, exit): ";
        string command;
        cin >> command;

        if (command == "insert") {
            // вставляем новый элемент данных
            cout << "Enter phone number and address: ";
            string phoneNumber, address;
            cin >> phoneNumber >> address;
            hashTable.insert(phoneNumber, address);
        } else if (command == "search") {
            // ищем элемент данных по номеру телефона
            cout << "Enter phone number to search: ";
            string phoneNumber;
            cin >> phoneNumber;
            Data* data = hashTable.search(phoneNumber);
            if (data != nullptr) {
                // если элемент данных найден, печатаем его
                cout << "Found: Phone Number: " << data->phoneNumber << ", Address: " << data->address << endl;
            } else {
                // если элемент данных не найден, печатаем сообщение
                cout << "Not found." << endl;
            }
        } else if (command == "remove") {
            // удаляем элемент данных по номеру телефона
            cout << "Enter phone number to remove: ";
            string phoneNumber;
            cin >> phoneNumber;
            hashTable.remove(phoneNumber);
        } else if (command == "print") {
            // печатаем все элементы данных
            hashTable.print();
        } else if (command == "exit") {
            // выходим из программы
            break;
        } else {
            // если команда неверна, печатаем сообщение
            cout << "Invalid command." << endl;
        }
    }
    return 0;
}
