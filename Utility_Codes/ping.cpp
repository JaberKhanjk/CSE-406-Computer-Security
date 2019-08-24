/*** from dust i have come, dust i will be ***/

#include<bits/stdc++.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip_icmp.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>
#include<signal.h>

using namespace std;

struct packet
{
    struct icmphdr header;
    string msg;
};

int main()
{
    int sockfd;
    string ip_address, reverse_hostname;
    struct sockaddr_in addr_con;


    return 0;
}
