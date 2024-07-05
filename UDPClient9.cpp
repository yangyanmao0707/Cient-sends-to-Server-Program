#include <iostream>
#include <winsock2.h>
#include <stdio.h>  
#include <stdlib.h>  
#include <math.h>
using namespace std;

#pragma comment(lib,"ws2_32.lib") 
#pragma warning(disable:4996) 

#define SERVER "127.0.0.1"  // or "localhost" - ip address of UDP server
#define BUFLEN 512  // max length of answer
#define PORT 8888  // the port on which to listen for incoming data

int main()
{
    system("title UDP Client");

    // initialise winsock
    WSADATA ws;
    printf("Initialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
    {
        printf("Failed. Error Code: %d", WSAGetLastError());
        return 1;
    }
    printf("Initialised.\n");

    // create socket
    sockaddr_in server;
    int client_socket;
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) // <<< UDP socket
    {
        printf("socket() failed with error code: %d", WSAGetLastError());
        return 2;
    }

    // setup address structure
    memset((char*)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.S_un.S_addr = inet_addr(SERVER);

    // start communication
    while (true)
    {
        char a[BUFLEN];
        char b[BUFLEN];
        char c[BUFLEN];

        float x1,x2,d;
        printf("a = ");
        cin.getline(a, BUFLEN);
        printf("b = ");
        cin.getline(b, BUFLEN);
        printf("c = ");
        cin.getline(c, BUFLEN);


        // send the message
        if (sendto(client_socket, a, strlen(a), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR && sendto(client_socket, b, strlen(b), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR && sendto(client_socket, c, strlen(c), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR)
        {
            printf("sendto() failed with error code: %d", WSAGetLastError());
            return 3;
        }

        // receive a reply and print it
        // clear the answer by filling null, it might have previously received data
        char answer[BUFLEN] = {};

        // try to receive some data, this is a blocking call
        int slen = sizeof(sockaddr_in);
        int answer_length;
        if (answer_length = recvfrom(client_socket, answer, BUFLEN, 0, (sockaddr*)&server, &slen) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code: %d", WSAGetLastError());
            exit(0);
        }
        
        	char *output;
		    
		    float a1 = strtol(a, &output, 10);
		    float b1 = strtol(b, &output, 10);
		    float c1 = strtol(c, &output, 10);
		    float q,p,s = b1 * b1 - 4*a1*c1;

		    
		    if (s > 0)
	    	{
	    		
	    		cout <<"兩相異實根"<< "\n";
	    		
		    	d=sqrt(s);
				//正解 
				x1=(-b1+d)/(2*a1);
				//負解 
				x2=(-b1-d)/(2*a1);   
			             	
				cout << "ans = "<< x1 <<" "<<"or"<<" "<< x2 << "\n";
			}
			else if (s < 0)
			{
				
				cout <<"兩共軛虛根"<< "\n";
				
				q = -b1 / (2 * a1);
				p = sqrt(-s) / (2 * a1); 
				
				cout << "ans = " << "\n";
				cout << q <<" "<< "+" <<" "<< p << "i" << "\n";
				cout << q <<" "<< "-" <<" "<< p << "i" << "\n";
				 
			}	
			else if (s == 0)
			
			{
				
				cout <<"兩相等實根"<< "\n";
				
				d=sqrt(s);
				//正解 
				x1=(-b1+d)/(2*a1);
				//負解 
				x2=(-b1-d)/(2*a1);   
				             	
				cout << "ans = "<< x1 <<" "<<"and"<<" "<< x2 << "\n";
			}		    

	    }

    closesocket(client_socket);
    WSACleanup();
}
