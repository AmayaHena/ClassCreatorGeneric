/*
** EPITECH PROJECT, 2019
** ClassCreator
** File description:
** File
*/

/* MKDIR LIB */
#include <sys/stat.h>
#include <sys/types.h>

#include "File.hpp"

std::vector<std::string> File::getFileSrc(void)
{
	return _fileSrc;
}

std::vector<std::string> File::getFileInc(void)
{
	return _fileInc;
}

std::vector<std::string> File::getFileStart(void)
{
	return _fileStart;
}

std::vector<std::string> File::getHeader(void)
{
	return _header;
}

std::vector<std::string> File::getMakefile(void)
{
	return _make;
}

std::vector<std::string> File::getCMake(void)
{
	return _cmake;
}

bool File::checkFileExist(const std::string &s)
{
	struct stat buffer;

	if (stat(s.c_str(), &buffer) == -1) {
		std::cout << "\033[0;31mFile \033[0m" << s << "\033[0;31m doesnt exits\033[0m" << std::endl;
		return false;
	}
	return true;
}

bool File::checkDirExist(const std::string &s)
{
	struct stat buffer;

	if (stat(s.c_str(), &buffer) == -1) {
		std::cout << "\033[0;31mDir \033[0m" << s << "\033[0;31m doesnt exits\033[0m" << std::endl;
		return false;
	}
	return true;
}

std::vector<std::string> File::loadFileToV(const std::string &path)
{
	std::vector<std::string> v;
	std::ifstream f(path);
	std::string s;

	while(std::getline(f, s))
		v.push_back(s);
	std::cout << "\033[0;32mFile \033[0m" << path << "\033[0;32m loaded\033[0m" << std::endl;
	return v;
}

std::vector<std::string> File::loadFile(const std::string &path, const bool request)
{
	std::vector<std::string> v;

	v.clear();
	if (request == false)
		return v;
	if (File::checkFileExist(path) == false)
		return v;
	return File::loadFileToV(path);
}

bool File::loadConfig(Parser &p)
{
	_fileSrc = loadFile(p.getPathSrc(), true);
	if (_fileSrc.empty())
		return false;
	_fileStart = loadFile(p.getPathStart(), true);
	if (_fileStart.empty() && !p.getPathStart().empty())
		return false;
	_fileInc = loadFile(p.getPathInc(), true);
	if (_fileInc.empty() && !p.getPathInc().empty())
		return false;
	_make = loadFile("config/makefile", p.getMakefile());
	_cmake = loadFile("config/CMakeLists.txt", p.getCMake());
	if ((p.getMakefile() && _make.empty())
		|| (p.getCMake() && _cmake.empty()))
		return false;
	return true;
}
