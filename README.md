# udpirsend - UDP-Controlled LIRC IR Sender

## Introduction

**udpirsend** enables UDP remote control of any LIRC sender.

It was designed to be used with Loxone (http://www.loxone.com) home automation,
which has the capability of sending simple UDP packets holding arbitrary data.


## Installation

Theoretically, it should be enough to run:

./waf --download configure build install

Note though, it has been tested on GNU/Linux (and compilation on OSX, with
MacPorts installed).


## Usage

Just run `./udpirsend &` to start it in the background. Optionally you can override
various settings, like LIRC server address, etc.


## Debug

To see debug output, specify a logfile via using --logfile switch or a config setting:
logfile=~/.logs/udpirsend.log

(Default config file location is ~/.udpirsendrc.)

