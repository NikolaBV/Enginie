#pragma once
#include <map>
#include <string>
#include "DocumentPath.h"
class RmlDocumentsPaths
{
public:
	RmlDocumentsPaths()
	{

	}
	void Init();

	static std::map<DocumentPath, std::string> documentPaths;

};

