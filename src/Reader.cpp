#include "Reader.h"
#include <sstream>

std::string FileReader::read() {
    std::ostringstream string_stream;
    string_stream << file.rdbuf();
    return string_stream.str();
}
