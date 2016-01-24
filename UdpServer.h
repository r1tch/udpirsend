#ifndef UDPSERVER_H_INCLUDED
#define UDPSERVER_H_INCLUDED
/**
 * (C) 2016, Richard G. Roman <richard.roman@gmx.de>
 * Created on 2016-01-23 15:46:37
 *
 */

#include <boost/array.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>

class UdpServer {
public:
  UdpServer(boost::asio::io_service* io_service, uint32_t portNumber);

private:
  void startReceive();
  void handleReceive(const boost::system::error_code& error,
                     std::size_t bytes_transferred);

private:
  boost::asio::ip::udp::socket socket_;
  boost::array<char, 4096> receiveBuffer_;
  boost::asio::ip::udp::endpoint peer_;
};
#endif
