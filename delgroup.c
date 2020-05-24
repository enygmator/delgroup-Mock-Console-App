#include"delgroup.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

Groups* AppendToGroupList(Groups* groupList, char* groupLine);

FILE* groupFilePtr;
Groups* groupList;

FILE* tempFilePtr;

void InitFileHandler_group()
{
    groupFilePtr = fopen("group", "r");
}

void InitGroupList()
{
    groupList = NULL;
}

void PrintFile_group()
{
    char chr;
    while ((chr = fgetc(groupFilePtr)) != EOF)
    {
        printf("%c", chr);
    }
    fseek(groupFilePtr, 0, SEEK_SET);
}

void PrintFileStr_group()
{
    char str[100];
    while (fgets(str, 100, groupFilePtr))
    {
        printf("%s", str);
    }
    fseek(groupFilePtr, 0, SEEK_SET);
}

void AddAllGroupsToGroupList()
{
    char str[100];
    fseek(groupFilePtr, 0, SEEK_SET);
    while (fgets(str, 100, groupFilePtr))
    {
        groupList = AppendToGroupList(groupList, str);
    }
    fseek(groupFilePtr, 0, SEEK_SET);
}

Groups* AppendToGroupList(Groups* groupListArgs, char* groupLine)
{
    Groups* groupList0 = groupListArgs;
    Groups* preGroups = groupList0;
    while (groupList0)
    {
        preGroups = groupList0;
        groupList0 = groupList0->next;
    }
    if(preGroups != NULL)
    {
        preGroups->next = (Groups*)malloc(sizeof(Groups));
        groupList0 = preGroups->next;
    }
    else
    {
        preGroups = (Groups*)malloc(sizeof(Groups));
        groupList0 = preGroups;
        groupListArgs = groupList0;
    }
    groupList0->next = NULL;
    int charPos = 0;
    char* groupName = groupLine;
    while (*groupName != ':' && *groupName != '\0' && *groupName != '\n')
    {
        groupList0->groupItem.name[charPos] = *groupName;
        groupName++;
        charPos++;
    }
    groupList0->groupItem.name[charPos] = '\0';
    strcpy(groupList0->groupItem.lineInFile, groupLine);
    return groupListArgs;
}

void PrintList_group()
{
    Groups* tempList = groupList;
    while (tempList)
    {
        printf("%s\t\t\t%s", tempList->groupItem.name, tempList->groupItem.lineInFile);
        tempList = tempList->next;
    }
    printf("\n");
}

void RemoveGroup(char* groupName)
{
    Groups* tempList = groupList, *preGroup = groupList;
    while (tempList)
    {
        if(!strcmp(tempList->groupItem.name, groupName))
        {
            printf("%s ", tempList->groupItem.name);
            if(!strcmp(groupList->groupItem.name, groupName))
            {
                preGroup = groupList;
                groupList = groupList->next;
                free(preGroup);
                return;
            }
            preGroup->next = tempList->next;
            free(tempList);
            return;
        }
        preGroup = tempList;
        tempList = tempList->next;
    }
    printf("The group `%s` does not exist\n", groupName);
}

void WriteGroupsToFile()
{
    tempFilePtr = fopen("group1", "w");
    Groups* tempList = groupList;
    while (tempList)
    {
        fputs(tempList->groupItem.lineInFile, tempFilePtr);
        tempList = tempList->next;
    }
}

void CloseFileHandler_group()
{
    fclose(groupFilePtr);
}

void CloseGroupList()
{
    Groups* gList = groupList, *preItem;
    while (gList)
    {
        preItem = gList;
        gList = gList->next;
        free(preItem);
    }
    groupList = NULL;
}