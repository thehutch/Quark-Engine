#pragma once

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

namespace QE
{
	/**
	 * Converts the mesh file at the specified path to the QMF format.
	 *
	 * @param filepath The filepath to the file to be converted
	 *
	 * @return True if successful, false otherwise
	 */
	extern void ConvertToQMF(const fs::path& filepath);
}
