#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "inifile.h"
#include <map>
#include <algorithm>

using namespace std;


IniFile::IniFile(string filename)
{
    ifstream inp;
    string line, current;

    regex section_test("\\[(.*?)\\]");
    regex value_test("(\\w+)(\\s*)=([^\\+]+(?!\\+{3}))");
    inp.open(filename.c_str(), ios::in);
    if (inp.is_open())
    {
	while(getline(inp,line))
	{
	    if (line.length() > 0) //Ignore empty lines
	    {
		smatch result;
		auto pos = line.find(';');      //Find the beginning of comments
		if (pos != string::npos)         //Delete the comment if it exists in a line
		{					
			line.erase(pos);
		}
		if (regex_search(line, result, section_test))
		{
		    
		    current = result[1]; //adds new section
		    std::transform(current.begin(), current.end(), current.begin(), ::tolower); //Makes section name lowercase
		} else if (regex_search(line, result, value_test)) {
		    string hold = result[1];
		    if(current == "")
		    {
			current = "global";
		    }
		    std::transform(hold.begin(), hold.end(), hold.begin(), ::tolower);  //Makes property name lowercase
		    mapIniFile[current][hold] = result[3]; //adds properties under section
		}
	    }
		  
	}
     }
     inp.close();

}

string IniFile::GetProfileString(string section, string property_name)
{
    for (auto const &sectionMap : mapIniFile) //Loops through section map
    {
	if (sectionMap.first == section)  //If section matches look through property map
	{
	    auto const &innerMap = sectionMap.second;
	    for (auto const &propertyMap : innerMap)
	    {
		if (propertyMap.first == property_name)  //If property matches, return property value
		{ return propertyMap.second; }  
	    }
	}
    }
    return "Does not exist";
}

void IniFile::printMap()
{
     for(auto const &sectionMap : mapIniFile) //Prints the section and the properties associated with it
     {
	 cout << "SECTION " << sectionMap.first << endl;
	 auto const &inner_map = sectionMap.second;
	 for(auto const &propertyMap : inner_map) {
	    cout << "PROPERTY " << propertyMap.first << endl;
	    cout << "VALUE " << propertyMap.second << endl;
	  }
	  cout << endl;
     }
}

int main()
{
     IniFile test("text.ini");
     test.printMap();
     return 0;
}
