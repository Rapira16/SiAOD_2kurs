#include <iostream>
#include <string>
#include <string_view>
#include <forward_list>
#include <algorithm>

using namespace std;

// Структура для хранения кодированных данных
struct CodeNode
{
    unsigned char beg; // смещение от начала окна поиска
    unsigned char len; // длина повторяющейся подстроки
    char ch; // текущий символ
};

// Функция для сдвига символа в строке
// Она используется для сдвига символа в окне поиска, когда мы находим повторяющуюся подстроку
bool push_shift (string& s, char c, size_t len)  // возвращает true, если первый символ был удален
{
    if (s.size() < len) {s.push_back(c); return false;}
    // сдвигаем символы в строке, чтобы освободить место для нового символа
    move (next(s.begin()), s.end(), s.begin());
    s.back() = c; return true;
}

// Функция для кодирования строки с помощью алгоритма LZ77
forward_list<CodeNode> LZ77 (string_view s, size_t win_len = 255)
{
    forward_list<CodeNode> res; auto it = res.before_begin();
    string win, buf; win.reserve(win_len); buf.reserve(win_len);
    CodeNode next; size_t saved_win_len = 0;
    // проходимся по каждому символу в строке
    for (char c : s) {
        buf.push_back(c);
        size_t pos;
        next.ch = c;
        // ищем повторяющуюся подстроку в окне поиска
        if ((pos = win.rfind(buf)) != string::npos) {
            // если нашли, то записываем смещение и длину повторяющейся подстроки
            next.beg = saved_win_len-pos; next.len = buf.size();
            if (  push_shift (win, c, win_len)  ) saved_win_len--;  // сдвиг символа в окне поиска
        } else {
            // если не нашли, то записываем новый символ и обнуляем буфер
            it = res.insert_after(it, next); buf.resize(0);
            next.beg = 0; next.len = 0;
            push_shift (win, c, win_len);
            saved_win_len = win.size();
        }
    }
    // если последний символ не был записан, то записываем его
    if (next.len != 0) {next.len--; res.insert_after(it, next);}
    return res;
}

// Функция для получения длины оригинальной строки
size_t LZ77length (const forward_list<CodeNode>& code) { 
    size_t len = 0;
    // проходимся по каждому кодированному символу и суммируем длины повторяющихся подстрок
    for (const CodeNode& cn : code) len += cn.len+1;
    return len;
}

// Функция для получения размера кодированных данных
size_t LZ77size (const forward_list<CodeNode>& code) {  
    // размер кодированных данных равен размеру структуры CodeNode, умноженному на количество кодированных символов
    return sizeof(CodeNode) * distance(code.begin(), code.end());
}

// Функция для декодирования кодированных данных
string LZ77decode (const forward_list<CodeNode>& code)
{
    string res;
    res.reserve(LZ77length(code)); // зарезервировать память для результата
    // проходимся по каждому кодированному символу и восстанавливаем оригинальную строку
    for (CodeNode cn : code) {
        for (size_t i = res.size()-cn.beg, e = i+cn.len; i != e; ++i)
            res += res[i];
        res += cn.ch;
    }
    return res;
}

// Оператор вывода для структуры CodeNode
ostream& operator<< (ostream& os, CodeNode cn) {
    return os << '<' << int(cn.beg) << ',' << int(cn.len) << ',' << cn.ch << '>';
}

int main()
{
    string s;
    s = "010110110110100010001"; // для тестирования
    auto code = LZ77(s,10);
    // выводим кодированные данные
    for (CodeNode cn : code) cout << cn << ' ';
    cout << endl;
    // декодируем кодированные данные и выводим оригина
