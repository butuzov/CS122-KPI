#include "code.hpp"

/**
 * We can use string stream here (but its slower).
 * We can use math way, but its a bit complicated.
 *
 * So we going to use sprintf  algotrithm here.
 */
int num_uint64_length(uint64 num){
  // one way
  //
  // char s[20];
  // return sprintf(s, "%llu", num);

  // or another....i'm gonna find ya'
  return (std::to_string(num)).size();
}

// input parameter, how many bytes will take our number..
uint64 random( int len ){
    assert(0 < len && len <= 8);
    uint64 random_number(0);

    int *bytes((int *) calloc(len, sizeof(int)));

    for (int i=0; i < len; i++){
        bytes[i] = ( rand() % (int) pow(2, 8 ) - 1 );
        random_number = random_number | ( uint64( bytes[i] ) << ( i * 8 ) );
       // std::cout << "Step " << i << " " << bytes[i] << " " << random_number << std::endl;
    }

    free(bytes);
    return random_number;
}

// return more random number from 1 to 8
// so n values can appear with a better freaquency
int get_random_index(){
    int length = 8;
    int values[length];
    for (int i=0; i < length; i++){
        values[i] = rand() % length + 1;
    }
    return values[rand() % length];
}

// generates file name with or without number.
std::string name(std::string name, int num = 0){
    std::stringstream value;

    if ( debug ){
      value << "/Volumes/r/";
    }

    value << name;
    if ( num > 0 ){
      value << "_" << std::to_string(num);
    }
    value << ".txt";
    return value.str();
}

// Helper method to show array.
void array_echo(int array_length, uint64* array) {
    std::cout << "[";
    for (int i = 0; i < array_length; i++) {
        std::cout << array[i] << (i+1 != array_length ? ", ": "");
    }
    std::cout << "]" << std::endl;
}

// should i update line (with file number?)
std::string maybe_update_line(std::string str, int num = 0){
  // перевіряємо чи данна строка вже містить дані про файл
  try {
      str.substr(POSITION, 1);
  } catch (const std::out_of_range& oor) {

      std::string n(std::to_string(num));

      int length(POSITION + n.size());
      if ( length > str.capacity() ){
          str.reserve(length);
      }

      str += std::string( (POSITION - str.size()) , ' ') + n;
  }
  return str;
}

// convert our line
// with only number or number with source file
// to uint64
uint64 line_to_number(std::string str){
    int pos(str.find( " " ));
    uint64 number;

    try {
        number = std::stoull( (-1 == pos ? str : str.substr(0, pos) ));
        return number;
    } catch (const std::invalid_argument& ia) {
        std::cout << "Problem " << str.size() << std::endl;
        throw;
    }
}


// Merge Sort Method.
void array_merge_sort(int array_length, uint64* array) {

    if ( array_length != 1 ) {

        // Size of Left array
        int left_length  = array_length / 2;

        // Size of the Right array
        int right_length = array_length - left_length;

        // Allocating memory for Left and Right arrays.
        uint64 *left_array( array_make( left_length ) );
        uint64 *right_array( array_make( right_length ) );

        // Initial Indexes.
        int left_index = 0, right_index = 0;

        // Dividing original array in two.
        for( int i = 0; i < array_length; i++ ) {
            if ( i < left_length ) {
                left_array[ left_index++ ] = array[ i ];
             } else {
                right_array[ right_index++ ] = array[ i ];
            }
        }

        /**
         * Actual Sort for both Sides
         */

        // recursive calls to sort left array...
        array_merge_sort( left_length, left_array );

        // array_echo(left_length, left_array);

        // ... and right arrays
        array_merge_sort( right_length, right_array );

        // array_echo( right_length, right_array );

        /**
         * Merging both sides!
         */

        // Reseting indexes for left and right array.
        left_index = 0, right_index = 0;

        // Original array index.
        int index = 0;

        // Merging values while sorting it.
        while( left_index < left_length && right_index < right_length ) {
            if ( left_array[ left_index ] < right_array[ right_index ] ) {
                array[ index++  ] = left_array[ left_index++ ];
            } else {
                array[ index++  ] = right_array[ right_index++ ];
            }
        }

        // If we have something left from left array, appending
        // it value to end of array.
        if ( left_index < left_length ) {
            for ( int j = left_index; j < left_length; j++){
                array[ index ++ ] = left_array[ j ];
            }
        }

        // If something left from right array, appending it value
        // to end of result array.
        if ( right_index < right_length ) {
            for ( int j = right_index; j < right_length; j++){
                array[ index ++ ] = right_array[ j ];
            }
        }

        free(left_array);
        free(right_array);
    }
}

