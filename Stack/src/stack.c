#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct _stringStackNode_t {
	char *                       data;
	struct _stringStackNode_t *  pNext;
} stringStackNode_t;

typedef struct _stringStack_t {
	stringStackNode_t *  pFirst;
	stringStackNode_t *  pLast;
} stringStack_t;

void PopFromStringStack( stringStack_t *pStack ) {
/*
====================
PopFromStringStack
 Pops an element
 from the string
 stack.
====================
*/
	
	stringStackNode_t *  tracer = pStack->pFirst;
	
	if ( pStack->pFirst != NULL ) { // Will not run if the stack is already empty.
		if ( ( pStack->pFirst )->pNext == NULL ) { // Empties the stack if there is only 1 element.
			free( pStack->pFirst );
			pStack->pFirst = NULL;
			pStack->pLast = NULL;
		} else {
			while ( tracer->pNext != pStack->pLast ) { // Finds the element before the last.
				tracer = tracer->pNext;
			}

			pStack->pLast = tracer; // Sets the pLast to the element to be the last (currently the one before last).
			tracer->pNext = NULL;
			
			if ( tracer == pStack->pFirst ) {
				pStack->pFirst = tracer; // Sets the pFirst to the same as the pLast if there is now only one element on the list.
			}
			
			free( tracer->pNext );
		}
	}
}

void ClearStringStack( stringStack_t *pStack ) {
/*
====================
ClearStringStack
 Clears a string
 stack.
====================
*/
	
	while( pStack->pFirst != NULL ) {
		PopFromStringStack( pStack ); // Pops the stack until there are no elements left.
	}
}

void ResetStringStack( stringStack_t **pStack ) {
/*
====================
ResetStringStack
 Resets a string
 stack. If a pointer
 to a NULL pointer
 is passed a new
 stack is created.
====================
*/
	
	if ( *pStack != NULL ) {
		ClearStringStack( *pStack );
	} else {
		*pStack = malloc( sizeof( stringStack_t ) );
		( *pStack )->pFirst = NULL;
		( *pStack )->pLast = NULL;
	}
}

void PushToStringStack( stringStack_t *pStack, char *data ) {
/*
====================
PushToStringStack
 Pushes a string to
 the string stack.
====================
*/
	
	stringStackNode_t *  new = malloc( sizeof( stringStackNode_t ) );

	if ( pStack->pLast != NULL ) {
		( pStack->pLast )->pNext = new; // The new element is set to be the last.
		pStack->pLast = new;
	} else { // If the stack is empty pFirst and pLast are set to the new element.
		pStack->pFirst = new;
		pStack->pLast = new;
	}
	
	new->pNext = NULL; // Terminates the stack.
	if ( ( new->data = malloc( strlen( data ) * sizeof( int ) ) ) ) { // Copies the new data.
		strcpy( new->data, data );
	} else {
		puts( "Out of memory. Likely execution data loss.\n" );
	}
}

bool EmptyStringStack( stringStack_t *pStack ) {
/*
====================
EmptyStringStack
 Checks if a string
 stack is empty.
====================
*/
	
	if ( pStack->pFirst == NULL ) {
		return true;
	} else {
		return false;
	}
}