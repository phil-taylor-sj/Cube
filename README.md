# Cube

Cube is yet another step in the ongoing struggle to turn the 1997 cult classic into a viable game.

<p align="center">
	<img src="https://raw.githubusercontent.com/phil-taylor-sj/images/main/cube-gameplay.png" alt="Logo" width="950"/>
</p>

## Structure

| Library | Overview |
| :--- | :--- |
| Actor | An entity component system to hold all dynamic entities which not tied to a single cell (Room) including the player entity. |
| Assets | A library comprised of singleton class objects to hold all texture, font and audio files.  |
| Engine | A library for the main game engine and input handler functionality. |
| Levels | A separate entity manager for the level environment. Each room is represented by a separate entity in which all associated features (walls, screens, sensors, labels, etc.) are contained as components. |
| Physics | A library to manage all collision detection and collision interaction functions. Includes a custom vector template class (Vec2) for storing and manipulating coordinates. |
| Scenes | A library which contains discrete game scenes (title screen, active level, game over screen, etc.), which are interchangable in the game engine. |
| Utilities | An auxillary library which contains all miscelaneous functions; predominantly mathematical and numerical processing, and procedural generation. |

## Setup & Configuration

1. Clone the repository

	`git clone https://github.com/phil-taylor-sj/Cube.git`

2. Download the SFML binaries, rename to SFML, and move into the lib/ folder.

	[Simple Fast Multimedia Library](https://www.sfml-dev.org/download/sfml/2.6.1/)
	Visual Studio C++ 64-bit

3. Navigate to the project folder and create a new build directory.

	`cd Cube`
	`mkdir build`
 
4. Navigate in the build directory and run CMake to setup the visual studio project file.

	`cd build`
	`CMake ../`

	Note: If CMake is not set to Visual Studio by default, the generator must be specified manually:

	`CMake -G "Visual Studio 17 2022" ../`

5. Open the Cube.sln project file in Visual Studio.

6. Right click on the 'Cube' project library and select 'Set as Startup Project'.
