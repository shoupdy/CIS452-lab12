#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char** argv)
{
   DIR *dirPtr;
   struct dirent *entryPtr;
   struct stat statBuf;

   char* command = argv[1];
   char* directory = argv[2];

   dirPtr = opendir (directory);

   while ((entryPtr = readdir (dirPtr))){
      printf ("%-20s", entryPtr->d_name);
      stat(entryPtr->d_name, &statBuf);
      if(strcmp(command, "-i")==0){
         printf("\tInode: %d\n", statBuf.st_ino);
      }else if(strcmp(command, "-n")==0){
         printf("\tUser: %d\t Group: %d\n", statBuf.st_uid, statBuf.st_gid);
      }
   }

   closedir (dirPtr);
   return 0;
}