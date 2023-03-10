#include <stdbool.h>

typedef struct _stringStackNode_t {
	char *                   data;
	struct _stringStackNode_t *  pNext;
} stringStackNode_t;

typedef struct _stringStack_t {
	stringStackNode_t *  pFirst;
	stringStackNode_t *  pLast;
} stringStack_t;

void PopFromStringStack( stringStack_t *pStack );
void ClearStringStack( stringStack_t *pStack );
void ResetStringStack( stringStack_t **pStack );
void PushToStringStack( stringStack_t *pStack, char *data );
bool EmptyStringStack( stringStack_t *pStack );