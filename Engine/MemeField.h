#pragma once
#include "Vei2.h"
#include "RectI.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include <assert.h>
#include <random>

class MemeField
{
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
		void Draw(const Vei2& screenPos, Graphics& gfx) const;
		void Reveal();
		bool IsRevealed();

	private:
		State state = State::Hidden;
		bool hasMeme = false;
	};

public:
	MemeField(int nMemes);
	void Draw(Graphics& gfx) const;
	void RevealAt(const Vei2& screenPos);
	RectI GetRekt() const;

private:
	Tile& TileAt(const Vei2& gridPos);
	const Tile& TileAt(const Vei2& gridPos) const;
	Vei2 ScreenToGrid(const Vei2& screenPos) const;

private:
	static constexpr int width = 20;
	static constexpr int height = 16;
	Tile field[width * height];
};