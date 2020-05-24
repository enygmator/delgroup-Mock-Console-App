#include"delgroup.h"
#include<stdio.h>

int main(char** args)
{
    InitFileHandler_group();
    InitGroupList();
    AddAllGroupsToGroupList();
    PrintList_group();
    char ch = 's';
    char str[100];
    while (ch != 'e')
    {
        printf("e(exit) s(show) r(remove) w(write to file): ");
        scanf(" %c", &ch);
        switch (ch)
        {
        case 's':
            PrintList_group();
            break;
        case 'r':
            printf("Enter group to remove: ");
            scanf("%s", &str);
            RemoveGroup(str);
            break;
        case 'w':
            WriteGroupsToFile();
            break;        
        default:
            break;
        }
    }
    CloseFileHandler_group();
    CloseGroupList();
    return 0;
}