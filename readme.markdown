Adaptive Shooter
====================

Adaptive Shooter is a 2D shoot'em up game developed by Bruno Baère Pederassi Lomba de Araujo for his M.Sc. thesis in Computer Science at PUC-Rio.

The game uses artificial intelligence (dynamic difficulty adaptivity) to detect player performance and adapt enemies stats to better suit the player's skills. The paper generated from this work can be accessed at [Research Gate](https://www.researchgate.net/publication/261550744_Evaluating_dynamic_difficulty_adaptivity_in_shoot%27em_up_games).

Compiling
---------------------
Visual Studio 2010 was used to generate solution and project files.

For the ADAPTIVE version, you must define ADAPTIVE in src/Scene/TesteScenePlayer.cpp as 1.

For the NON-ADAPTIVE version, you must define ADAPTIVE in src/Scene/TestScenePlayer.cpp as 0.

Running the game
---------------------
In Release mode, the game executable file should be put in a directory with copies of data directory and Scripts directory.

Ex:
AdaptiveShooter.exe data/ Scripts/

Dependencies
---------------------
These dependencies should be compiled and included in dependencies directory

* ClanLib 3.0
* Lua 5.1.4
* Google Test Framework 1.6

License
---------------------
Check the LICENSE file for the legal license.

Acknowledgements
---------------------

- Lua 5.1.4 - Copyright 1994–2012 [Lua.org](http://www.lua.org), PUC-Rio.
- SpriteLib - Copyright 1996-2011 by Ari Feldman [Widget Worx](http://www.widgetworx.com).
- ArWing original design by Nintendo, art by [StepDragon](http://www.pixeljoint.com/p/27164.htm).
- Some of the sounds in this project were created by [David McKee (ViRiX)](http://soundcloud.com/virix).
- Sounds (c) by [Michel Baradari](http://apollo-music.de). Licensed under [CC BY 3.0](http://creativecommons.org/licenses/by/3.0/). Hosted on opengameart.org.
- Digital Memories by LukHash. Available at (http://www.jamendo.com/en/track/777892/digital-memories). Licensed under CC BY NC SA.
