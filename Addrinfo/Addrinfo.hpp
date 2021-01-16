#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>



struct Addrinfo : public addrinfo
{
      Addrinfo () : addrinfo {
            .ai_flags = AI_PASSIVE,                       // use my IP
            .ai_family = AF_UNSPEC,                      // AF_INET, AF_INET6, AF_UNSPEC
            .ai_socktype = SOCK_STREAM,                   // SOCK_STREAM, SOCK_DGRAM
            .ai_protocol = 0,                    // use 0 for "any"
            .ai_addrlen = 0,                    // size of ai_addr in bytes
            .ai_addr = nullptr,                 // struct sockaddr_in or _in6
            .ai_canonname = nullptr,            // full canonical hostname
            .ai_next = nullptr                  // linked list, next node
      }
      {


      }
      
      
      friend std::ostream& operator<< (std::ostream& os, const Addrinfo& addressInfo)
      {
            if ( addressInfo.ai_addr == nullptr )
            {
                  throw std::runtime_error ("null");
            }
            
            for (const addrinfo* i = &addressInfo; i != nullptr; i = i -> ai_next)
            {
                  char ip4_ip6 [INET_ADDRSTRLEN];
                  
                  switch ( i -> ai_addr -> sa_family )
                  {
                              
                        case AF_INET:
                              inet_ntop(addressInfo.ai_family, &((sockaddr_in*)(i -> ai_addr))->sin_addr, ip4_ip6, sizeof(ip4_ip6));
                              break;
                              
                        case AF_INET6:
                              inet_ntop(addressInfo.ai_family, &((sockaddr_in6*)(i -> ai_addr))->sin6_addr, ip4_ip6, sizeof(ip4_ip6));
                              break;
                              
                        default:
                              break;
                  }
                  
                  os << ip4_ip6;
                  if ( i -> ai_next != nullptr ) {
                        os << "\n";
                  }
            }
            
            
            return os;
      }
};


//void print (const char* ipString)
//{
//      struct addrinfo hints, *res, *p;
//      int status;
//      char ipstr[INET6_ADDRSTRLEN];
//      
//      
//      memset(&hints, 0, sizeof hints);
//      hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
//      hints.ai_socktype = SOCK_STREAM;
//      
//      if ((status = getaddrinfo(ipString, NULL, &hints, &res)) != 0) {
//            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
//            exit(-1);
//      }
//      
//      printf("IP addresses for %s:\n\n", ipString);
//      
//      for(p = res;p != NULL; p = p->ai_next) {
//            void *addr;
//            char *ipver;
//            
//            // get the pointer to the address itself,
//            // different fields in IPv4 and IPv6:
//            if (p->ai_family == AF_INET) { // IPv4
//                  struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
//                  addr = &(ipv4->sin_addr);
//                  ipver = "IPv4";
//            } else { // IPv6
//                  struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
//                  addr = &(ipv6->sin6_addr);
//                  ipver = "IPv6";
//            }
//            
//            // convert the IP to a string and print it:
//            inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
//            printf("  %s: %s\n", ipver, ipstr);
//      }
//      
//      freeaddrinfo(res); // free the linked list
//      
//      
//}
