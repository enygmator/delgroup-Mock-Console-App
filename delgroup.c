#include"delgroup.h"

Groups* AppendToGroupList(Groups* groupList, char* groupLine);

//Here, global variables have been used as any of these function might have to access the same variable
//and because the main function does not handle the variable passing to each of these functions
//as it doesn't make sense to have multiple instances of the delgroup command at once and
//also because this file can then act as a "service" to the main "system"

FILE* groupFilePtr; //File pointer to 'group' file
Groups* groupList; //The first element of the 'group' file's linked list

FILE* gshadowFilePtr; //File pointer to 'gshadow' file
Groups* gshadowList; //The first element of the 'gshadow' file's linked list

FILE* group_ModifiedFilePtr; //File pointer to modified 'group' file
FILE* gshadow_ModifiedFilePtr; //File pointer to modified 'gshadow' file

/// <summary>
/// Initiates the file handlers i.e. file pointers to the 'group' and 'gshadow' files
/// </summary>
void InitFileHandlers()
{
    //Opens files with read permissions
    groupFilePtr = fopen("group", "r");
    gshadowFilePtr = fopen("gshadow", "r");
}

/// <summary>
/// Initiates both the Linked lists by setting First element to NULL
/// </summary>
void InitGroupLists()
{
    groupList = NULL;
    gshadowList = NULL;
}

/// <summary>
/// This function Prints both the Files character by character
/// </summary>
void PrintFiles()
{
    char chr;
    fseek(groupFilePtr, 0, SEEK_SET);
    fseek(gshadowFilePtr, 0, SEEK_SET);
    //Reads characters until EOF is reached
    while ((chr = fgetc(groupFilePtr)) != EOF)
    {
        printf("%c", chr);
    }
    fseek(groupFilePtr, 0, SEEK_SET);//resets file pointer
    while ((chr = fgetc(gshadowFilePtr)) != EOF)
    {
        printf("%c", chr);
    }
    fseek(gshadowFilePtr, 0, SEEK_SET);
}

/// <summary>
/// This function Prints both the Files line by line
/// </summary>
void PrintFilesStr()
{
    char str[100];
    fseek(groupFilePtr, 0, SEEK_SET);
    fseek(gshadowFilePtr, 0, SEEK_SET);
    while (fgets(str, 100, groupFilePtr))
    {
        printf("%s", str);
    }
    fseek(groupFilePtr, 0, SEEK_SET);
    while (fgets(str, 100, gshadowFilePtr))
    {
        printf("%s", str);
    }
    fseek(gshadowFilePtr, 0, SEEK_SET);
}

/// <summary>
/// Adds all the "groups" from the 'group' and 'gshadow' file to their respective linked lists
/// </summary>
void AddAllGroupsToGroupLists()
{
    char str[100];
    fseek(groupFilePtr, 0, SEEK_SET); //resets file pointer position
    fseek(gshadowFilePtr, 0, SEEK_SET);
    while (fgets(str, 100, groupFilePtr))
    {
        groupList = AppendToGroupList(groupList, str);
    }
    fseek(groupFilePtr, 0, SEEK_SET);
    while (fgets(str, 100, gshadowFilePtr))
    {
        gshadowList = AppendToGroupList(gshadowList, str);
    }
    fseek(gshadowFilePtr, 0, SEEK_SET);
}

/// <summary>
/// Appends a groupItem (Group) to the group List
/// </summary>
/// <param name="groupListArgs">The first element of the Linked List</param>
/// <param name="groupLine">The "group" string extracted from the file</param>
/// <returns>The first element of the Linked List</returns>
Groups* AppendToGroupList(Groups* groupListArgs, char* groupLine)
{
    Groups* groupList0 = groupListArgs;
    Groups* preGroups = groupList0; //Remembering the previous node of the Linked list
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
        //In case the Linked list's first element has not been created
        preGroups = (Groups*)malloc(sizeof(Groups));
        groupList0 = preGroups;
        groupListArgs = groupList0;
    }
    groupList0->next = NULL;
    int charPos = 0;
    char* groupName = groupLine;
    //Copies the group name to the group item's "Name" attribute
    while (*groupName != ':' && *groupName != '\0' && *groupName != '\n')
    {
        groupList0->groupItem.name[charPos] = *groupName;
        groupName++;
        charPos++;
    }
    //Copies the entire string to the group item's "name" attribute
    groupList0->groupItem.name[charPos] = '\0';
    strcpy(groupList0->groupItem.lineInFile, groupLine);
    //Returns the first element of the Linked List
    return groupListArgs;
}

