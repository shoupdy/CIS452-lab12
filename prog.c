#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Provide an argument and directory path.\n");
        return 1;
    }

    DIR *dirPtr;
    struct dirent *entryPtr;
    struct stat statBuf;

    char *command = argv[1];
    char *directory = argv[2];

    chdir(directory);
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

    dirPtr = opendir(directory);

    while ((entryPtr = readdir(dirPtr)))
    {
        char tmp[2];
        memcpy(tmp, entryPtr->d_name, 1);

        if (strcmp(tmp, ".") == 0)
        {
            continue;
        }

        printf("%-20s", entryPtr->d_name);
        stat(entryPtr->d_name, &statBuf);

        if (strcmp(command, "-i") == 0)
        {
            printf("\tInode: %lld\n", statBuf.st_ino);
        }
        else if (strcmp(command, "-n") == 0)
        {
            printf("\tUser: %d\t Group: %d\n", statBuf.st_uid, statBuf.st_gid);
        }
    }

    closedir(dirPtr);
    return 0;
}