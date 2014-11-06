#include "Sock.h"
#include "libs.h"

int	main()   // IMPORTANT: use Level::destroyAllLogger() to clean.
{
  Sock		testSocket(SOCK_STREAM);
  const char	*hostname = "www.error500.fr";
  
  /*
    By veryfying the value
    of the sock _fd, we check if
    its creation was a success
    or not.
  */

  if(testSocket.getFd() == -1)
    return(-1);

  /*
    We check the return value of
    connectByHostName to see if 
    the user is allowed to
    continue or if he needs to
    retry to log in.
  */
  if (testSocket.connectByHostname(hostname) == 1)
    {
      Logger::root->log(Level::INFO, "Authentication succed. Execution is launched.");
      //launch normal execution
    }
  else
    {
      Logger::root->log(Level::SEVERE,
			"Rollercops was not able to connect to the server.\nExiting\n.");
      Logger::destroyAllLogger();
      return (-1);
    }
  Logger::destroyAllLogger();
  return (0);
}
