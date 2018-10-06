    // COMP1521 18s2 mymysh ... command history
    // Implements an abstract data object
    //TBD free up history

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "history.h"
    #include <errno.h>



    #ifdef DEBUG
    #  define D(x) x
    #else
    #  define D(x)
    #endif

    // This is defined in string.h
    // BUT ONLY if you use -std=gnu99
    //extern char *strdup(const char *s);

    // Command History
    // array of command lines
    // each is associated with a sequence number

    #define MAXHIST 20
    #define MAXSTR  200

    #define HISTFILE ".mymysh_history"

    typedef struct _history_entry {
        int   seqNumber;
        char  *commandLine; //a single entry
    } HistoryEntry;

    typedef struct _history_list {
        int nEntries; //index for commands (0 and 20)
        HistoryEntry commands[MAXHIST]; //array of all 20 commands
    } HistoryList;

    HistoryList CommandHistory;

    char *historyFileName = "";


    // initCommandHistory()
    // - initialise the data structure
    // - read from .history if it exists

    /**
    * READ FROM $HOME/.mymysh_history, IF THAT EXISTS
    * RETURNS THE SEQ NUMBER OF LAST COMMAND
    */


    int initCommandHistory(){

        CommandHistory.nEntries = 0;

        setHistoryFileName();
        FILE* file;
        file = fopen(historyFileName, "r");
        //Checking if file exists
        if (file){
            D(printf("mymysh.history exists\n"));
            char entry[MAXSTR];
            int i = CommandHistory.nEntries; //index of CommandHistory.commands[i]
            int num = 0;
            while(fscanf(file, " %3d  %[^\n]s\n", &num, entry) == 2){
                D(printf("sequence no = %d, command= %s\n", num, entry));
                CommandHistory.commands[i].seqNumber = num;
                CommandHistory.commands[i].commandLine = strdup(entry);
                i++;
            }
            CommandHistory.nEntries = i; //the index to start from next in CommandHistory.command[i]
            D(printf("Next vacant index %d\n", CommandHistory.nEntries));
            fclose(file);
            D(printf("Returning seq number = %d\n", CommandHistory.commands[CommandHistory.nEntries-1].seqNumber));
            //the latest sequence number of command
            return CommandHistory.commands[CommandHistory.nEntries-1].seqNumber;
        }else{
            //file doesn't exists or cannot be opened
            D(printf("File doesn't exist\n"));
            D(printf("Returning seq number = 0\n"));
            return 0;
        }
    }

    void setHistoryFileName() {
        char* home = getenv("HOME");
        char* filename = strcat(home,"/");
        historyFileName = strcat(filename, HISTFILE);
        D(printf("History path in init : %s\n", historyFileName));
    }

    void addToCommandHistory(char *cmdLine, int seqNo){

        char * cmdLineCopy = malloc(strlen(cmdLine) + 1);
        strcpy(cmdLineCopy, cmdLine);

        D(printf("ADDING %s TO COMMAND HISTORY with seq no : %d\n", cmdLineCopy, seqNo));

        HistoryEntry newEntry;
        newEntry.seqNumber = seqNo;
        newEntry.commandLine = cmdLineCopy;

        int i = CommandHistory.nEntries;
        D(printf("Current entry = %d\n", i));

        if(i >= MAXHIST){
            //shifting the elements
            for(int j = 1 ; j < MAXHIST ; j++ ){

                CommandHistory.commands[j-1] = CommandHistory.commands[j];
            }
            CommandHistory.commands[MAXHIST-1] = newEntry;
        }else{
            //printf("Else value of i = %d\n",i);
            CommandHistory.commands[i] = newEntry;
        }
        CommandHistory.nEntries++;
    }

    void showCommandHistory(){
        D(printf("SHOWING THE COMMAND HISTORY\n"));

        for (int i = 0; i < MAXHIST; i++){
            HistoryEntry entry = CommandHistory.commands[i];
            if(entry.seqNumber == 0){
                break;
            }
            printf(" %3d  %s\n", entry.seqNumber, entry.commandLine);
        }
    }


    char* getCommandFromHistory(int seqNo){
        for(int i = 0; i < MAXHIST ; i++){
            HistoryEntry entry = CommandHistory.commands[i];
            if( seqNo == entry.seqNumber ){
                D(printf("returning command %s for %d\n", entry.commandLine, seqNo));
                return entry.commandLine;
            }
        }
        D(printf("returning command NULL for %d\n", seqNo));
        return NULL;
    }

    /**
    * Returns the seq number of last command from history.
    * If there are no commands in history, returns -1.
    * @return
    */
    int getSeqOfLastCommandFromHistory(){
        int lastCommandIndex = -1;
        if(CommandHistory.nEntries == 0 ){
            lastCommandIndex = -1;
        } else if ((CommandHistory.nEntries > 0) && (CommandHistory.nEntries < MAXHIST)) {
            lastCommandIndex = CommandHistory.nEntries -1;
        } else{
            lastCommandIndex = MAXHIST -1;
        }
        D(printf("Last Command Index : %d\n", lastCommandIndex));
        if(lastCommandIndex == -1){
            return -1;
        } else{
            return CommandHistory.commands[lastCommandIndex].seqNumber;
        }
    }


    void saveCommandHistory(){

        FILE *file;
        D(printf("History path in save = %s\n", historyFileName));
        D(printf("Opening file in write mode\n"));
        file = fopen(historyFileName, "w");
        if (file == NULL) {
            D(printf("File could not be opened\n"));
            D(printf("error number = %s\n", strerror(errno)));
        }

        if (file) {
            for (int i = 0; i < MAXHIST; i++) {
                HistoryEntry entry = CommandHistory.commands[i];
                if(entry.seqNumber == 0){
                    break;
                }
                fprintf(file, "%d %s\n", entry.seqNumber, entry.commandLine);
            }
        }
        fclose(file);
    }

    // cleanCommandHistory
    // - release all data allocated to command history
    void cleanCommandHistory()
    {
        for(int i = 0 ; i < MAXHIST ; i++){
            HistoryEntry entry = CommandHistory.commands[i];
            if(entry.seqNumber == 0){
                break;
            }
            //free(entry.commandLine);
        }
    }

