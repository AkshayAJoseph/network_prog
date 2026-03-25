#include&lt;stdio.h&gt;
#include&lt;stdlib.h&gt;

#include&lt;unistd.h&gt;
#define NOF_PACKETS 10
int rd(int a)
{
int rn = (random() % 10) % a;
return rn == 0 ? 1 : rn;
}
int main()
{
int packet_sz[NOF_PACKETS], i, clk,
b_size, o_rate, p_sz_rm=0, p_sz, p_time,
op;
for(i = 0; i&lt;NOF_PACKETS; ++i)
packet_sz[i] = rd(6) * 10;
for(i = 0; i&lt;NOF_PACKETS; ++i)
printf(&quot;\npacket[%d]:%d bytes\t&quot;, i,
packet_sz[i]);
printf(&quot;\nEnter the Output rate:&quot;);
scanf(&quot;%d&quot;, &amp;o_rate);
printf(&quot;Enter the Bucket Size:&quot;);
scanf(&quot;%d&quot;, &amp;b_size);
for(i = 0; i&lt;NOF_PACKETS; ++i)
{
if( (packet_sz[i] + p_sz_rm) &gt; b_size)
if(packet_sz[i] &gt; b_size)
printf(&quot;\n\nIncoming packet size (%dbytes)
is Greater than bucket capacity (%dbytes)-
PACKET REJECTED&quot;, packet_sz[i],
b_size);
else
printf(&quot;\n\nBucket capacity exceeded-
PACKETS REJECTED!!&quot;);
else
{
p_sz_rm += packet_sz[i];
printf(&quot;\n\nIncoming Packet size: %d&quot;,
packet_sz[i]);
printf(&quot;\nBytes remaining to Transmit: %d&quot;,
p_sz_rm);
p_time = rd(4) * 10;
printf(&quot;\nTime left for transmission: %d
units&quot;, p_time);
for(clk = 10; clk &lt;= p_time; clk += 10)

{
sleep(1);
if(p_sz_rm)
{
if(p_sz_rm &lt;= o_rate)
op = p_sz_rm, p_sz_rm = 0;
else
op = o_rate, p_sz_rm -= o_rate;
printf(&quot;\nPacket of size %d Transmitted&quot;,
op);
printf(&quot;----Bytes Remaining to Transmit:
%d&quot;, p_sz_rm);
}
else
{
printf(&quot;\nTime left for transmission: %d
units&quot;, p_time-clk);
printf(&quot;\nNo packets to transmit!!&quot;);
}
}
}
}
}