// Heap Sort
void array_heap_sort(int array_length, uint64* array){

    if (array_length <= 1) {
        return;
    }

    auto hipify = [&]( int array_length, int index ) -> void {

        // next child to check.
        int next = (index == 0) ? 1 : 2*index;

        // Next is next (in heap representation of array)
        while( next < array_length ) {

            // in case ir right next is larger...
            if ( next < (array_length-1) && array[next+1] > array[next] ) {
                next++;
            }

            if ( array[index] > array[next] ) {
                break;
            }

            swap(&array[index], &array[next]);
            index = next;
            next *= 2; // one more way up...
        }
    };

    /* Building Heap in Array.*/
    for (int i = (array_length / 2) - 1; i >= 0; i--) {
        hipify(array_length, i);
    }

    // Final Sort
    for (int i = array_length-1; i >=0; i-- ){
         swap(&array[0], &array[i]);
         hipify(i, 0);
    }

}

// Swap operation for array elements.
// that doesn't require extra space.
void swap(uint64 *a, uint64 *b){
    if (a == b) {
        return;
    }
    // Maxim Myhailovich! 10nx!!!
    *a = *a + *b; // updating value of a y b
    *b = *a - *b; // updating value of b by (a minus b(b still holds value))
    *a = *a - *b; // updating value of a by decrementing b.
    return;
}

// Memory allocation for array.
uint64* array_make(int array_length) {
    return (uint64 *) calloc(array_length, sizeof(uint64) );
}

// fill array with zero values.
// used during debug and testing and array generation.
void array_fill(int array_length, uint64* array) {
    srand(time(0));
    for (int i = 0; i < array_length; i++) {
      //  array[i] = uint64( rand() % array_length );
       array[i] = random( get_random_index() ) ;
    }
}

/*
 * This is one of 3 most important functions here.
 * this will:
 * - split file into chuncs of unsorted data.
 * - sort it with our predefined sort algorith
 * - proccess merging files simular to merge sort.
 */
int split_big_file( std::string file ) {
    // File -> unserted_n.
    int n(0), counter(0);
    std::string line;

    // Incoming (Input file)
    std::ifstream incoming;
    incoming.open( file );
    if ( !incoming.good() ){
        std::logic_error( "we cant open this file" );
    }


    std::ofstream unsorted;
    while ( std::getline( incoming, line ) ) {
        // if counter reseted we starting new file.
        if ( n == 0 ) {
            unsorted.open( name( "unsorted", (counter+1) ) );
        }

        unsorted << line << std::endl;

        // if counter greater them limit,
        // we closign file and starting new counter.
        if (++n >= NUMBERS_PER_UNSORTED_ARRAY ){
          counter++;
          n = 0;
          unsorted.close();
        }
    }

    // Closing stream.
    incoming.close();
    unsorted.close();

    return counter + 1;
}


/*
 * This is one of 3 most important functions here.
 * this will:
 * - sort file! (and change content)
 */
bool sort_file( std::string file) {

    // no file -> no sorting.
      std::ifstream incoming;
      incoming.open( file );
    if ( ! incoming.good() ) {
        return false;
    }

    // Array and memory allocation.
    int array_length( NUMBERS_PER_UNSORTED_ARRAY );
    uint64 *array( array_make( array_length ) );

    // lines counter.
    int lines(0);

    // Buffer string
    std::string       line_string;

    while ( std::getline( incoming, line_string ) ) {
        std::stringstream line_stream;
        line_stream << line_string;       // casetig string to string stream
        line_stream >> array[lines];      // casting to uint64 from stream
        lines++;
    }
    incoming.close();

    //std::cout << lines;

    // debug setting.
    // array_echo(array_length, array);

    // if array is smaller - fix memory allocation.
    if ( lines != array_length ) {
        array = (uint64 *) realloc(array, lines*sizeof(uint64));
        array_length = lines;
    }

    // debug - elements in array
    // std::cout << lines << " " << array_length;

    // sort array.
    // array_merge_sort(array_length, array);

    array_heap_sort(array_length, array);


    std::ofstream outgoing;
    outgoing.open( file );

    // initiating previous with NOT the first value.
    uint64 previous(array[0] + 1);

    for (int i=0; i < array_length; i++){
        if ( previous != array[i] ) {
            previous   = array[i];
            outgoing  << array[i];
            outgoing  << std::endl;
        }
    }
    outgoing.close();

    // release allocation
    free(array);

    return true;
}


