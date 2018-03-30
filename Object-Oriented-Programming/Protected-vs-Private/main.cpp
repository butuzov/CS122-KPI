#include <iostream>
#include <string>

class Padre {
    public:
        std::string text = "Soy Padre";

        Padre()  {
            std::cout << "Empezar: " <<  text <<std::endl;
        }

        ~Padre(){
              std::cout << "Fin: " << text << std::endl;
        }

    public:
        void test(){
            privado();
            protegido();
        }

    private:
        void privado(){
            std::cout << "Soy privado" << std::endl;
        }
    protected:

        void protegido(){
            std::cout << "Soy protegido" << std::endl;
        }

};


class Hijo: public Padre  {
    public:
        std::string text = "Soy Hijo";

        Hijo()  {
            std::cout << "Empezar: " <<  text <<std::endl;
        }

        ~Hijo(){
              std::cout << "Fin: " << text << std::endl;
        }
    // public:
    //     void test(){
    //         privado();
    //         protegido();
    //     }

    private:
        void privado(){
            std::cout << "Soy hijo privado" << std::endl;
        }
    protected:

        void protegido(){
            std::cout << "Soy hijo protegido" << std::endl;
        }
};

int main(){

    Padre* p = new Padre();
    p->test();
    delete p;

    std::cout << std::string( 90, '.' ) << std::endl;

    Hijo* h = new Hijo();
    h->test();
    delete h;
}
