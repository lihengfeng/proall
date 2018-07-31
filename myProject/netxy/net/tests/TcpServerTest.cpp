/*************************************************************************
	> File Name: TcpServerTest.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Fri Oct 13 12:06:04 2017
 ************************************************************************/

#include<netxy/net/Epoller.h>
#include<netxy/net/TcpServer.h>
#include<string>

using namespace netxy::net;
using namespace std;

int main(){
	Epoller ep;
	TcpServer ts(&ep,10);
	ts.setMessageCallback([](ConnectSocketManager* csm){
			cout<<csm->in_buffer.readAll()<<endl;
			csm->send("用户不在线，请稍后联系");
	});
	for(int i=0;i<10;i++)
	{
		int s=9999-i;
		ts.listen(s);
	}
	ts.start();
}
