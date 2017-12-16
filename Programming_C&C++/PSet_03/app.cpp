#include <string>
#include <iostream>
#include <sstream>                /* strings stream       */
#include <stdlib.h>               /* malloc, free, atoi   */
#include <vector>                 /* vector               */
#include <map>                    /* maps                 */
#include "app.hpp"


/**
 * Завантаження данних
 *
 * @param  file file path
 * @return      status
 */
int load_csv(  const char * file, LinkedList<Employee> *employees ){

    // Reading data from cvs file and populating our struct.
    FILE *fp = fopen(file, "r" );
    if ( fp == NULL ) {
        fclose( fp );
        std::cerr << "Can't open source file" << std::endl;
        return 1;
    }


    int counter(0);
    std::string field;
    std::stringstream value;

    std::string Name;
    std::string Position;
    int Day, Month, Year;
    std::vector<int> salary;

    // buffer
    char buffer[1];
    while( fread( buffer, 1, 1, fp ) > 0 ) {

        if ( buffer[0] == 44 || buffer[0] == 10 ) {

            switch( counter % 100 ) {
                case 0:
                    Name = value.str();
                    break;
                case 1:
                    Position = value.str();
                    break;
                break;
                case 2:
                    Year = atoi( ( value.str() ).c_str() );
                    break;
                case 3:
                    Month = atoi( ( value.str() ).c_str() );
                    break;
                case 4:
                    Day = atoi( ( value.str() ).c_str() );
                    break;
                default:
                  salary.push_back( atoi( ( value.str() ).c_str() ) );
                  break;
            }




            // clean up
            value.str( std::string() );

            // counter increment
            ++counter;

            if ( buffer[0] == 10 ) {

                // std::cout << employee.Name
                //           << employee.Position
                //           << employee.Day
                //           << employee.Month
                //           << employee.Year
                //           << std::endl;

                Employee employee;
                employee.Name = Name;
                employee.Position = Position;
                employee.Day = Day;
                employee.Month = Month;
                employee.Year = Year;
                employee.salary = salary;
                (*employees).insert(employee);

                // employee = new Employee();
                // reseting value of employee manually.
                Name = Position = std::string();
                Day = Month = Year = 0;
                salary.clear();

                counter = 0;
            }


        } else {
          value << buffer[0];
        }
    }

    fclose( fp );
    return 0;
}


bool operator <  ( WorkerAge a, WorkerAge b ){

    if ( std::get<1>(a) != std::get<1>(b) ) {
        return std::get<1>(a) > std::get<1>(b);
    }

    if ( std::get<2>(a) != std::get<2>(b) ) {
        // printf("case 2\n");
        return std::get<2>(a) > std::get<2>(b);
    }

    if (  std::get<3>(a) != std::get<3>(b) ) {
        // printf("case 3\n");
        return std::get<3>(a) > std::get<3>(b);
    }

    return false;
}
