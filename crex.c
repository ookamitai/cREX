#include <stdio.h>
#include <string.h>

#define MAX_BUF 4095

int main(int argc, char *argv[])
{
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
    
    strcpy(working_path, argv[0]);
    strcat(working_path, "\\..");
    /*printf("config> Set working directory as %s.\n", working_path);*/
    
    strcat(working_path, "\\crexcfg.txt");
    /*printf("config> Try to read %s.\n", working_path);*/
    ptr = fopen(working_path, "r");
    
    if (ptr == NULL)
    {
    	printf("config> Configuration file cannot be found.\n");
    	return 2;
	}
    
	/*printf("parser> Received %d arguments.\n", argc-1);*/
    
    if (argc < 8)
    {
    	printf("parser> Not enough arguments.\n");
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
        /* printf("%s\n", argv[i]); */
        strcat(com_args, " ");
        strcat(com_args, argv[i]);
    }
    
    /*printf("parser> Arguments are%s\n", com_args);*/
    
    strcpy(flag, argv[5]);
    /*printf("parser> Flag is %s.\n", flag);*/
    
	
    while (fgets(line, 255, ptr) != NULL)
	{
        /*printf("config> Read line: %s", line);*/
		find_ptr = strstr(line, "=");
		if (find_ptr != NULL)
		{
			/*printf("config> Found identifier at %p\n", find_ptr);*/
			token = strtok(line, "=");
			strcpy(resamp_id, token);
			resamp_id[strcspn(resamp_id, "\n")] = 0;
			token = strtok(NULL, "=");
			strcpy(resamp_path, token);
			resamp_path[strcspn(resamp_path, "\n")] = 0;
			/*printf("config> Registered %s as %s.\n", &resamp_path, &resamp_id);*/
			if (strstr(flag, resamp_id) != NULL)
			{
				break;
			}
		}	
	}


    strcat(resamp_path, com_args);
    /*printf("parser> Command to be excuted: %s.\n", resamp_path);*/
    
    sys_ret = system(resamp_path);
    /*printf("\nProcess finished with return value %d.\n", &sys_ret);*/
    return 0;
}
