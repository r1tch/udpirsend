#ifndef LIRC_H_INCLUDED
#define LIRC_H_INCLUDED
/**
 * (C) 2016, Richard G. Roman <richard.roman@gmx.de>
 * Created on 2016-01-31 16:20:47
 *
 */

#include <boost/array.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/local/stream_protocol.hpp>
#include <boost/asio/steady_timer.hpp>

#include <cstdint>
#include <string>

// simply forwarding the command string to LIRC, format for single send:
// SEND_ONCE <remote_name> <command_code> [<count>]
class Lirc {
public:
  Lirc(boost::asio::io_service* io_service);
  void send(const std::string& bytes);

  void shutdownSocket(const boost::system::error_code& error);

private:
  void startReceive();
  void handleReceive(const boost::system::error_code& error,
                     std::size_t                      bytes_transferred);

private:
  boost::asio::local::stream_protocol::socket socket_;
  boost::asio::local::stream_protocol::endpoint peer_;
  boost::asio::steady_timer shutdownTimer_;
  boost::array<char, 4096> receiveBuffer_;

private:
  static const char* DefaultSocket_;
  static const uint16_t DefaultInetPort_;
};

#endif
