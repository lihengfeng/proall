/*************************************************************************
  > File Name: HttpServer.h
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Fri Nov 24 13:57:26 2017
 ************************************************************************/

#include"ThreadPool.h"
#include<string.h>
using namespace std;
class HttpServer{
	public:
		HttpServer(const char*name){
			sprintf(serverName,"Server: %s/0.1.0\r\n",name);
			pool.start(10);  //打开10个线程
		}
		explicit HttpServer(int threadNum,const char*name){
			sprintf(serverName,"Server: %s/0.1.0\r\n",name);
			pool.start(threadNum);  //打开10个线程
		}
		void listenPort(int port);
		void start();
		int getLine(int fd,char*buf,int size);
		void unimplemented(int client);
		void notFound(int client);
		void readRequest(int clientFd);  
		void headers(int clientFd);
		void cat(int clientFd,ifstream& fs); //发送文件内容
		void cat2(int clientFd,int fd); //发送文件内容
		void returnFile(int fd,const string& path);
		void returnFile2(int fd,const string& path);
		void cannot_execute(int client);  
		void bad_request(int client);
		void exec(int clientFd,const string& method,const string& path,const string& params);
private:
		int myPort=-1;
		int myFd=-1;
		ThreadPool pool; //创建线程池
		char serverName[128]; 
};

