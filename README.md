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

 * (Boy on the left)Aleix Castillo Arrià: [Aleix Castillo Arrià](https://github.com/AleixCas95)

 * (Boy on the right)Albert Cayuela Naval: [Albert Cayuela Naval](https://github.com/AlbertCayuela)
 
 # Development of the Assignature
 
We began with the creation of two map levels using tiled, after learning how to load those levels with tiled to the code, we start with  adding, saving and loading the player(with some basic movement). Once we got the player working, we iplemented enemies, their path using BFS, dijkstra and then the A*. After that the interaction with the player. At the same time we included the control of the framrate in the game capping the FPS or changing it with the dt of the game. We also used Brofiler to know how efficient is our code and finally we implemented the User Interface and the HUD of the game. One of the main recourses for this assignament was the implementation of entities system to controll all the modules and their caracteristics.
 
 
 ## Tasks done
 
 ### Aleix Castillo Arrià:
 * Entities system
 * Enemy Air entity
 * Player dash/attack states
 * Enemies pathing
 * Player-enemies interaction
 * Profiling
 
 ### Albert Cayuela Naval:
 * Enemy Ground entity
 * Timer 
 * Pathfinding
 * Enemies pathing
 * UML



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


## Github repository link

https://github.com/AleixCas95/DeafeatNemesis

## Download the last verision

link release

 ### License
 
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


