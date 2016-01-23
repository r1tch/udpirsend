#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED
/**
 * (C) 2016, Richard G. Roman <richard.roman@gmx.de>
 * Created on 2016-01-19 14:37:36
 *
 */

#include <ctime>
#include <fstream>

class Logger {
public:
  static Logger& Instance()
  {
    static Logger Logger_;

    return Logger_;
  }

  void initWithFilename(const char* filename)
  {
    logfile_.close();
    logfile_.open(filename, std::ios::out | std::ios::app);
    logTimestamp(logfile_);
    logfile_ << "Init" << std::endl;
  }

  void logTimestamp(std::ostream& os)
  {
    time_t t = time(nullptr);
    struct tm stm;

    localtime_r(&t, &stm);

    char tmp[21];
    strftime(tmp, 21, "%Y-%m-%d %H:%M:%S ", &stm);

    os << tmp;
  }

  std::ofstream logfile_;

private:
  Logger() {}
};
#define L(msg) do { \
        Logger::Instance().logTimestamp(Logger::Instance().logfile_); \
        Logger::Instance().logfile_ << msg << std::endl << std::flush; \
    } while (false)

#endif
