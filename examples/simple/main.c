#include <stdio.h>
#include <stdint.h>

#include "module1.h"
#include "module2.h"

#include "logger/logger_backend.h"

int main(void) {
	module1_foo();
	module2_foo();

	logger_printModulesInfo();
}
