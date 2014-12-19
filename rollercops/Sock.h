/*
** Class Sock
** General socket class
*/

#ifndef		__SOCK_HH__
# define	__SOCK_HH__

# include	"libs.h"
# include	"logging.h"

typedef		int SOCKET;
typedef		struct sockaddr_in	SOCKADDR_IN;
typedef		struct sockaddr		SOCKADDR;
typedef		struct in_addr		IN_ADDR;


# if	defined(_WIN32) || defined(_WIN64)
#  include	<winsock2.h>
#  pragma	comment(lib, "Ws2_32.lib")
# elif	defined(linux) || defined(__APPLE__)
#  include	<sys/types.h>
#  include	<sys/socket.h>
#  include	<netinet/in.h>
#  include	<arpa/inet.h>
#  include	<unistd.h> /* close */
#  include	<netdb.h> /* gethostbyname */
#  define	INVALID_SOCKET	-1
#  define	SOCKET_ERROR	-1
#  define	closesocket(s)	close(s)
// use -lws_32 compilation option
# endif

# define	SOCK_IP		"www.error500.fr/"
# define	SOCK_PORT	80

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
	int	connectByHostname(const char *hostname);
	int	authenticationCheck(char *answer);
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
