#include&lt;stdio.h&gt;
#include&lt;sys/types.h&gt;
#include&lt;netinet/in.h&gt;
#include&lt;string.h&gt;
#include&lt;stdlib.h&gt;
#include&lt;unistd.h&gt;
int main(){
FILE *fp;
int sd, newsd, n, bd, port, clilen;
char fileread[100], rcv[100];
struct sockaddr_in servaddr, cliaddr;
printf(&quot;Enter the port address\n&quot;);
scanf(&quot;%d&quot;,&amp;port);
sd= socket(AF_INET, SOCK_STREAM, 0);
if(sd&lt;0){
printf(&quot;Can&#39;t create socket\n&quot;);
exit(0);
}
printf(&quot;Socket created\n&quot;);
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr =
htonl(INADDR_ANY);
servaddr.sin_port=htons(port);
bd=bind(sd,(struct sockaddr *) &amp;servaddr,
sizeof(servaddr));
if (bd&lt;0)
{
printf(&quot;Bind failed\n&quot;);
exit(0);
}
printf(&quot;Bind successful\n&quot;);
listen(sd,5);
clilen = sizeof(cliaddr);
newsd=accept(sd,(struct sockaddr
*)&amp;cliaddr,&amp;clilen);
if(newsd&lt;0)
{
printf(&quot;Accept failed\n&quot;);
exit(0);
}

printf(&quot;Connection accepted \n&quot;);
n = recv(newsd,rcv,100,0);
rcv[n]=&#39;\0&#39;;
fp=fopen(rcv,&quot;r&quot;);
if(fp==NULL)
{
send(newsd,&quot;error&quot;,5,0);
}
else{

while(fgets(fileread,sizeof(fileread),fp))
{
send(newsd, fileread, strlen(fileread),0);
sleep(1);
}
send(newsd,&quot;completed&quot;,9,0);
fclose(fp);
}
close (newsd);
close(sd);
return 0;
}
