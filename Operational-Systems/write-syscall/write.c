#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

// Cia Programma sprymae pershym argumentom ima failu,
// i pishe do niogo use show bude peredano piznishe.

int main (int arg_count, char *arg_verbs[]) {

    if ( arg_count < 3 ) {
        printf("./write filename.txt any extra data\n");
        return 1;
    }

    // inicializacia failovogo descriptory
    int fd;

    // Iakcho faily ne isnue to mi iogo stvorimo
    // abo vidkriyemo iakcho vin dostupniі існує
    if ( ! access( arg_verbs[1], F_OK ) ) {
      fd = open( arg_verbs[1], O_WRONLY );
    } else {
      fd = creat( arg_verbs[1], O_WRONLY ) ;
    }

    // U vypadku pomilky
    // vyidemo z programmy
    if ( fd == -1 ) {
        perror(arg_verbs[1]);
        return EXIT_FAILURE;
    }

    // Using
    char* end = " ";

    for (int counter = 2; counter < arg_count; counter++ ) {
        write(fd, arg_verbs[counter], strlen(arg_verbs[counter]));

        // rozdiluvach
        if ( counter != ( arg_count - 1 ) ){
          write(fd, end, 1);
        }
    }

    // Final endl character.
    end = "\n";
    write(fd, end, 1);
    close(fd);

    return 0;
}
