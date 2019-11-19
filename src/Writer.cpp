/*
** EPITECH PROJECT, 2019
** ClassCreator
** File description:
** Writer
*/

/* STD Library */
#include <functional>

/* STD Types Library */
#include <fstream>
#include <string>

#include "Writer.hpp"

Writer::Writer() : _tag_ref("/*#!")
{
	_type["Makefile"] = MAKE;
	_type["CMake"] = CMAKE;

	_tagMake["ProgramName"] = PROGNAME;
	_tagMake["SrcMakefile"] = SRCMAKE;
	_tagMake["SrcCMake"] = SRCCMAKE;
	_tagMake["IncCMake"] = INCCMAKE;
	_tagMake["Compiler"] = COMPILER;
}

void Writer::setHeader(std::vector<std::string> v)
{
	_header = v;
}

void Writer::setFile(const std::vector<std::string> &v)
{
	_file = v;
}

void Writer::setSrc(const std::vector<std::string> &v)
{
	_src = v;
}

void Writer::setInc(const std::vector<std::string> &v)
{
	_inc = v;
}

void Writer::setCompiler(const std::string &s)
{
	_compiler = s;
}

void Writer::cleanRessources()
{
	_of.close();
	_file.clear();
	_src.clear();
	_inc.clear();
	_compiler.clear();
}

int Writer::occurenceNbInS(const std::string &s, const std::string &tag)
{
	int N = s.length();
	int M = tag.length();
	int match = 0;
	int j = 0;

	for (int i = 0; i <= N - M; i++) {
		for (j = 0; j < M; j++)
			if (s[i + j] != tag[j])
				break;
		if (j == M)
			match++;
	}
	return match;
}

void Writer::writeVectorInFile(const std::string &s1, const std::vector<std::string> &v, const std::string &s2)
{
	for (const std::string &s: v)
		_of << s1 << s << s2 << std::endl;
}

std::ofstream Writer::createFile(const std::string &name, const std::string &path, const std::string &type)
{
	std::string s;

	switch (_type[type]) {
		case MAKE:
			s = path + "/Makefile";
			break;
		case CMAKE:
			s = path + "/CMakeLists.txt";
			break;
		default:
			s = path + "/" + name + type;
			break;
	}
	std::ofstream file(s);
	std::cout << "\033[0;32mFile \033[0m" << path << '/' << name << "\033[0;32m created\033[0m" << std::endl;
	return file;
}

void Writer::useTagG(const std::string &tag, const std::string &name)
{
	if (tag == "FileName")
		_of << name;
}

void Writer::useTagMake(const std::string &tag, const std::string &path)
{
	switch (_tagMake[tag]) {
		case PROGNAME :
			_of << path;
			return;
		case SRCMAKE :
			Writer::writeVectorInFile("\t\t", _src, "\t\\");
			return;
		case SRCCMAKE :
			Writer::writeVectorInFile("\t", _src, "");
			return;
		case INCCMAKE :
			Writer::writeVectorInFile("\t", _inc, "");
			return;
		case COMPILER :
			_of << _compiler;
			return;
	}
}

void Writer::useTag(const std::string &tag, const std::string &path, const std::string &type)
{
	if (tag == "Header") {
		Writer::writeVectorInFile("", _header, "");
		return;
	}
	switch (_type[type]) {
		case MAKE :
			Writer::useTagMake(tag, path);
			return;
		case CMAKE :
			Writer::useTagMake(tag, path);
			return;
		default:
			Writer::useTagG(tag, path);
			return;
	}
}

void Writer::processTag(const std::string &s, const std::string &path, const std::string type)
{
	std::string buf;
	int i = 0;
	int j = s.find(_tag_ref, 0);
	int k = Writer::occurenceNbInS(s, _tag_ref);

	for (int m = 0; m != k; m++) {
		while (i < j)
			_of << s[i++];
		while (s[i++] != '!');
		while (s[i] != '*')
			buf += s[i++];
		i += 2;
		Writer::useTag(buf, path, type);
		j = s.find(_tag_ref, j + 1);
		buf.clear();
	}
	for (unsigned int pos = i; pos < s.length(); pos++)
		_of << s[pos];
	_of << std::endl;
}

bool Writer::create(const std::string &name, const std::string &path, const std::string type)
{
	_of = Writer::createFile(name, path, type);

	for (const std::string &s: _file) {
		if (Writer::occurenceNbInS(s, _tag_ref) > 0)
			Writer::processTag(s, path, type);
		else
			_of << s << std::endl;
	}
	Writer::cleanRessources();
	return true;
}
