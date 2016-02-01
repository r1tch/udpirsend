# udpirsend - UDP-Controlled LIRC IR Sender

## Introduction

**udpirsend** enables UDP remote control of any LIRC sender.

It was designed to be used with Loxone (http://www.loxone.com) home automation,
which has the capability of sending simple UDP packets holding arbitrary data.


## Installation

Theoretically, it should be enough to run:

  ./waf update --files=boost
  ./waf configure build 

..then as root:
  ./waf install

Note though, it has been tested on GNU/Linux (and compilation on OSX, with
MacPorts installed).

Should the download of boost.py fail for some reason, just copy extras/boost.py to
.waf-\*/waflib/extras/

## Raspberry PI / Raspbian 8 (jessie)

Here you need to specify Boost lib location with --boost-lib :

  ./waf --boost-libs=/usr/lib/arm-linux-gnueabihf/ configure build


## Usage

Just run `./udpirsend &` to start it in the background. Optionally you can override
various settings, like LIRC server address, etc.

On Debian-based systems you can add a line to /etc/rc.local (below pi is the username):

su - pi -c /usr/local/bin/udpirsend &

## Debug

To see debug output, specify a logfile via using --logfile switch or a config setting:
logfile=~/.logs/udpirsend.log

(Default config file location is ~/.udpirsendrc.)

