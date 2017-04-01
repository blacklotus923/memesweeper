#include "MemeField.h"
#include <algorithm>

void MemeField::Tile::SpawnMeme()
{
	hasMeme = true;
}

bool MemeField::Tile::HasMeme() const
{
	return hasMeme;
}

void MemeField::Tile::Draw(const Vei2 & screenPos, const FieldState& fstate, Graphics & gfx) const
{
	switch (fstate)
	{
	case FieldState::OK:
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
			else SpriteCodex::DrawTileNumber(memesAround, screenPos, gfx);
			break;
		}
	}
		break;
	case FieldState::GameOver:
	{
		switch (state)
		{
		case State::Hidden:
			if (hasMeme) SpriteCodex::DrawTileBomb(screenPos, gfx);
			else SpriteCodex::DrawTileButton(screenPos, gfx);
			break;
		case State::Flagged:
			SpriteCodex::DrawTileButton(screenPos, gfx);
			if (hasMeme)
			{
				SpriteCodex::DrawTileBomb(screenPos, gfx);
				SpriteCodex::DrawTileFlag(screenPos, gfx);
			}
			else
			{
				SpriteCodex::DrawTileFlag(screenPos, gfx);
				SpriteCodex::DrawTileCross(screenPos, gfx);
			}
			break;
		case State::Revealed:
			if (hasMeme) SpriteCodex::DrawTileBombRed(screenPos, gfx);
			else SpriteCodex::DrawTileNumber(memesAround, screenPos, gfx);
			break;
		}
	}
		break;
	case FieldState::Won:
	{
		switch (state)
		{
		case State::Hidden:
			if (hasMeme) SpriteCodex::DrawTileBomb(screenPos, gfx);
			else SpriteCodex::DrawTileNumber(memesAround, screenPos, gfx);
			break;
		case State::Flagged:
			if (hasMeme)
			{
				SpriteCodex::DrawTileButton(screenPos, gfx);
				SpriteCodex::DrawTileBomb(screenPos, gfx);
				SpriteCodex::DrawTileFlag(screenPos, gfx);
			}
			else
			{
				SpriteCodex::DrawTileFlag(screenPos, gfx);
				SpriteCodex::DrawTileCross(screenPos, gfx);
			}
			break;
		case State::Revealed:
			SpriteCodex::DrawTileNumber(memesAround, screenPos, gfx);
			break;
		}
	}
		break;
	}
}

void MemeField::Tile::Reveal()
{
	assert(!IsRevealed());
	state = State::Revealed;
}

bool MemeField::Tile::ToggleFlag()
{
	assert(!IsRevealed());
	if (IsFlagged())state = State::Hidden;
	else state = State::Flagged;
	return HasMeme();
}

bool MemeField::Tile::IsRevealed() const
{
	return state == State::Revealed;
}

bool MemeField::Tile::IsFlagged() const
{
	return (state == State::Flagged);
}

void MemeField::Tile::SetMemesAround(const int nMemes)
{
	memesAround = nMemes;
}

int MemeField::Tile::GetMemesAround() const
{
	return memesAround;
}

MemeField::MemeField(const int nMemes) : nMemes(nMemes)
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
	for (Vei2 gridPos = { 0,0 }; gridPos.y < height; ++gridPos.y)
	{
		for (gridPos.x = 0; gridPos.x < width; ++gridPos.x)
		{
			TileAt(gridPos).SetMemesAround(GetMemesAroundTile(gridPos));
		}
	}
}

void MemeField::Draw(Graphics & gfx) const
{
	gfx.DrawRect(GetRekt().GetExpanded(borderSize), borderColor);
	gfx.DrawRect(GetRekt(), SpriteCodex::baseColor);
	for (Vei2 gridPos = { 0,0 }; gridPos.y < height; ++gridPos.y)
	{
		for (gridPos.x = 0; gridPos.x < width; ++gridPos.x)
		{
			TileAt(gridPos).Draw((gridPos*SpriteCodex::tileSize)+offset, fstate, gfx);
		}
	}
}

bool MemeField::RevealAt(const Vei2 & screenPos)
{
	if (fstate == FieldState::OK)
	{
		assert(screenPos.x >= GetRekt().left && screenPos.x < GetRekt().right
			&& screenPos.y >= GetRekt().top && screenPos.y < GetRekt().bottom);
		Vei2 gridPos = ScreenToGrid(screenPos);
		if (!TileAt(gridPos).IsRevealed() && !TileAt(gridPos).IsFlagged())
		{
			TileAt(gridPos).Reveal();
			if (TileAt(gridPos).HasMeme())
			{
				fstate = FieldState::GameOver;
				return true;
			}
		}
	}
	return false;
}

bool MemeField::FlagAt(const Vei2 & screenPos)
{
	if (fstate == FieldState::OK)
	{
		assert(screenPos.x >= GetRekt().left && screenPos.x < GetRekt().right
			&& screenPos.y >= GetRekt().top && screenPos.y < GetRekt().bottom);
		Vei2 gridPos = ScreenToGrid(screenPos);
		if (!TileAt(gridPos).IsRevealed())
		{
			if (TileAt(gridPos).ToggleFlag())
			{
				memesFlagged++;
				if (memesFlagged == nMemes)
				{
					fstate = FieldState::Won;
					return true;
				}
			}
			else memesFlagged--;
		}
	}
	return false;
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
	return Vei2((screenPos-offset) / SpriteCodex::tileSize);
}

int MemeField::GetMemesAroundTile(const Vei2 gridPos) const
{
	const int xMin = std::max(0, gridPos.x - 1);
	const int yMin = std::max(0, gridPos.y - 1);
	const int xMax = std::min(width - 1, gridPos.x + 1);
	const int yMax = std::min(height -1, gridPos.y + 1);

	int c = 0;

	for (Vei2 gridPos = { xMin,yMin }; gridPos.y <= yMax; ++gridPos.y)
	{
		for (gridPos.x = xMin; gridPos.x <= xMax; ++gridPos.x)
		{
			if(TileAt(gridPos).HasMeme()) c++;
		}
	}

	return c;
}

RectI MemeField::GetRekt() const
{
	return RectI(xOffset, (width*SpriteCodex::tileSize) + xOffset, yOffset, (height*SpriteCodex::tileSize) + yOffset);
}

MemeField::FieldState MemeField::GetFieldState() const
{
	return fstate;
}
