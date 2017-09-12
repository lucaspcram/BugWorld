[![Travis](https://travis-ci.org/lucaspcram/BugWorld.svg?branch=master)](https://travis-ci.org/lucaspcram/BugWorld)

# BugWorld

A simple ncurses-based puzzle game.

## Screenshots
Screenshots to come!

## Building
BugWorld requires the ncurses development libraries to build.
Tested and works with GCC 4.8.4 as well as clang 3.9.0.

On Debian/Ubuntu
```
$ sudo apt-get install libncurses5-dev
```

Or on CentOS/RHEL/Fedora
```
$ sudo yum install ncurses-devel
```
Then just
```
$ make all
$ ./bin/bugworld
```
to get the game running. You can install the `bugworld` executable anywhere
once it is compiled.

## Notes
* BugWorld writes score information to the file `.bugworldscore` in your home folder

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
