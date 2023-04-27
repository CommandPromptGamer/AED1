#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

void Quicksort( int* array, int size );
bool TestOrder( int *array, int size );
void PrintArray( int *array, int size );

int main( int argc, char *argv[] ) {
    int    size = 10;
    int *  array;
    bool   raw = false;
    bool   test = false;

    srand( time( NULL ) );

    for ( int i = 0; i < argc; i++ ) {
        if ( !strcmp( argv[ i ], "--size" ) || !strcmp( argv[ i ], "-s" ) ) {
            size = atoi( argv[ i + 1 ] );
        } else if ( !strcmp( argv[ i ], "--raw" ) || !strcmp( argv[ i ], "-r" ) ) {
            raw = true;
        } else if ( !strcmp( argv[ i ], "--test" ) || !strcmp( argv[ i ], "-t" ) ) { 
            test = true;
        } else if ( !strcmp( argv[ i ], "--help" ) || !strcmp( argv[ i ], "-h" ) ) {
            printf( "O programa gera um vetor aleatório de determinado tamanho e o ordena.\n" );
            printf( "\tOpções:\n" );
            printf( "\t\t-r ou --raw:\n" );
            printf( "\t\t\tImprime apenas o vetor ordenado e não o aleatório original, nem se ele está de fato ordenado.\n" );
            printf( "\t\t-s ou --size:\n" );
            printf( "\t\t\tEspecifica o tamanho do vetor aleatório. Deve ser seguido de um número inteiro decimal.\n" );
            printf( "\t\t\tPadrão: 10.\n" );
            printf( "\t\t-t ou --test:\n" );
            printf( "\t\t\tImprime apenas se a ordenação foi bem sucedida.\n" );
            printf( "\t\t\t-r e --raw são ignorados se essa opção é usada.\n" );
            printf( "\t\t-h ou --help:\n" );
            printf( "\t\t\tMostra a ajuda do programa.\n" );

            return 0;
        }
    }

    array = malloc( size * sizeof( int ) );

    for( int i = 0; i < size; i++ ) {
        array[i] = rand();
    }

    if ( !raw && !test ) {
        printf( "O vetor aleatório é:\n" );
        PrintArray( array, size );
    }

    Quicksort( array, size );
    
    if ( !raw && !test ) {
        printf( "O vetor em ordem é:\n" );
        PrintArray( array, size );
    } else if ( !test ) {
        for ( int i = 0; i < size; i++ ) {
            printf( "%d ", array[ i ] );
        }
    }

    if ( !raw && !test ) {
        TestOrder( array, size ) ? printf( "O vetor foi ordenado adequadamente.\n" ) : printf( "O vetor não foi ordenado adequadamente.\n" );
    }

    if ( test ) {
        TestOrder( array, size ) ? printf( "O vetor foi ordenado adequadamente.\n" ) : printf( "O vetor não foi ordenado adequadamente.\n" );
    }

    return 0;
}

bool TestOrder( int *array, int size ) {
    for ( int i = 0; i < size - 1; i++ ) {
        if ( array[ i ] > array[ i + 1 ] ) {
            return false;
        }
    }

    if ( array[ size - 2 ] > array[ size - 1 ] ) {
        return false;
    }

    return true;
}

void PrintArray( int *array, int size ) {
    printf("{");
    
    for(int i = 0; i < size - 1; i++){
        printf("%d, ", array[i]);
    }
    
    printf("%d}\n", array[size - 1]);
}

void _Quicksort_r( int *array, int left, int right ) {
    int  pivot;
    int  i;
    int  j;
    int  aux;

    i = left;
    j = right;

    pivot = array[ left + rand() % ( right - left + 1 ) ];

    do {
        while ( array[ i ] < pivot ) {
            i++;
        }

        while ( pivot < array[ j ] ) {
            j--;
        }

        if ( i <= j ) {
            aux = array[ i ];
            array[ i ] = array[ j ];
            array[ j ] = aux;

            i++;
            j--;
        }
    } while ( i <= j );

    if ( left < j ) {
        _Quicksort_r( array, left, j );
    }

    if ( i < right ) {
        _Quicksort_r( array, i, right );
    }
}

void Quicksort( int* array, int size ) {
    _Quicksort_r( array, 0, size - 1 );
}