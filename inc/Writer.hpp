/*
** EPITECH PROJECT, 2019
** ClassCreator
** File description:
** Writer
*/

#ifndef WRITER_HPP_
#define WRITER_HPP_

/* STD Library */
#include <iostream>
#include <vector>
#include <map>
#include <fstream>

class Writer {

	public:

		Writer();
		~Writer() = default;

		/* Create file and write in Public */
		bool create(const std::string &name, const std::string &path, const std::string type);

		/* Setter */
		void setHeader(const std::vector<std::string> v);
		void setFile(const std::vector<std::string> &v);
		void setSrc(const std::vector<std::string> &v);
		void setInc(const std::vector<std::string> &v);

	private:

		/* Create file and write in Private */
		void useTag(const std::string &tag, const std::string &name, const std::string &path, const std::string &type);
		void processTag(const std::string &s, const std::string &name, const std::string &path, const std::string type);

		/* Tag File By File */
		void useTagG(const std::string &tag, const std::string &name);
		void useTagMake(const std::string &tag, const std::string &path);

		/* Tools */
		void cleanRessources();
		int occurenceNbInS(const std::string &s, const std::string &tag);
		void writeVectorInFile(const std::string &s1, const std::vector<std::string> &v, const std::string &s2);
		std::ofstream createFile(const std::string &name, const std::string &path, const std::string &type);

		/* enum for maps */
		enum type {MAKE, CMAKE};
		enum tagMake {PROGNAME, SRCMAKE, SRCCMAKE, INCCMAKE, COMPILER};

		/* Variables - Ressource for string switch */
		std::map<std::string, type> _type;
		std::map<std::string, tagMake> _tagMake;

		/* Variables - Ressources for files writing */
		std::vector<std::string> _header;
		std::vector<std::string> _file;
		std::ofstream _of;
		std::string _tag_ref;

		/* Variables - Ressources for files information (Tag) */
		std::vector<std::string> _src;
		std::vector<std::string> _inc;

};

#endif /* !WRITER_HPP_ */
