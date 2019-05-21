
<h1 align="center">XY</h1>
<h3 align="center">Warning</h3>
<p align="center">This is still a experimental fork, please check the original one by
<a href="https://github.com/arnaudjuracek/xy">https://github.com/arnaudjuracek/xy</a>.
<br><br>This repo contains a modified version of the firmware that uses the <b>MeOrion.h</b> library by makeblock in order to keep better readability of the code.
Currently it is still in development.</p><br>

<div align="center">
  <a href="http://www.makeblock.com/xy-plotter-robot-kit/">
    <img src="preview.png?raw=true">
  </a>
</div>

<h3 align="center">node.js for makeblock XY plotter v2.0</h3>
<div align="center">
  <!-- License -->
  <a href="https://raw.githubusercontent.com/arnaudjuracek/xy/master/LICENSE">
    <img src="https://img.shields.io/badge/license-MIT-blue.svg?style=flat-square" alt="License" />
  </a>
</div>

<!-- 
## Features
- [./firmware](https://github.com/arnaudjuracek/xy/tree/master/firmware) : custom Arduino firmware
  - boundaries defined by the plotter's limit switches
  - pen's servo auto-sleep to prevent wear-out
  - faster _home_ command
- [./lib](https://github.com/arnaudjuracek/xy/tree/master/lib) : node.js library
  - SVG support
  - [Processing-like API](https://processing.org/reference/) for 2D primitives (see [API](#api) below)
  - commands chaining for better readability -->

## Credits
As [Daniel Shiffman's](https://twitter.com/shiffman) Twitter states,
> I'm not qualified for any of this.

So, huge thanks to Michael Fogleman, Inconvergent and Arnaud Juracek:

The Arduino firmware is based on [Michael Fogleman](https://github.com/fogleman/xy)'s one. 
Thanks to the work in Python of [Michael Fogleman](https://github.com/fogleman/xy) and [Anders Hoff](https://github.com/inconvergent/).
The nodejs code has been rewritten from scratch, but many thanks to [Arnaud Juracek](https://github.com/arnaudjuracek/xy) upon which I took the inspiration to start. 

## License

[MIT](https://tldrlegal.com/license/mit-license).
