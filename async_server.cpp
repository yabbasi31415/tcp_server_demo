//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <list>
#include <utility>

using namespace std;
using boost::asio::ip::tcp;

class server {
public:
  server(boost::asio::io_service &io_service, short port)
      : io_service_(io_service),
        acceptor_(io_service, tcp::endpoint(tcp::v4(), port)) {
    do_accept();
  }

private:
  void do_accept() {
    auto socket_ = make_unique<tcp::socket>(io_service_);
    acceptor_.async_accept(*socket_,
                           [this, &socket_](boost::system::error_code ec) {
                             if (!ec) {
                               socket_list_.push_back(std::move(socket_));
                               do_read(socket_list_.back());
                             }
                             do_accept();
                           });
  }

  void do_read(unique_ptr<tcp::socket> &socket_) {
    socket_->async_read_some(
        boost::asio::buffer(data_, max_length),
        [this, &socket_](boost::system::error_code ec, std::size_t length) {
          if (!ec) {
            cout << "Server received: " << data_ << endl;
            // write to all other sockets
            for(auto it = socket_list_.begin(); it != socket_list_.end(); ++it)
            {
              do_write(*it, length);
            }
          }
          do_read(socket_);
        });
  }

  void do_write(const unique_ptr<tcp::socket> &socket_, std::size_t length) {
    boost::asio::async_write(
        *socket_, boost::asio::buffer(data_, length),
        [this](boost::system::error_code ec, std::size_t /*length*/) {
          if (!ec) {
            cout << "Server sent: " << data_ << endl;
          }
        });
  }

  tcp::acceptor acceptor_;
  list<unique_ptr<tcp::socket>> socket_list_;
  boost::asio::io_service &io_service_;

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