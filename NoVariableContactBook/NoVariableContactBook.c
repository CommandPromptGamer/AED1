#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PERSON_SIZE ( 10 * sizeof( char ) + sizeof( int ) + sizeof( unsigned long long ) ) // The size of each person on the contact book.
#define PBUFFER_OFFSET sizeof( int ) // First person offset from the count int at the start of pBuffer.
#define NODE_SIZE ( sizeof( void* ) * 3 )

void ClearDatabase( void ** database );
void RebuidDatabase( void ** database, void * pBuffer );

int main() {
	void *  pBuffer = malloc( sizeof( int ) );
	void *  database = NULL;

	*( int* )pBuffer = 0;

	while (1) {
		printf("Escolha uma opção: \n1 - Incluir registro\n2 - Apagar registro por nome\n3 - Buscar por um registro\n4 - Listar o arquivo\n5 - Sair\nEntre a sua opção: ");
		
		switch ( getchar() ) {
			case '1':
				if ( !( pBuffer = realloc( pBuffer, ( ( *( int* )pBuffer + 1 ) * PERSON_SIZE ) + PBUFFER_OFFSET ) ) ) {
					goto outOfMemory;
				}
				
				getchar();
				printf( "Entre o nome: " );  // Name
				scanf( "%[^\n]s", ( char* )pBuffer + ( PBUFFER_OFFSET + ( PERSON_SIZE * ( *( int* )pBuffer ) ) ) );

				printf( "Entre a idade: " ); // Age
				scanf( "%d", ( int * )( ( char* )pBuffer + ( PBUFFER_OFFSET + ( PERSON_SIZE * ( *( int* )pBuffer ) ) + 10 * sizeof( char ) ) ) );

				printf("Entre o telefone: "); // Phone number
				scanf( "%lld", ( unsigned long long * )( ( char* )pBuffer + ( PBUFFER_OFFSET + ( PERSON_SIZE * ( *( int* )pBuffer ) ) + 10 * sizeof( char ) + sizeof( int ) ) ) );
				getchar();

				//RebuidDatabase( &database, pBuffer );

				( *( int* )pBuffer )++;
				
				break;
			
			case '2':
				#define REMOVE_ITERATOR ( *( int* )( ( ( char * )pBuffer + ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + 10 * sizeof( char ) ) )
				
				if ( !( pBuffer = realloc( pBuffer, ( ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + 10 * sizeof( char ) + sizeof( int ) ) ) ) {
					goto outOfMemory;
				}

				REMOVE_ITERATOR = 0;
				
				getchar();
				printf( "Entre o nome do registro que deseja remover: " );
				scanf( "%[^\n]s", ( char* )pBuffer + ( ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET );

				while ( REMOVE_ITERATOR < *( int* )pBuffer ) {
					if ( !strcmp( ( char * )pBuffer + ( ( ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET ), ( char* )pBuffer + REMOVE_ITERATOR * PERSON_SIZE + PBUFFER_OFFSET ) ) {
						memmove( ( char* )pBuffer + REMOVE_ITERATOR * PERSON_SIZE + PBUFFER_OFFSET, ( char* )pBuffer + REMOVE_ITERATOR * PERSON_SIZE + PBUFFER_OFFSET + PERSON_SIZE, *( int* )pBuffer * PERSON_SIZE - REMOVE_ITERATOR * PERSON_SIZE - PERSON_SIZE );
						
						if ( !( pBuffer = realloc( pBuffer, ( ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + 10 * sizeof( char ) + sizeof( int ) ) ) ) {
							goto outOfMemory;
						}
						
						break;
					}
					
					REMOVE_ITERATOR++;
				}
				
				( *( int* )pBuffer )--;

				//RebuidDatabase( &database, pBuffer );
				
				getchar();
				break;
			
			case '3':
				// Search for record.
				
				getchar();
				break;
			
			case '4':
				void *  tracer = *( void** )database;

				while ( tracer ) {
					puts( ( char* )tracer );
					
					tracer = *( void** )tracer;
				}
				
				getchar();
				break;
			
			case '5':
				exit( 0 ); // Exit the program.
				break;
			
			default:
				printf( "Opção inválida." );
				break;
		}
	}

	outOfMemory:
	puts( "Fatal: out of memory." );
	exit( 1 );

	return 0;
}

void ClearDatabase( void ** database ) {
/*
====================
ClearDatabase
 Clears the
 database.
====================
*/
	
	void **  tracer = database;
	void *   old;

	old = *tracer;
	free( old );

	while ( *tracer ) {
		old = *tracer;
		tracer = *tracer;
		free( old );
	}

	*database = NULL;
}

void RebuidDatabase( void ** database, void * pBuffer ) {  // BROKEN
/*
====================
RebuldDatabase
 Rebuilds the
 database from
 pBuffer.
====================
*/

	#define CURRENT_STRING ( ( char* )pBuffer + *iterator * PERSON_SIZE + PBUFFER_OFFSET )

	int *    iterator = malloc( sizeof( int ) );
	void **  tracer;
	void *   previous;
	void *   newNode;

	*database = NULL;
	tracer = database;

	*iterator = 0;

	while( *iterator < *( int* )pBuffer ) {
		newNode = malloc( NODE_SIZE );

		while ( tracer && strcmp( ( char* )tracer, CURRENT_STRING ) > 1 ) {
			previous = *tracer;
			*tracer = **( void*** )tracer;
		}

		*tracer = newNode;  // Next.

		if ( *iterator == 0 ) {  // Previous.
			*( void** )( ( char* )tracer + sizeof( void * ) ) = NULL;
		} else {
			*( void** )( ( char* )tracer + sizeof( void * ) ) = previous;
		}

		*( void** )( ( char* )tracer + sizeof( void * ) * 2 ) = CURRENT_STRING;  // Datum.
	
		( *iterator )++;
	}

	free( iterator );
}