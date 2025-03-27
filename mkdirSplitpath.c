#include "types.h"
#include <string.h>
#include <stdlib.H>
#include <stdio.h>
#include <libgen.h>

extern struct NODE* root;
extern struct NODE* cwd;

struct NODE* searchChild(struct NODE* parents, const char* name);


// handles tokenizing and absolute and relative path options
struct NODE* searchChild(struct NODE* parent, const char* name) {
    struct NODE* current = parent->childPtr;
    while(current) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->siblingPtr;
    }
    return NULL;

}

//make directory
void mkdir(char pathName[]){

    // TO BE IMPLEMENTED
    //
    // YOUR CODE TO REPLACE THE PRINTF FUNCTION BELOW

    if (strcmp(pathName, "/") == 0 || strlen(pathName) == 0) {
        printf("MKDIR ERROR: no path provided\n");
        return;
    }

    char baseName[64], dirName[128];
    struct NODE* parent = splitPath(pathName, baseName, dirName);

    if (!parent) return;

    if (searchChild(parent, baseName)) {
        printf("MKDIR ERROR: directory %s already exists\n", pathName);
        return;
    }

    struct NODE* newNode = (struct NODE*)malloc(sizeof(struct NODE));
    if (!newNode) {
        perror("MKDIR ERROR: memory allocation failed");
        return;
    }

    strcpy(newNode->name, baseName);
    newNode->fileType = 'D';
    newNode->parentPtr = parent;
    newNode->childPtr = NULL;
    newNode->siblingPtr = NULL;

    if (!parent->childPtr) {
        parent->childPtr = newNode;
    } else {
        struct NODE* current = parent->childPtr;
        while (current->siblingPtr) {
            current = current->siblingPtr;
        }
        current->siblingPtr = newNode;
    }

    printf("MKDIR SUCCESS: node %s successfully created\n", pathName);

    return;
}

//handles tokenizing and absolute/relative pathing options
struct NODE* splitPath(char* pathName, char* baseName, char* dirName){

    // TO BE IMPLEMENTED
    // NOTE THAT WITHOUT COMPLETING THIS FUNCTION CORRECTLY
    // rm, rmdir, ls, cd, touch COMMANDS WILL NOT EXECUTE CORRECTLY
    // SEE THE PROVIDED SOLUTION EXECUTABLE TO SEE THEIR EXPECTED BEHAVIOR

    // YOUR CODE HERE
    //

    if (strcmp(pathName, "/") == 0) {
        strcpy(baseName, "/");
        strcpy(dirName, "/");
        return root;
    }

    char temp1[128], temp2[128]; 
    strcpy(temp1, pathName);
    strcpy(temp2, pathName);
    strcpy(dirName, dirname(temp1));
    strcpy(baseName, basename(temp2));

    struct NODE* traversal;

    if (pathName[0] == '/') {
        traversal = root;
    } else {
        traversal = cwd;
    }

    if (strcmp(dirName, ".") == 0) {
        return traversal;
    }

    char tempDir[128];
    strcpy(tempDir, dirName);

    char* token = strtok(tempDir, "/");
    while (token) {
        traversal = searchChild(traversal, token);
        if (!traversal) {
            printf("ERROR: directory %s does not exist\n, token");
            return NULL;
        }
        token = strtok(NULL, "/");
    }

    return NULL;
}
