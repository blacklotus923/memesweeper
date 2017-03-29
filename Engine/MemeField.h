#pragma once
#include "Vei2.h"
#include "RectI.h"
#include "Graphics.h"
#include "SpriteCodex.h"
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
		void Draw(const Vei2& gridPos, Graphics& gfx);
	private:
		State state = State::Hidden;
		bool hasMeme = false;
	};

public:
	MemeField(int nMemes);
	void DrawField(Graphics& gfx);
	Tile& TileAt(const Vei2 gridPos);
	const Tile& TileAt(const Vei2& gridPos) const;
	RectI GetRekt();

public:

private:
	static constexpr int tileSize = 16;
	static constexpr int width = 20;
	static constexpr int height = 16;
	Tile field[width * height];
};