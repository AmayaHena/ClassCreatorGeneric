/*
** EPITECH PROJECT, 2019
** ClassCreatorWIP
** File description:
** State
*/

#include "State.hpp"

void State::createInc(Parser &p, Writer &w, const std::vector<std::string> &file, const std::string &path, std::string name)
{
	w.setFile(file);
	w.create(name , p.getProjectName() + "/inc" + path, p.getExtInc());
}

void State::createSrc(Parser &p, Writer &w, const std::vector<std::string> &file, const std::string &path, std::string name)
{
	w.setFile(file);
	w.create(name, p.getProjectName() + "/src" + path, p.getExtSrc());
}

void State::createIncRoot(Parser &p, Writer &w, const std::vector<std::string> &file, const std::string &s)
{
	w.setFile(file);
	w.create(s, p.getProjectName() + "/inc", p.getExtInc());
}

void State::createSrcRoot(Parser &p, Writer &w, const std::vector<std::string> &file, const std::string &s)
{
	w.setFile(file);
	w.create(s, p.getProjectName() + "/src", p.getExtSrc());
}

void State::generateStart(Parser &p, Writer &w, const std::vector<std::string> &file)
{
	if (p.getPathStart().empty())
		return;
	w.setFile(file);
	w.create("start", p.getProjectName(), p.getExtStart());
}

void State::generateMakefile(Parser &p, Writer &w, const std::vector<std::string> &file, const std::vector<std::string> &src)
{
	if (!p.getMakefile())
		return;
	w.setFile(file);
	w.setSrc(src);
	w.create("Makefile", p.getProjectName(), "Makefile");
}

void State::generateCMake(Parser &p, Writer &w, const std::vector<std::string> &file, const std::vector<std::string> &inc, const std::vector<std::string> &src)
{
	if (!p.getCMake())
		return;
	w.setFile(file);
	w.setInc(inc);
	w.setSrc(src);
	w.create("CMakeLists", p.getProjectName(), "CMake");
}