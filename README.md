XY
===
🤖✏️ — node.js for makeblock XY plotter v2.0

### Features

- [./firmware](https://github.com/arnaudjuracek/xy/tree/master/firmware) : custom Arduino firmware
  - boundaries defined by the plotter's limit switches
  - pen's servo auto-sleep to prevent wear-out
- [./server](https://github.com/arnaudjuracek/xy/tree/master/rpi-server) : node.js server
  - SVG support

### Installation

###### Firmware

_please note that this firmware has not been tested with the official makeblock softwares_
- download and install the [Arduino Software](https://www.arduino.cc/en/Main/Software)
- open [./firmware/firmware.ino](https://github.com/arnaudjuracek/xy/tree/master/firmware/firmware.ino)
- upload it to your board, making sure you've selected the right port and board (_Leonardo_ or _Uno_ depending of your configuration)
- if you want to go back to the official firmware, use the [mDrawBot software](https://github.com/Makeblock-official/mDrawBot)

###### Server
```sh

```

### Credits
The arduino firmware is based on [Fogleman](https://github.com/fogleman/xy)'s one.

### License

MIT.