#define BASE_C_IMPLEMENTATION 1
#include "tests/bytes_buffer_test.c"
#include "tests/utf8_test.c"
#include "tests/arena_test.c"
#include "tests/string_test.c"

int main(){
	// Run all tests
	test_bytes_buffer();
	test_utf8();
	test_arena();
}
