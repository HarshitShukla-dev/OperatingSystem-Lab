#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>

int main()
{
 struct dirent *dptr;
 
 int a = mkdir("My_Directory", 0777);
 int b = mkdir("Your_Directory", 0777);
 
 if(a==0 && b==0){
  printf("* Directories named 'My_Directory' and 'Your_Directory' has been created Successfully. \n");
 }
 else{
  printf("* Either directories named 'My_Directory' & 'Your_Directory' already exist or they were not able to create due to any Error. \n");
 }
 
 int fd1 = open("My_Directory/My_File.txt", O_CREAT|O_RDWR, 0777);
 
 printf("* File named 'My_File.txt' has been created Successfully in Directory named 'My_Directory'. \n");
 printf(" \n");
 
 char c[1000];
 
 printf("#Enter content: \n");
 scanf("%[^\n]s", c);
 printf(" \n");
 
 int size=0;
 
 for(int i=0;i<100;i++)
 {
if(c[i]=='\0'){
   break;
  }
  
  else{
   size++;
  }
 }
 
 write(fd1, c, size);
 printf("@ Given input text from user has been Successfully copied in file named 'My_File.txt'. \n");
 printf(" \n");
 
 DIR *dp = opendir("Your_Directory");
 
 int no_of_files=-2;
 
 while(NULL != (dptr=readdir(dp)))
 {
  no_of_files++;
 }
 
 printf("# No. of files in directory which is named 'Your_Directory' are: \n");
 printf("%d\n",no_of_files);
 printf(" \n");
 
 int fd2 = open("Your_Directory/My_File_Copy.txt", O_CREAT | O_RDWR, 0777);
 printf("* File named 'My_File_Copy.txt' has been created Successfully in Directory named 'Your_Directory'. \n");
 
 write(fd2, c, size);
 printf("* Content of File named 'My_File' in Directory named 'My_Directory' has been Successfully Copied to file named 'My_File_Copy.txt' which is in Directory named 'Your_Directory' \n");
 printf(" \n");
 
 // -----------------------------------------------------------------------------------------
 
 DIR *dp1 = opendir("Your_Directory");
 
 int new_no_of_files=-2;
 
 while(NULL != (dptr=readdir(dp1)))
 {
  new_no_of_files++; 
 }
 
 printf("# Now no. of files in directory which is named 'Your_Directory' are: \n");
 printf("%d\n", new_no_of_files);
 printf(" \n");
 
 return 0;
}
