#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	const int num = 4224;
	char dec[ 11 ];

	itoa( num, dec, 10 );

	for ( int i = 0; i < strlen( dec ) / 2; i++ ) {
		if ( dec[ i ] != dec[ strlen( dec ) - i - 1 ] ){
			printf( "False\n" );

			return 0;
		}
	}

	printf( "True\n" );

	return 0;
}