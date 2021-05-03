# Linux

Compiling in Linux (tested on Ubuntu 17) requires three steps:
1. Installing dependencies
2. Compiling and installing ClanLib 3.0
3. Compiling AdaptiveShooter itself

## Dependencies
1. `sudo apt-get install make g++ automake libtool libfreetype6-dev libfontconfig1-dev libgl1-mesa-dev libxrender-dev libasound2-dev doxygen liblua5.1-0-dev`

## ClanLib 3.0
Most ClanLib components should compile with these settings. ClanSqlite is not necessary, though. AdaptiveShooter is *not* compatible with ClanLib 4.0.
1. Clone [ClanLib 3.0-stable](https://github.com/sphair/ClanLib/).
2. `./autogen.sh && ./configure && make && sudo make install`

## AdaptiveShooter
`cmake` uses the [FindClanLib.cmake](FindClanLib.cmake) script to locate ClanLib 3.0 on your default install location.
1. `cmake .`
2. `make`

# Windows

The Visual Studio 15 (Visual Studio 2017) project files on [solution](solution) directory should be enough.

## Dependencies
Except from ClanLib 3.0, the only external dependency Lua 5.1.4 is included in [dependencies](dependencies) directory.

## ClanLib 3.0

1. Clone my fork of [ClanLib 3.0](http://github.com/killerasus/ClanLib).
2. On ClanLib directory
    1. If using Visual Studio 2017 - `git checkout patch-1`.
    2. If using Visual Studio 2019 - `git checkout vs2019-patch`.
4. Generate VS project files with the `configure.exe` tools.
5. Compile the solution and copy the ouput directory to `dependencies/clanlib`.

## AdaptiveShooter
Should be easy to compile using the VS solution files.
