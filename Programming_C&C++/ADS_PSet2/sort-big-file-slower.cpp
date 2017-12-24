#include "code.cpp"

// this functionality isn't optimal.
// but this is first implementation, so its ok.
//
// its better to
//  - sort array on initial read from unsorted big file.
//  - dump sorted number to files.
//  - merge files.
//
//  You better to dump a string into file not a number,
//  because its easier to generate large strings (4kb is optimal, after
//  that we need to increase capacity and add there all elements again
//  and again..) then write number and check its size and add size to
//  limit.


int main(){
    // Splitting Large Fiels into chunks

    int sorted(0), unsorted( split_big_file( name("data.in") ) );

    // Sorting Files.
    for (int i=1; i <= unsorted; i++ ){

        std::string unsorted_F(name("unsorted", i ));
        std::string sorted_F(name("sorted", i ));

        if ( sort_file( unsorted_F ) ) {
            sorted++;
            rename( unsorted_F.c_str(), sorted_F.c_str() );
        }
    }

    // std::cout << "Sorted " << sorted << std::endl;
    // std::cout << "Un merged " << sorted << std::endl;
    // std::cout << "Un sorted " << unsorted << std::endl;
    if ( (unsorted - sorted) > 0 ){
        throw;
    }

    merge_files( sorted );

    return 0;
}
