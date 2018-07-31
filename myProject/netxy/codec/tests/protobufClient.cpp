
#include"Person.pb.h"

#include<netxy/net/ConnectSocketManager.h>
#include<netxy/net/TcpClient.h>
#include<netxy/codec/ProtobufDispatcher.h>
#include<netxy/codec/ProtobufCodec.h>

#include<iostream>
#include<sstream>
#include<string>
#include<vector>

using namespace std;


using namespace netxy::base;
using namespace netxy::net;
using namespace netxy::codec;

typedef	shared_ptr<ConnectSocketManager> ConnectSocketManagerPtr;
int main(){
	Person person;
	School school;
	Book book;

	ProtobufDispatcher dispathcher;
	ProtobufCodec  encode(dispathcher);
	TcpClient tc;
	
	vector<ConnectSocketManagerPtr> v;
	v.reserve(40);

	for(int i=0;i<5;i++){
		ConnectSocketManagerPtr cp=tc.connect("127.0.0.1",9999-i);
		if(cp){
			v.push_back(cp);
		}
		else
			cout<<"csf"<<i<<"为空, port="<<9999-i<<endl;
	}
	int id;
	std::string name;
	std::string email;
	std::string address;
	std::string author;
	while(true){
		cout<<"input id"<<endl;
		while(1)
		{
			cin>>id;

			if(cin.fail()) //如果输入不匹配，fail()会返回真
			{
				cout<<"不是int," ;			
				cin.clear();  //清除fail状态	
			//	cin.sync();   //清除缓冲区,但这里不起作用
				cin.ignore();
				cout<<"重输:";
				continue;
			}
			else
				break;

		}
		person.set_id(id);

		cout<<"input name email"<<endl;
		cin>>name>>email;
		person.set_email(email);
		for(int i=0;i<v.size();i++){
			string nameNum=name+":"+to_string(i);
			person.set_name(nameNum);
			encode.send(v[i].get(),person);
		}
		cout<<"input name address"<<endl;
		cin>>name>>address;
		school.set_address(address);
		for(int i=0;i<v.size();i++){
			string nameNum=name+":"+to_string(i);
			school.set_name(nameNum);
			encode.send(v[i].get(),school);
		}
		cout<<"input name author"<<endl;
		cin>>name>>author;
		book.set_author(author);
		for(int i=0;i<v.size();i++){
			string nameNum=name+":"+to_string(i);
			book.set_name(nameNum);
			encode.send(v[i].get(),book);
		}
	}
	cout<<"end"<<endl;
}
