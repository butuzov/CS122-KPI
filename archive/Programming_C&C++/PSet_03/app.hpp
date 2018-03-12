/* Структура елемента данних - працівник */
struct Employee {
    std::string Name;
    std::string Position;
    int Day;
    int Month;
    int Year;
    std::vector<int> salary;
};

// завантажувач данних
int load_csv( const char *, LinkedList<Employee>*);

// зарплатно вікова тупля
// 1) std::string Name
// 2) int Year
// 3) int Month
// 4) int Day
// 5) int Salary
typedef std::tuple<std::string, int, int, int, int> WorkerAge;
