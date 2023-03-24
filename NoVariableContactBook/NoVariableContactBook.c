#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PERSON_SIZE ( 10 * sizeof( char ) + sizeof( int ) + sizeof( unsigned long long ) ) // The size of each person on the contact book.
#define PBUFFER_OFFSET sizeof( int ) // First person offset from the count int at the start of pBuffer.
#define NODE_SIZE ( sizeof( void* ) * 3 )

void ClearDatabase( void ** database );
void RebuildDatabase( void ** database, void * pBuffer );

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
						
						if ( !( pBuffer = realloc( pBuffer, ( ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + 10 * sizeof( char ) + sizeof( int ) ) ) ) {
							goto outOfMemory;
						}
						
						break;
					}
					
					REMOVE_ITERATOR++;
				}
				
				( *( int* )pBuffer )--;
				
				getchar();
				
				goto rebuildDatabase;
				
				break;
			
			case '3':
				// Search for record.
				
				getchar();
				break;
			
			case '4':
				void *  tracer = database;
				printf( "%p\n", *( void** )tracer );
				
				while ( tracer ) {  // Frees the database.
					printf( "%s\n", *( char** )( ( char* )tracer + sizeof( void* ) * 2 ) );
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

	rebuildDatabase:
	/*
	#define TRACER ( *( void ** )( ( ( char * )pBuffer + ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET ) )
	#define PREVIOUS ( *( void ** )( ( ( char * )pBuffer + ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + sizeof( void* ) ) )
	#define NEW_NODE ( *( void ** )( ( ( char * )pBuffer + ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + sizeof( void* ) * 2 ) )
	#define REBUILD_ITERATOR ( *( int * )( ( ( char * )pBuffer + ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + sizeof( void* ) * 3 ) )
	*/

	#define NEXT PREVIOUS

	void *  TRACER;
	void *  PREVIOUS;
	void *  NEW_NODE;
	int     REBUILD_ITERATOR;

	if ( !( pBuffer = realloc( pBuffer, ( ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + sizeof( void * ) * 2 ) ) ) {  // Allocs spcace for the tracer and previous variables.
		goto outOfMemory;
	}

	TRACER = database;

	while ( TRACER != NULL ) {  // Frees the database.
		NEXT = *( void** )TRACER;
		free( TRACER );
		TRACER = NEXT;
	}

	database = NULL;

	if ( *( int* )pBuffer >= 1 ) {  // First node
		NEW_NODE = malloc( NODE_SIZE );
		database = NEW_NODE;

		*( void** )( ( char* )NEW_NODE ) = NULL;  // Next
		*( void** )( ( char* )NEW_NODE + sizeof( void* ) ) = NULL;  // Previous
		*( void** )( ( char* )NEW_NODE + sizeof( void* ) * 2 ) = ( void * )( ( char* )pBuffer + PBUFFER_OFFSET );  // Data

		REBUILD_ITERATOR = 1; // REBUILD_ITERATOR is set to 1 as we have the first node already.
	
		while ( REBUILD_ITERATOR < *( int* )pBuffer ) {
			TRACER = database;

			while ( *( void** )TRACER && strcmp( *( char** )TRACER, *( char** )( *( int* )pBuffer + REBUILD_ITERATOR * PERSON_SIZE + PBUFFER_OFFSET ) ) < 1 ) {
				PREVIOUS = TRACER;
				TRACER = *( void** )TRACER;
			}

			NEW_NODE = malloc( NODE_SIZE );

			if ( *( void** )( ( char* )TRACER + sizeof( void * ) ) == NULL ) {  // Sets the database head to the new node if it is the first.
				database = NEW_NODE;
			}
			
			*( void** )TRACER = NEW_NODE;  // Next from the previous node
			*( void** )( ( char* )NEW_NODE + sizeof( void* ) ) = PREVIOUS;  // Previous of the new node
			*( void** )( ( char* )NEW_NODE + sizeof( void* ) * 2 ) = *( char** )TRACER;  // Data of the new node

			REBUILD_ITERATOR++;
		}
	}

	if ( !( pBuffer = realloc( pBuffer, ( ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET ) ) ) {  // Deallocs the variables.
		goto outOfMemory;
	}

	goto menu;

	outOfMemory:
	puts( "Fatal: out of memory." );
	exit( 1 );

	return 0;
}