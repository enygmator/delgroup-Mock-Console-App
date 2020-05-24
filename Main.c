#include"delgroup.h"

/// <summary>
/// Displays the help dialog for information on using this console app
/// </summary>
void ShowHelpDialog()
{
    printf("This command is used to remove groups from a linux/Windows machine.\nThis is actually a linux command");
    printf(" replicated on windows.\n\nIf a group does not exist and you try to remove it, you get the error message:\n");    
    printf("The group `<groupName>` does not exist\n\n");
    printf("Use the command like this:\nWindows: .\\deluser.exe <group name>\nLinux: ./deluser.exe <group name>\n\n");
    printf("Example: \nWindows: .\\deluser.exe root\nLinux: ./deluser.exe root\nThe above example deletes the user root.\n");
}

/// <summary>
/// This is the main function/ starting point of the program
/// </summary>
/// <param name="argc">Number of arguments passed to the program via CLI</param>
/// <param name="argv">The arguments (as strings/ char**/ char* []) passed to the program via CLI</param>
/// <returns>0 : successful :: 1 : unsuccessful</returns>
int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        ShowHelpDialog();
    }
    if(argc > 2)
    {
        printf("[ERROR]\tToo many arguments passed.\n\nTry using `--help` to figure out the error.\n");
        return 1;
    }
    if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
    {
        ShowHelpDialog();
        return 0;
    }
    InitFileHandlers();
    InitGroupLists();
    AddAllGroupsToGroupLists();
    char str[100] = "NULL", ch;
    if(RemoveGroupFrom_group(argv[1]) == false || RemoveGroupFrom_gshadow(argv[1]) == false)
    {
        printf("Aborting..."); //Aborting if the removal of the group was unsuccessful. This can happen if the files are
        // not properly set i.e. there has been tampering with the files, etc.
        return 1;
    }
    //We have an option to modify the original files or create modified files
    printf("Do you want to modify the original files? (Y/N): ");
    scanf(" %c", &ch);
    if (ch == 'Y' ||ch == 'y')
    {
        WriteGroupsToFile("group", "gshadow");
    }
    else if (ch == 'N' ||ch == 'n')
    {
        WriteGroupsToFile("group_Modified", "gshadow_Modified");
    }
    else
    {
        printf("No file was modified.\n");
    }
    CloseList_group();
    CloseList_gshadow();
    return 0;
}