void merge_files( int sorted ){
    int n(0), next_sorted(0), merged(0), next_merged(0);

    while ( true ) {

        n++;

        std::ofstream result;
        std::string file_result_name(""), file_result_tmp_name("");

        // initiating zero variables (w zero values sometimes)
        std::ifstream file_a, file_b;
        // bool status_a(false), status_b(false);
        std::string line_a(""), line_b(""), file_a_name(""), file_b_name("");

        uint64 number_a(0), number_b(0), file_a_n(0), file_b_n(0);


        if (next_sorted < sorted) {

          // incrementing next merged
          ++next_merged;

          // always updating.
          merged = next_merged;

          file_a_n = ++next_sorted;
          file_a_name = name( "sorted", file_a_n );
          file_a.open( file_a_name );

          // we going to ignore fact that its possible for this
          // file to not exists.
          file_b_n = ++next_sorted;
          file_b_name = name( "sorted", file_b_n );
          file_b.open( file_b_name );

          file_result_name = name("merged", next_merged );
          file_result_tmp_name = name( "tmp" );
          result.open( file_result_tmp_name );
        } else {

            // Finally if merge at least one (need this to get rid of tempprary
            // merged) file and we don't need to merge any more.
            if ( merged == 1 ){
                rename( ( name("merged", merged) ).c_str(), (name("data.out")).c_str() );
                return;
            }

            // next_merged counter reset.
            if ( next_merged >= merged ){
                next_merged = 0;
            }

            // File A
            file_a_n = ++next_merged;
            file_a_name = name( "merged", file_a_n );
            file_a.open( file_a_name );

            // FIle B
            file_b_n = ++next_merged;
            file_b_name = name( "merged", file_b_n );
            file_b.open( file_b_name );

            // Result File
            file_result_name = name("merged", next_merged / 2 );
            file_result_tmp_name = name( "tmp" );
            result.open( file_result_tmp_name );

            // merged updated.
            if ( next_merged >= merged ){
                merged = next_merged / 2;
                if ( merged == 1 ) {
                    file_result_name = name("data.out");
                }
            }
        }

        while( true ) {

            // reading lines and numbers.
            if ( file_a.is_open() && line_a.empty()
                  && std::getline( file_a, line_a ) ) {
                number_a = line_to_number(line_a);
            }

            if ( file_b.is_open() && line_b.empty()
                  && std::getline( file_b, line_b ) ) {
                number_b = line_to_number(line_b);
            }

            if ( line_a.empty() && line_b.empty() ){
                // no more left.
                break;
            } else if ( line_a.empty() ) {

                // if A empty we can copy line from B
                result << maybe_update_line( line_b, file_b_n ) << std::endl;
                line_b = std::string();

            } else if ( line_b.empty() ) {

                // if B empty we can copy line from A
                result << maybe_update_line( line_a, file_a_n ) << std::endl;
                line_a = std::string();

            } else {
                std::string line;
                if ( number_a < number_b ) {
                    // std::cout << number_a << " < " << number_b << std::endl;

                    line = maybe_update_line( line_a, file_a_n );
                    line_a = std::string();

                } else if ( number_a > number_b ) {
                    // std::cout << number_a << " > " << number_b << std::endl;

                    line = maybe_update_line( line_b, file_b_n );
                    line_b = std::string();
                } else {
                    // they are eqvivalent!
                    // std::cout << number_a << " == " << number_b << std::endl;

                    line = maybe_update_line( line_a, file_a_n );
                    line_a = line_b = std::string();
                }
                result << line << std::endl;;
            }
        }

        // first clean up.
        if (file_a.is_open()) {
            file_a.close();
            remove( file_a_name.c_str() );
        }

        if (file_b.is_open()) {
            file_b.close();
            remove( file_b_name.c_str() );
        }

        // next save results.
        result.close();
        rename( file_result_tmp_name.c_str(), file_result_name.c_str() );
        result.close();
    }
}
