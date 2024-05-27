#pragma once
#include <iostream>
using namespace std;

class Helper {
public:
	void my_strcpy(char* str1, const char* str2) {
		if (str1 == nullptr || str2 == nullptr) {
		}
		while (*str2) {
			*str1++ = *str2++;
		}
		*str1 = '\0';
	}


	char* my_strcat(char* dest, const char* src) {
		char* ptr = dest;
		while (*ptr != '\0') {
			ptr++;
		}
		while (*src != '\0') {
			*ptr = *src;
			ptr++;
			src++;
		}
		*ptr = '\0';
		return dest;
	}

	int my_strcmp(char* cstring1, const char* cstring2) {
		int i = 0;
		while (cstring1[i] != '\0' && cstring2[i] != '\0') {
			char char1 = tolower(cstring1[i]);
			char char2 = tolower(cstring2[i]);

			if (char1 < char2) {
				return -1;
			}
			else if (char1 > char2) {
				return 1;
			}

			i++;
		}

		if (cstring1[i] == '\0' && cstring2[i] == '\0') {
			return 0;
		}
		else if (cstring1[i] == '\0') {
			return -1;
		}
		else {
			return 1;
		}
	}

};
