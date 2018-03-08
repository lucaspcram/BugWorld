[![Travis](https://travis-ci.org/lucaspcram/BugWorld.svg?branch=master)](https://travis-ci.org/lucaspcram/BugWorld)

# BugWorld

A simple ncurses-based action-puzzle game.

## Features
* animated ASCII graphics
* map generation based on 2D Perlin noise
* high score tracking

## Screenshots
![Main Menu](/img/screenshot1.png)
![In Game](/img/screenshot2.png)
![High Score Screen](/img/screenshot3.png)

## Supported Operating Systems
* GNU/Linux
* macOS (tested on High Sierra 10.13)
* Windows 10 (using Windows Subsystem for Linux)
* Cygwin (WIP support coming soon, hopefully)
* Probably more, feel free to test and contribute!

## Building
Requires the ncurses development libraries to build and run.
Check your operating system documentation for instructions
on installing ncurses if you need it - you probably already have it.

Build just like:
```
$ export CC=gcc
$ make all
```
Note you can use clang instead if you wish.

Read the help menu first!
```
$ ./bin/bugworld --help
```

You can install the `bugworld` executable anywhere
once it is compiled.

## Notes
* BugWorld writes score information to the file `.bugworldscore` in your home folder

## License
This project is released under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing
See the [CONTRIBUTING.md](CONTRIBUTING.md) file for details.

