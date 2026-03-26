//1
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int flushLetters(char start, char end, int len) {
    if (len == 0) return 0;
    
    if (len >= 3) {
        cout << start << '-' << end;
    } else if (len == 2) {
        cout << start << end;
    } else {
        cout << start;
    }
    return 0;
}

int flushDigits(string& digits) {
    if (!digits.empty()) {
        if (digits.length() != 3) {
            cout << digits;
        }
        digits = "";
    }
    return 0;
}

int main() {
    char ch;
    char seq_start = 0, seq_end = 0;
    int seq_len = 0;
    string digit_buf = "";

    while (cin.get(ch)) {
        if (isdigit(ch)) {
            flushLetters(seq_start, seq_end, seq_len);
            seq_len = 0;
            digit_buf += ch;
        } else if (isalpha(ch)) {
            flushDigits(digit_buf);
            
            if (seq_len == 0) {
                seq_start = ch;
                seq_end = ch;
                seq_len = 1;
            } else if (ch == seq_end + 1 && ((islower(seq_end) && islower(ch)) || (isupper(seq_end) && isupper(ch)))) {
                seq_end = ch;
                seq_len++;
            } else {
                flushLetters(seq_start, seq_end, seq_len);
                seq_start = ch;
                seq_end = ch;
                seq_len = 1;
            }
        } else {
            flushLetters(seq_start, seq_end, seq_len);
            seq_len = 0;
            flushDigits(digit_buf);
            cout << ch;
        }
    }
    
    flushLetters(seq_start, seq_end, seq_len);
    flushDigits(digit_buf);

    return 0;
}


//2
#include <iostream>

using namespace std;

double TrapezoidArea(double a, double b, double h) {
    if (a == 0 || b == 0 || h == 0) {
        throw "\nПомилка: Один з параметрів дорівнює нулю!";
    }
    if (a < 0 || b < 0 || h < 0) {
        throw "\nПомилка: Знайдено від'ємний параметр!";
    }
    
    return ((a + b) / 2.0) * h;
}

int main() {
    double a, b, h;

    cout << "Введіть першу основу трапеції (a): ";
    cin >> a;
    cout << "Введіть другу основу трапеції (b): ";
    cin >> b;
    cout << "Введіть висоту трапеції (h): ";
    cin >> h;

    try {
        double area = TrapezoidArea(a, b, h);
        cout << "\nПлоща трапеції: " << area << endl;
    }
    catch (const char* report) {
        cerr << report << " (a=" << a << ", b=" << b << ", h=" << h << ")" << endl;
    }

    return 0;
}
