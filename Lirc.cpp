/**
 * (C) 2016, Richard G. Roman <richard.roman@gmx.de>
 * Created on 2016-01-31 18:14:35
 *
 */

#include <boost/asio/buffer.hpp>
#include <boost/system/system_error.hpp>
#include <chrono>

#include "Lirc.h"
#include "Logger.h"

const char* Lirc::DefaultSocket_      = "/var/run/lirc/lircd";
const uint16_t Lirc::DefaultInetPort_ = 8765;

Lirc::Lirc(boost::asio::io_service* io_service)
  : socket_(*io_service),
  peer_(DefaultSocket_),
  shutdownTimer_(*io_service)
{
}

void
Lirc::send(const std::string& bytes)
{
  using namespace boost::asio;

  if (!socket_.is_open()) {
    L("Connecting to " << peer_);
    try {
      socket_.connect(peer_);     // TODO exceptions or errors?? Test for non-existent socket file
    } catch (boost::system::system_error ex) {
      L("Connect error to " << peer_ << ": " << ex.what());
      return;
    }

    startReceive();
  }

  L("Sending " << bytes);
  socket_.send(boost::asio::buffer(bytes));

  shutdownTimer_.cancel();
  shutdownTimer_.expires_from_now(std::chrono::seconds(2));
  shutdownTimer_.async_wait(std::bind(&Lirc::shutdownSocket, this,
                                      std::placeholders::_1));
}

void
Lirc::startReceive()
{
  socket_.async_read_some(boost::asio::buffer(receiveBuffer_),
                          std::bind(&Lirc::handleReceive,
                                    this,
                                    std::placeholders::_1 /* error_code */,
                                    std::placeholders::_2 /* bytes_transferred */));
}

void
Lirc::handleReceive(const boost::system::error_code& error,
                    std::size_t                      bytes_transferred)
{
  using namespace boost::asio;
  if (error) {
    L("Lirc: receive error: " << error.message());
    return;
  }

  L("LIRC response: " << std::string(receiveBuffer_.data(), bytes_transferred));
  startReceive();
}

void
Lirc::shutdownSocket(const boost::system::error_code& error)
{
  if (error == boost::asio::error::operation_aborted) {
    return;                             // happens upon cancel()
  } else if (error) {
    L("Lirc: shutdownSocket timer error: " << error.message());
    return;
  } else if (!socket_.is_open()) {
    L("shutdownSocket: socket not open");
    return;
  }

  L("Shutting down socket");
  socket_.shutdown(boost::asio::local::stream_protocol::socket::shutdown_both);
  socket_.close();
}
