#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "stack.h"

void PrintAllFileAndFolderPathsBellowPath_r( char * startPath, stringStack_t *pathStack, int depth );

int main() {
    stringStack_t *  stack = NULL;

    ResetStringStack( &stack );
    PushToStringStack( stack, "abc" );
    PushToStringStack( stack, "def" );
    PopFromStringStack( stack );
    PushToStringStack( stack, "ghi" );
    PushToStringStack( stack, "jkl" );
    ResetStringStack( &stack );

    printf( "%d\n", EmptyStringStack( stack ) );

    stringStack_t *  pathStack = NULL;
    ResetStringStack( &pathStack );

    PrintAllFileAndFolderPathsBellowPath_r( "C:\\Users\\lucas", pathStack, 0 );

    return 0;
}

void PrintAllFileAndFolderPathsBellowPath_r( char * startPath, stringStack_t *pathStack, int depth ) {
    for ( int i = 1; i < depth; i++ ) { // Prints two dahses for each depth.
        putchar('-');
        putchar('-');
    }

    puts( startPath );

    DIR *   directory = opendir( startPath );
    struct  dirent *entry;
    char *  path = NULL;
    int     skipDotCounter = 0;
    while ( ( entry = readdir( directory ) ) != NULL ) { // Goes through all the subdirectories of the startPath and calls the function on them to print them all.
        if ( skipDotCounter < 2 ) {
            skipDotCounter++;
            continue;
        }
        
            if ( ( path = realloc( path, ( strlen(startPath) + strlen( entry->d_name ) + 1 ) * sizeof( char ) ) ) != NULL ) {
            strcpy( path, startPath );
            strcat( path, "/" );
            strcat( path, entry->d_name );
            PushToStringStack( pathStack, path );
            PrintAllFileAndFolderPathsBellowPath_r( entry->d_name, pathStack, depth + 1 );
            PopFromStringStack( pathStack );
        } else {
            puts( "Out of memory. Likely execution data loss.\n" );
        }
    }
    
    closedir( directory );
    free( path );
    path = NULL;
}