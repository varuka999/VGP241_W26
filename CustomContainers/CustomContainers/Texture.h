#pragma once

#include <iostream>

class Texture
{
public:
	Texture() {}

	Texture(const std::string& filePath)
		: mFilePath(filePath)
	{

	}

	~Texture() {}

	bool Print() const
	{
		if (mFilePath.empty())
		{
			return false;
		}

		std::cout << "Rendering: " << mFilePath << " ";
		return true;
	}

private:
	std::string mFilePath = "";
};