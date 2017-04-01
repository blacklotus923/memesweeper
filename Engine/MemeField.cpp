#include "MemeField.h"

void MemeField::Tile::SpawnMeme()
{
	hasMeme = true;
}

bool MemeField::Tile::HasMeme() const
{
	return hasMeme;
}

void MemeField::Tile::Draw(const Vei2 & screenPos, Graphics & gfx) const
{
	switch (state)
	{
	case State::Hidden:
		SpriteCodex::DrawTileButton(screenPos, gfx);
		break;
	case State::Flagged:
		SpriteCodex::DrawTileButton(screenPos, gfx);
		SpriteCodex::DrawTileFlag(screenPos, gfx);
		break;
	case State::Revealed:
		if (hasMeme) SpriteCodex::DrawTileBomb(screenPos, gfx);
		else SpriteCodex::DrawTile0(screenPos, gfx);
		break;
	}
}

void MemeField::Tile::Reveal()
{
	state = State::Revealed;
}

bool MemeField::Tile::IsRevealed()
{
	return state == State::Revealed;
}

MemeField::MemeField(int nMemes)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> xDist(0, width - 1);
	std::uniform_int_distribution<int> yDist(0, height - 1);

	for (int spawned = 0; spawned < nMemes; spawned++)
	{
		Vei2 spawnPos;
		do
		{
			spawnPos = { xDist(rng), yDist(rng) };
		} while (TileAt(spawnPos).HasMeme());
		TileAt(spawnPos).SpawnMeme();
	}
}

void MemeField::Draw(Graphics & gfx) const
{
	gfx.DrawRect(GetRekt(), SpriteCodex::baseColor);
	for (Vei2 gridPos = { 0,0 }; gridPos.y < height; ++gridPos.y)
	{
		for (gridPos.x = 0; gridPos.x < width; ++gridPos.x)
		{
			TileAt(gridPos).Draw(gridPos*SpriteCodex::tileSize, gfx);
		}
	}
}

void MemeField::RevealAt(const Vei2 & screenPos)
{
	assert(screenPos.x >= 0 && screenPos.x < width*SpriteCodex::tileSize
		&& screenPos.y >= 0 && screenPos.y < height*SpriteCodex::tileSize);
	Vei2 gridPos = ScreenToGrid(screenPos);
	if(!TileAt(gridPos).IsRevealed()) TileAt(screenPos / SpriteCodex::tileSize).Reveal();
}

MemeField::Tile & MemeField::TileAt(const Vei2& gridPos)
{
	return field[gridPos.y * width + gridPos.x];
}

const MemeField::Tile & MemeField::TileAt(const Vei2 & gridPos) const
{
	return field[gridPos.y * width + gridPos.x];
}

Vei2 MemeField::ScreenToGrid(const Vei2 & screenPos) const
{
	return Vei2(screenPos / SpriteCodex::tileSize);
}

RectI MemeField::GetRekt() const
{
	return RectI(0,width*SpriteCodex::tileSize,0,height*SpriteCodex::tileSize);
}
