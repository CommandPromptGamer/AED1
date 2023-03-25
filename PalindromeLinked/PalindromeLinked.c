#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

void Push( struct ListNode **head, int number );
void Clear( struct ListNode **head );
bool isPalindrome(struct ListNode* head);

int main() {
	struct ListNode *  list = NULL;

	Push( &list, 5 );
	Push( &list, 4 );
	Push( &list, 3 );
	Push( &list, 2 );
	Push( &list, 3 );
	Push( &list, 4 );
	Push( &list, 5 );

	isPalindrome( list ) ? printf( "5432345 is palindrome\n" ) : printf( "5432345 is not palindrome\n" ) ;

	Clear( &list );

	Push( &list, 1 );
	Push( &list, 2 );
	Push( &list, 3 );
	Push( &list, 4 );
	Push( &list, 5 );

	isPalindrome( list ) ? printf( "12345 is palindrome\n" ) : printf( "12345 is not palindrome\n" ) ;

	Clear( &list );

	Push( &list, 1 );
	Push( &list, 2 );
	Push( &list, 3 );
	Push( &list, 3 );
	Push( &list, 2 );
	Push( &list, 1 );

	isPalindrome( list ) ? printf( "123321 is palindrome\n" ) : printf( "123321 is not palindrome\n" ) ;

	Clear( &list );

	return 0;
}

void Push( struct ListNode **head, int number ) {
	struct ListNode *   newElement = malloc( sizeof( struct ListNode ) );
	struct ListNode **  tracer = head;
	
	newElement -> val = number;
	newElement -> next = NULL;

	while ( *tracer != NULL ) {
		tracer = &( ( *tracer ) -> next );
	}

	*tracer = newElement;
}

void Clear( struct ListNode **head ) {
	struct ListNode *  tracer = *head;
	struct ListNode *  temp;
	
	while( tracer != NULL ) {
		temp = tracer;
		tracer = tracer -> next;
		free( temp );
	}

	*head = NULL;
}

bool isPalindrome(struct ListNode* head){
	struct ListNode *  tracer;
	struct ListNode *   last;
	struct ListNode *   current;

	tracer = head;

	while ( tracer -> next != NULL ) {
		tracer = tracer -> next;
	}

	last = tracer;
	current = head;

	if ( current -> val != last -> val ) {
		return false;
	}

	while ( current != last && current -> next != last ) {
		current = current -> next;

		tracer = head;
		while ( tracer -> next != last ) {
			tracer = tracer -> next;
		}
		last = tracer;

		if ( current -> val != last -> val ) {
			return false;
		}
	}

	return true;
}