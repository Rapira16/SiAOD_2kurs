#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Структура для хранения символа и его частоты
struct let {
    char lt; // символ
    int cnt; // частота символа
    let(char lt, int cnt) {
        // инициализируем символ и его частоту
        this->lt = lt;
        this->cnt = cnt;
    }
};

// Функция сравнения для сортировки символов по частоте
bool compare_lets(const let *pr1, const let *pr2) {
    // сравниваем частоты символов
    return pr1->cnt > pr2->cnt;
}

// Рекурсивная функция для кодирования методом Шеннона-Фано
void rec(int st, int fn, int sm[], map<char, string> &codes, vector<let *> counts) {
    // если стартовый индекс больше или равен конечному, то выходим из функции
    if (st >= fn) {
        return;
    }
    char r = '0';
    int ed = fn;
    for (int i = st; i <= fn; ++i) {
        // добавляем символ к коду
        codes[counts[i]->lt] += r;
        if (i == fn || fn - st == 1 || (sm[i + 1] - sm[st]) > (sm[fn + 1] - sm[i + 1])){
            // меняем код на '1' и обновляем конечный индекс
            r = '1';
            ed = i;
            break;
        }
    }
    for (int i = ed + 1; i <= fn; ++i) {
        // добавляем символ к коду
        codes[counts[i]->lt] += r;
    }
    // рекурсивно вызываем функцию для левого и правого подмассивов
    rec(st, ed, sm, codes, counts);
    rec(ed + 1, fn, sm, codes, counts);
}

// Функция для создания карты кодов методом Шеннона-Фано
map<char, string> make_map(string text){
    map<char, string> codes;
    vector<let *> counts;

    string set_text = "";
    for (int i = 0; i < text.length(); ++i){
        // если символ не встречался ранее, то добавляем его в set_text
        if (count(set_text.begin(), set_text.end(), text[i]) == 0){
            set_text += text[i];
            codes[text[i]] = "";
        }
    }

    for (int i = 0; i < set_text.length(); ++i){
        // создаем структуру let для каждого символа
        counts.push_back(new let(set_text[i], count(text.begin(), text.end(), set_text[i])));
    }

    // сортируем структуры let по частоте символов
    sort(counts.begin(), counts.end(), compare_lets);

    int sm[counts.size() + 1];
    sm[0] = 0;
    for (int i = 0; i < counts.size(); ++i){
        // вычисляем сумму частот символов
        sm[i + 1] = sm[i] + counts[i]->cnt;
    }

    int st = 0;
    int fn = counts.size() - 1;
    char r = '0';
    int ed = 0;

    // вызываем рекурсивную функцию для кодирования
    rec(st, fn, sm, codes, counts);

    return codes;
}

// Функция для кодирования строки методом Шеннона-Фано
string code(string text, map<char, string> codes){
    string s = "";
    for (int i = 0; i < text.length(); ++i){
        // добавляем код символа к строке
        s += codes[text[i]];
    }
    return s;
}

// Функция для декодирования строки методом Шеннона-Фано
string decode(string text, map<char, string> codes){
    string s = "";
    string buffer = "";
    for (int i = 0; i < text.length(); ++i){
        buffer += text[i];
        for (auto &[lt, code] : codes){
            // если код символа совпадает с буфером, то добавляем символ к строке
            if (code == buffer){
                s += lt;
                buffer = "";
                break;
            }
        }
    }
    return s;
}

// Структура для хранения узла дерева Хаффмана
struct haf
{
    char lt; // символ
    char code; // код символа
    int cnt; // частота символа
    haf *left; // левый ребенок
    haf *right; // правый ребенок
    haf(char lt, int cnt, haf *left, haf *right, char code){
        // инициализируем символ, код, частоту и детей
        this->lt = lt;
        if (left && right){
            this->cnt = left->cnt + right->cnt;
        }else{
            this->cnt = cnt;
        }
        this->left = left;
        this->right = right;
        this->code = code;
    }
    // Функция для поиска символа в дереве Хаффмана
    char find(string code, int ind = 0){
        // если мы достигли листа дерева, то возвращаем символ
        if (!this->left && !this->right){
            if (code.length() == ind){
                return this->lt;
            }else{
                return '@';
            }
        }

        // если индекс больше длины кода, то возвращаем '@'
        if (ind >= code.length()){
            return '@';
        }

        // если код символа равен '0', то идем в левое поддерево
        if (code[ind] == '0'){
            return this->left->find(code, ind + 1);
        }
        // если код символа равен '1', то идем в правое поддерево
        return this->right->find(code, ind + 1);
    }

