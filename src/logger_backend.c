#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "logger/logger_common.h"
#include "loggerPrinter.h"

extern struct _loggerModuleInfo __start_logger_modules_info;
extern struct _loggerModuleInfo __stop_logger_modules_info;

struct loggerModulesInfo {
	struct _loggerModuleInfo *const start;
	struct _loggerModuleInfo *const stop;
} const logger_modules_info = {
	.start = &__start_logger_modules_info,
	.stop = &__stop_logger_modules_info,
};

static void printParamsList(const struct _loggerMessage *const message) {
	const char *const format_string = message->format_string;
	const uint16_t params_size = message->params_size;
	const void *param_list = message->params_list;

	char tmp_buffer[255];
	loggerPrint_printData(format_string, tmp_buffer , param_list, params_size);
	printf("%s\n", tmp_buffer);
}

void printMessage(const struct _loggerMessage *const message) {

	printf("log_level: %d\n\r"
		   "module_name: %s\n\r"
		   "line: %d\n\r"
		   "params_size: %d\n\r",
		   message->log_level,
		   message->module_name,
		   message->source_code_line,
		   message->params_size);
	printParamsList(message);
}

static inline const char *const logLevelToString(const struct _loggerMessage *const message) {
	static const char *const log_level_string[] = {
		"ERR",
		"WRN",
		"INF",
		"DBG"
	};

	return log_level_string[message->log_level - 1];
}

uint8_t __logger_buffer[100];

static uint16_t getModulesCount(void) {
	const uint16_t modules_amount = logger_modules_info.stop - logger_modules_info.start;
	return modules_amount;
}

static int16_t findModuleIndex(char *token) {
	const uint16_t token_length = strlen(token);
	const uint16_t modules_amount = getModulesCount();

	for (int i = 0; i < modules_amount; i++) {
		const char *current_module_name = logger_modules_info.start[i].name;
		uint16_t matched_chars = 0;

		for(int j = 0; j < token_length; j++) {
			if (token[j] != current_module_name[j]) {
				break;
			}

			if(++matched_chars == token_length) {
				return i;
			}
		}
	}

	return -1; 
}

static const char *const getModuleName(uint16_t module_index) {
	const uint16_t modules_amount = getModulesCount();
	if (module_index > modules_amount) {
		return NULL;
	}

	return logger_modules_info.start[module_index].name;
}

void *_logger_reserveMemory(uint32_t memory_size) {
	return __logger_buffer;
}

void _logger_commitMessage(const struct _loggerMessage *const message) {
	printMessage(message);
}

/* -------------------------------------------- API -------------------------------------------- */

void logger_printModulesInfo(void) {
	const uint16_t modules_amount = getModulesCount();
	for(int i = 0; i < modules_amount; i++) {
		printf("%d. %s, level: %d\n",
			   i,
			   logger_modules_info.start[i].name,
			   logger_modules_info.start[i].runtime_log_level);
	}
}

void logger_setModuleLogLevelByIndex(uint16_t module_index, uint8_t log_level) {
	logger_modules_info.start[module_index].runtime_log_level = log_level;
}

void logger_setModuleLogLevelByName(char *module_name, uint8_t log_level) {
	const int16_t module_idx = findModuleIndex(module_name);
	if (module_idx < 0) {
		return;
	}

	logger_setModuleLogLevelByIndex(module_idx, log_level);
}
