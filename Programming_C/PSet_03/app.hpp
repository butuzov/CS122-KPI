/* Структура елемента данних - працівник */
struct Employee {
    std::string Name;
    std::string Position;
    int Day;
    int Month;
    int Year;
    std::vector<int> salary;
    // конструктор стракта
    // Employee(): Name(), Position(), Day(0), Month(0), Year(0) {};
};

// завантажувач данних
int load_csv( const char *, LinkedList<Employee>*);
