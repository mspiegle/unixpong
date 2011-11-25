#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include <string>

using namespace std;

class Connection {
	private:
		int  fd;
	
	protected:
		bool __inet_bind(string ipport);
		bool __inet_bind(string ip, int port);
		bool __inet_bind(const char* ipport);
		bool __inet_bind(const char* ip, int port);
		bool __inet_bind(int port);

		bool __inet_connect(struct sockaddr_in* addr, int size);
		bool __inet_connect(const char* ip, int port);
		bool __inet_connect(const char* ipport);
		bool __inet_connect(string ipport);
		bool __inet_connect(string ip, int port);

	public:
		Connection();
		Connection(int fd);
		~Connection();

		bool Listen();
		Connection Accept();
		bool Send(void *buf, int size);
		bool Recv(void *buf, int size);

		virtual bool Bind(struct sockaddr *addr, int size);
		virtual bool Socket(int domain, int type, int protocol);
		virtual bool Connect(struct sockaddr *addr, int size);

};

class UdpConnection : public Connection {
	private:

	public:
		UdpConnection();
		~UdpConnection();

		bool Socket();

		bool Bind(string ipport);
		bool Bind(string ip, int port);
		bool Bind(const char *ipport);
		bool Bind(const char *ip, int port);
		bool Bind(int port);

		bool Connect(struct sockaddr_in *addr, int size);
		bool Connect(const char *ip, int port);
		bool Connect(const char *ipport);
		bool Connect(string ipport);
		bool Connect(string ip, int port);
};

class TcpConnection : public Connection {
	private:

	public:
		TcpConnection();
		~TcpConnection();
	
		bool Socket();

		bool Bind(string ipport);
		bool Bind(string ip, int port);
		bool Bind(const char *ipport);
		bool Bind(const char *ip, int port);
		bool Bind(int port);

		bool Connect(struct sockaddr_in *addr, int size);
		bool Connect(const char *ip, int port);
		bool Connect(const char *ipport);
		bool Connect(string ipport);
		bool Connect(string ip, int port);
};

class UnixConnection : public Connection {
	private:

	public:
		UnixConnection();
		~UnixConnection();
	
		bool Socket();
		
		bool Bind();
		bool Bind(string path);
		bool Bind(const char *path);

		bool Connect();
		bool Connect(struct sockaddr_un *addr, int size);
		bool Connect(string path);
		bool Connect(const char *path);
};

#endif /* _SOCKET_H_ */
