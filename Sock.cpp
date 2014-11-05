#include	"Sock.hh"

Sock::Sock(int type)
{
	this->_fd = socket(AF_INET, type, 0);
	if (this->_fd == INVALID_SOCKET)
		(*new SMaker << "Socket creation failure.").failWithL();
}

Sock::Sock()
	:_fd(INVALID_SOCKET)
{
}

Sock::~Sock()
{
	closesocket(this->_fd);
}

void		Sock::init()
{
#if		defined(_WIN32) || defined(_WIN64)
	WSADATA	wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) < 0)
		(*new SMaker << "WSAStartup failure.").failWithL();
#endif
}

void		Sock::end()
{
#if		defined(_WIN32) || defined(_WIN64)
	WSACleanup();
#endif
}

SOCKET		Sock::getFd() const
{
	return  this->_fd;
}
