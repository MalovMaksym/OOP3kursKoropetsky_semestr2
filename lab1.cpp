//lab1_1
#include <iostream>
#include <string>

using namespace std;

class Passport {
public:
    string series;
    int number;
    string firstName;
    string lastName;
    int birthYear;
    int authorityCode;
    bool isMale;

    int calculateAge(int currentYear) {
        return currentYear - birthYear;
    }
};

int main() {
    Passport pass1;

    cout << "Введіть серію паспорта: ";
    cin >> pass1.series;

    cout << "Введіть номер паспорта: ";
    cin >> pass1.number;

    cout << "Введіть ім'я: ";
    cin >> pass1.firstName;

    cout << "Введіть прізвище: ";
    cin >> pass1.lastName;

    cout << "Введіть рік народження: ";
    cin >> pass1.birthYear;

    cout << "Введіть код органу, що видав: ";
    cin >> pass1.authorityCode;

    cout << "Чоловіча стать (1 - так, 0 - ні): ";
    cin >> pass1.isMale;

    cout << "\n--- Дані про об'єкт ---" << endl;
    cout << "Паспорт: " << pass1.series << " " << pass1.number << endl;
    cout << "ПІБ: " << pass1.lastName << " " << pass1.firstName << endl;
    cout << "Рік народження: " << pass1.birthYear << endl;
    cout << "Код органу: " << pass1.authorityCode << endl;

    if(pass1.isMale) {
        cout << "Стать: Чоловіча" << endl;
    } else {
        cout << "Стать: Жіноча" << endl;
    }

    cout << "\nПоточний вік: " << pass1.calculateAge(2026) << " років" << endl;

    return 0;
}

//lab1_2
#include <iostream>
#include "Passport.h"

using namespace std;

int main() {
    int count;
    cout << "Введіть кількість паспортів: ";
    cin >> count;

    Passport* arr = new Passport[count];

    for (int i = 0; i < count; i++) {
        cout << "\n--- Введення даних для паспорта " << i + 1 << " ---\n";
        cout << "Серія: ";
        cin >> arr[i].series;
        cout << "Номер: ";
        cin >> arr[i].number;
        cout << "Ім'я: ";
        cin >> arr[i].firstName;
        cout << "Прізвище: ";
        cin >> arr[i].lastName;
        cout << "Рік народження: ";
        cin >> arr[i].birthYear;
        cout << "Код органу: ";
        cin >> arr[i].authorityCode;
        cout << "Чоловіча стать (1 - так, 0 - ні): ";
        cin >> arr[i].isMale;
    }

    cout << "\n========================================\n";
    for (int i = 0; i < count; i++) {
        cout << "Дані про паспорт " << arr[i].series << " " << arr[i].number << ":\n";
        cout << "ПІБ: " << arr[i].lastName << " " << arr[i].firstName << "\n";
        cout << "Рік народження: " << arr[i].birthYear << "\n";
        cout << "Код органу: " << arr[i].authorityCode << "\n";
        cout << "Стать: " << (arr[i].isMale ? "Чоловіча" : "Жіноча") << "\n";
        cout << "Повнолітній: " << (arr[i].getIsAdult() ? "Так" : "Ні") << "\n";
        cout << "----------------------------------------\n";
    }

    delete[] arr;
    return 0;
}

//passport.cpp
#include "Passport.h"

int Passport::calculateAge(int currentYear) {
    return currentYear - birthYear;
}

bool Passport::getIsAdult() {
    return calculateAge(2026) >= 18;
}

//passport.h
#ifndef PASSPORT_H
#define PASSPORT_H

#include <string>

class Passport {
public:
    std::string series;
    int number;
    std::string firstName;
    std::string lastName;
    int birthYear;
    int authorityCode;
    bool isMale;

    int calculateAge(int currentYear);
    bool getIsAdult(); 
};

#endif
