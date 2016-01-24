/**
 * (C) 2016, Richard G. Roman <richard.roman@gmx.de>
 * Created on 2016-01-23 16:27:28
 *
 */

#include <boost/bind.hpp>
#include <cstdint>
#include <iostream>

#include "Logger.h"
#include "UdpServer.h"

using namespace boost::asio::ip;

UdpServer::UdpServer(boost::asio::io_service* io_service, uint32_t portNumber)
  : socket_(*io_service, udp::endpoint(udp::v4(), portNumber))
{
  startReceive();
}

void
UdpServer::startReceive()
{
  using namespace boost::asio;

  socket_.async_receive_from(
    buffer(receiveBuffer_),
    peer_,
    std::bind(&UdpServer::handleReceive,
              this,
              std::placeholders::_1 /* error_code */,
              std::placeholders::_2 /* bytes_transferred */));
}

void
UdpServer::handleReceive(const boost::system::error_code& error,
                         std::size_t                      bytes_transferred)
{
  using namespace boost::asio;
  if (error) {
    L("Receive error: " << error.message());
  } else {
    std::cout << "<< (" << bytes_transferred << "b from " << peer_ << "): "
              << std::string(receiveBuffer_.data(), bytes_transferred) << std::endl;
  }

  startReceive();
}
