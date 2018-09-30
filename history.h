// COMP1521 18s2 mymysh ... command history
// Implements an interface to an abstract data object

#include <stdio.h>

// Functions on the Command History object

//TBD
void cleanCommandHistory();

void addToCommandHistory(char *cmdLine, int seqNo);
char *getCommandFromHistory(int seqNo);
char *getCommandFromHistory(int seqNo);
void saveCommandHistory();
int initCommandHistory();
void showCommandHistory();
void setHistoryFileName();