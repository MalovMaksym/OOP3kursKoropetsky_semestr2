//1
#include <iostream>
#include <string>

using namespace std;

class TicketNode {
public:
    string destination;
    int flightNumber;
    string passengerName;
    string date;
    TicketNode* next;

    TicketNode() : flightNumber(0), next(NULL) {}

    bool input() {
        cout << "Введіть пункт призначення: ";
        cin >> destination;
        cout << "Введіть номер рейсу: ";
        cin >> flightNumber;
        cout << "Введіть ПІБ пасажира: ";
        cin.ignore();
        getline(cin, passengerName);
        cout << "Введіть дату вильоту (ДД.ММ.РРРР): ";
        cin >> date;
        return true;
    }

    string getInfo() const {
        return "Рейс: " + to_string(flightNumber) + " | Куди: " + destination + 
               " | Пасажир: " + passengerName + " | Дата: " + date;
    }
};

class TicketList {
private:
    TicketNode* head;
    TicketNode* tail;

public:
    TicketList() : head(NULL), tail(NULL) {}

    bool add() {
        TicketNode* newNode = new TicketNode();
        newNode->input();
        
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        cout << "Заявку успішно додано!\n";
        return true;
    }

    int displayAll() const {
        if (head == NULL) {
            cout << "Список порожній.\n";
            return 0;
        }
        
        TicketNode* current = head;
        int count = 0;
        while (current != NULL) {
            cout << current->getInfo() << endl;
            current = current->next;
            count++;
        }
        return count;
    }

    int displaySpecific() const {
        int searchFlight;
        string searchDate;
        
        cout << "\nВведіть номер рейсу для пошуку: ";
        cin >> searchFlight;
        cout << "Введіть дату для пошуку: ";
        cin >> searchDate;

        TicketNode* current = head;
        int count = 0;
        
        while (current != NULL) {
            if (current->flightNumber == searchFlight && current->date == searchDate) {
                cout << current->getInfo() << endl;
                count++;
            }
            current = current->next;
        }
        
        if (count == 0) {
            cout << "Заявок за цими даними не знайдено.\n";
        }
        return count;
    }

    bool remove() {
        string searchName;
        cout << "\nВведіть ПІБ пасажира для видалення: ";
        cin.ignore();
        getline(cin, searchName);

        TicketNode* current = head;
        TicketNode* previous = NULL;

        while (current != NULL) {
            if (current->passengerName == searchName) {
                if (previous == NULL) {
                    head = current->next;
                } else {
                    previous->next = current->next;
                }
                if (current == tail) {
                    tail = previous;
                }
                delete current;
                cout << "Заявку видалено.\n";
                return true;
            }
            previous = current;
            current = current->next;
        }
        
        cout << "Пасажира не знайдено.\n";
        return false;
    }

    ~TicketList() {
        TicketNode* current = head;
        while (current != NULL) {
            TicketNode* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
};

int main() {
    TicketList list;
    
    cout << "=== Демонстрація роботи зі списком заявок ===\n\n";
    
    list.add();
    cout << "\n";
    list.add();
    
    cout << "\n--- Всі заявки ---\n";
    int total = list.displayAll();
    cout << "Всього записів: " << total << "\n";
    
    list.displaySpecific();
    list.remove();
    
    cout << "\n--- Оновлений список ---\n";
    list.displayAll();
    
    return 0;
}

//2
#include <iostream>
#include <string>

using namespace std;

class FlightData {
private:
    string destination;
    int flightNumber;
    string passengerName;
    string date;

public:
    FlightData() : flightNumber(0) {}

    bool input() {
        cout << "Введіть пункт призначення: ";
        cin >> destination;
        cout << "Введіть номер рейсу: ";
        cin >> flightNumber;
        cout << "Введіть ПІБ пасажира: ";
        cin.ignore();
        getline(cin, passengerName);
        cout << "Введіть дату: ";
        cin >> date;
        return true;
    }

    string getInfo() const {
        return "Рейс: " + to_string(flightNumber) + " | Куди: " + destination + 
               " | Пасажир: " + passengerName + " | Дата: " + date;
    }
};

template <class T>
class Node {
public:
    T data;
    Node<T>* next;

    Node() : next(NULL) {}
};

template <class T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    LinkedList() : head(NULL), tail(NULL) {}

    bool add() {
        Node<T>* newNode = new Node<T>();
        newNode->data.input();
        
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        cout << "Дані додано до списку!\n";
        return true;
    }

    int displayAll() const {
        if (head == NULL) {
            cout << "Список порожній.\n";
            return 0;
        }
        
        Node<T>* current = head;
        int count = 0;
        while (current != NULL) {
            cout << current->data.getInfo() << endl;
            current = current->next;
            count++;
        }
        return count;
    }

    ~LinkedList() {
        Node<T>* current = head;
        while (current != NULL) {
            Node<T>* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
};

int main() {
    LinkedList<FlightData> myList;
    
    cout << "=== Демонстрація роботи шаблонного списку ===\n\n";
    
    myList.add();
    cout << "\n";
    myList.add();
    
    cout << "\n--- Вміст списку ---\n";
    int count = myList.displayAll();
    cout << "Кількість елементів: " << count << endl;
    
    return 0;
}

//3
#include <iostream>
#include <string>

using namespace std;

class File {
protected:
    string filename;
    int sizeBytes;

public:
    File() : filename(""), sizeBytes(0) {}

    virtual bool input() {
        cout << "Введіть ім'я файлу (наприклад, text.txt): ";
        cin >> filename;
        cout << "Введіть розмір файлу в байтах: ";
        cin >> sizeBytes;
        return true;
    }

    virtual string getInfo() const {
        return "Файл: " + filename + " | Розмір: " + to_string(sizeBytes) + " байт";
    }
};

class ExtendedFile : public File {
private:
    string creationDate;
    string creationTime;

public:
    ExtendedFile() : File(), creationDate(""), creationTime("") {}

    bool input() override {
        File::input();
        cout << "Введіть дату створення (ДД.ММ.РРРР): ";
        cin >> creationDate;
        cout << "Введіть час створення (ГГ:ХХ): ";
        cin >> creationTime;
        return true;
    }

    string getInfo() const override {
        string baseInfo = File::getInfo();
        return baseInfo + "\nДата створення: " + creationDate + "\nЧас створення: " + creationTime;
    }
};

int main() {
    ExtendedFile myFile;
    
    cout << "=== Демонстрація роботи класу File з успадкуванням ===\n\n";
    
    myFile.input();
    
    cout << "\n--- Інформація про файл ---\n";
    cout << myFile.getInfo() << endl;
    
    return 0;
}
