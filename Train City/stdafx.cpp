// stdafx.cpp : source file that includes just the standard includes
// Train City.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

const std::string intToString(const int value)
{
	std::ostringstream text;
	text << value;
	return text.str();

}

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
