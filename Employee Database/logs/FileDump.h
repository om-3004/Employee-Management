#ifndef _FILEDUMP_H
#define _FILEDUMP_H

#include <iostream>
#include <fstream>
#include "string.h"

namespace LogSystem {
	class fileDump {
	private:
		std::ofstream outFile{};
	public:
		fileDump() : outFile{ "default-log.txt", std::ios::app } {}
		fileDump(const std::string& fileName) : outFile{ fileName, std::ios::app } {}

		void flushStream(const std::string& m_BufferLog) {
			outFile << m_BufferLog;
			outFile.flush();
		}
	};
}

#endif