Adaptive Shooter
====================

Adaptive Shooter is a 2D shoot'em up game developed by Bruno Baère Pederassi Lomba de Araujo for his M.Sc. thesis in Computer Science at PUC-Rio.

The game uses artificial intelligence (dynamic difficulty adaptivity) to detect player performance and adapt enemies stats to better suit the player's skills. The paper generated from this work can be accessed at [Research Gate](https://www.researchgate.net/publication/261550744_Evaluating_dynamic_difficulty_adaptivity_in_shoot%27em_up_games).

Building
---------------------
See [BUILDING.md](BUILDING.md) for details.

| Service | System | Compiler | Status |
| ------- | ------ | -------- | -----: |
|[Travis-CI](https://app.travis-ci.com/github/killerasus/adaptive_shooter)| Ubuntu 16.04.7 LTS | gcc 5.4.0 | [![Build Status](https://app.travis-ci.com/killerasus/adaptive_shooter.svg?branch=master)](https://app.travis-ci.com/github/killerasus/adaptive_shooter) |

Running the game
---------------------
In Release mode, the game executable file should be put in a directory with copies of data directory and Scripts directory. This is automatic in Linux using `cmake`.

Windows example:
AdaptiveShooter.exe data/ Scripts/

Dependencies
---------------------
In a Windows build, these dependencies should be compiled and included in dependencies directory

* [ClanLib 3.0](https://github.com/sphair/ClanLib/tree/3.0-stable)
* [Lua 5.1.4](https://sourceforge.net/projects/luabinaries/files/5.1.4/)
* [Google Test Framework 1.6](https://github.com/google/googletest)

License
---------------------
[![MIT License][license-badge]](LICENSE)
Check the [LICENSE](LICENSE) file for the legal license.

Acknowledgements
---------------------

- ClanLib 3.0-stable - Copyright (c) 1997-2005 The ClanLib Team
- Lua 5.1.4 - Copyright 1994–2012 [Lua.org](http://www.lua.org), PUC-Rio.
- SpriteLib - Copyright 1996-2011 by Ari Feldman [Widget Worx](http://www.widgetworx.com).
- ArWing original design by Nintendo, art by [StepDragon](http://www.pixeljoint.com/p/27164.htm).
- Some of the sounds in this project were created by [David McKee (ViRiX)](http://soundcloud.com/virix).
- Sounds (c) by [Michel Baradari](http://apollo-music.de). Licensed under [CC BY 3.0](http://creativecommons.org/licenses/by/3.0/). Hosted on [opengameart.org](http://opengameart.org).
- Digital Memories by LukHash. Available at (http://www.jamendo.com/en/track/777892/digital-memories). Licensed under CC BY NC SA.

[license-badge]: https://img.shields.io/badge/license-MIT-007EC7.svg
