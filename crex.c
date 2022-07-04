#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BUF 4095

int main(int argc, char *argv[])
{
	clock_t start, end;
    start = clock();
    int i = 0;
    char com_args[MAX_BUF] = "";
    FILE *ptr;
    char line[MAX_BUF];
    char *token;
    char *find_ptr;
    char resamp_id[MAX_BUF];
    char resamp_path[MAX_BUF];
    char flag[MAX_BUF];
    int sys_ret;
    char working_path[MAX_BUF];
    char tmp[MAX_BUF] = "\"";
    int x = 0, len, j;
    
    printf("crex ver0.2 - Resampler Extended Rewrite in C.\n");
    printf("Copyright ookamitai, 2022. All rights reserved.\n");
    strcpy(working_path, argv[0]);
    strcat(working_path, "\\..");
    //printf("config> Set working directory as %s.\n", working_path);
    
    strcat(working_path, "\\crexcfg.txt");
    //printf("config> Try to read %s.\n", working_path);
    ptr = fopen(working_path, "r");
    
    if (ptr == NULL)
    {
    	printf("config> Configuration file cannot be found.\n");
    	return 2;
	}
    
	//printf("parser> Received %d arguments.\n", argc-1);
    
    if (argc == 1)
    {
    	printf("crex only works as a backend for UTAU.\n");
    	system("pause>nul");
    	return 3;
	}
	
	if (argc != 1 && argc < 8)
    {
    	printf("parser> Not enough arguments.\n");
    	system("pause>nul");
    	return 3;
	}
	
	strcat(tmp, argv[1]);
	strcat(tmp, "\"");
	strcpy(argv[1], tmp);
	
	strcpy(tmp, "\"");
	strcat(tmp, argv[2]);
	strcat(tmp, "\"");
	strcpy(argv[2], tmp);
    
    for(i = 1; i < argc; i++)
    {
        strcat(com_args, " ");
        strcat(com_args, argv[i]);
    }
    
    //printf("parser> Arguments are%s\n", com_args);
    
    strcpy(flag, argv[5]);
    //printf("parser> Flag is %s.\n", flag);
	len = strlen(flag);
	   	
  	while(x < len)
	{
		if(flag[x] == '/')
		{
			j = x;
			while(j < len)
			{
				flag[j] = flag[j + 1];
				j++;
			}
			len--;
			x--;	
		}
		x++; 
	}	
	
	printf("parser> FLAG->%s.\n", flag);
	
    while (fgets(line, MAX_BUF, ptr) != NULL)
	{
        //printf("config> Read line: %s", line);
		find_ptr = strstr(line, "=");
		if (find_ptr != NULL)
		{
			//printf("config> Found identifier at %p\n", find_ptr);
			token = strtok(line, "=");
			strcpy(resamp_id, token);
			resamp_id[strcspn(resamp_id, "\n")] = 0;
			token = strtok(NULL, "=");
			strcpy(resamp_path, token);
			resamp_path[strcspn(resamp_path, "\n")] = 0;
			printf("config> %s->%s.\n", resamp_id, resamp_path);
		}	
	}
	ptr = fopen(working_path, "r");
    while (fgets(line, MAX_BUF, ptr) != NULL)
	{
        //printf("config> Read line: %s", line);
		find_ptr = strstr(line, "=");
		if (find_ptr != NULL)
		{
			//printf("config> Found identifier at %p\n", find_ptr);
			token = strtok(line, "=");
			strcpy(resamp_id, token);
			resamp_id[strcspn(resamp_id, "\n")] = 0;
			token = strtok(NULL, "=");
			strcpy(resamp_path, token);
			resamp_path[strcspn(resamp_path, "\n")] = 0;
			if (strstr(flag, resamp_id) != NULL)
			{
				printf("main> Use resampler id %s.\n", resamp_id);
				break;
			}
		}	
	}
	
    strcat(resamp_path, com_args);
    strcat(resamp_path, "> nul");
    //printf("main> Command to be excuted: %s\n", resamp_path);
    sys_ret = system(resamp_path); 
    end = clock();
    printf("Process exited after %d msec with return value %d\n", (end - start), sys_ret);
    return 0;
}
