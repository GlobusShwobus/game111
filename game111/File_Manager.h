#pragma once

#include <fstream>
#include <filesystem>

class FileManager {

public:
	
	FileManager() = default;

	const std::vector<std::filesystem::path> GetTextureFolderContents(const char* relative_folder_path)const;

private:
	FileManager(const FileManager&) = delete;
	FileManager(FileManager&&)noexcept = delete;
	FileManager& operator=(const FileManager&) = delete;
};