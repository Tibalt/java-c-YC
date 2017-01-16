#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#define DEBUG 0
#define BUFFER 4096

//open ap.txt for text input
static const char* exFile = "ap.txt";
static char inputBuffer[BUFFER];

int main(int argc, const char** argv)
{
   FILE *fp = fopen(exFile,"r");
   /*check and see if the pointer is null in otherwords see if the memory location
   refered to by fp is set...no memory location should be zero if you want to reference
   it	 
   
   Here are some good ways to do this other than the way I did it below:
   if(!fp) {do error}
   if(fp == NULL) {do error}
   and then there's the way I did it below
   */
   
   if(fp == 0){
      fprintf(stderr,"Null pointer exception, check file name.\n");
      exit(-1);
   }

   //check and see if an error occured during open
   const int err = ferror(fp);
   if(err != 0){
      /*
	 void perror(const char* err)
	 returns specific error message to string attached.

      */
      const char* errMessage = strcat("Something bad happened while opening file ",exFile);
      perror(errMessage);
   }
#if (DEBUG == 1)   
else
{
      fprintf(stderr,"Success opening file!!\n");
}
#endif




setbuf(fp,inputBuffer); //set a buffer for input

uint64_t *num = (uint64_t*) malloc(sizeof(uint64_t));
uint64_t total = 0;
uint64_t n = 0;

//test for eof
/*
feof(*fp) - returns a boolean true if at end of file and false otherwise
*/

while(!feof(fp)){
   //fscanf returns the number of items it converted using %llu, if it's not equal to 1 we don't want to continue
   if(fscanf(fp,"%"PRIu64"",num)!=1)
      break; //you could do a lot of stuff here as far as error handling but basically something bad has happened
   total+= *num; //add to total the value at memory location num
   n++;
#if (DEBUG == 1)   
   fprintf(stderr,"line number %"PRIu64"\n",n);
#endif 
}

free(num);

const double average = (double) total / (double) n;
//close the inputfile
fclose(fp);

//declare our outputfile, use a pipe in this case to a java process
//we open a java process for this process to pipe to, also it is 
//technically a bi-directional pipe so we can use any of the modifiers
//like r/w/r+/etc
static const char* outFile = "java -cp . StreamTest";

FILE *fp_out = popen(outFile,"w");
//setbuf(fp_out,outputBuffer);

fprintf(fp_out,"Total: %"PRIu64", Integers: %"PRIu64", Average: %.4f\n",total,n,average);



/*
int fflush(*fp) pushes any data in the buffer to be written
the return value returns 0 if successful or !=0 if an error 
occurs....remember return values in C often equal exceptions

*/   
   fflush(fp_out);

/*

int 

*/
   fclose(fp_out);

   return 1;
}
