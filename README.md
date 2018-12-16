# Defeat the Nemesis
 ![](https://github.com/AleixCas95/Deafeat-the-Nemesis/blob/master/DevGame/Game/docs/startgame.PNG?raw=true)

## The game

For this assignment we have forked [Underground-Hero](https://github.com/MAtaur00/Underground-Hero) [v 0.3](https://github.com/MAtaur00/Underground-Hero/tree/0.3)

This is a little game made by two students of the Videogame Desing and Develompent degree. It is a small plataformer with two levels, where the player can move right, left and jump, attack and dash to kill the enemy.
The game has been made using C++, SDL and pugi libraries. 
The maps have been made using tiled as the colliders.

*Note: Player can kill all the enemies but sometimes, the enemy on the ground is hard to kill.

 ![](https://github.com/AleixCas95/Deafeat-the-Nemesis/blob/master/DevGame/Game/docs/websitephoto.jpg?raw=true)



## Authors 

 ### (Boy on the left) Aleix Castillo Arrià: [Aleix Castillo Arrià](https://github.com/AleixCas95)
 
 * In charge of all the base of the systems.
 * Pathfinding aplication.
 * Interaccion beetween modules.
 * Q&A.
 
 ### (Boy on the right)Albert Cayuela Naval: [Albert Cayuela Naval](https://github.com/AlbertCayuela)
 
 * UI Scenes modules
 * System elements
 * Sprites
 * Tools modules
 * Pathfinding
 
 
# The main core subsystems

Our code is structured in modules.
Paths, levels , animations and some textures are read and loaded through parsin xml files to avoid "magic numbers" or random variables, to make the reading and understanding easier.
The main module is the j1App.cpp/j1App.h Module, that manages all the others modules by calling them with the respective functions. Some of those funcions are shared with the J1Module.
Once we have all the necessaries module, we used folders with diferents systems for a better organization and perforance. Those systems are the Entities System and the UI sytem.




## Github repository link

[Link here](https://github.com/AleixCas95/DeafeatNemesis)

## Download the last verision

[Link here](https://github.com/AleixCas95/Deafeat-the-Nemesis/releases/tag/3.0)

## Gameplay Video

<iframe width="560" height="315" src="https://www.youtube.com/embed/MAiDKeBfwgA" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Controls

* Left and Right arrows to move

* Up arrow to jump.

* Left or Right while falling if you have a wall in your left or right to slide down.

* Up arrow to jump while sliding walls.

* F to make a dash.

* G to attack.


## Debugging Fucionalities

* F1  Start from the very first level 

* F2  Start from the beginning of the current level

* F3 Start from the next level

* F5  Save the current state 

* F6  Load the previous state (even across levels)

* F8  View UI Objects

* F9  To view colliders / logic 

* F10 God Mode

* F11 Cap FPS


 # License
 
 MIT License
 
 Copyright (c) [2018] [Aleix Castillo Arrià, Albert Cayuela Naval]
 
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE


