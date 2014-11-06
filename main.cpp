#include "Sock.h"
#include "libs.h"

int	main()
{
  Sock		testSocket(SOCK_STREAM);
  const char	*hostname = "www.error500.fr";

  testSocket.connectByHostname(hostname);
  Logger::destroyAllLogger();

  //test
  // IMPORTANT: use Level::destroyAllLogger() to clean.
  return (0);
}
