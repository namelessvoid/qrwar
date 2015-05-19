------------
Introduction
------------

Quad Ruled War (qrw) is a turn based strategy game taking place on a board seperated into squares much like chess. The goal was to produce a minimalistic game for short and fast battles. It only supports hot seat modus for two players on one machine.

--------
Building
--------

.. image:: https://travis-ci.org/namelessvoid/qrwar.svg?branch=master
    :target: https://travis-ci.org/namelessvoid/qrwar.. image:: https://travis-ci.org/namelessvoid/qrwar.png?branch=master :target: https://travis-ci.org/namelessvoid/qrwar :alt: Travis build status image


The source comes with an CMake file and dependes on:

- CMake
- SFML_ (>= 2.0)
- SFGUI_ (>= 0.2.0)
- TinyXML_ (>= 2.0)
- CppUnit_ (for unittesting only)

Notes:

Issues with Ubuntu and TinyXML2: Ubuntu provides a quite old tinyxml2 version through apt, so you have to build it manuall.

Issues with Ubuntu and SFGUI: I ran into compiling errors ('looser throw specifier') when compiling SFGUI on Ubuntu. This may be caused by a bug in g++-4.7.3 and could be resolved by upgrading to g++-4.8. You can have a look at `this <https://github.com/namelessvoid/qrwar/blob/aa780eef5637fe3d4d8cd6a3c3bb148e3e9377af/.travis.yml#L6-L9>`_ to see how I did it.

There are issues (at least on Linux Mint) when SFML 1.6 and 2.0 are installed at the same time. Altough requires(SFML 2.0) is set, it seems to find 1.6 first and make tries to link against the old library.

If you've got any problems feel free to create an issue.

Installation is not yet supported.

--------
The Game
--------

========
Controls
========

The game is primarily controlled by mouse. During deployment, a unit / terrain can be selected in the right sidebar and placed by clicking on an empty square on the board. A unit can be moved by selecting it on the board and clicking the destinatin square.

===============
Units & Terrain
===============

Image explanation:

- Hitpoints: |HP|
- Attack: |Attack|
- Defense: |Defense|
- Movement: |Movement|

- Swordman: |Swordman|
- Archer: |Archer|
- Spearman: |Spearman|

- Wood: |Wood|
- Hill: |Hill|
- Tower: |Tower|

+----------+------+--------+---------+----------+
| Name     | |HP| ||Attack|||Defense|||Movement||
+----------+------+--------+---------+----------+
||Swordman||  5   | 2      | 1       | 3        |
+----------+------+--------+---------+----------+
||Archer|  |  5   | 2      | 1       | 3        |
+----------+------+--------+---------+----------+
||Spearman||  5   | 2      | 1       | 3        |
+----------+------+--------+---------+----------+
||Wood|    |      | -1     | +1      |          |
+----------+------+--------+---------+----------+
||Hill|    |      | +1     | -1      |          |
+----------+------+--------+---------+----------+
||Tower|   |      | +1     | +1      |          |
+----------+------+--------+---------+----------+


========
Gameplay
========

The game is parted in 3 phases:

1. Unit selection
2. Deployment and Terrain placement
3. Battle

When hitting "New game" a window pops up. You can set the size of the board and the number of each unit both players get.

After "Start game" was clicked you are on the battlefield to deploy your units. You can select what you want to place on the menu on the right. Move the Cursor with the arrow keys to the destination and hit return.

"Into battle" starts the actual game. On the right top menu the name of the current player appears. He can move the cursor with the arrow keys. Hitting return selects the current unit. Move the appearing red cursor to the destination (plain square to move, enemy unit to attack) and hit return again to perform the action.

"Next" changes the player. The battle is over when one player has no units left.

---------------------
Third party resources
---------------------

- Knightsquest.ttf_

  True Type Font by GemFonts_ See the .zip file for further information.

.. Dependencies:
.. _SFML: http://www.sfml-dev.org/
.. _SFGUI: http://sfgui.sfml-dev.de/
.. _CppUnit: http://sourceforge.net/projects/cppunit/
.. _TinyXml: http://www.grinninglizard.com/tinyxml2/index.html

.. Images:
.. |HP| image:: https://github.com/namelessvoid/qrwar-data/raw/master/img/gui/health.png
.. |Attack| image:: https://github.com/namelessvoid/qrwar-data/raw/master/img/gui/attack.png
.. |Defense| image:: https://github.com/namelessvoid/qrwar-data/raw/master/img/gui/defense.png
.. |Movement| image:: https://github.com/namelessvoid/qrwar-data/raw/master/img/gui/movement.png

.. |Archer| image:: https://github.com/namelessvoid/qrwar-data/raw/master/img/units/p1archer.png
.. |Swordman| image:: https://github.com/namelessvoid/qrwar-data/raw/master/img/units/p1swordman.png
.. |Spearman| image:: https://github.com/namelessvoid/qrwar-data/raw/master/img/units/p1spearman.png

.. |Wood| image:: https://github.com/namelessvoid/qrwar-data/raw/master/img/terrain/wood.png
.. |Hill| image:: https://github.com/namelessvoid/qrwar-data/raw/master/img/terrain/hill.png
.. |Tower| image:: https://github.com/namelessvoid/qrwar-data/raw/master/img/terrain/wall.png


.. Third party stuff:
.. _Knightsquest.ttf: http://moorstation.org/typoasis/designers/graham/fonts/knightsq.zip
.. _GemFonts: http://moorstation.org/typoasis/designers/gemnew/home.html
