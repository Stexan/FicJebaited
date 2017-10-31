#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

//namespace ClientNamespace
//{
  class Client {
   private:
     void error(const char *msg);
   public:
     void send(const char *ip, int port, const char *msg);
  };
//}
