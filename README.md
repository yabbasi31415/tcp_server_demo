# tcp_server_demo

* A TCP echo server in C++ that supports multiple simultaneuos clients.
* Uses Boost Asio library.
* Server implementation is based on this [example](https://www.codeproject.com/Articles/1264257/Socket-Programming-in-Cplusplus-using-boost-asio-T).

### How to Run
* Get Boost ASIO library and g++ compiler for Linux
  - sudo apt-get install libboost-all-dev  
  - sudo apt-get install g++
  
* Compile and run the server
  - g++ async_server.cpp -o async_server -lboost_system
  - ./async_server
  
* In a new terminal, start a telnet client application 
  - telnet 127.0.0.1 1234 (the IP and port are set in async_server.cpp file)
 * The server should echo whatever is sent from the client.
 * Create multiple telnet connections with the server simultaneuously.
   - telnet 127.0.0.*x* 1234  (where *x* is between 0 and 255)
