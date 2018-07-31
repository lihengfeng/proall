#ifndef ACCEPTSOCKETMANAGER_H
#define ACCEPTSOCKETMANAGER_H

#include<netxy/net/Manager.h>

#include"unistd.h"

namespace netxy{
	namespace net{
		class AcceptSocketManager :public Manager{
			public:
				typedef std::function<void(int)> AcceptCallback;

				AcceptSocketManager(int fid,Epoller* ep):Manager(fid,ep){
					isConnecting=true;
				};

				AcceptSocketManager(AcceptSocketManager& other) = delete;
				AcceptSocketManager& operator=(AcceptSocketManager& other) = delete;
				~AcceptSocketManager(){}

				void doRead();
				void setAcceptCallback(const AcceptCallback& cb){
					acceptCallback=cb;
				}
			private:
				AcceptCallback acceptCallback;
		};
	}
}

#endif
