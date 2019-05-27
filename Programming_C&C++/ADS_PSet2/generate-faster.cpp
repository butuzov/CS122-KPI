#include "code.cpp"

int main(){

    // This is a test, I have run it with different options
    // to check on how better to write to file.
    //
    //
    // Results for writing 500mb file.
    //
    // buffer 63         -> [Finished in 6.209s]
    //
    // buffer - .5kb     -> [Finished in 6.492s]
    // buffer - 1 kb     -> [Finished in 6.657s]
    // buffer - 2 kb     -> [Finished in 6.627s]
    // buffer - 2.5 kb   -> [Finished in 6.572s]
    // buffer - 4 kb     -> [Finished in 6.79s]
    //
    //  after this point - the bigger buffer the slower write...
    //
    // buffer - 5 kb     -> [Finished in 7.133s]
    // buffer - 10kb     -> [Finished in 8.075s]
    // buffer - 25kb     -> [Finished in 14.638s]
    // buffer - 50kb     -> [Finished in 26.479s]
    // buffer - 100kb    -> [Finished in 51.507s]
    //
    // This is faster implementation, becaurse we only writing our number
    // to string and then checking it size (O(1) operation) when
    // dumping data to file.

    srand( time(NULL) );

    uint64 random_number(0);    // our random number container
    std::string buffer_str;

    uint64 buffer_limit( uint64( 1024 * 4 ) );
    std::string filename( name( "rands", buffer_limit ));

    uint64 file_size(0);
    uint64 file_limit( uint(1024) * uint(1024) * uint(1024) * uint(1) );

    std::ofstream data_in;
    data_in.open ( filename );
    //
    std::cout << std::endl;

    // Generating Numbers List
    while( true ) {

        random_number = random(get_random_index());
        buffer_str   = buffer_str + std::to_string( random_number ) + "\n";

        if ( buffer_str.size() > buffer_limit ){
            data_in << buffer_str;
            // data_in << std::flush;
            file_size = file_size + buffer_str.size();
            buffer_str = std::string();
        }

        if ( file_size >= file_limit )
            break;
    }

   data_in.close();
}
