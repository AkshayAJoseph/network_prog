#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    FILE *fp;
    int sd, newsd, n, bd, port, clilen;
    char fileread[100], rcv[100];
    struct sockaddr_in servaddr, cliaddr;

    printf("Enter the port address\n");
    scanf("%d",&port);

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if(sd<0){
        printf("Can't create socket\n");
        exit(0);
    }

    printf("Socket created\n");

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    bd = bind(sd,(struct sockaddr *) &servaddr, sizeof(servaddr));
    if (bd<0)
    {
        printf("Bind failed\n");
        exit(0);
    }

    printf("Bind successful\n");

    listen(sd,5);

    clilen = sizeof(cliaddr);
    newsd = accept(sd,(struct sockaddr *)&cliaddr, &clilen);

    if(newsd<0)
    {
        printf("Accept failed\n");
        exit(0);
    }

    printf("Connection accepted \n");

    n = recv(newsd,rcv,100,0);
    rcv[n] = '\0';

    fp = fopen(rcv,"r");

    if(fp==NULL)
    {
        send(newsd,"error",5,0);
    }
    else
    {
        while(fgets(fileread,sizeof(fileread),fp))
        {
            send(newsd, fileread, strlen(fileread),0);
            sleep(1);
        }

        send(newsd,"completed",9,0);
        fclose(fp);
    }

    close(newsd);
    close(sd);

    return 0;
}
