/*
** EPITECH PROJECT, 2019
** ClassCreatorWIP
** File description:
** State
*/

#ifndef STATE_HPP_
#define STATE_HPP_

/* STD LIB */
#include <iostream>
#include <vector>

/* Class */
#include "Parser.hpp"
#include "Writer.hpp"
#include "Dir.hpp"

class State {

	public:

		State() = default;
		~State() = default;

		/* Tools - state the writer and launch writer */

		/* CPP HPP Interface for complex arch */
		void createInc(Parser &p, Writer &w, const std::vector<std::string> &file, const std::string &path, std::string name);
		void createSrc(Parser &p, Writer &w, const std::vector<std::string> &file, const std::string &path, std::string name);

		/* CPP HPP Interface at Root */
		void createIncRoot(Parser &p, Writer &w, const std::vector<std::string> &file, const std::string &s);
		void createSrcRoot(Parser &p, Writer &w, const std::vector<std::string> &file, const std::string &s);

		/* main Makefile CMake at Root */
		void generateStart(Parser &p, Writer &w, const std::vector<std::string> &file);
		void generateMakefile(Parser &p, Writer &w, const std::vector<std::string> &file, const std::vector<std::string> &src);
		void generateCMake(Parser &p, Writer &w, const std::vector<std::string> &file, const std::vector<std::string> &inc, const std::vector<std::string> &src);

	private:

		Dir _d;

};

#endif /* !STATE_HPP_ */
