#include "httpd.h"

int main(int c, char** v)
{
    serve_forever("12913");
    return 0;
}



void handle_request(char *pIdentfier, char *pUri)
{
		char command[100]={'\0'};
		if( 0==strcmp(pIdentfier,"media=play")) 
		{
			char * token, * last;
			last = token = strtok(pUri, "/");
			for (;(token = strtok(NULL, "/")) != NULL; last = token);
			printf("%s\n", last);
			strcpy(command,"sh ");
			strcat(command,last);
			system(command);
		
		}
		


}
