# delgroup - Mock console app
This is an assignment os part of PSWC course, PES University  
DONE BY: T Tarun Aditya  
Email: tarun.aditya.bc@gmail.com  

**Personal comment**: This project is something I have no interest in working on and I only did it to complete the assignment. The code I have used doesn't handle minor bugs, which are now part of the issues section. It may also be noted that the code used here more or less shows how I code in a rough manner without much consideration as to the security or any other implications it might have in the future. I have no interest in working on it in the future.

# PROJECT STATEMENT
**Assignment 9**: Write a program in C to mimic the “delgroup” command on Linux. This command will delete a group. It has to handle 2 files “group” and “gshadow”. Both these files will be in some folder specified by an environment variable PFILE. The program has to take all arguments as command line arguments (Refer man pages for the command line arguments)
The program has to delete all references to this group in the files group and shadow. Copy these two files /etc/group and /etc/gshadow from any Linux system into another folder and then execute your program.
delgroup GName (The only argument is the name of the group being deleted)

## PROJECT GUIDELINES
1. Make sure that you have your code in at least 2 .c files and one .h file. (**DONE**)
2. You need to have a relevant makefile to build the executable. (**DONE**)
3. Accept as many inputs as possible through command line arguments (**DONE**)
4. The “main” function should be restricted to just taking the required inputs, calling other functions for the required processing and then displaying the results (**DONE**)
5. Avoid (minimize) the use of global variables (If you are using, you have to justify why you have to use global variables – apart from saying “it makes your life easier”) (**DONE**)
6. The functions as far as possible, have to accept arguments and return the required result. If you have functions which do not accept any parameters and do not return anything, that code might as well be part of the main function. (**DONE**)
7. When you build the executable, make sure that there are no “warnings” left.  (**DONE**)
8. The variables used in your program should have meaningful names. Avoid using i,j,k,l  (**DONE**)
9. Write meaningful comments. A program without comments will not be accepted (**DONE**)
10. Check for all possible error conditions and handle these gracefully.  (**NOT DONE**)
11. Validate all the input values  (**DONE**) (NOTE: The file input is not validated)
12. Clearly mention any known bugs still left in the program which you are unable to fix. (**DONE**)
13. Clearly mention any assumptions you have made  (**DONE**)
14. Also, mention any constraints under which your program might work correctly. (**DONE**)
15. GUI is not mandatory.(**DONE**)
16. It would be good to make sure all these programs work on Windows as well as Linux. (**DONE**)
17.  You can use whatever tools you are comfortable with. But, when you submit your program, make sure that there is a “makefile” which just needs the “make” utility and the “gcc” compiler to build your executable.(**DONE**)

## Instructions
- 3 Marks - for following the guidelines in letter and spirit
- 2 Marks - For handling all possible errors in their programs (Checking for return values from functions, validating inputs, etc)
- 5 Marks - The actual working of the program.

# Research
- ``The group `fsds' does not exist.`` is displayed if a group does not exist.  

### ``group`` file

- Example: ``video:x:44:tarun``

|group name  |Password  |Group ID  |Group List  |  
|---------|---------|---------|---------|  
|  video  | x | 44 |tarun  |
- Details:
    - group_name: It is the name of group. If you run ls -l command, you will see this name printed in the group field.
    - Password: Generally password is not used, hence it is empty/blank. It can store encrypted password. This is useful to implement privileged groups.
    - Group ID (GID): Each user must be assigned a group ID. You can see this number in your /etc/passwd file.
    - Group List: It is a list of user names of users who are members of the group. The user names, must be separated by commas.

### ``gshadow`` file

- Example: ``netdev:!::tarun``

|group name  |Password  |Group Admin  |Group members  |  
|---------|---------|---------|---------|  
|  netdev  | ! |  |tarun  |

- Details:
    1. **Group Name**: This is the name of the group.

    2. **Encrypted Password Of Group**: The encrypted password for the group. If set, non-members of the group can join the group by typing the password for that group using the newgrp command. If the value of this field is ! then no user is allowed to access the group using the newgrp command. A value of !! is treated the same as a value of ! However, it also indicates that a password has never been set before. If the value is null, only group members can log into the group.

    3. **Group Administrator**: All the members of the group, listed here with a comma. You can add or remove group members using the gpasswd command

    4. **Group Members**: All the members of the group listed here are regular members with separated by a comma i.e. a non-administrative member of the groups.


# Limitations
1. the length of each line in any file shouldn't exceed 100 characters.
2. the length of each group name shouldn't exceed 30 characters.
3. If group and gshadow file are empty there might be issues./ if they contain something other than what they are supposed to contain, it might just turn out to be a grave security issue.
4. It fails to gracefully end if the files can't be read, or memory can't be allocated for the program.

# ISSUES/TODO
1. check for FILE pointer being null
2. check for fseek returning non-zero value
3. check if malloc is successful in allocation memory
4. merge RemoveGroupFrom_group and RemoveGroupFrom_gshadow to single function
5. If group and gshadow file are empty there might be issues./ if they contain something other than what they are supposed to contain, it might just turn out to be a grave security issue.

# Installation/BUILD
There is no installation for this app. You need to just build it and run it.  
- To build it on windows, run `.\BUILD.ps1` or `make -f build.mk`
- To clean the directory, run `.\BUILD.ps1 clean`.
- On linux, run `make -f build.mk`.   
**NOTE**: You must have `GCC` and `make` installed in your windows/linux machine

# Usage
To use it, after building it, run `.\delgroup.exe <group name>` on windows and/or `./delgroup.exe <group name>` on linux,
where the `<group name>` is the group you want to delete from the files `group` and `gshadow` already present in the repo,
altering them, or creating a separate modified file.

# Development
When you are developing, just follow the [BUILD](Installation/BUILD) process and then the [USAGE](Usage) instructions.

# Contribution
This is a highly unlikely circumstance, but if you want to contribute, you may do so and PR it and I shall gladly merge it into the repo after verification.

# LICENSE
This project has been open-sourced on github with the Apache License, Version 2.0, January 2004. Read the License file for further details.