#pragma once
#include <exception>

class FileInputException : std::exception
{
public:
	FileInputException();
};

