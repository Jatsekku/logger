#pragma once

#include <stdint.h>

void loggerPrint_printData(const char *const format_string,
			   char *const output_buffer,
			   const void *const data,
			   uint16_t data_size);