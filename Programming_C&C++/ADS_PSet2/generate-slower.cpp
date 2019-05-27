#include "code.cpp"

int main(){

    // seed for rand
    srand( time(NULL) );


   std::ofstream data_in;
   data_in.open ( name("data.in") );
    //
    uint64 random_number(0);    // our random number container
    uint64 totalsize(0);          // total size we using now.

    // Total Allowed size;
    uint64 size(0);
    size = uint(1024) * uint(1024) * uint(1024) * uint(1);


    // Generating Numbers List
    while( true ) {


        random_number = random(get_random_index());
        int random_number_size = num_uint64_length( random_number ) + 1;

        data_in << random_number << std::endl;

        // update size counter.
        totalsize += random_number_size;
        if ( totalsize > size ){
            break;
        }
    }

   data_in.close();
}
