/**
 * (C) 2016, Richard G. Roman <richard.roman@gmx.de>
 * Created on 2016-01-31 16:15:53
 *
 */

#include <boost/algorithm/string.hpp>

#include "CommandParser.h"
#include "Lirc.h"
#include "Logger.h"

void
CommandParser::udpReceived(const std::string& bytes)
{
  L("Sending to lirc:" << bytes);

  lirc_->send(bytes);
}
