# Linux

## Dependencies
1. sudo apt-get install make g++ automake libtool libfreetype6-dev libfontconfig1-dev libgl1-mesa-dev libxrender-dev libasound2-dev doxygen lua52-devel
2. Clone my fork of ClanLib 3.0 with VS14 patch http://github.com/killerasus/ClanLib
3. On ClanLib directory git checkout patch-1
4. ./autogen.sh && ./configure && make && sudo make install

## AdaptiveShooter
1. cmake .
2. make
