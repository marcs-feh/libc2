#define BASE_C_IMPLEMENTATION 1
#include "string.h"
#include <stdio.h>

int main(){
	String s = str_from("H한ellИo");
	printf("\"%.*s\"\n", FmtString(s));

	printf("Bytes: %ld Codepoints: %ld\n", s.len, str_codepoint_count(s));
	for(isize n = 0; n < 7; n++){
		printf("N: %ld, OFF: %ld\n", n, str_codepoint_offset(s, n));
	}

	return 0;
}
