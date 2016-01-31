#ifndef COMMANDPARSER_H_INCLUDED
#define COMMANDPARSER_H_INCLUDED
/**
 * (C) 2016, Richard G. Roman <richard.roman@gmx.de>
 * Created on 2016-01-31 15:54:51
 *
 */

#include "UdpServer.h"

class Lirc;

class CommandParser : public UdpServer::ReceiveCallback {
public:
  CommandParser(Lirc* lirc) : lirc_(lirc) {}

  virtual void udpReceived(const std::string& bytes) override;

private:
  Lirc* lirc_;
};

#endif
