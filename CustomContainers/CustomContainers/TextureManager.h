#pragma once

#include "Globals.h"
#include "Texture.h"
#include "UnorderedMap.h"

class TextureManager
{
public:
	static TextureManager* Get()
	{
		static TextureManager sInstance;
		return &sInstance;
	}

	std::size_t LoadTexture(const std::string& filePath)
	{
		std::size_t uniqueID = Globals::HashFunction(filePath);
		Texture texture(filePath);
		mTextures.Insert(uniqueID, texture);

		return uniqueID;
	}

	Texture GetTexture(std::size_t uniqueID) const
	{
		Texture texture;
		if (mTextures.Find(uniqueID, texture)) {}
		else { std::cout << "Texture not found!\n"; }

		return texture;
	}

private:
	TextureManager() = default;
	~TextureManager() = default;
	UnorderedMap<std::size_t, Texture> mTextures;
};