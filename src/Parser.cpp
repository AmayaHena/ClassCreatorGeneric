/*
** EPITECH PROJECT, 2019
** ClassCreator
** File description:
** parser
*/

#include "Parser.hpp"

Parser::Parser() : _makefile(false), _cmake(false) {}

std::string Parser::getProjectName(void)
{
	return _project_name;
}

std::vector<std::string> Parser::getSubFiles(void)
{
	return _sub_files;
}

bool Parser::getMakefile(void)
{
	return _makefile;
}

bool Parser::getCMake(void)
{
	return _cmake;
}

std::string Parser::getArchitecture()
{
	return _architecture;
}

std::string Parser::getCompiler()
{
	return _compiler;
}

std::string Parser::getPathStart()
{
	return _path_start;
}

std::string Parser::getPathSrc()
{
	return _path_src;
}

std::string Parser::getPathInc()
{
	return _path_inc;
}

std::string Parser::getExthStart()
{
	return _ext_start;
}

std::string Parser::getExthSrc()
{
	return _ext_inc;
}

std::string Parser::getExtInc()
{
	return _ext_inc;
}

bool Parser::helperCommand()
{
    std::cout << "usage: classCreator [Project Name] [-MCAcSsif] ..." << std::endl
              << std::endl << "\tOptions:" << std::endl
              << "\t-M\tmake a makefile" << std::endl
              << "\t-C\tmake CMakeLists.txt for CMake" << std::endl
              << "\t-c\ttake your compiler as parametter" << std::endl
              << "\t-s\ttake your config file for src folder" << std::endl
              << "\t-i\ttake your config file for inc folder" << std::endl
              << "\t-S\ttake your config file for start function" << std::endl
              << "\t-A\ttake a file as parameter following this option and generate an architecture" << std::endl << std::endl;
    return false;
}

void Parser::AVOptions(const std::vector<std::string> &v, const unsigned int i)
{
	for (int j = 1; v[i][j]; j++) {
		switch (v[i][j]) {
		case 'M' :
			_makefile = true;
			break;
		case 'C' :
			_cmake = true;
			break;
		case 'A' :
			_architecture = v[i + 1];
			break;
		case 'c' :
			_compiler = v[i + 1];
			break;
		case 'S' :
			_path_start = v[i + 1];
			break;
		case 's' :
			_path_src = v[i + 1];
			break;
		case 'i' :
			_path_inc = v[i + 1];
			break;
		case 'f' :
			for (unsigned z = i + 1; v[z][0] != '-'; z++) {
				if (v[z].empty())
					return;
				_sub_files.push_back(v[z]);
			}
			break;
		}
	}
}

bool Parser::parsingAV(const std::vector<std::string> &v)
{
	if (v.empty())
		return false;
	if (v[0] == "-h")
		return Parser::helperCommand();
	_project_name = v[0];
	for (unsigned int i = 1; i < v.size(); i++)
		if (v[i][0] == '-')
			Parser::AVOptions(v, i);
	return true;
}

bool Parser::configCheck()
{
	if (_path_src.empty())
		return false;
	if (_makefile && _compiler.empty())
		return false;
	return true;
}

std::string Parser::parseExt(std::string &s)
{
	std::string ext;
	int i = 0;

	while (s[i++] != '.');
	for (int j = 0; s[i]; i++)
		ext[j] += s[i];
	return ext;
}

void Parser::extension()
{
	if (!_path_start.empty())
		_ext_start = Parser::parseExt(_path_start);
	if (!_path_src.empty())
		_ext_src = Parser::parseExt(_path_src);
	if (!_path_inc.empty())
		_ext_inc = Parser::parseExt(_path_inc);
}

bool Parser::parsingProceed(const std::vector<std::string> &v)
{
	if (v.empty())
		return false;
	Parser::parsingAV(v);
	if (!Parser::configCheck())
		return false;
	Parser::extension();
	return true;
}
