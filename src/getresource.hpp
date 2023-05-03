#include <string>
#include <iostream>
#include <filesystem>
#include <system_error>

namespace std_fs = std::filesystem;

std::string file_to_string(std_fs::path& filepath);
std::string file_to_string(std_fs::path&& filepath);