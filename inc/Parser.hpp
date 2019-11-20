/*
** EPITECH PROJECT, 2019
** ClassCreator
** File description:
** parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

/* STD Library */
#include <iostream>

/* STD Types Library */
#include <vector>

/* Types Library */
#include <sstream>
#include <iterator>

class Parser {

	public:

		Parser();
		~Parser() = default;

		/* Parsing public */
		bool helperCommand(void);
		bool parsingProceed(const std::vector<std::string> &v);

		/* Getters */
		std::string getProjectName();
		std::vector<std::string> getSubFiles();
		std::string getArchitecture();
		std::string getCompiler();

		std::string getPathStart();
		std::string getPathSrc();
		std::string getPathInc();

		std::string getExtStart();
		std::string getExtSrc();
		std::string getExtInc();

		bool getMakefile();
		bool getCMake();

	private:

		/* Parsing AV */
		void AVOptions(const std::vector<std::string> &v, const unsigned int i);
		bool parsingAV(const std::vector<std::string> &v);
		void extension();

		/* Verification */
		bool configCheck();

		/* Variables - Ressources for user inputs */
		std::string _project_name;
		std::vector<std::string> _sub_files;
		std::string _architecture;
		std::string _compiler;
		std::string _path_start;
		std::string _ext_start;
		std::string _path_src;
		std::string _ext_src;
		std::string _path_inc;
		std::string _ext_inc;
		bool _makefile;
		bool _cmake;

};

#endif /* !PARSER_HPP_ */
