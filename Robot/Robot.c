#include <stdio.h>
#include <stdbool.h>

bool judgeCircle(char * moves); // Does not conform to code style convention: carbon copy of assignment text.

int main() {
	judgeCircle( "UD" ) ? printf( "UD: true.\n" ) : printf( "UD: false.\n" ); // Tests.
	judgeCircle( "LL" ) ? printf( "LL: true.\n" ) : printf( "LL: false.\n" );

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