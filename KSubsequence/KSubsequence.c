#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int *Solve( int* nums, int k, int size );

int main() {
    int    nums[] = {2, 1, 3, 3}; // Test 1
    //int    nums[] = {-1, -2, 3, 4}; // Test 2
    //int    nums[] = {3, 4, 3, 3}; // Test 3
    int    size = 4; // Always 4 for these 3 test cases.
    int    k = 2; // Test 1
    //int    k = 3; // Test 2
    //int    k = 2; // Test 3
    int *  result;

    result = Solve( nums, k, size );
    
    // Prints the result.
    printf( "{" );
    for ( int i = 0; i < k - 1; i++ ) {
        printf( "%d, ", result[ i ] );
    }
    printf("%d}\n", result[ k - 1 ]);
    
    free( result ); // Frees the result allocated in Solve().

    return 0;
}

bool InArray( int *array, int size, int n ) {
    for ( int i = 0; i < size; i++ ) {
        if ( n == array[ i ] ) {
            return true;
        }
    }

    return false;
}

int *Solve( int* nums, int k, int size ) {
    int  *result = malloc( k * sizeof( int ) );
    int  aux;

    for ( int i = 0; i < k; i++ ) {
        result[ i ] = 0;
    }
    
    for ( int i = 0; i < k; i++ ) {
        for ( int j = 0; j < size; j++ ) {
            if ( nums[ j ] > nums[ result[ i ] ] && !InArray( result, k, j ) ) {
                result[ i ] = j;
            }
        }
    }

    for ( int i = 0; i < k / 2; i++ ) {
        aux = result[ i ];
        result[ i ] = result[ k - 1 ];
        result[ k - 1 ] = aux;
    }

    for ( int i = 0; i < k; i++ ) {
        result[ i ] = nums[ result [ i ] ];
    }

    return result;
}