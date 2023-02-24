#include <stdio.h>

int Staircase_r( int step, int goal );

int main() {
	for ( int i = 1; i <= 10; i++ ) { // Testa o Staircase_r() com uma quantidade de 1 a 10 degraus.
		printf( "%d\n", Staircase_r( 0, i ) );
	}

	return 0;
}

int Staircase_r( int step, int goal ) {
/*
====================
Staircase_r
 Calcula o número de
 formas de subir a
 escada subindo um
 ou 2 degraus por
 vez por força
 bruta.
====================
*/

	int ammount = 0;

	if ( step + 1 > goal ) {
		return 0;
	} else if ( step + 1 == goal ) {
		return 1;
	} else if ( step + 2 == goal ) {
		return 2;
	} else {
		ammount += Staircase_r( step + 1, goal );
		ammount += Staircase_r( step + 2, goal );
	}

	return ammount;
}