#include "Server.hpp"


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>





void sigchld_handler(int s)
{
      // waitpid() might overwrite errno, so we save and restore it:
      int saved_errno = errno;
      
      while(waitpid(-1, NULL, WNOHANG) > 0);
      
      errno = saved_errno;
}


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
      if (sa->sa_family == AF_INET) {
            return &(((struct sockaddr_in*)sa)->sin_addr);
      }
      
      return &(((struct sockaddr_in6*)sa)->sin6_addr);
}





std::ostream& operator<< (std::ostream& os, const std::pair<int*, size_t>& p) {
      os << "{";
      for(int i = 0; i < p.second; ++i){
            os << p.first[i];
            if ( i < p.second - 1 ) {
                  os << ",";
            }
      }
      os << "}";
      return os;
}
