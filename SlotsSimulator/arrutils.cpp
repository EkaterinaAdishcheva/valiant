#include "stdafx.h"
#include <stdio.h>
#include "utils.h"


/*
Util functions to read a file ignoring comments
Comments starts with "#", "//" or ";" and continues to the end of line
*/
#define READBUF 10240
bool is_blank(char ch) {
	return ch == ' ' || ch == '\t' || ch == ':' || ch == '_' || ch == ',' || ch == '-';
}
bool is_comment(char ch) {
	return ch == '#' || ch == '/' || ch == ';';
}
bool is_stop(char ch) {
	return ch == '\n' || ch == '\0';
}
bool is_token(char ch) {
	return !is_blank(ch) && !is_stop(ch);
}
void read_int_file(const wchar_t * filename, int * tgt) {
	char buf[READBUF], *str;
	FILE * file;

	_wfopen_s(&file, filename, L"r");

	while (fgets(buf, READBUF, file)) {
		str = buf;
		// ignore utf-8 header
		if (str[0] == -17 && str[1] == -69 && str[2] == -65) {
			str += 3;
		}
		while (is_blank(*str)) {
			str++;
		}
		if (is_comment(*str) || is_stop(*str)) {
			continue;
		}
		while (1) {
			if (is_stop(*str) || is_comment(*str) || !sscanf_s(str, "%d", tgt)) {
				break;
			}
			tgt++;
			while (is_token(*str)) {
				str++;
			}
			while (is_blank(*str)) {
				str++;
			}
		}
	}
	fclose(file);
}

void sum_int64_arr(UINT64 dst[], UINT64 term[], UINT64 len) {
	for (int j = 0; j < len; j++) {
		*(dst++) += *(term++);
	}
}
void max_int64_arr(UINT64 dst[], UINT64 term[], UINT64 len) {
	for (int j = 0; j < len; j++) {
		if ((*dst) < *(term)) {
			(*dst) = *(term);
		}
		dst++; term++;
	}
}
