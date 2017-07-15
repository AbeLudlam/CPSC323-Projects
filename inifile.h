#ifndef INIFILE_H_
#define INIFILE_H_
#include <string>
#include <map>
using namespace std;

class IniFile
{
    public:
	IniFile(string filename);
	string GetProfileString(string section, string property_name);
	void printMap();
    private:
	map<string, map<string, string>> mapIniFile;
};

#endif //INIFILE_H_

