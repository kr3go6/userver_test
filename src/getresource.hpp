#include <string>
#include <iostream>
#include <filesystem>
#include <system_error>

namespace fs = std::filesystem;

std::string file_to_string(fs::path& filepath);
std::string file_to_string(fs::path&& filepath);