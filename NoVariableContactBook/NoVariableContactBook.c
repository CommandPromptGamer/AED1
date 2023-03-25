#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

static_assert( CHAR_BIT == 8, "A char is not a byte (or a byte is not 8 bits)." );

#define PERSON_SIZE ( 10 * sizeof( char ) + sizeof( int ) + sizeof( unsigned long long ) ) // The size of each person on the contact book.
#define PBUFFER_OFFSET sizeof( int ) // The offset of the first person from the start of pBuffer, comes from the amount of records int at the beginning.
#define NODE_SIZE ( sizeof( void* ) * 3 )  // The size of a node. The first void* pointer is the next node, the second is the previous node and the third is the data.

int main() {
	void *  pBuffer = malloc( sizeof( int ) );  // The pBuffer is initially allocated to contain the int containing the amount of records.
	void *  database = NULL;

	*( int* )pBuffer = 0;  // The amount of records is initialized at 0.

	while (1) {
		menu:
		printf("Escolha uma opção: \n1 - Incluir registro\n2 - Apagar registro por nome\n3 - Buscar por um registro\n4 - Listar o arquivo\n5 - Sair\nEntre a sua opção: ");
		
		switch ( getchar() ) {
			case '1':
				if ( !( pBuffer = realloc( pBuffer, ( ( *( int* )pBuffer + 1 ) * PERSON_SIZE ) + PBUFFER_OFFSET ) ) ) {  // Allocates space for the new record.
					goto OutOfMemory;
				}
				
				getchar();
				printf( "Entre o nome: " );  // Name
				scanf( "%[^\n]s", ( char* )pBuffer + ( PBUFFER_OFFSET + ( PERSON_SIZE * ( *( int* )pBuffer ) ) ) );

				printf( "Entre a idade: " ); // Age
				scanf( "%d", ( int * )( ( char* )pBuffer + ( PBUFFER_OFFSET + ( PERSON_SIZE * ( *( int* )pBuffer ) ) + 10 * sizeof( char ) ) ) );

				printf("Entre o telefone: "); // Phone number
				scanf( "%llu", ( unsigned long long * )( ( char* )pBuffer + ( PBUFFER_OFFSET + ( PERSON_SIZE * ( *( int* )pBuffer ) ) + 10 * sizeof( char ) + sizeof( int ) ) ) );
				getchar();

				( *( int* )pBuffer )++;  // Increments the amount of records.

				putchar( '\n' );  // Spacing before the menu.
				
				goto RebuildDatabase;
				break;
			
			case '2':
				#define REMOVE_ITERATOR ( *( int* )( ( ( char * )pBuffer + ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + 10 * sizeof( char ) ) )
				#define REMOVED ( *( char* )( ( ( char * )pBuffer + ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + 10 * sizeof( char ) + sizeof( int ) ) )
				
				if ( !( pBuffer = realloc( pBuffer, ( ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + 10 * sizeof( char ) + sizeof( int ) + sizeof( char ) ) ) ) {  // Allocates space for the input string, the iterator and the removed "bool" char.
					goto OutOfMemory;
				}

				REMOVE_ITERATOR = 0;
				REMOVED = 0;
				
				getchar();
				printf( "Entre o nome do registro que deseja remover: " );
				scanf( "%[^\n]s", ( char* )pBuffer + ( ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET );

				while ( REMOVE_ITERATOR < *( int* )pBuffer ) {
					// The input string and the string being iterated are compared and when they match all the records after it are moved to its location, overriding it.					
					if ( !strcmp( ( char * )pBuffer + ( ( ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET ), ( char* )pBuffer + REMOVE_ITERATOR * PERSON_SIZE + PBUFFER_OFFSET ) ) {
						memmove( ( char* )pBuffer + REMOVE_ITERATOR * PERSON_SIZE + PBUFFER_OFFSET, ( char* )pBuffer + REMOVE_ITERATOR * PERSON_SIZE + PBUFFER_OFFSET + PERSON_SIZE, *( int* )pBuffer * PERSON_SIZE - REMOVE_ITERATOR * PERSON_SIZE - PERSON_SIZE );
						( *( int* )pBuffer )--;  // Decrements the amount of records.
						
						puts( "Registro removido.\n" );
						REMOVED = 1;
						break;
					}
					
					REMOVE_ITERATOR++;
				}

				if ( !REMOVED ) {
					puts( "Registro não encontrado.\n" );
				}
				
				getchar();
				
				goto RebuildDatabase;
				break;
			
			case '3':
				#define SEARCH_ITERATOR ( *( int* )( ( ( char * )pBuffer + ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + 10 * sizeof( char ) ) )
				#define PRINTED ( *( char* )( ( ( char * )pBuffer + ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + 10 * sizeof( char ) + sizeof( char ) ) )

				if ( !( pBuffer = realloc( pBuffer, ( ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + 10 * sizeof( char ) + sizeof( int ) + sizeof( char ) ) ) ) {  // Allocates space for the input string, the iterator and the printed "bool" char.
					goto OutOfMemory;
				}
				
				SEARCH_ITERATOR = 0;
				PRINTED = 0;

				getchar();
				printf( "Entre o nome do registro que deseja buscar: " );
				scanf( "%[^\n]s", ( char* )pBuffer + ( ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET );

				while ( SEARCH_ITERATOR < *( int* )pBuffer ) {
					// The input string and the string being iterated are compared and when they match the details of that record are printed.
					if ( !strcmp( ( char * )pBuffer + ( ( ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET ), ( char* )pBuffer + SEARCH_ITERATOR * PERSON_SIZE + PBUFFER_OFFSET ) ) {
						printf( "=====================\nNome: %s\nIdade: %d\nTelefone: %llu\n=====================\n\n", ( char* )pBuffer + SEARCH_ITERATOR * PERSON_SIZE + PBUFFER_OFFSET, *( int* )( ( char* )( ( char* )pBuffer + SEARCH_ITERATOR * PERSON_SIZE + PBUFFER_OFFSET ) + 10 * sizeof( char ) ), *( unsigned long long* )( ( char* )( ( char* )pBuffer + SEARCH_ITERATOR * PERSON_SIZE + PBUFFER_OFFSET ) + 10 * sizeof( char ) + sizeof( int ) ) );
						PRINTED = 1;

						break;
					}

					SEARCH_ITERATOR++;
				}

				if ( !PRINTED ) {
					puts( "Registro não encontrado.\n" );
				}

				getchar();

				goto RebuildDatabase;
				break;
			
			case '4':
				#define LIST_TRACER ( *( void ** )( ( ( char * )pBuffer + ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET ) )  // No space needs to be allocated as we already have 3 pointers and an int allocated from the RebuildDatabase and we only need 1.
				//void *  LIST_TRACER;  // Debug variable

				LIST_TRACER = database;

				while( LIST_TRACER != NULL ) {
					printf( "=====================\nNome: %s\nIdade: %d\nTelefone: %llu\n", *( char** )( ( char* )LIST_TRACER + sizeof( void* ) * 2 ), *( int* )( *( char** )( ( char* )LIST_TRACER + sizeof( void* ) * 2 ) + 10 * sizeof( char ) ), *( unsigned long long* )( *( char** )( ( char* )LIST_TRACER + sizeof( void* ) * 2 ) + 10 * sizeof( char ) + sizeof( int ) ) );
				
					LIST_TRACER = *( void** )LIST_TRACER;
				}

				if ( *(int* )pBuffer >= 1 ) {
					puts( "=====================" );
				}

				if ( *( int* )pBuffer == 0 ) {
					puts( "Não há nenhum registro para listar." );  // A newline is not put as it will be added in the putchar regardless of wether this string was put or not.
				}

				putchar( '\n' );  // Spacing before the menu.

				getchar();
				break;
			
			case '5':
				exit( 0 ); // Exit the program.
				break;

			case '\n':
				puts( "Entre uma opção. Use 5 para sair.\n" );
				break;
			
			default:
				puts( "Opção inválida.\n" );
				getchar();
				break;
		}
	}

	RebuildDatabase:
	#define TRACER ( *( void ** )( ( ( char * )pBuffer + ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET ) )
	#define PREVIOUS ( *( void ** )( ( ( char * )pBuffer + ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + sizeof( void* ) ) )
	#define NEW_NODE ( *( void ** )( ( ( char * )pBuffer + ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + sizeof( void* ) * 2 ) )
	#define REBUILD_ITERATOR ( *( int * )( ( ( char * )pBuffer + ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + sizeof( void* ) * 3 ) )

	#define NEXT PREVIOUS  // The PREVIOUS is called NEXT for readability when it is used to indicate the next node.

	if ( !( pBuffer = realloc( pBuffer, ( ( *( int* )pBuffer ) * PERSON_SIZE ) + PBUFFER_OFFSET + sizeof( void * ) * 3 + sizeof( int ) ) ) ) {  // Allocs space for the tracer and previous variables.
		goto OutOfMemory;
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
			TRACER = &database;
			PREVIOUS = NULL;

			printf( "Adding %s\n", ( char* )pBuffer + REBUILD_ITERATOR * PERSON_SIZE + PBUFFER_OFFSET );
			
			while( *( void** )TRACER != NULL && strcmp( *( char** )( ( char* )TRACER + sizeof( void* ) * 2 ), ( char* )pBuffer + REBUILD_ITERATOR * PERSON_SIZE + PBUFFER_OFFSET ) < 0 ) {
				PREVIOUS = TRACER;
				TRACER = *( void** )TRACER;
			}
			
			// Hacky workaround to the fact the tracer is going one more position than it should for some reason ¯\_(ツ)_/¯.
			if ( *( void** )TRACER != NULL ) {  // Only do the hack if the node is not the first being added, there is no need (or way) to set the tracer to a node before the only node.
				if ( PREVIOUS == NULL ) {  // If the node will be added to the beginning
					TRACER = database;  // Set the tracer to the beginning
					PREVIOUS = NULL;  // Set the previous to NULL, as there is no previous
				} else {  // If the node is not the first
					TRACER = PREVIOUS;  // Make the tracer go back one position
					PREVIOUS = *( void** )( ( char* )PREVIOUS + sizeof( void* ) );  // Set the previous to be the previous of the previous node
				}
			}

			NEW_NODE = malloc( NODE_SIZE );

			*( void** )NEW_NODE = *( void** )TRACER;  // Next of the new node
			
			*( void** )TRACER = NEW_NODE;  // Next of the previous node
			
			*( void** )( ( char* )NEW_NODE + sizeof( void* ) ) = PREVIOUS; // Previous of the new node
			
			*( void** )( ( char* )NEW_NODE + sizeof( void* ) * 2 ) = ( void* )( ( char* )pBuffer + REBUILD_ITERATOR * PERSON_SIZE + PBUFFER_OFFSET );  // Data of the new node

			if ( *( void** )NEW_NODE != NULL ) {  // Previous of the next node
				*( void** )( ( char* )( *( void** )NEW_NODE ) + sizeof( void* ) ) = NEW_NODE;
			}

			if ( *( void** )( *( char** )TRACER + sizeof( void* ) ) == NULL ) {  // The database is updated if the new node is added to the beginning.
				database = TRACER;
			}

			REBUILD_ITERATOR++;
		}
	} else {
		database = NULL;
	}

	goto menu;

	OutOfMemory:
	puts( "Fatal: out of memory.\n" );
	exit( 1 );

	return 0;
}