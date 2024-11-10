#pragma once
#include <stdint.h>

// #define LOGGER_MODULES_LEVELS_SECTION __attribute__((section("logger_levels")))
// #define LOGGER_MODULES_NAMES_SECTION __attribute__((section("logger_names")))
#define LOGGER_MODULES_INFO_SECTION __attribute__((section("logger_modules_info")))

struct _loggerModuleInfo {
	uint8_t runtime_log_level;
	const char *const name;
};

//Jacek (TODO): Check real size, alignment?
struct _loggerMessage {
	const char *module_name;
	const char *format_string;
	uint16_t source_code_line;
	uint16_t params_size;
	uint8_t log_level;
	uint8_t params_list[];
};