/// <summary>
/// Prints the Linked lists to the terminal
/// </summary>
void PrintLists()
{
    Groups* tempList = groupList;
    while (tempList)
    {
        printf("%s\t\t\t%s", tempList->groupItem.name, tempList->groupItem.lineInFile);
        tempList = tempList->next;
    }
    printf("\n");
    tempList = gshadowList;
    while (tempList)
    {
        printf("%s\t\t\t%s", tempList->groupItem.name, tempList->groupItem.lineInFile);
        tempList = tempList->next;
    }
    printf("\n");
}

/// <summary>
/// Removes a group item from the 'group' linked list
/// </summary>
/// <param name="groupName">Name of the group you want to remove</param>
/// <returns>Whether the group was removed successfully</returns>
bool RemoveGroupFrom_group(char* groupName)
{
    Groups* tempList = groupList, *preGroup = groupList;
    while (tempList)
    {
        if(!strcmp(tempList->groupItem.name, groupName))
        {
            //Checks if the element to be removed is the first element o the linked list
            if(!strcmp(groupList->groupItem.name, groupName))
            {
                preGroup = groupList;
                groupList = groupList->next;
                free(preGroup);
                printf("The group `%s` was removed from the `group` file\n", groupName);
                return true;
            }
            preGroup->next = tempList->next;
            free(tempList);
            printf("The group `%s` was removed from the `group` file\n", groupName);
            return true;
        }
        preGroup = tempList;
        tempList = tempList->next;
    }
    printf("The group `%s` does not exist in `group` file\n", groupName);
    return false;
}

/// <summary>
/// Removes a group item from the 'gshadow' linked list
/// </summary>
/// <param name="groupName">Name of the group you want to remove</param>
/// <returns>Whether the group was removed successfully</returns>
bool RemoveGroupFrom_gshadow(char* groupName)
{
    Groups* tempList = gshadowList, *preGroup = gshadowList;
    while (tempList)
    {
        if(!strcmp(tempList->groupItem.name, groupName))
        {
            //Checks if the element to be removed is the first element o the linked list
            if(!strcmp(gshadowList->groupItem.name, groupName))
            {
                preGroup = gshadowList;
                gshadowList = gshadowList->next;
                free(preGroup);
                printf("The group `%s` was removed from the `gshadow` file\n", groupName);
                return true;
            }
            preGroup->next = tempList->next;
            free(tempList);
            printf("The group `%s` was removed from the `gshadow` file\n", groupName);
            return true;
        }
        preGroup = tempList;
        tempList = tempList->next;
    }
    printf("The group `%s` does not exist in `gshadow` file\n", groupName);
    return false;
}

/// <summary>
/// Writes the Linked lists / string of modified group items to a file
/// </summary>
/// <param name="group_FileName">File name of the modified 'group' Linked list</param>
/// <param name="gshadow_FileName">File name of the modified 'gshadow' Linked list</param>
void WriteGroupsToFile(char* group_FileName, char* gshadow_FileName)
{
    //Closes previous file handles
    fclose(groupFilePtr);
    fclose(gshadowFilePtr);

    //opens files with write permissions
    group_ModifiedFilePtr = fopen(group_FileName, "w");
    Groups* tempList = groupList;
    while (tempList)
    {
        //Writes to the files
        fputs(tempList->groupItem.lineInFile, group_ModifiedFilePtr);
        tempList = tempList->next;
    }

    gshadow_ModifiedFilePtr = fopen(gshadow_FileName, "w");
    tempList = gshadowList;
    while (tempList)
    {
        fputs(tempList->groupItem.lineInFile, gshadow_ModifiedFilePtr);
        tempList = tempList->next;
    }

    //Closes previous file handles
    fclose(group_ModifiedFilePtr);
    fclose(gshadow_ModifiedFilePtr);
}

/// <summary>
/// Frees memory by destructing the Linked list
/// </summary>
void CloseList_group()
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

/// <summary>
/// Frees memory by destructing the Linked list
/// </summary>
void CloseList_gshadow()
{
    Groups* gList = gshadowList, *preItem;
    while (gList)
    {
        preItem = gList;
        gList = gList->next;
        free(preItem);
    }
    groupList = NULL;
}