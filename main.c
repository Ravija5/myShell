#include <stdio.h>
#include <unistd.h>
#include "history.h"

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


void testShowCommandHistory();

void testInitCommandHistory();

void testSaveCommandHistory();

void testGetCommandFromHistory();

void testCleanCommandHistory();

void testSeqOfLastCommand();

void testOutputRedirect();

void testInputRedirect();

int main() {
    printf("Hello, World!\n");


    testInputRedirect();


    //testOutputRedirect();
    //testSeqOfLastCommand();
    //testInitCommandHistory();
    //testSaveCommandHistory();
    //testShowCommandHistory();
    //testGetCommandFromHistory();
    //testCleanCommandHistory();
    return 0;
}

void testInputRedirect() {
    int newfd;    /* new file descriptor */

    if ((newfd = open("in.txt", O_RDONLY)) < 0) {
        perror("in.txt open failed.");	/* open failed */
     //   return 1;
    }

    char a[100];
    printf( "A - Reading from STD INPUT:");
    gets(a );
    printf( "\nA - Value read from STD INPUT: ");
    puts(a );


    char b[100];
    printf( "\nB - Now reading from FILE: ");

    int saved = dup(STDIN_FILENO); //Saving original
    close(0);
    dup2(newfd, STDIN_FILENO);
    gets(b );


    dup2(saved, STDIN_FILENO); //Restoring
    close(newfd);

    printf( "\nB - Value b read from FILE: ");
    puts(b );



    char c[100];
    printf( "\nC - Now reading again from STD INPUT: ");
    gets(c );
    printf( "\nC - Value read from STD INPUT: ");
    puts(c );

    char d[100];
    printf( "\nD - AGAIN Now reading again from STD INPUT: ");
    gets(d );
    printf( "\nD - Value read from STD INPUT: ");
    puts(d );
}

void testSeqOfLastCommand() {
    addToCommandHistory("eleven", 11);
    addToCommandHistory("twelve", 12);
    addToCommandHistory("thirteen", 13);
    addToCommandHistory("fourteen", 14);
    addToCommandHistory("fifteen", 15);
    addToCommandHistory("sixteen", 16);
    int x = getSeqOfLastCommandFromHistory();
    showCommandHistory();
    printf("SEQ: %d", x);
}

void testCleanCommandHistory() {
    addToCommandHistory("eleven", 11);
    addToCommandHistory("twelve", 12);
    addToCommandHistory("thirteen", 13);

    cleanCommandHistory();
}

void testGetCommandFromHistory() {
    addToCommandHistory("eleven", 11);
    addToCommandHistory("twelve", 12);
    addToCommandHistory("thirteen", 13);
    getCommandFromHistory(15);
    getCommandFromHistory(13);

}

void testSaveCommandHistory() {
    addToCommandHistory("eleven", 11);
    addToCommandHistory("twelve", 12);
    addToCommandHistory("thirteen", 13);
    addToCommandHistory("fourteen", 14);
    addToCommandHistory("fifteen", 15);
    addToCommandHistory("sixteen", 16);
    saveCommandHistory();
}

void testInitCommandHistory() {
    initCommandHistory();
}

void testShowCommandHistory() {
    addToCommandHistory("one", 1);
    addToCommandHistory("two", 2);
    addToCommandHistory("three", 3);
    addToCommandHistory("four", 4);
    addToCommandHistory("five", 5);
    addToCommandHistory("six", 6);
    showCommandHistory();
}

void testOutputRedirect(){
    int newfd;	/* new file descriptor */

    if ((newfd = open("file1.txt", O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) {
        perror("file1.txt");	/* open failed */
        exit(1);
    }
    printf("This goes to the standard output.\n");

    int saved = dup(STDOUT_FILENO);
    close(1);

    dup2(newfd, STDOUT_FILENO);

    printf("This goes to file.\n");

    dup2(saved, STDOUT_FILENO);
    close(newfd);

    printf("Now back to console.\n");
}
