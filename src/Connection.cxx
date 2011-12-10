#include "Connection.hxx"
#include "Common.hxx"

#include <string>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>

using namespace std;

Connection::Connection() {
	this->fd = 0;
	signal(SIGPIPE, SIG_IGN);
}

Connection::Connection(int fd) {
	this->fd = fd;
}

Connection::~Connection() {
	close(this->fd);
}

bool
Connection::__inet_bind(string ipport) {
	size_t pos;

	if ( string::npos == ( pos = ipport.rfind(":")) )
		return false;

	string ip    = ipport.substr(0, pos);
	string sport = ipport.substr(pos, string::npos);

	int port = atoi(sport.c_str());

	if ( Connection::__inet_bind(ip.c_str(), port) )
		return true;
        
	return false;
}

bool
Connection::__inet_bind(string ip, int port) {
	if ( Connection::__inet_bind(ip.c_str(), port) )
		return true;
        
	return false;
}

bool
Connection::__inet_bind(const char* ipport) {
	char* pos;
	char* buf = NULL;
	
	if ( NULL == (buf = strdup(ipport)) )
		return false;

	if ( NULL == (pos = strrchr(buf, ':')) )
		return false;
        
	//turn ":" into null to create 2 strings
	//possibly dirty?
	*pos = '\0';

	const char* ip = buf;
	int port = atoi(pos + 1);

	if ( Connection::__inet_bind(ip, port) ) {
		free(buf);
		return true;
	}

	free(buf);   
	return false;
}

bool
Connection::__inet_bind(const char* ip, int port) {
	struct sockaddr_in addr;
	bzero(&addr, sizeof(struct sockaddr_in));

	addr.sin_family = PF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);

	if ( Connection::Bind((struct sockaddr*)&addr, sizeof(struct sockaddr_in)) )
		return true;
        
	return false;
}

bool
Connection::__inet_bind(int port) {
	const char* ip = "0.0.0.0";

	if ( Connection::__inet_bind(ip, port) )
		return true;
        
	return false;
}

bool
Connection::__inet_connect(struct sockaddr_in* addr, int size) {
	if ( Connection::Connect((struct sockaddr*)addr, size) )
		return true;

	return false;
}

bool
Connection::__inet_connect(const char* ip, int port) {
	struct sockaddr_in addr;
	bzero(&addr, sizeof(struct sockaddr_in));

	addr.sin_family = PF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(port);

	if ( Connection::__inet_connect(&addr, sizeof(struct sockaddr_in)) )
		return true;
        
	return false;
}

bool
Connection::__inet_connect(const char* ipport) {
	char* pos;
	char* buf = NULL;

	if ( NULL == (buf = strdup(ipport)) )
		return false;

	if ( NULL == (pos = strrchr(buf, ':')) )
		return false;
        
	//turn ":" into null to create 2 strings
	//dirty?
	*pos = '\0';

	const char* ip = buf;
	int port = atoi(pos + 1);

	if ( Connection::__inet_connect(ip, port) ) {
		free(buf);
		return true;
	}

	free(buf);
	return false;
}

bool
Connection::__inet_connect(string ip, int port) {
	if ( Connection::__inet_connect(ip.c_str(), port) )
		return true;
        
	return false;
}

bool
Connection::__inet_connect(string ipport) {
	size_t pos;

	if ( string::npos == ( pos =  ipport.rfind(":")) )
		return false;

	string ip    = ipport.substr(0, pos);
	string sport = ipport.substr(pos, string::npos);

	int port = atoi(sport.c_str());

	if ( Connection::__inet_connect(ip.c_str(), port) )
		return true;
        
	return false;
}

bool
Connection::Bind(struct sockaddr* addr, int size) {
	if ( -1 != bind(this->fd, addr, size))
		return true;

	return false;
}

Connection
Connection::Accept() {
	return Connection(accept(this->fd, NULL, NULL));
}

bool
Connection::Send(void* buf, int size) {
	int bs = 0;

	while ( bs < size ) {
		if ( 0 >= (bs += write(this->fd, buf, size)) )
			return false;
	}

	return true;
}

bool
Connection::Recv(void* buf, int size) {
	int bw = 0;

	while ( bw < size ) {
		if ( 0 >= (bw += read(this->fd, buf, size)) )
			return false;
	}

	return true;
}

bool
Connection::Listen() {
	if ( -1 != listen(this->fd, CON_LIMIT) )
		return true;
	
	return false;
}

bool
Connection::Connect(struct sockaddr* addr, int size) {
	if ( -1 != connect(this->fd, addr, size) )
		return true;
	
	return false;
}

bool
Connection::Socket(int domain, int type, int protocol) {
	if ( -1 != (this->fd = socket(domain, type, protocol)) )
		return true;
	
	return false;
}

UdpConnection::UdpConnection() { }

UdpConnection::~UdpConnection() { }

bool
UdpConnection::Socket() {
	if ( Connection::Socket(PF_INET, SOCK_DGRAM, 0) )
		return true;

	return false;
}

