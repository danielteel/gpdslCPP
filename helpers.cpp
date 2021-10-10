#include "helpers.h"
#include <string>
#include <cmath>

bool isSpace(int chr) {
	if (chr <= 32) {
		return true;
	}
	return false;
	/*switch (chr) {
	case ' ':
	case '\t':
	case '\n':
	case '\v':
	case '\f':
	case '\r':
		return true;
	}
	return false;*/
}

bool isDigit(int chr) {
	switch (chr) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return true;
	}
	return false;
}

bool isAlpha(int chr) {
	if ((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z')) {
		return true;
	}
	return false;
}

bool isAlNum(int chr) {
	return (isAlpha(chr) || isDigit(chr));
}


bool compare_float(double x, double y, double epsilon) {
	if (fabs(x - y) < epsilon)
		return true; //they are same
	return false; //they are not same
}

std::string& ltrim(std::string& s, const char* t) {
	s.erase(0, s.find_first_not_of(t));
	return s;
}

std::string& rtrim(std::string& s, const char* t) {
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}

std::string& trim(std::string& s, const char* t) {
	return ltrim(rtrim(s, t), t);
}

std::string stringToLowerCopy(std::string str) {
	std::string retStr;
	for (auto & chr : str) {
		retStr += tolower(chr);
	}
	return retStr;
}
void stringToLower(std::string& str) {
	for (size_t i = 0; i < str.length();i++) {
		str[i] = tolower(str[i]);
	}
}


std::string doubleToString(double value, int decimalPlaces) {
	char buffer[64];
	snprintf(buffer, sizeof(buffer), "%.*f", decimalPlaces, value);
	return std::string(buffer);
}

std::string trimmedDoubleToString(double value, int mostDecimalPlaces) {
	std::string doubleString = doubleToString(value, mostDecimalPlaces);
	int length = doubleString.length();
	size_t index = doubleString.find_last_of(".");
	if (index != std::string::npos && length > 2) {
		for (size_t i = doubleString.length(); i > 0; i--) {
			if (doubleString[i - 1] == '0') {
				length--;
			} else {
				if (doubleString[i - 1] == '.') {
					length--;
				}
				break;
			}
		}
	}
	return doubleString.substr(0,length);
}

std::string trimmedDoubleToString(double value) {
	std::string doubleString = std::to_string(value);
	int length = doubleString.length();
	size_t index = doubleString.find_last_of(".");
	if (index != std::string::npos && length > 2) {
		for (size_t i = doubleString.length(); i > 0; i--) {
			if (doubleString[i - 1] == '0') {
				length--;
			} else {
				if (doubleString[i - 1] == '.') {
					length--;
				}
				break;
			}
		}
	}
	return doubleString.substr(0, length);
}

std::string encodeString(std::string str) {
	std::string encoded;
	for (size_t i = 0; i < str.size(); i++) {
		switch (str[i]) {
		case 0:
			encoded += "%0";
		case '\'':
			encoded += "%p";
			break;
		case '"':
			encoded += "%q";
			break;
		case '%':
			encoded += "%%";
			break;
		case '\\':
			encoded += "%s";
			break;
		case '\r':
			encoded += "%r";
			break;
		case '\n':
			encoded += "%n";
			break;
		default:
			encoded += str[i];
			break;
		}
	}
	return encoded;
}

std::string decodeString(std::string str) {
	std::string decoded;
	for (size_t i = 0; i < str.size(); i++) {
		if (str[i] == '%') {
			i++;
			if (i < str.size()) {
				switch (str[i]) {
				case '0':
					decoded += '\0';
					break;
				case 'p':
					decoded += '\'';
					break;
				case 'q':
					decoded += '"';
					break;
				case '%':
					decoded += '%';
					break;
				case 's':
					decoded += '\\';
					break;
				case 'r':
					decoded += '\r';
					break;
				case 'n':
					decoded += '\n';
					break;
				}
			}
		} else {
			decoded += str[i];
		}
	}
	return decoded;
}

std::string stripTrailingNumber(std::string str) {
	trim(str);
	int i;
	for (i = int(str.length()) - 1; i >= 0; i--) {
		if (!isDigit(str[i])) {
			break;
		}
	}
	return str.substr(0, i + 1);
}