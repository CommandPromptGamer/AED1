#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PERSON_SIZE ( sizeof( char ) * 10 + sizeof( int ) + sizeof( unsigned long long ) )

void Add( void *pBuffer, int *count, char *name, int age, unsigned long long telephone );
void RemoveByIndex( void *pBuffer, int *count, int index );
void RemoveByPointer( void *pBuffer, int *count, void *position );
void* FindByName( void *pBuffer, int *count, char *name );
void* GetPointerFromIndex( void *pBuffer, int index );
void PrintPerson( void *person );
void List( void *pBuffer, int count );

int main() {
	void *              pBuffer = malloc(1);
	int                 count = 0;
	int                 option;
	char                name[10];
	int 			    age;
	int                 index;
	unsigned long long  telephone;
	void *              record;

	do {
	printf("Escolha uma opção: \n1 - Incluir registro\n2 - Apagar registro por índice\n3 - Apagar registro por nome\n4 - Buscar por um registro\n5 - Listar o arquivo\n6 - Sair\nEntre a sua opção: ");
	scanf("%d", &option);
	getchar();

	switch ( option ) {
	case 1:
		printf( "Entre o nome: " );
		scanf("%[^\n]s", name);
		printf( "Entre a idade: " );
		scanf("%d", &age);
		printf("Entre o telefone: ");
		scanf("%lld", &telephone);

		Add( pBuffer, &count, name, age, telephone );
		
		break;

	case 2:
		printf( "Entre o índice do registro que deseja apagar: " );
		scanf("%d", &index);

		RemoveByIndex( pBuffer, &count, index );

		break;

	case 3:
		printf( "Entre o nome do registro que deseja remover: " );
		scanf( "%[^\n]s", name );

		RemoveByPointer( pBuffer, &count, FindByName( pBuffer, &count, name ) );

		break;

	case 4:
		printf("Entre o nome que deseja encontrar: ");
		scanf( "%[^\n]s", name );

		record = FindByName( pBuffer, &count, name );
		
		printf("Registro: %d\n", ( int )( ( ( char* )record - ( char* )pBuffer ) / PERSON_SIZE ) );
		PrintPerson( record );
		putchar('\n');

		break;

	case 5:
		List( pBuffer, count );
		break;
	}

	} while ( option != 6 );

	return 0;
}

void Add( void *pBuffer, int *count, char *name, int age, unsigned long long telephone ) {
/*
====================
Add
 Adiciona um
 registro ao
 arquivo.
====================
*/
	
	pBuffer = realloc( pBuffer, ( *count + 1 ) * PERSON_SIZE );
	void *position = ( char* )pBuffer + ( *count ) * PERSON_SIZE;

	strcpy( position, name );
	position = ( char* )position + 10 * sizeof( char );
	*( int* )position = age;
	position = ( char* )position + sizeof( int );
	*( unsigned long long* )position = telephone;

	( *count )++;
}

void RemoveByIndex( void *pBuffer, int *count, int index ) {
/*
====================
RemoveByIndex
 Remove um registro
 indicado pelo
 índice.
====================
*/
	
	void *position = GetPointerFromIndex( pBuffer, index );
	RemoveByPointer( pBuffer, count, position );
}

void RemoveByPointer( void *pBuffer, int *count, void *position ) {
/*
====================
RemoveByPointer
 RemoveUmRegistro
 indicado por um
 ponteiro.
====================
*/
	
	memmove( position, ( char* )position + PERSON_SIZE, ( ( char* )pBuffer + ( PERSON_SIZE * ( *count ) ) - ( char* )position ) - PERSON_SIZE );
	pBuffer = realloc( pBuffer, PERSON_SIZE * ( *count ) - 1 );

	( *count )--;
}

void* FindByName( void *pBuffer, int *count, char *name ) {
	/*
====================
FindByName
 Encontra um
 registro pelo nome.
====================
*/
	
	void *position;
	
	for ( int i = 0; i < ( *count ); i++ ) {
		position = GetPointerFromIndex( pBuffer, i );
		
		if ( !strcmp( position, name ) ) {
			return position;
		}
	}

	return NULL;
}

void* GetPointerFromIndex( void *pBuffer, int index ) {
/*
====================
GetPointerFromIndex
 Retorna o ponteiro
 de determindo
 registro indicado
 por um índice.
====================
*/
	
	return ( void * )( ( char* )pBuffer + ( index ) * PERSON_SIZE );
}

void PrintPerson( void *person ) {
/*
====================
PrintPerson
 Imprime os dados de
 um registro
 indicado por um
 ponteiro.
====================
*/
	
	printf( "Nome: %s\nIdade: %d\nTelefone: %lld\n", ( char* )person, *( int* )( ( char* )person + 10 ),  *( unsigned long long* )( ( char* )person + 10 + sizeof ( int ) ) );
}

void List( void *pBuffer, int count ) {
/*
====================
List
 Imprime os dados de
 todos os registros.
====================
*/
	
	for ( int i = 0; i < count; i++ ) {
		PrintPerson( ( char* )pBuffer + PERSON_SIZE * i );
		putchar('\n');
	}
}