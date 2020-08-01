#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "image.h"

int main(int argc, char *argv[])
{
 readfile = fopen(argv[1], "rt+");

 //Record the print version into a new dir in extemp box folder, so
 //find the filename itself for recording purposes

 i=-1; 

 fseek (readfile,0,SEEK_END);  //Set starting point to end
 size = ftell(readfile);       //Find file size
 fseek (readfile,0,SEEK_SET);  //Set starting point to start

 readfiledata = malloc(size);  //Allocate memory for char
 
 printf("Filename is %s\n", argv[1]);
 printf("Size is %d\n", size);
 printf("Copied %s to steve.tmp\n", argv[1]);
 
 i=-1;

 do
 {
  static int i=0;
  readfiledata[i] = fgetc(readfile);
  i++;
 }
 while(!feof(readfile));

 fclose(readfile);

 temp=fopen("steve.tmp", "wt+");
 fputs(readfiledata, temp);


#if DEBUG
 printf("Trying to print readfiledata\n");
 printf( "%s\n",readfiledata);
#endif

//-------------

 printf("Writing to File %s\n", argv[1]);
 sleep(2);

 writefile = fopen(argv[1], "wt+");

 do //Search the data
 {
  n=-1;
  p=m-1;

  printf("Processing byte %d of file %s\n",m,argv[1]);

  strcpy(test, NULL); //wipe test at the beginning of loop


#if DEBUG
  printf("p is %d\n", p);
  printf("readfiledata p\n");
  printf("m is %d\n", m);
  sleep(2);
#endif

  n=-1;

  do //transcribe the four
   test[n++] = readfiledata[p++];
  while(n<8);
 
#if DEBUG
  printf("test is %s\n",test);
  printf("p is %d m is %d\n", p,m);
  sleep(2);
#endif

  if((strncmp(test, "<img",4) ==0) ||
     (strncmp(test, "<map",4) ==0) ||
     (strncmp(test, "</map>",6) ==0) ||
     (strncmp(test, "<form>",6) ==0) ||
     (strncmp(test, "</form>",7) ==0) ||
     (strncmp(test, "<FORM>",6)==0) ||
     (strncmp(test, "</FORM>",7)==0) ||
     (strncmp(test, "<input",6) ==0) ||
     (strncmp(test, "<INPUT",6) ==0) ||
     (strncmp(test, "<IMG",4) ==0) ||
     (strncmp(test, "<MAP",4) ==0) ||
     (strncmp(test, "</MAP>",6) ==0) ||
     (strncmp(test, "<b>",3)  ==0) ||
     (strncmp(test, "<B>",3)  ==0) ||
     (strncmp(test, "</b>",4) ==0) ||
     (strncmp(test, "</B>",4) ==0) ||
     (strncmp(test, "<area",5) ==0) ||	
     (strncmp(test, "<AREA",5) ==0)) //Found image, so look for ending '>'
  {
   p=0; //Reset p to 0 so that we can add it to 0 to find out how long the img is  


#if DEBUG
   printf("img found at m is %d p is %d\n",m,p);
   sleep(3);
#endif

   do
   {
    p++;
    if(readfiledata[m+p] == '>')
    { 
//     printf("Found >\n");
     m+=p; //The number of spaces that p found added to m so it doesn't copy the img


#if DEBUG
     printf("p is %d, m is %d\n", p,m);
     printf("Will next start at %d with %c\n", m, readfiledata[m]);	
     sleep(1);
#endif


     strcpy(test, NULL); //To prevent 'hey look, i found an image' over and over...
     break;
    }  


#if VDEBUG
    printf("With p at %d trying to find >\n", p);
    printf("Readfiledata p is %c\n", readfiledata[p]);
#endif


   }while(readfiledata[m+p] != '>');
  }
  else if((strncmp(test, "bgcolor=",8)==0) ||
          (strncmp(test, "BGCOLOR=",8)==0) ||
  	  (strncmp(test, "bgcolor:",8)==0) ||
 	  (strncmp(test, "BGCOLOR:",8)==0) ||
	  (strncmp(test, "bgcolor =",9)==0) ||
          (strncmp(test, "BGCOLOR =",9)==0) ||
  	  (strncmp(test, "bgcolor :",9)==0) ||
 	  (strncmp(test, "BGCOLOR :",9)==0))
  {
   p=0;
   fputs("bgcolor=#FFFFFF ", writefile);
   do
   {
    p++;
    if((readfiledata[m+p] == ' ')||(readfiledata[m+p] == '>'))
    {
     m+=p;
     strcpy(test, NULL); //To prevent 'hey look, i found an image' over and over...
     break;
    }
   }while(readfiledata[m+p] != ' ');
  }
  else if((strncmp(test, "color=",6)==0) ||
          (strncmp(test, "COLOR=",6)==0) ||
  	  (strncmp(test, "color:",6)==0) ||
 	  (strncmp(test, "COLOR:",6)==0) ||
	  (strncmp(test, "color =",7)==0) ||
          (strncmp(test, "COLOR =",7)==0) ||
  	  (strncmp(test, "color :",7)==0) ||
 	  (strncmp(test, "COLOR :",7)==0))
  {
   p=0;
   fputs("color=#000000", writefile);
   do
   {
    p++;
    if((readfiledata[m+p] == ' ')||(readfiledata[m+p] == '>'))
    {
     m+=p;
     strcpy(test, NULL); //To prevent 'hey look, i found an image' over and over...
     break;
    }
   }while(readfiledata[m+p] != ' ');
  }  else if((strncmp(test, "size=",5)==0) ||
  	  (strncmp(test, "SIZE=",5)==0))
  {
   p=0;
   fputs("size=\"2\" ", writefile);
   do
   {
    p++;
    if((readfiledata[m+p] == ' ')||(readfiledata[m+p] == '>'))
    {
     m+=p;
     strcpy(test, NULL); //To prevent 'hey look, i found an image' over and over...
     break;
    }
   }while(readfiledata[m+p] != ' ');
  }
  else if(strncmp(test, "src=",4) ==0)
  {
   p=0;
   do
   {
    p++;
    if(readfiledata[m+p] == '"')
    {
     m+=p;
     strcpy(test,NULL);
     break;
    }
   }while(readfiledata[m+p] != '"');
  }
  else if((strncmp(test, "<SELECT",7) ==0) ||
          (strncmp(test, "<select",7) ==0))
  {
   p=0;
   do
   {
    p++;
   
    q=-1;


    do //transcribe the four
     test[q++] = readfiledata[(m+p)+q];
    while(q<9);

    printf("%s is test\n", test);

    if((strncmp(test,"</select>",9)==0)||(strncmp(test,"</SELECT>",9)==0))
    {
     p+=q;
     m+=p;
     m-=1;

#if DEBUG
     printf("m is %d, p is %d, q is %d\n",m,p,q);
     printf("test is %s\n",test);
#endif

     strcpy(test,NULL);
     break;
    }
   }while((strncmp(test,"</select>",9)!=0)||(strncmp(test,"</SELECT>",9)!=0));
  }
  else if((strncmp(test, "background=",11) ==0) ||
          (strncmp(test, "BACKGROUND=",11) ==0))
  {
   p=0;
   do
   {
    p++;
   
    q=-1;


/*
    do //transcribe the four
     test[q++] = readfiledata[(m+p)+q];
    while(q<9);
*/

    if(strncmp(test,"\"",1)==0)
    {
     p+=q;
     m+=p;
     m-=1;

#if DEBUG
     printf("m is %d, p is %d, q is %d\n",m,p,q);
     printf("test is %s\n",test);
#endif

     strcpy(test,NULL);
     break;
    }
   }while(strncmp(test,"\"",1)!=0);
  }
  else
  {


#if DEBUG
   printf("Writing char %c at readfile %d to assfrad.txt\n", readfiledata[m], m);
   sleep(3);
#endif

   fputc(readfiledata[m], writefile); //And write that char to the file
  }

 m++; //Inc main counter after loop

 }while((m+4)<size); //Don't let it look past the file
 





 return 1;
}





