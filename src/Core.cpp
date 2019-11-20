/*
** EPITECH PROJECT, 2019
** ClassCreator
** File description:
** Core
*/

#include "Core.hpp"

bool Core::architectCode(const std::vector<std::string> &arch_comp)
{
	std::vector<std::string> tmp;
	std::string path;
	std::string path_past = _p.getProjectName();

	for (const std::string &s: arch_comp) {
		tmp = _a.cutLine(s);
		path_past = _p.getProjectName();
		for (unsigned int i = 0; i < tmp.size(); i++)  {
			path = path +  "/" + tmp[i];
			if (!_p.getPathInc().empty() && _d.createDir(_p.getProjectName() + "/inc" + path)) {
				_s.createInc(_p, _w, _f.getFileInc(), path, tmp[i]);
				_inc.push_back("inc" + path + "/" + tmp[i] + _p.getExtInc());
			}
			if (_d.createDir(_p.getProjectName() + "/src" + path)) {
 				_s.createSrc(_p, _w, _f.getFileSrc(), path, tmp[i]);
				_src.push_back("src" + path + "/" + tmp[i] + _p.getExtSrc());
			}
			path_past = path;
		}
		tmp.clear();
		path.clear();
	}
	return true;
}

void Core::minimalCode()
{
	_w.setHeader(_f.getHeader());
	_w.setCompiler(_p.getCompiler());
	_d.createDir(".", _p.getProjectName());

	if (!_p.getPathInc().empty())
		_d.createDir(_p.getProjectName(), "inc");
	_d.createDir(_p.getProjectName(), "src");

	if (!_p.getPathInc().empty()) {
		_d.createDir(_p.getProjectName() + "/inc/" + _p.getProjectName());
		_s.createInc(_p, _w, _f.getFileInc(), "/" + _p.getProjectName(), _p.getProjectName());
	}

	_d.createDir(_p.getProjectName() + "/src", _p.getProjectName());
	_s.createSrc(_p, _w, _f.getFileSrc(), "/" + _p.getProjectName(), _p.getProjectName());

	_inc.push_back("inc/" + _p.getProjectName() + "/" + _p.getProjectName() + _p.getExtInc());
	_src.push_back("src/" + _p.getProjectName() + "/" + _p.getProjectName()  + _p.getExtSrc());
}

bool Core::generateCode()
{
	Core::minimalCode();

	if (_p.getArchitecture().empty() && !_p.getSubFiles().empty())
		for (const std::string &s : _p.getSubFiles())
			_arch.push_back("- " + s);

	if (!_p.getArchitecture().empty()) {
		_arch = _f.loadFile(_p.getArchitecture(), true);
		if (_arch.empty())
			return false;
	}

	if (!Core::architectCode(_a.completePartial(_arch)))
		return false;
	return true;
}

void Core::buildProject()
{
	std::string s;

	if (_p.getMakefile() == true)
		s = "make && make clean";
	if (_p.getCMake() == true)
		s = "cmake CMakeLists.txt && make";
	chdir(_p.getProjectName().c_str());
	system(s.c_str());
}

bool Core::run(const std::vector<std::string> &v)
{
	if (!_p.parsingProceed(v)) {
		std::cout << "use helper : ./classCreator -h" << std::endl;
		return false;
	}

	if (!_f.loadConfig(_p))
		return false;
	if (!Core::generateCode())
		return false;


	if (!_p.getPathStart().empty()) {
		_src.push_back("start" + _p.getExtStart());
		_s.generateStart(_p, _w, _f.getFileStart());
	}

	if (_p.getMakefile())
		_s.generateMakefile(_p, _w, _f.getMakefile(), _src);
	if (_p.getCMake())
		_s.generateCMake(_p, _w, _f.getCMake(), _inc, _src);
	if ((_p.getMakefile() || _p.getCMake()) && !_p.getPathStart().empty())
		Core::buildProject();
	return true;
}
