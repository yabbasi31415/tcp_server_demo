//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>

using namespace std;
using boost::asio::ip::tcp;

// void print(const boost::system::error_code & /*e*/) {
//   cout << "Echo Server Started" << endl;
// }

class server {
public:
  server(boost::asio::io_service &io_service, short port)
      : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
        socket_(io_service), timer_(io_service, boost::posix_time::seconds(2)) {
    do_accept();
  }

private:
  void do_accept() {
    acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
      if (!ec) {
        do_read();
      }
      do_accept();
    });
  }

  void do_read() {
    socket_.async_read_some(
        boost::asio::buffer(data_, max_length),
        [this](boost::system::error_code ec, std::size_t length) {
          if (!ec) {
            cout << "Server received: " << data_ << endl;
            timer_.async_wait(std::bind(&server::timeout, this,
                                        std::placeholders::_1, length));
          }
        });
  }

  void do_write(std::size_t length) {
    boost::asio::async_write(
        socket_, boost::asio::buffer(data_, length),
        [this](boost::system::error_code ec, std::size_t /*length*/) {
          if (!ec) {
            cout << "Server sent: " << data_ << endl;
            do_read();
          }
        });
  }

  void timeout(const boost::system::error_code &, std::size_t length) {
    cout << "Timeout: " << endl;
    do_write(length);
  }

  tcp::acceptor acceptor_;
  tcp::socket socket_;
  boost::asio::deadline_timer timer_;

  enum { max_length = 1024 };
  char data_[max_length];
};

int main() {
  try {
    boost::asio::io_service io_service;
    server s(io_service, 1234);

    io_service.run();
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}