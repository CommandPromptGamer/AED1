#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PERSON_SIZE ( 10 * sizeof( char ) + sizeof( int ) + sizeof( unsigned long long ) ) // The size of each person on the contact book.
#define PBUFFER_OFFSET sizeof( int ) // First person offset from the count int at the start of pBuffer.
#define NODE_SIZE ( sizeof( void* ) * 3 )

int main() {
	void *  pBuffer = malloc( sizeof( int ) );
	void *  database = NULL;

	*( int* )pBuffer = 0;

	while (1) {
		menu:
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

				( *( int* )pBuffer )++;
				
				goto rebuildDatabase;
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
						
						break;
					}
					
					REMOVE_ITERATOR++;
				}
				
				( *( int* )pBuffer )--;
				
				getchar();
				
				goto rebuildDatabase;
				break;
			
			case '3':
				#define SEARCH_ITERATOR ( *( int* )( ( ( char * )pBuffer + ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + 10 * sizeof( char ) ) )

				SEARCH_ITERATOR = 0;

				getchar();
				printf( "Entre o nome do registro que deseja buscar: " );
				scanf( "%[^\n]s", ( char* )pBuffer + ( ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET );

				while ( SEARCH_ITERATOR < *( int* )pBuffer ) {
					if ( !strcmp( ( char * )pBuffer + ( ( ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET ), ( char* )pBuffer + SEARCH_ITERATOR * PERSON_SIZE + PBUFFER_OFFSET ) ) {
						printf( "Nome: %s\nIdade: %d\nTelefone: %lld\n", ( char* )pBuffer + SEARCH_ITERATOR * PERSON_SIZE + PBUFFER_OFFSET, *( int* )( ( char* )( ( char* )pBuffer + SEARCH_ITERATOR * PERSON_SIZE + PBUFFER_OFFSET ) + 10 * sizeof( char ) ), *( unsigned long long* )( ( char* )( ( char* )pBuffer + SEARCH_ITERATOR * PERSON_SIZE + PBUFFER_OFFSET ) + 10 * sizeof( char ) + sizeof( int ) ) );
						
						break;
					}

					SEARCH_ITERATOR++;
				}

				getchar();

				goto rebuildDatabase;
				break;
			
			case '4':
				#define LIST_TRACER ( *( void ** )( ( ( char * )pBuffer + ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET ) )  // No space needs to be allocated as we already have 3 pointers ans an int allocated from the rebuildDatabase.
				//void *  LIST_TRACER;  // Debug variable

				LIST_TRACER = database;

				while( LIST_TRACER != NULL ) {
					printf( "Nome: %s\nIdade: %d\nTelefone: %lld\n", *( char** )( ( char* )LIST_TRACER + sizeof( void* ) * 2 ), *( int* )( *( char** )( ( char* )LIST_TRACER + sizeof( void* ) * 2 ) + 10 * sizeof( char ) ), *( unsigned long long* )( *( char** )( ( char* )LIST_TRACER + sizeof( void* ) * 2 ) + 10 * sizeof( char ) + sizeof( int ) ) );
				
					LIST_TRACER = *( void** )LIST_TRACER;
				}

				getchar();
				break;
			
			case '5':
				exit( 0 ); // Exit the program.
				break;
			
			default:
				printf( "Opção inválida.\n" );
				getchar();
				break;
		}
	}

	rebuildDatabase:
	#define TRACER ( *( void ** )( ( ( char * )pBuffer + ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET ) )
	#define PREVIOUS ( *( void ** )( ( ( char * )pBuffer + ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + sizeof( void* ) ) )
	#define NEW_NODE ( *( void ** )( ( ( char * )pBuffer + ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + sizeof( void* ) * 2 ) )
	#define REBUILD_ITERATOR ( *( int * )( ( ( char * )pBuffer + ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + sizeof( void* ) * 3 ) )

	#define NEXT PREVIOUS  // The PREVIOUS is called NEXT for readability when it is used to indicate the next node.

	/*void *  TRACER;  // Debug variables
	void *  PREVIOUS;
	void *  NEW_NODE;
	int     REBUILD_ITERATOR;*/

	if ( !( pBuffer = realloc( pBuffer, ( ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + sizeof( void * ) * 3 + sizeof( int ) ) ) ) {  // Allocs spcace for the tracer and previous variables.
		goto outOfMemory;
	}

	TRACER = database;

	while ( TRACER != NULL ) {  // Frees the database.
		NEXT = *( void** )TRACER;
		free( TRACER );
		TRACER = NEXT;
	}

	if ( *( int* )pBuffer >= 1 ) {
		TRACER = malloc( NODE_SIZE );
		database = TRACER;

		*( void** )TRACER = NULL;  // Next
		*( void** )( ( char* )TRACER + sizeof( void* ) ) = NULL; // Previous
		*( void** )( ( char* )TRACER + sizeof( void* ) * 2 ) = ( void* )( ( char* )pBuffer + PBUFFER_OFFSET );  // Data

		REBUILD_ITERATOR = 1;  // The iterator starts at 1 because we already have the first node.

		while ( REBUILD_ITERATOR < *( int* )pBuffer ) {
			TRACER = database;
			
			while ( *( void** )TRACER && strcmp( *( char** )( ( char* )TRACER + sizeof( void* ) * 2 ), ( char* )pBuffer + REBUILD_ITERATOR * PERSON_SIZE + PBUFFER_OFFSET ) < 0 ) {
				PREVIOUS = TRACER;
				TRACER = *( void** )TRACER;
			}

			NEW_NODE = malloc( NODE_SIZE );
			//printf( "New node: %p\n", NEW_NODE );

			*( void** )NEW_NODE = *( void** )TRACER;  // Next of the new node
			//printf( "Next: %p\n", *( void** )TRACER );
			*( void** )( ( char* )NEW_NODE + sizeof( void* ) ) = PREVIOUS; // Previous of the new node
			//printf( "Previous: %p\n", PREVIOUS );
			*( void** )( ( char* )NEW_NODE + sizeof( void* ) * 2 ) = ( void* )( ( char* )pBuffer + REBUILD_ITERATOR * PERSON_SIZE + PBUFFER_OFFSET );  // Data of the new node
			//printf( "Data: %p\n", ( void* )( ( char* )pBuffer + REBUILD_ITERATOR * PERSON_SIZE + PBUFFER_OFFSET ) );
			*( void** )TRACER = NEW_NODE;  // Next of the previous node

			if ( *( void** )NEW_NODE != NULL ) {  // Previous of the next node
				*( void** )( ( char* )( *( void** )NEW_NODE ) + sizeof( void* ) ) = NEW_NODE;
			}

			if ( *( void** )( *( char** )TRACER + sizeof( void* ) ) == NULL ) {  // The database is updated if the new node is added to the beginning.
				database = TRACER;
			}

			REBUILD_ITERATOR++;
		}
	}

	goto menu;

	outOfMemory:
	puts( "Fatal: out of memory.\n" );
	exit( 1 );

	return 0;
}