#include "BaseTypes.h"
#include "IOManager.h"

#include <fstream>
#include "Errors.h"
#include "Logger.h"

namespace Engine
{
	bool IOManager::ReadFileToBuffer(const char* filepath, std::vector<byte>& buffer)
	{
		std::ifstream file(filepath, std::ios::binary);
		if (file.fail())
		{
			log("Could not open file %s", filepath);
			fatalError("Could not open file!");
			return false;
		}

		//seek to the end
		file.seekg(0, std::ios::end);

		//Get the file size
		int fileSize = (int) file.tellg();
		file.seekg(0, std::ios::beg);

		//reduce the file size by any header bytes that might be present
		fileSize -= (int) file.tellg();

		buffer.resize(fileSize);
		file.read((char*)&(buffer[0]), fileSize);
		return true;
	}
}