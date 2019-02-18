# SpaceInvaders
Space Invaders game clone done as a software project for C++ programming class

## Menu
Game starts in menu screen where you can select desired difficulty. Use arrow keys to navigate the menu and SPACE or ENTER key to confirm your choice. If you select CUSTOM game difficulty, you can then specify name of the configuraion file (see below for details).

## Gameplay
Your goal is to prevent attacking alient from landing on your planet. You can shoot them down using your cannon and gain score points. Shooting rockets costs you energy, which get restored over time (you can see your current energy level in the top right hand corner). If any of the enemies lands on ground, you lose a life. Also beware of shooting enemies. If a rocket hits you, you also lose a life.

### Controls
Use LEFT and RIGHT arrow keys to move sideways. Pressing and holding SPACE key shoots rockets from your cannon. 

P key pauses the game and ESCAPE returns you back to main menu if the game is paused.

## Configuraion
You can create custom difficulties using configuraion files located in `data/config/`. The file should have extension `.txt` and the name should contain only small letters and numbers (this is because of the font used to draw the text in the menu).

To open your custom game configuration, select CUSTOM game mode in the menu and type in the file name **without extension**.

### Gameplay options
First specify global gameplay options in format `OPTION:VALUE`, one per line.
* LIVES (how many lives does player have) - value is integer
* SPEED (movement speed of player) - value is float
* ENERGY_RESTORE (restore rate of player energy, one shot costs `0.15` energy and player has a maximum of `1` unit of energy) - value is float

### Waves
Then you can specify the waves of enemies. First write `WAVES:` on a separate line (including colon). Then each line represents one wave of enemies. Wave description must contain 4 parameters separated by a space character.

First parameter is number of enemies spawned in the wave (integer). Second is type of enemies, this parameter is string and can contain multiple values. If the string contains `S`, simple enemies get spawned. If it contains `M`, moving enemies get spawned. And lastly, use `H` for shooting enemies. If the second parameter contains more than one letter, all specified types can be spawned (one is selected at random for each new spawned enemy). Last two parameters are float numbers and represent the minimum and maximum time between spawning two enemies.

Each wave lasts untill all enemies of that wave are spawned. Then the next wave begins. Last wave keeps repeating until the player dies.

You can see examples of game configurations in `easy.txt`, `hard.txt` and `expert.txt` files.

