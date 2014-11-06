#include	"Sock.h"

/* 
   Socket creator -- 
   argument 'type' is the same
   used in function socket(2)
   if _fd (socket file descriptor)
   == -1 raise an error log.
*/
Sock::Sock(int type) 
{
  this->_fd = socket(AF_INET, type, 0);
  if (this->_fd == INVALID_SOCKET)
    Logger::root->log(Level::SEVERE, "Invalide socket error.");
}

Sock::Sock()
	:_fd(INVALID_SOCKET)
{
}

/*
  Basic Socket Destructor
  close the socket with its fd
*/
Sock::~Sock()
{
	closesocket(this->_fd);
}

/*
  Function used to check the
  validity of the log in arguments.
  Search the string "AUTH_SUCCESS"
  in the server's answer to allow
  or not to continue.
*/
int		Sock::authenticationCheck(char *answer)
{
  int		count = 0;
  char		*strSuccess = (char *)malloc(20);

  strcpy(strSuccess, "AUTH_SUCCESS");
  if(strstr(answer, strSuccess) != NULL)
    {
      Logger::root->log(Level::INFO, "Authentication succed.");
      return (1);
    }
  else
    {
      Logger::root->log(Level::INFO, "Authentication failed.");
      return (-1);
    }
  return (-1);
}

/*
  Connect by Hostname us the hostname
  passed by  and the sockaddr_in
  structure to connect to  the server.
*/

int		Sock::connectByHostname(const char *hostname)
{
  char	buffer[2048];
  char	*bufferRead = (char *)malloc(2048);
  char	*bufferRead2 = (char *)malloc(2048);
  int i = 0;
  
  struct hostent* server = gethostbyname(hostname);
  if(server == NULL)
    {
      Logger::root->log(Level::SEVERE, "Can not reach server.");
      return(-1);
    }
 
  struct sockaddr_in serverAddress = { 0 };
  serverAddress.sin_addr = *(IN_ADDR *) server->h_addr;
  serverAddress.sin_port = htons(SOCK_PORT);		 /* on utilise htons pour le port */
  serverAddress.sin_family = AF_INET;

  if (connect(this->_fd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < SOCKET_ERROR)
    {
      Logger::root->log(Level::SEVERE, "Socket connect failed.");
      return(-1);
    }

  /*
    Once the socket is connected,
    buffer is filled with the request
    and writtend on the socket to send
    it.
  */

  strcpy(buffer,
	 "POST http://error500.fr/everything/collet/ HTTP/1.1\nContent-Type: application/x-www-form-urlencoded\nHost: http://error500.fr\nContent-Length:25\n\nlogin=panda&password=love");
  write(this->_fd, buffer, strlen(buffer));

  /*
    Then, we read on the socket 
    to get the answer, char by
    char to get the \0.
    Every char is added to 
    bufferRead2.
    BufferRead2 is then send
    to authenticationCheck to see
    if the log in parametres were
    right or false.
  */
  read(this->_fd, bufferRead, 1);
  strcat(bufferRead2, bufferRead);
  while(bufferRead[i] != '\0')
    {    
      read(this->_fd, bufferRead, 1);
      strcat(bufferRead2, bufferRead);
    }  
  std::cout << "readed : " << bufferRead2 << std::endl;  
  /*
    if authentication is ok, then
    the function return 1. Else
    it means the authentication
    failed.
  */
  if (authenticationCheck(bufferRead2) == 1)
    return (1);
  else
    return (-1);
}	

/*
  initialize function for Windows
*/
void		Sock::init()
{
#if		defined(_WIN32) || defined(_WIN64)
  WSADATA	wsa;

  if (WSAStartup(MAKEWORD(2, 2), &wsa) < 0)
    Logger::root->log(Level::SEVERE, "WSAStartup failure.");

#endif
}


/*
  ending function for Windows
*/
void		Sock::end()
{
#if		defined(_WIN32) || defined(_WIN64)
  WSACleanup();
#endif
}

/*
  Getter
*/
SOCKET		Sock::getFd() const
{
  return  this->_fd;
}
