Adaptive Shooter
====================

Adaptive Shooter is a 2D shoot'em up game developed by Bruno Baère Pederassi Lomba de Araujo for his M.Sc. thesis in Computer Science at PUC-Rio.

The game uses artificial intelligence (dynamic difficulty adaptivity) to detect player performance and adapt enemies stats to better suit the player's skills. The paper generated from this work can be accessed at [Research Gate](https://www.researchgate.net/publication/261550744_Evaluating_dynamic_difficulty_adaptivity_in_shoot%27em_up_games).

Building
---------------------
See [BUILDING.md](BUILDING.md) for details.

| Service | Status |
| ------- | -----: |
| GitHub Actions (CMake) | [![CMake](https://github.com/killerasus/adaptive_shooter/actions/workflows/cmake.yml/badge.svg?branch=master)](https://github.com/killerasus/adaptive_shooter/actions/workflows/cmake.yml) |

Running the game
---------------------
The game executable must run with copies of the `data/` directory and the `Scripts/` directory
alongside it. CMake's post-build step copies both automatically, in Debug and Release alike —
just launch the executable from its own folder:

Linux example:
```bash
./build/bin/AdaptiveShooter
```

Windows example:
```cmd
.\build\bin\Release\AdaptiveShooter.exe
```

Dependencies
---------------------
All dependencies are bundled with the repository and built automatically by CMake —
no manual compilation step:

* [ClanLib 3.0](https://github.com/killerasus/ClanLib/tree/cmake) (`cmake` branch, built in-tree)
* [Lua 5.1.4](https://www.lua.org) (sources vendored under `dependencies/lua/`, built as static `lua51`)
* [Google Test Framework 1.6](https://github.com/google/googletest) (`dependencies/gtest-1.6.0/`)

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
