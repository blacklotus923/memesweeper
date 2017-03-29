#include "MemeField.h"

void MemeField::Tile::SpawnMeme()
{
	hasMeme = true;
}

bool MemeField::Tile::HasMeme() const
{
	return hasMeme;
}

void MemeField::Tile::Draw(const Vei2 & gridPos, Graphics & gfx)
{
	SpriteCodex::DrawTileButton(gridPos*tileSize, gfx);
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

void MemeField::DrawField(Graphics & gfx)
{
	gfx.DrawRect(GetRekt(), SpriteCodex::baseColor);
	for (Vei2 gridPos = { 0,0 }; gridPos.y < height; ++gridPos.y)
	{
		for (gridPos.x = 0; gridPos.x < width; ++gridPos.x)
		{
			TileAt(gridPos).Draw(gridPos, gfx);
		}
	}
}

MemeField::Tile & MemeField::TileAt(const Vei2 gridPos)
{
	return field[gridPos.y * width + gridPos.x];
}

const MemeField::Tile & MemeField::TileAt(const Vei2 & gridPos) const
{
	return field[gridPos.y * width + gridPos.x];
}

RectI MemeField::GetRekt()
{
	return RectI(0,width*tileSize,0,height*tileSize);
}
