typedef struct Group
{
    char name[30];
    char lineInFile[100];
    // The rest if the stuff describing a group have not been included
    // as they are considered irrelevant in this program
} Group;

typedef struct Groups
{
    Group groupItem;
    struct Groups* next;
} Groups;


void InitFileHandler_group();
void InitGroupList();
void PrintFile_group();
void PrintFileStr_group();
void AddAllGroupsToGroupList();
void PrintList_group();
void RemoveGroup(char* groupName);
void WriteGroupsToFile();
void CloseFileHandler_group();
void CloseGroupList();