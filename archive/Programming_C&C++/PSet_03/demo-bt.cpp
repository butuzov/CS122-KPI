/**
 * New Type - Worker Salary and comparison operators overload.
 */
typedef std::tuple<std::string, int> WorkerSalary ;

bool operator <  ( WorkerSalary a, WorkerSalary b ){
    return std::get<1>(a) < std::get<1>(b);
}
bool operator >  ( WorkerSalary a, WorkerSalary b ){
    return std::get<1>(a) > std::get<1>(b);
}
bool operator >= ( WorkerSalary a, WorkerSalary b ){
    return std::get<1>(a) >= std::get<1>(b);
}
bool operator <= ( WorkerSalary a, WorkerSalary b ){
    return std::get<1>(a) >= std::get<1>(b);
}
bool operator == ( WorkerSalary a, WorkerSalary b ){
    return std::get<1>(a) == std::get<1>(b);
}
bool operator != ( WorkerSalary a, WorkerSalary b ){
    return std::get<1>(a) != std::get<1>(b);
}

#include "binary-tree.cpp"

template <>
std::string BinaryTree<WorkerSalary>::view(WorkerSalary item){
  return std::get<0>(item) + " with " + std::to_string(std::get<1>(item));
}

int main(){

    BinaryTree<WorkerSalary> salaryData;

    WorkerSalary worker_1 = std::make_tuple("Bohuslava Synycia", 4000);
    WorkerSalary worker_2 = std::make_tuple("Oleksander Holub", 3000);
    WorkerSalary worker_3 = std::make_tuple("Andrian Emu", 3000);
    WorkerSalary worker_4 = std::make_tuple("Daniel Jay", 2000);
    WorkerSalary worker_5 = std::make_tuple("Jacob Kiwi", 1000);

    salaryData.insert(worker_1);
    salaryData.insert(worker_2);
    salaryData.insert(worker_3);
    salaryData.insert(worker_4);
    salaryData.insert(worker_5);

    salaryData.showtree();

}
