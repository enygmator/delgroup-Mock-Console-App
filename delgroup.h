#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/// <summary>
/// Represents a single Group of users (derived from a string in 'group' or 'gshadow' file)
/// </summary>
typedef struct Group
{
    char name[30]; //The name of the group
    char lineInFile[100]; //The entire string in the 'group' or 'gshadow' file
} Group;

/// <summary>
/// Represents a node of the Linked list of "Group" type
/// </summary>
typedef struct Groups
{
    Group groupItem; //The "Group" item of the node in the linked list
    struct Groups* next; //The pointer to the next node of the linked list
} Groups;

void InitFileHandlers();
void InitGroupLists();
void PrintFiles();
void PrintFilesStr();
void AddAllGroupsToGroupLists();
void PrintLists();
bool RemoveGroupFrom_group(char* groupName);
bool RemoveGroupFrom_gshadow(char* groupName);
void WriteGroupsToFile(char* group_FileName, char* gshadow_FileName);
void CloseList_group();
void CloseList_gshadow();