void debug(std::string message){
  std::cout << message <<std::endl;
}

#include "list.cpp"

int main(int argc, char* argv[]){

  LinkedList<int> numbers;

  numbers.insert(1);
  numbers.insert(2);
  numbers.insert(3);
  numbers.visualize();
  //
  // numbers.shift(); // its OK!
  // numbers.shift(); // its OK!
  numbers.front();
  numbers.next();
  numbers.remove();
  numbers.append(4);
  numbers.prepend(0);
  numbers.insert(100);

  //numbers.remove();
  numbers.visualize();
  //
  std::cout << "Head is "    <<  numbers.view(numbers.head()) << std::endl;
  std::cout << "Current is " <<  numbers.view(numbers.current()) << std::endl;
  std::cout << "Tail is "    <<  numbers.view(numbers.tail()) << std::endl;

}