    // Функция для получения кода символа в дереве Хаффмана
    string get_code(char lt) {
        // если мы достигли листа дерева, то возвращаем код символа
        if (!this->left && !this->right) {
            if (this->lt == lt) {
                return string(1, this->code);
            }
            else {
                return "";
            }
        }

        // рекурсивно вызываем функцию для левого и правого поддеревьев
        string s = this->left->get_code(lt) + this->right->get_code(lt);
        if (s != "" && this->code != '@') {
            return this->code + s;
        }
        return s;
    }
};

// Функция сравнения для сортировки узлов дерева Хаффмана
bool compare_hafs(const haf *pr1, const haf *pr2){
    // сравниваем частоты символов
    return pr1->cnt < pr2->cnt;
}

// Функция для создания дерева Хаффмана
haf *make_haf(string text){
    vector<haf *> cnts;

    string set_text = "";
    for (int i = 0; i < text.length(); ++i){
        // если символ не встречался ранее, то добавляем его в set_text
        if (count(set_text.begin(), set_text.end(), text[i]) == 0){
            set_text += text[i];
        }
    }

    for (int i = 0; i < set_text.length(); ++i){
        // создаем структуру haf для каждого символа
        cnts.push_back(new haf(set_text[i], count(text.begin(), text.end(), set_text[i]), nullptr, nullptr, '@'));
    }
    haf *ptr;
    while (cnts.size() > 1){
        // сортируем структуры haf по частоте символов
        sort(cnts.begin(), cnts.end(), compare_hafs);
        cnts[0]->code = '0';
        cnts[1]->code = '1';
        ptr = new haf('@', 0, cnts[0], cnts[1], '@');
        cnts.push_back(ptr);
        cnts.erase(cnts.begin());
        cnts.erase(cnts.begin());
    }
    ptr = cnts[0];
    return ptr;
}

// Функция для кодирования строки методом Хаффмана
string code_h(string text, haf* codes){
    string s = "";
    for (int i = 0; i < text.length(); ++i){
        // добавляем код символа к строке
        s += codes->get_code(text[i]);
    }
    return s;
}

string decode_h(string text, haf* codes) {
    string s = "";
    string buffer = "";
    char lt = '@';
        for (int i = 0; i < text.length(); ++i) {
            buffer += text[i];
            lt = codes->find(buffer);
            if (lt != '@') {
                s += lt;
                buffer = "";
        }
    }
    return s;
}

int main(){
    string s = "Мой котёнок очень\n"
               "странный, Он не\n"
               "хочет есть сметану, К\n"
               "молоку не прикасался\n"
               "И от рыбки отказался.";
    map<char, string> codes = make_map(s);
    string coded_s = code(s, codes);
    string decoded_s = decode(coded_s, codes);
    cout << "Кодирование методом Шеннона-Фано:" << endl;
    cout << "Исходная строка:" << endl
         << "Размер в битах: " << s.length() * 8 << endl
         << s << endl
         << endl
         << "Закодированная строка:" << endl
         << "Размер в битах: " << coded_s.length() << endl
         << coded_s << endl
         << endl
         << "Раскодированная строка:" << endl
         << decoded_s << endl
         << endl
         << endl;

    s = "И главное, Артем, главное... Не ешь желтый снег! Ха-ха-ха...";
    haf *codes_h = make_haf(s);
    coded_s = code_h(s, codes_h);
    decoded_s = decode_h(coded_s, codes_h);
    cout << "Кодирование методом Хаффмана:" << endl;
    cout << "Исходная строка:" << endl
         << "Размер в битах: " << s.length() * 8 << endl
         << s << endl
         << endl
         << "Закодированная строка:" << endl
         << "Размер в битах: " << coded_s.length() << endl
         << coded_s << endl
         << endl
         << "Раскодированная строка:" << endl
         << decoded_s << endl
         << endl
         << endl;
    return 0;
}
