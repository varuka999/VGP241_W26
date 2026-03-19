#pragma once

#include "TextureManager.h"

struct Vector2
{
	float x;
	float y;
};

class Entity
{
public:
	void Initialize(const std::string& textureFilePath)
	{
		mTextureID = TextureManager::Get()->LoadTexture(textureFilePath);
		RandomizePosition();
	}

	void Update()
	{
		RandomizePosition();
	}

	void Render()
	{
		if (TextureManager::Get()->GetTexture(mTextureID).Print())
		{
			std::cout << "(" << mPosition.x << ", " << mPosition.y << ") Distance: " << DistanceSqrToOrigin() << "\n";
		}
	}

	float DistanceSqrToOrigin() const
	{
		return (mPosition.x * mPosition.x) + (mPosition.y * mPosition.y);
	}

private:
	void RandomizePosition()
	{
		mPosition = { -20 + (float)(rand() % 41), -20 + (float)(rand() % 41) };
	}

	std::size_t mTextureID;
	Vector2 mPosition;
};