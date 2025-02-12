#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "File_Manager.h"
#include <map>

enum class TextureName;

class TextureManager {

	std::map<std::string, SDL_Texture*> textures;
	bool is_init = false;

public:

	TextureManager() = default;
	
	void InitializeTextures(const std::vector<std::filesystem::path>& texture_path_list, SDL_Renderer* renderer);

	SDL_Texture* GetTexture(const std::string& name)const;
	SDL_Texture* GetTexture(const TextureName name)const;//for future

	~TextureManager();
public:
	TextureManager(const TextureManager&) = delete;
	TextureManager(TextureManager&&)noexcept = delete;
	TextureManager& operator=(const TextureManager&) = delete;
};

enum class TextureName {
	player_ver1,
};
