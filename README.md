# tcp_server_demo

* A TCP echo server in C++ that supports multiple simultaneuos clients.
* Server implementation is based on this [example](https://www.boost.org/doc/libs/1_65_1/doc/html/boost_asio/example/cpp11/echo/async_tcp_echo_server.cpp) from Boost ASIO library (compatible with Version 1.65.1).
* Async timer added to the file but not in use

### How to Run
* Get Boost ASIO library and g++ compiler for Linux
  - sudo apt-get install libboost-all-dev  
  - sudo apt-get install g++
  
* Run make
  - mkdir build
  - cd build
  - cmake ..
  - make
  - ./async_server
  
* In a new terminal, start a telnet client application 
  - telnet 127.0.0.1 1234 (the IP and port are set in async_server.cpp file)
 * The server should echo whatever is sent from the client.
 * Create multiple telnet connections with the server simultaneuously.
   - telnet 127.0.0.*x* 1234  (where *x* is between 0 and 255)
