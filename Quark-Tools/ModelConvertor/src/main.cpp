#include "convertor.hpp"

/**
 * Parses the commandline arguments and searches for the file paths which will be processed
 *
 * @param argc The number of commandline arguments
 * @param argv The commandline arguments
 * @param files The file paths
 */
void ParseCommandLine(int argc, char* argv[], std::vector<fs::path>& files);

int main(int argc, char* argv[])
{
	// Parse the command line
	std::vector<fs::path> files;
	ParseCommandLine(argc, argv, files);

	// Convert all the files from the command line
	for (const auto& filepath : files)
	{
		QE::ConvertToQMF(filepath);
	}

	return EXIT_SUCCESS;
}

void ParseCommandLine(int argc, char* argv[], std::vector<fs::path>& files)
{
	// Convert the arguments to a vector
	std::vector<std::string> args(argc);
	for (auto i = 0; i < argc; ++i)
	{
		args[i] = argv[i];
	}

	for (auto i = 0U; i < args.size(); ++i)
	{
		if ((i + 1) < args.size())
		{
			if (args[i] == "-f")
			{
				auto path = fs::u8path(args[i + 1]);
				if (fs::is_regular_file(path))
				{
					files.push_back(path);
					i++;
				}
			}
			else if (args[i] == "-d")
			{
				auto path = fs::u8path(args[i + 1]);
				if (fs::is_directory(path))
				{
					for (auto& entry : fs::directory_iterator(path))
					{
						if (fs::is_regular_file(entry))
						{
							files.push_back(entry);
							i++;
						}
					}
				}
			}
		}
	}
}
