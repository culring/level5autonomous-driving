#pragma once
#include <exception>
#include <string>

class FileInputException : std::exception
{
public:
	FileInputException();
};

