#pragma once
#include "Vei2.h"
#include "RectI.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include <assert.h>
#include <random>

class MemeField
{
public:
	enum class FieldState {OK,GameOver,Won};
private:
	class Tile
	{
	public:
		enum class State
		{
			Hidden,
			Flagged,
			Revealed
		};
	public:
		void SpawnMeme();
		bool HasMeme() const;
		void Draw(const Vei2& screenPos, const FieldState& fstate, Graphics& gfx);
		void Reveal();
		void SetPressed(bool pressed);
		void ToggleFlag();
		bool IsRevealed() const;
		bool IsFlagged() const;
		void SetMemesAround(const int nMemes);
		int GetMemesAround() const;

	private:
		State state = State::Hidden;
		bool hasMeme = false;
		int memesAround = -1;
		bool isPressed = false;
	};

public:
	MemeField(const Vei2& center, const int nMemes);
	void Draw(Graphics& gfx);
	void PressAt(const Vei2& screenPos);
	bool RevealAt(const Vei2& screenPos);
	bool FlagAt(const Vei2& screenPos);
	RectI GetRekt() const;
	FieldState GetFieldState() const;

private:
	Tile& TileAt(const Vei2& gridPos);
	const Tile& TileAt(const Vei2& gridPos) const;
	Vei2 ScreenToGrid(const Vei2& screenPos) const;
	int GetMemesAroundTile(const Vei2 gridPos) const;

private:
	static constexpr int width = 5;
	static constexpr int height = 5;
	static constexpr int borderSize = 7;
	static constexpr Color borderColor = { 69,69,69 };
	int nMemes;
	int nFlags;
	int memesFlagged = 0;
	Vei2 center;
	Vei2 offset = center - Vei2{(width*SpriteCodex::tileSize) / 2, (height*SpriteCodex::tileSize) / 2};
	Tile field[width * height];
	FieldState fstate = FieldState::OK;
};