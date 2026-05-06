#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main()
{
    FILE *fp;
    int csd, s, cport;
    char name[100], rcvg[100], fname[100];
    struct sockaddr_in servaddr;

    printf("Enter the port: ");
    scanf("%d",&cport);

    csd = socket(AF_INET,SOCK_STREAM,0);
    if(csd<0)
    {
        printf("Socket creation failed\n");
        exit(0);
    }

    printf("Socket created\n");

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(cport);

    if(connect(csd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0)
    {
        printf("Connection failed\n");
        exit(0);
    }

    printf("Connected\n");

    printf("Enter existing file name: ");
    scanf("%s",name);

    printf("Enter new file name: ");
    scanf("%s",fname);

    fp = fopen(fname,"w");

    send(csd,name,strlen(name),0);

    while(1)
    {
        s = recv(csd,rcvg,100,0);
        rcvg[s] = '\0';

        if(strcmp(rcvg,"error")==0)
        {
            printf("File not available\n");
            break;
        }
        else if(strcmp(rcvg,"completed")==0)
        {
            printf("File transfer completed\n");
            break;
        }
        else
        {
            printf("%s",rcvg);
            fprintf(fp,"%s",rcvg);
        }
    }

    fclose(fp);
    close(csd);

    return 0;
}
