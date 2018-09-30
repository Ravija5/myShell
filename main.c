#include <stdio.h>
#include "h.h"



void testShowCommandHistory();

void testInitCommandHistory();

void testSaveCommandHistory();

void testGetCommandFromHistory();

void testCleanCommandHistory();

int mainX() {
    printf("Hello, World!\n");
//
//    testInitCommandHistory();
//    testSaveCommandHistory();
//    testShowCommandHistory();

    //testGetCommandFromHistory();

    //testCleanCommandHistory();

    return 0;
}

void testCleanCommandHistory() {
    addToCommandHistory("eleven" , 11);
    addToCommandHistory("twelve" , 12);
    addToCommandHistory("thirteen" , 13);

    cleanCommandHistory();
}

void testGetCommandFromHistory() {
    addToCommandHistory("eleven" , 11);
    addToCommandHistory("twelve" , 12);
    addToCommandHistory("thirteen" , 13);
    getCommandFromHistory(15);
    getCommandFromHistory(13);

}

void testSaveCommandHistory() {
    addToCommandHistory("eleven" , 11);
    addToCommandHistory("twelve" , 12);
    addToCommandHistory("thirteen" , 13);
    addToCommandHistory("fourteen" , 14);
    addToCommandHistory("fifteen" , 15);
    addToCommandHistory("sixteen" , 16);
    saveCommandHistory();
}

void testInitCommandHistory() {
    initCommandHistory();
}

void testShowCommandHistory() {
    addToCommandHistory("one" , 1);
    addToCommandHistory("two" , 2);
    addToCommandHistory("three" , 3);
    addToCommandHistory("four" , 4);
    addToCommandHistory("five" , 5);
    addToCommandHistory("six" , 6);
    showCommandHistory();
}
