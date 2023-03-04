#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#define USE_TERMINAL_COLORS
#define PRINT_TO_TERMINAL
#define TEST_COUNT 100
#define STRING_LENGHT 20

#ifdef USE_TERMINAL_COLORS
	#define TRUE_PRINT "\033[92m%s: true.\n\033[0m"
	#define FALSE_PRINT "\033[91m%s: false.\n\033[0m"
#else
	#define TRUE_PRINT "%s: true.\n"
	#define FALSE_PRINT "%s: false.\n"
#endif

bool judgeCircle(char * moves); // Does not conform to code style convention: carbon copy of assignment text.
char *GetRandomMovesString( int lenght );

int main() {
	char *  movesString;
	
	srand( time( NULL ) );

	for ( int i = 0; i < TEST_COUNT; i++ ) {
		movesString = GetRandomMovesString( STRING_LENGHT );
		
		#ifdef PRINT_TO_TERMINAL
			judgeCircle( movesString ) ? printf( TRUE_PRINT, movesString ) : printf( FALSE_PRINT, movesString );
		#else
			judgeCircle( movesString );
		#endif

		free( movesString );
	}

	return 0;
}

bool judgeCircle(char * moves) {
	int     xPos = 0;
	int     yPos = 0;
	char *  move = moves;

	while ( *move != '\0' ) {
		switch ( *move ) {
			case 'R':
				xPos++;
				break;
			case 'L':
				xPos--;
				break;
			case 'U':
				yPos++;
				break;
			case 'D':
				yPos--;
				break;
			
			default:
				return false; // Invalid sequence returns false.
				break;
		}

		move++;
	}

	if ( xPos != 0 || yPos != 0 ) {
		return false;
	} else {
		return true;
	}
}

char *GetRandomMovesString( int lenght ) {
	char *  movesString;
	
	if ( !( movesString = malloc( ( lenght + 1 ) * sizeof( char ) ) ) ) {
		printf( "Out of memory.\n" );
		exit( 1 );
	}

	for ( int i = 0; i < lenght; i++ ) {
		switch ( rand() % 4 ) {
		case 0:
			movesString[ i ] = 'R';
			break;
		case 1:
			movesString[ i ] = 'L';
			break;
		case 2:
			movesString[ i ] = 'U';
			break;
		case 3:
			movesString[ i ] = 'D';
			break;
		}
	}

	movesString[ lenght ] = '\0';

	return movesString;
}