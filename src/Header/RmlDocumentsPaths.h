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

	static std::map<DocumentPath, std::string> documentPaths;

};

