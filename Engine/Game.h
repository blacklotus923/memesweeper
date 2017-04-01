/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "MemeField.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	MemeField field;
	/********************************/
};

//TODO

//Check if mouse is contained by rect of grid (add recti function Contains) _DONE
//Handle mouse events to get just the left down/ right down event (use while !kbd.mouse.isempty()) _DONE
//Flag toggle function, isflagged function _DONE
//only flag when not revealed _DONE
//function to get number of memes around tile, function to set neighbor memes for each tile _DONE
//track number of memes nearby per tile _DONE
//draw numbers (add function to spritecodex to take int and draw)  _DONE
//draw based on fucked/not fucked _DONE

//Homework:
//draw grid centered on screen _DONE
//draw border around grid
//add win/lose state and screen
//add only as much flags as bombs
//change mouse click so that holding the mouse "presses" the button, but action taken only when releasing left button
//and draws tile button in pressed state under mouse while pressed