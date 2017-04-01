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
		void Draw(const Vei2& screenPos, const FieldState& fstate, Graphics& gfx) const;
		void Reveal();
		bool ToggleFlag();
		bool IsRevealed() const;
		bool IsFlagged() const;
		void SetMemesAround(const int nMemes);
		int GetMemesAround() const;

	private:
		State state = State::Hidden;
		bool hasMeme = false;
		int memesAround = -1;
	};

public:
	MemeField(const int nMemes);
	void Draw(Graphics& gfx) const;
	void RevealAt(const Vei2& screenPos);
	void FlagAt(const Vei2& screenPos);
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
	static constexpr int xOffset = (Graphics::ScreenWidth - (width*SpriteCodex::tileSize)) / 2;
	static constexpr int yOffset = (Graphics::ScreenHeight - (height*SpriteCodex::tileSize)) / 2;
	static constexpr int borderSize = 7;
	static constexpr Color borderColor = { 69,69,69 };
	int nMemes;
	int memesFlagged = 0;
	const Vei2 offset = { xOffset, yOffset };
	Tile field[width * height];
	FieldState fstate = FieldState::OK;
};