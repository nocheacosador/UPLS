#include "logger.h"
#include <iostream>

namespace na
{
	Logger& log = Logger::instance().addStream(&std::cerr).logToFile();
};