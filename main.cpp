/**
 * (C) 2016, Richard G. Roman <richard.roman@gmx.de>
 * Created on 2016-01-17 15:52:02
 *
 */

#include <cstdint>

#include <boost/program_options.hpp>
#include <iostream>

#include "Logger.h"

void
parseArgs(int argc, char** argv, uint32_t* portNumber)
{
  using namespace boost::program_options;

  options_description options {
    "Options"
  };

  std::string logfile;
  std::string configFile = std::string(getenv("HOME")) + "/.loxirrc";

  options.add_options()
    ("help,h", "Help Screen")
    ("port,p", value<uint32_t>(portNumber)->default_value(6969), "Port Number to Listen On")
    ("logfile,l", value<std::string>(&logfile), "Logfile")
    ("config", value<std::string>(&configFile)->default_value(configFile), "Configuration File");

  variables_map vm;
  try {
    store(parse_command_line(argc, argv, options), vm);
    if (vm.count("config")) {
      std::ifstream ifs(vm["config"].as<std::string>().c_str());
      if (ifs)
        store(parse_config_file(ifs, options), vm);
    }
  } catch (const error& ex) {
    std::cerr << ex.what() << std::endl;
  }
  notify(vm);

  Logger::Instance().initWithFilename(logfile.c_str());

  if (vm.count("help"))
    std::cout << options << std::endl;
}

int
main(int argc, char** argv)
{
  uint32_t portNumber;

  parseArgs(argc, argv, &portNumber);

  L("Exiting");
  return 0;
}
