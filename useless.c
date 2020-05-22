#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

#define PERROR(name, args...) \
	do {printf(args); usage(name);} while(0)

void usage(char * name);

int main(int argc, char *argv[], char *envp[])
{
    /*two command-line arguments: 
    1. the name of the executable file
    2. the file with the list of programs with delay*/

    if (argc != 2)
      PERROR(argv[0], "Wrong number of arguments!\n\n");

    FILE *f_input;
    int j = 1;
    f_input = fopen(argv[1], "r"); /*open file for reading*/
    int mode;
    fscanf(f_input, "%d", &mode);
    if (mode == 0)
    {
        // BSM
        printf("BSM!\n");
        FILE *f_test;
        f_test = fopen("test.txt", "w");
        fprintf(f_test, "%s", "main_bsm");
        fclose(f_test);
    }
    else if (mode == 1)
    {
      // BSM
      printf("Hedging!\n");
      FILE *f_test;
      f_test = fopen("test.txt", "w");
      fprintf(f_test, "%s", "main_delta");
      fclose(f_test);
    }
    
    
    
    if (f_input == NULL) 
      PERROR(argv[0], "Incorrect input file!\n\n"); /*an error occurs when you try to open a file*/

    int t = 0; /*time*/
    int ret = 0; /*the number of arguments accepted*/
    char str[FILENAME_MAX] = {};
    while ((ret = fscanf(f_input, "%d %[^\n]%*c", &t, str)) == 2) 
    {
		  printf("%s is executed with delay %d\n", str, t);
      
      if (t < 0)
      PERROR(argv[0], "Incorrect format of input data! Time t = %d seconds for process %s takes a negative value!\n\n", t, str);

    
      pid_t pid = fork(); /*create process*/
		  if (pid == -1)
      {
			  assert(!"Fork failure!");
		  }
      else if (pid == 0)
      {
			  printf("%s is executed in child\n", str);
			  sleep(t);
        /*divide string into part to work with double programms*/
        char *istr;
        char sep[10]= " ";
        istr = strtok(str, sep);

        istr = strtok(NULL, sep);

        if (istr == NULL)
        {
            /*single program*/
            execlp(str, str, NULL);
			      printf("\"%s\" is failed!\n", str); /* execlp returns the control -> error */ 
			      exit(EXIT_FAILURE); /*exit(1)*/
        }
        else if (istr != NULL)
        {
            /*program with one command-line argument*/
            execlp(str, str, istr, NULL);
            printf("\"%s\" is failed!\n", str);  
			      exit(EXIT_FAILURE);
        }
		  }
    }

    while (wait(NULL) != -1) {}; /*wait until all child processes complete their work, 
    at the same time remove the zombies*/

    if (!feof(f_input)) 
      PERROR(argv[0], "File format is incorrect! %d parameters was read\n\n", ret);
    return 0;
}

void usage(char * name)
{
	assert (name);

	printf("Usage: %s <filename>\n"
		"<filename> type:\n"
		"<t : time in seconds> <program executed> <one possible arguments of command-line>\n"
    "Example: %s input.txt\n"
    "2 mkdir FOLDER - create new directory <FOLDER> with a delay of 2 second \n",
		name, name);

	exit(EXIT_FAILURE);
}

