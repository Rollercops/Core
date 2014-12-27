#include	"TcpSock.hh"

TcpSock::TcpSock()
  :Sock(SOCK_STREAM)
{
}

TcpSock::TcpSock(int port)
  :Sock(SOCK_STREAM)
{
  this->sBind(port);
}

TcpSock::TcpSock(int port, std::string ip)
  :Sock(SOCK_STREAM)
{
  this->cConnect(port, ip);
}

TcpSock::TcpSock(TcpSock const & main)
  :Sock()
{
  int sinsize = sizeof this->_sin;

  if ((this->_fd = accept(main.getFd(), reinterpret_cast<SOCKADDR*>(&this->_sin), &sinsize)) == INVALID_SOCKET)
    (*new SMaker << "Accept failure.").failWithL();
}

TcpSock::~TcpSock()
{
}

void		TcpSock::sBind(int port)
{
  this->_sin.sin_family = AF_INET;
  this->_sin.sin_port = htons(port);
  this->_sin.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind (this->_fd, reinterpret_cast<SOCKADDR*>(&this->_sin), sizeof this->_sin) == SOCKET_ERROR)
    (*new SMaker << "Binding failure.").failWithL();
  if (listen(this->_fd, 0) == SOCKET_ERROR)
    (*new SMaker << "Listening failure.").failWithL();
}

TcpSock*	TcpSock::sAccept()
{
  return new TcpSock(*this);
}

void		TcpSock::cConnect(int port, std::string ip)
{
  this->_sin.sin_family = AF_INET;
  this->_sin.sin_port = htons(port);
  //	this->_sin.sin_addr = *(IN_ADDR *)gethostbyname("www.rollercops.com")->h_addr;
  this->_sin.sin_addr.s_addr = inet_addr(ip.c_str());
  if (connect(this->_fd, reinterpret_cast<SOCKADDR*>(&this->_sin), sizeof SOCKADDR) == SOCKET_ERROR)
    (*new SMaker << "Connect failure.").failWithL();
}

void		TcpSock::queue(std::string & msg)
{
  (*new SMaker << "queued : '" << msg << "'").log();
  this->_oBuff.append(msg).append(LINE_SEP);
  this->write();
}

bool		TcpSock::upToDate() const
{
  return this->_oBuff.empty();
}

bool		TcpSock::write()
{
  int		r;

  if ((r = send(this->_fd, this->_oBuff.c_str(), this->_oBuff.length(), 0)) == -1)
    return false;
  this->_oBuff.erase(0, r);
  return true;
}

bool		TcpSock::read()
{
  int		r;
  size_t	p;

  if ((r = recv(this->_fd, this->_buff, BUFF_SIZE - 1, 0)) == -1)
    return false;
  this->_buff[r] = '\0';
  this->_iBuff.append(this->_buff);
  while ((p = this->_iBuff.find(LINE_SEP)) != std::string::npos)
    {
      this->_msg.push(this->_iBuff.substr(0, p));
      this->_iBuff.erase(0, p + SIZE_SEP);
    }
  return true;
}

bool		TcpSock::isEmpty() const
{
  return this->_msg.empty();
}

std::string	TcpSock::getMsg()
{
  std::string	r(this->_msg.front());

  this->_msg.pop();
  (*new SMaker << "got : '" << r << "'").log();
  return r;
}
