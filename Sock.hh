/*
** Class Sock
** General socket class
*/

#ifndef		__SOCK_HH__
# define	__SOCK_HH__

# include	"libs.hh"

# if	defined(_WIN32) || defined(_WIN64)
#  include	<winsock2.h>
#  pragma	comment(lib, "Ws2_32.lib")
# elif	defined(linux)
#  include	<sys/types.h>
#  include	<sys/socket.h>
#  include	<netinet/in.h>
#  include	<arpa/inet.h>
#  include	<unistd.h> /* close */
#  include	<netdb.h> /* gethostbyname */
#  define	INVALID_SOCKET	-1
#  define	SOCKET_ERROR	-1
#  define	closesocket(s)	close(s)
typedef		int SOCKET;
typedef		struct sockaddr_in	SOCKADDR_IN;
typedef		struct sockaddr		SOCKADDR;
typedef		struct in_addr		IN_ADDR;
// use -lws_32 compilation option
# endif

# define	SOCK_IP		"127.0.0.1"
# define	SOCK_PORT	4242

class		Sock
{
protected:
	SOCKET	_fd;
private:
	Sock(Sock const &);
	Sock &	operator=(Sock const &);
public:
	Sock(int type);
protected:
	// reserved for inheriting class usage
	Sock();
public:
	virtual ~Sock();
	static void	init();
	static void	end();
	SOCKET	getFd() const;
	//send
	//recv
	//bind (?)
	//connect (? client)
	//listen (?)
	//accept(?)
};

/*
** TODO
** - consider switching to Abstarct of Interface class for general socket
** - partial redisign or extra driver class allowing blind usage of inheriting classes
*/

#endif	//	__SOCK_HH__
