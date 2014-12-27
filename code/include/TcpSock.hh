/*
** Class TcpSock
** Socket class based on TCP/IP protocol
*/

#ifndef		__TCPSOCK_HH__
# define	__TCPSOCK_HH__

# include	"Sock.hh"

# define	BUFF_SIZE	1024
# define	LINE_SEP	"\r\n"
# define	SIZE_SEP	2

class		TcpSock : public Sock
{
protected:
  SOCKADDR_IN	_sin;
  std::string	_oBuff;
  char		_buff[BUFF_SIZE];
  std::string	_iBuff;
  std::queue<std::string>	_msg;
private:
  TcpSock &	operator=(TcpSock const &);
public:
  // tcp socket :
  TcpSock();
  // server tcp socket :
  TcpSock(int port);
  // client tcp socket :
  TcpSock(int port, std::string ip);
protected:
  // not a copy-constructor, reserved for sAccept usage :
  TcpSock(TcpSock const & main);
public:
  virtual ~TcpSock();
  void		sBind(int port);
  TcpSock*	sAccept();
  void		cConnect(int port, std::string ip);
  void		queue(std::string & msg);
  bool		upToDate() const;
  bool		write();
  bool		read();
  bool		isEmpty() const;
  std::string	getMsg();
};

#endif	//	__TCPSOCK_HH__
