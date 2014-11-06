#include	"Sock.h"

Sock::Sock(int type) // Socket creation with error log if failure 
{
  this->_fd = socket(AF_INET, type, 0);
  if (this->_fd == INVALID_SOCKET)
    Logger::root->log(Level::SEVERE, "Invalide socket error.");
}

Sock::Sock()
	:_fd(INVALID_SOCKET)
{
}

Sock::~Sock()
{
	closesocket(this->_fd);
}

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
  serverAddress.sin_port = htons(SOCK_PORT); /* on utilise htons pour le port */
  serverAddress.sin_family = AF_INET;

  if (connect(this->_fd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < SOCKET_ERROR)
    {
      Logger::root->log(Level::SEVERE, "Socket connect failed.");
      return(-1);
    }
  strcpy(buffer,
	 "POST http://error500.fr/everything/collet/ HTTP/1.1\nContent-Type: application/x-www-form-urlencoded\nHost: http://error500.fr\nContent-Length:25\n\nlogin=panda&password=love");
  write(this->_fd, buffer, strlen(buffer));
  read(this->_fd, bufferRead, 1);
  strcat(bufferRead2, bufferRead);
  while(bufferRead[i] != '\0')
    {    
      read(this->_fd, bufferRead, 1);
      strcat(bufferRead2, bufferRead);
    }  
  close(this->_fd);
  std::cout << "buffer : " << bufferRead2 << " \nBUFFER READ CLOSED\n"<< std::endl;
  return (0);
}	

void		Sock::init()
{
#if		defined(_WIN32) || defined(_WIN64)
  WSADATA	wsa;

  if (WSAStartup(MAKEWORD(2, 2), &wsa) < 0)
    Logger::root->log(Level::SEVERE, "WSAStartup failure.");

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