bool
UdpConnection::Bind(string ipport) {
	if ( Connection::__inet_bind(ipport) )
		return true;
        
	return false;
}

bool
UdpConnection::Bind(string ip, int port) {
	if ( Connection::__inet_bind(ip, port) )
		return true;

	return false;
}

bool
UdpConnection::Bind(const char* ipport) {
	if ( Connection::__inet_bind(ipport) )
		return true;

	return false;
}

bool
UdpConnection::Bind(const char* ip, int port) {
	if ( Connection::__inet_bind(ip, port) )
		return true;

	return false;
}

bool
UdpConnection::Bind(int port) {
	if ( Connection::__inet_bind(port) )
		return true;

	return false;
}

bool
UdpConnection::Connect(struct sockaddr_in* addr, int size) {
	if ( Connection::__inet_connect(addr, size) )
		return true;

	return false;
}

bool
UdpConnection::Connect(const char* ip, int port) {
	if ( Connection::__inet_connect(ip, port) )
		return true;

	return false;
}

bool
UdpConnection::Connect(const char* ipport) {
	if ( Connection::__inet_connect(ipport) )
		return true;

	return false;
}

bool
UdpConnection::Connect(string ipport) {
	if ( Connection::__inet_connect(ipport) )
		return true;

	return false;
}

bool
UdpConnection::Connect(string ip, int port) {
	if ( Connection::__inet_connect(ip, port) )
		return true;

	return false;
}

TcpConnection::TcpConnection() { }

TcpConnection::~TcpConnection() { }

bool
TcpConnection::Bind(const char* ip, int port) {
	if ( Connection::__inet_bind(ip, port) )
		return true;
	
	return false;
}

bool
TcpConnection::Bind(string ipport) {
	if ( Connection::__inet_bind(ipport) )
		return true;
	
	return false;
}

bool
TcpConnection::Bind(string ip, int port) {
	if ( Connection::__inet_bind(ip, port) )
		return true;
	
	return false;
}

bool
TcpConnection::Bind (const char* ipport) {
	if ( Connection::__inet_bind(ipport) )
		return true;
	
	return false;
}


bool
TcpConnection::Bind(int port) {
	if ( Connection::__inet_bind(port) )
		return true;
	
	return false;
}

bool
TcpConnection::Socket() {
	if ( Connection::Socket(PF_INET, SOCK_STREAM, 0) )
		return true;
	
	return false;
}

bool
TcpConnection::Connect(struct sockaddr_in* addr, int size) {
	if ( Connection::__inet_connect(addr, size) )
		return true;

	return false;
}

bool
TcpConnection::Connect(const char* ip, int port) {
	if ( Connection::__inet_connect(ip, port) )
		return true;
	
	return false;
}

bool
TcpConnection::Connect(const char* ipport) {
	if ( Connection::__inet_connect(ipport) )
		return true;
	
	return false;
}

bool
TcpConnection::Connect(string ipport) {
	if ( Connection::__inet_connect(ipport) )
		return true;
	
	return false;
}

bool
TcpConnection::Connect(string ip, int port) {
	if ( Connection::__inet_connect(ip, port) )
		return true;
	
	return false;
}


UnixConnection::UnixConnection() { }

UnixConnection::~UnixConnection() {
}

bool
UnixConnection::Bind(const char* path) {
	struct sockaddr_un addr;
	bzero(&addr, sizeof(struct sockaddr_un));
	
	struct stat buf;

	//if the socket already exists
	//we should try to remove it
	if ( -1 != stat(path, &buf) )
		if ( -1 == unlink(path) )
			return false;
	
	addr.sun_family = AF_UNIX;
	//sockaddr_un.sun_path is a char[108] in sys/un.h
	strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);

	if ( Connection::Bind((struct sockaddr*)&addr, sizeof(struct sockaddr_un)) )
		return true;
	
	return false;
}

bool
UnixConnection::Bind() {
	if ( UnixConnection::Bind(SOCK_PATH) )
		return true;
	
	return false;
}

bool
UnixConnection::Socket() {
	if ( Connection::Socket(PF_UNIX, SOCK_STREAM, 0) )
		return true;

	return false;
}

bool
UnixConnection::Connect(struct sockaddr_un* addr, int size) {
	if ( Connection::Connect((struct sockaddr*)addr, size) )
		return true;
	
	return false;
}

bool
UnixConnection::Connect() {
	if ( UnixConnection::Connect(SOCK_PATH) )
		return true;

	return false;
}

bool
UnixConnection::Connect(string path) {
	if ( UnixConnection::Connect(path.c_str()) )
		return true;

	return false;
}

bool
UnixConnection::Connect(const char* path) {
	struct sockaddr_un addr;
	bzero(&addr, sizeof(struct sockaddr_un));

	addr.sun_family = AF_UNIX;
	//sockaddr_un.sun_path is a char[108] in sys/un.h
	strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);
	
	if ( Connection::Connect((struct sockaddr*)&addr, sizeof(struct sockaddr_un)) )
		return true;

	return false;
}

