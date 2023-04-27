#include <stdio.h>

int main() {
    int  value;
    int  previous;

    scanf( "%d", &previous );
    scanf( "%d", &value );

    do {
        if ( value < previous ) {
            printf( "Não ordenado.\n" );
            
            return 0;
        }
        
        previous = value;
    } while ( scanf( "%d", &value ) == 1 );

    printf( "Ordenado.\n" );

    return 0;
}