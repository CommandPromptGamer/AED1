#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Add( char *theString, char *newString, int *size, int *count );
char *Get( char *theString, int index );
void Remove( char *theString, int index, int *Size, int *count );
void List(char *theString, int count);

int main (){
	char *theString = malloc( sizeof( char ) );
	int size = 1;
	int count = 1;
	int option;
	char stringToAdd[50];
	int stringToRemove;

	theString[0] = '\0';

	do {
		printf( "– 1) Adicionar nome\n– 2) Remover nome\n– 3) Listar\n– 4) Sair\nEntre a opção: " );
		scanf("%d", &option);
		getchar();

		switch (option) {
		case 1:
			printf( "Entre o nome para adicionar: " );
			scanf("%[^\n]s", stringToAdd);
			Add( theString, stringToAdd, &size, &count );
			break;
		
		case 2:
			printf( "Entre o índice do nome para remover: " );
			scanf("%d", &stringToRemove);
			Remove( theString, stringToRemove, &size, &count );
			break;

		case 3:
			List(theString, count);
			break;
		}
	} while ( option >= 1 && option < 4 );

	return 0;
}

void Add( char *theString, char *new, int *size, int *count ){
/*
====================
Add
 Adiciona uma string
 a string que contém
 as strings.
====================
*/

	int newStringSize = strlen( new );
	theString = realloc( theString, (*size + newStringSize + 1) * sizeof ( char ) );

	memcpy( &theString[ *size ], new, (newStringSize + 1) *  sizeof ( char ) );

	*size += newStringSize + 1;
	(*count)++;
}

char *Get( char *theString, int index ) {
/*
====================
Get
 Encontra o ponteiro
 que aponta para a
 string de
 determinado índice.
====================
*/
	
	int currentIndex = 0;
	int i = 0;

	do {
		if ( theString[i] == '\0' ) {
			currentIndex++;
		}
		
		i++;
	} while ( currentIndex < index + 1 );

	return &theString[ i ];
}

void Remove( char *theString, int index, int *size, int *count ) {
/*
====================
Remove
 Remove uma string
 da string que
 contém as strings.
====================
*/

	char *stringToRemove = Get( theString, index );
	int stringToRemoveSize = strlen( stringToRemove );

	memmove( stringToRemove, stringToRemove + stringToRemoveSize + 1, ( ( &theString[ *size ] - stringToRemove ) - stringToRemoveSize ) * sizeof( char ) );

	theString = realloc( theString, *size - ( stringToRemoveSize + 1 ) );
	*size -= ( stringToRemoveSize + 1 );
	(*count)--;
}

void List(char *theString, int count) {
/*
====================
List
 Imprime todas as
 strings.
====================
*/
	
	char *currentString = theString;

	for ( int i = 0; i < count; i++ ) {
		if ( i ) {
			printf( "%s\n", currentString );
		}

		currentString += strlen( currentString ) + 1;
	}
}