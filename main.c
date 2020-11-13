#include "httpd.h"
#include <sys/stat.h>
#include <sys/types.h>

int main(int c, char** v)
{
    serve_forever("12913");
    return 0;
}



void handle_request(char *pIdentfier, char *pUri)
{
		char command[100]={'\0'};
		char gstreamCommond[2048]={'\0'};
		FILE *fptr=NULL; char fname[100]={"test.sh"};
		
		if( 0==strncmp(pIdentfier,"media=", strlen("media="))) 
		{
			printf("2 ident=%s,puri=%s\n",pIdentfier,pUri);
			char * token, * last;
			last = token = strtok(pUri, "/");
			for (;(token = strtok(NULL, "/")) != NULL; last = token);
						
			remove("test.sh");
			char * token1, * last1;
			last1 = token1 = strtok(pIdentfier, "=");
			for (;(token1 = strtok(NULL, "=")) != NULL; last1 = token1);
			
			fptr = fopen (fname,"w");
			fputs("#!/bin/bash\n",fptr);
			fputs("echo \"Streaming Invoked\"\n",fptr);
			snprintf(gstreamCommond,2048,"/usr/bin/gst-launch-1.0 rtspsrc location=%s ! rtph264depay name=demux ! h264parse ! avdec_h264 ! videoconvert ! glimagesink & \n",last1);
			
			fputs(gstreamCommond,fptr);
			fputs("echo \"Streaming Ended\"\n",fptr);
			fputs("sleep 30\n",fptr);
			fputs("echo \"Dying\"\n",fptr);
			fclose(fptr);
			char mode[] = "0777";
    		int i=strtol(mode, 0, 8);
			chmod(fname,i);
		
			 strcpy(command,"sh ");
			 strcat(command,fname);
			 system(command);
		
		}
		


}
