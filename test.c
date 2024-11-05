#if 0
cd "$(dirname "$0")"
name="test"
cc -o "$name" test.c gottzlib.c -lm -Wall -Wextra -Werror -O3 && chmod +x "$name" && ./"$name" "$@"
exit
#endif
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "gottzlib.h"

typedef int (*Test_Function)(void);

typedef struct Test {
	Test_Function func;
	char* description;
} Test;

int test_quick_pread(void) {
	const char* command = "echo -n \"Hello \"; sleep 1; echo \"World!\"";

	size_t buffer_size;
	char* buffer = gottz_quick_pread(&buffer_size, command);
	if (!buffer || !buffer_size) {
		perror("could not read from process");
		return 1;
	}

	int result = strcmp(buffer, "Hello World!\n");
	free(buffer);

	return result;
}

Test tests[] = {
	{ test_quick_pread, "gottz_quick_pread"	},
	{ 0, 0 }
};

int main(int argc, char* args[]) {
	setvbuf(stdout, NULL, _IONBF, 0);
	int count = 0;
	while(tests[++count].func){};

	// todo:
	// instead of running through the tests to count them, only count up to the specified test id.
	if (argc > 2 && strcmp(args[1], "run") == 0) {
		// welcome to partial testing land!
		int id = atoi(args[2]) -1;
		if (id >= count || id < 0) {
			perror("supplied test case does not exist.");
			return 1;
		}
		return tests[id].func();
	}

	// todo:
	// cd into the program directory. not mandatory yet.

	printf("welcome to test land!\n\n");
	int padding = (int)log10(count) + 1;
	printf("%d tests found.\nrunning tests!\n\n", count);

	int passed = 0;

	for(int i = 0; i < count; i++) {
		Test test = tests[i];
		printf("[%-*d/%-*d] %s ... ", padding, i +1, padding, count, test.description);
		// todo: invoke args[0] run i instead of the following:
		int result = test.func();
		if (result == 0) passed++;
		printf("%s\n", result == 0 ? "pass" : "FAILED");
	}

	printf("\n%d of %d tests succeeded!\n", passed, count);

	if (passed < count) {
		printf("sadly %d tests failed :( plz fix!\n", count - passed);
		return 1;
	}

	return 0;
}
