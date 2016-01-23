# loxir - UDP-Controlled LIRC Client

## Introduction

**loxir** enables UDP remote control of any LIRC server.

The name originates from the fact that it was designed to be used with Loxone
(http://www.loxone.com) home automation, that has the capability of sending
simple UDP packets holding arbitrary data.


## Installation

Theoretically, it should be enough to run:

./waf --download configure build install

Note though, it has been tested on GNU/Linux (and compilation on OSX, with
MacPorts installed).


## Usage

Just run `./loxir &` to start it in the background. Optionally you can override
various settings, like LIRC server address, etc. (TODO: list options here.)

