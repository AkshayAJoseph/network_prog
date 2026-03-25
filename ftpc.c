#include&lt;stdio.h&gt;
#include&lt;stdlib.h&gt;
#include&lt;sys/socket.h&gt;
#include&lt;netinet/in.h&gt;
#include&lt;unistd.h&gt;
#include&lt;string.h&gt;
#include&lt;arpa/inet.h&gt;
int main()
{
FILE *fp;
int csd, s, cport;
char name[100], rcvg[100], fname[100];
struct sockaddr_in servaddr;
printf(&quot;Enter the port: &quot;);
scanf(&quot;%d&quot;,&amp;cport);
csd = socket(AF_INET,SOCK_STREAM,0);
if(csd&lt;0)
{
printf(&quot;Socket creation failed\n&quot;);
exit(0);
}
printf(&quot;Socket created\n&quot;);
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr =
inet_addr(&quot;127.0.0.1&quot;);
servaddr.sin_port = htons(cport);
if(connect(csd,(struct sockaddr
*)&amp;servaddr,sizeof(servaddr))&lt;0)
{
printf(&quot;Connection failed\n&quot;);
exit(0);
}
printf(&quot;Connected\n&quot;);
printf(&quot;Enter existing file name: &quot;);
scanf(&quot;%s&quot;,name);
printf(&quot;Enter new file name: &quot;);
scanf(&quot;%s&quot;,fname);
fp = fopen(fname,&quot;w&quot;);
send(csd,name,strlen(name),0);
while(1)
{
s = recv(csd,rcvg,100,0);
rcvg[s]=&#39;\0&#39;;

if(strcmp(rcvg,&quot;error&quot;)==0)
{
printf(&quot;File not available\n&quot;);
break;
}

else if(strcmp(rcvg,&quot;completed&quot;)==0)
{
printf(&quot;File transfer completed\n&quot;);
break;
}

else
{
printf(&quot;%s&quot;,rcvg);
fprintf(fp,&quot;%s&quot;,rcvg);
}
}
fclose(fp);
close(csd);
return 0;
}
