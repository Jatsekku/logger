#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#include "numberPrinter.h"

#define LOGGER_CSTRING_PARAM_MAX_SIZE (512)

#define force_inline inline __attribute__((always_inline))

typedef uint8_t i64PrinterFunction(char *output_buffer, int64_t num);
typedef uint8_t u64PrinterFunction(char *output_buffer, uint64_t num);

enum loggerParserBaseType {
	LOGGER_PARSER_BASE_DECIMAL,
	LOGGER_PARSER_BASE_BINARY,
	LOGGER_PARSER_BASE_HEX,
};

static i64PrinterFunction *const i64_printer_functions[] = {
	[LOGGER_PARSER_BASE_DECIMAL] = numberPrinter_i64ToDecimalAscii,
	[LOGGER_PARSER_BASE_BINARY] = (i64PrinterFunction*)numberPrinter_u64toBinBigEndianAsciiAligned,
	[LOGGER_PARSER_BASE_HEX] = (i64PrinterFunction*)numberPrinter_u64toHexBigEndianAsciiAligned,
};

static u64PrinterFunction *const u64_printer_functions[] = {
	[LOGGER_PARSER_BASE_DECIMAL] = numberPrinter_u64ToDecimalAscii,
	[LOGGER_PARSER_BASE_BINARY] = numberPrinter_u64toBinBigEndianAsciiAligned,
	[LOGGER_PARSER_BASE_HEX] = numberPrinter_u64toHexBigEndianAsciiAligned,
};

static struct loggerParserState {
	const char *format_string_head;
	char *output_buffer_head;
	const void *data_head;
	const void *data_tail;
	enum loggerParserBaseType base_type;
} parser_state;

static force_inline const void *getData(uint8_t size) {
	assert(((parser_state.data_head + size) <= parser_state.data_tail)
		&& "Attempt to acces data behind the range");
	const void *const data = parser_state.data_head;
	parser_state.data_head += size;
	return data;
}

// Data geters
static force_inline char getChar() {
	return *(char*)getData(sizeof(char));
}

static force_inline signed short int getSignedShortInt() {
	return *(signed short*)getData(sizeof(signed short));
}

static force_inline unsigned short int getUnsignedShortInt() {
	return *(unsigned short*)getData(sizeof(unsigned short));
}

static force_inline signed int getSignedInt() {
	return *(signed int*)getData(sizeof(signed int));
}

static force_inline unsigned int getUnsignedInt() {
	return *(unsigned int*)getData(sizeof(unsigned int));
}

static force_inline signed long int getSignedLongInt() {
	return *(signed long int*)getData(sizeof(signed long int));
}

static force_inline unsigned long int getUnsignedLongInt() {
	return *(unsigned long int*)getData(sizeof(unsigned long int));
}

static force_inline signed long long int getSignedLongLongInt() {
	return *(signed long long int*)getData(sizeof(signed long long int));
}

static force_inline unsigned long long int getUnsignedLongLongInt() {
	return *(unsigned long long int*)getData(sizeof(unsigned long long int));
}

static force_inline int8_t getInt8() {
	return *(int8_t*)getData(sizeof(int8_t));
}

static force_inline int16_t getInt16() {
	return *(int16_t*)getData(sizeof(int16_t));
}

static force_inline int32_t getInt32() {
	return *(int32_t*)getData(sizeof(int32_t));
}

static force_inline int64_t getInt64() {
	return *(int64_t*)getData(sizeof(int64_t));
}

static force_inline uint8_t getUint8() {
	return *(uint8_t*)getData(sizeof(uint8_t));
}

static force_inline uint16_t getUint16() {
	return *(uint16_t*)getData(sizeof(uint16_t));
}

static force_inline uint32_t getUint32() {
	return *(uint32_t*)getData(sizeof(uint32_t));
}

static force_inline uint64_t getUint64() {
	return *(uint64_t*)getData(sizeof(uint64_t));
}

static force_inline char* getCharPtr() {
	return (char*)getData(sizeof(char*));
}

// Data printers
static force_inline void sprintPreviousFormatChar() {
	*parser_state.output_buffer_head++ = *(parser_state.format_string_head - 1);
}

static force_inline void sprintPercentSign() {
	*parser_state.output_buffer_head++ = '%';
}

static force_inline void sprintChar() {
	*parser_state.output_buffer_head++ = getChar();
}

static force_inline void sprintSignedShortInt() {
	const signed short int num = getSignedShortInt();

	i64PrinterFunction *const printer_function = i64_printer_functions[parser_state.base_type];
	parser_state.output_buffer_head += printer_function(parser_state.output_buffer_head, num);
}

static force_inline void sprintUnsignedShortInt() {
	const unsigned short int num = getUnsignedShortInt();

	u64PrinterFunction *const printer_function = u64_printer_functions[parser_state.base_type];
	parser_state.output_buffer_head += printer_function(parser_state.output_buffer_head, num);
}

static force_inline void sprintSignedLongInt() { 
	const signed long int num = getSignedLongInt();

	i64PrinterFunction *const printer_function = i64_printer_functions[parser_state.base_type];
	parser_state.output_buffer_head += printer_function(parser_state.output_buffer_head, num);
}

static force_inline void sprintUnsignedLongInt() { 
	const unsigned long int num = getUnsignedLongInt();

	u64PrinterFunction *const printer_function = u64_printer_functions[parser_state.base_type];
	parser_state.output_buffer_head += printer_function(parser_state.output_buffer_head, num);
}

static force_inline void sprintSignedLongLongInt() { 
	const signed long long int num = getSignedLongLongInt();

	i64PrinterFunction *const printer_function = i64_printer_functions[parser_state.base_type];
	parser_state.output_buffer_head += printer_function(parser_state.output_buffer_head, num);
}

static force_inline void sprintUnsignedLongLongInt() { 
	const unsigned long long int num = getUnsignedLongLongInt();

	u64PrinterFunction *const printer_function = u64_printer_functions[parser_state.base_type];
	parser_state.output_buffer_head += printer_function(parser_state.output_buffer_head, num);
}

static force_inline void sprintCString() {
	const char *str = getCharPtr();

	for (size_t i = 0; i < LOGGER_CSTRING_PARAM_MAX_SIZE; i++) {
		char c = *str++;
		if ('\0' == c) {
			break;
		}
		*parser_state.output_buffer_head++ = c; 
	}
}

static force_inline void sprintInt64From(int64_t num) {
	i64PrinterFunction *const printer_function = i64_printer_functions[parser_state.base_type];
	parser_state.output_buffer_head += printer_function(parser_state.output_buffer_head, num);
}

static force_inline void sprintUint64From(uint64_t num) {
	u64PrinterFunction *const printer_function = u64_printer_functions[parser_state.base_type];
	parser_state.output_buffer_head += printer_function(parser_state.output_buffer_head, num);
}

// Matches: i, f, u
static force_inline void matchLongLongType(void) {
	switch (*parser_state.format_string_head++) {
		// %llu
		case 'u':
			sprintUnsignedLongLongInt();
		//% 
		case 'f':
			assert(false && "Float not supported yet");
		case 'i':
			sprintSignedLongLongInt();
		default:
			sprintPreviousFormatChar();
	}
}

// Matches: i, f, l, u
static force_inline void matchLongAndDoubleType() {
	switch (*parser_state.format_string_head++) {
		// %lu
		case 'u':
			sprintUnsignedLongInt();
			break; 
		// %li
		case 'i':
			sprintSignedLongInt();
			break;
		// %lf
		case 'f':
			assert(false && "Float not supported yet");
			break;
		// %ll
		case 'l':
			matchLongLongType();
			break;
		default:
			sprintPreviousFormatChar();

	}
}

// Matches: 8, 16, 32, 64,
// Intentionally without inline specifier
static void matchIntBitwidth(bool is_signed) {
	uint64_t num_unsigned;
	int64_t num_signed;

	// %u8/%i8 -> uint8_t/int8_t
	if ('8' == *parser_state.format_string_head) {
		parser_state.format_string_head++;
		const uint8_t num = getUint8();; 
		num_unsigned = (uint8_t)num;
		num_signed = (int8_t)num;
		goto end;
	}

	switch (*(uint16_t*)parser_state.format_string_head) {
		// %i/%u
		default: {
			parser_state.format_string_head += 1;
			const unsigned int num = getUnsignedInt();
			num_unsigned = (unsigned int)num;
			num_signed = (signed int)num;
		} break;
		// %u16/%i16 -> uint16_t/int16_t
		case ('1' | '6'  << 8): {
			parser_state.format_string_head += 2;
			const uint16_t num = getUint16();
			num_unsigned = (uint16_t)num;
			num_signed = (int16_t)num;
		} break;
		// %u32/%i32 -> uint32_t/int32_t
		case ('3' | '2'  << 8): {
			parser_state.format_string_head += 2;
			const uint32_t num = getUint32();
			num_unsigned = (uint32_t)num;
			num_signed = (int32_t)num;
		} break;
		// %u64/%i64 -> uint64_t/int64_t
		case ('6' | '4'  << 8): {
			parser_state.format_string_head +=2;
			const uint64_t num = getUint64();
			num_unsigned = (uint64_t)num;
			num_signed = (int64_t)num;
		} break;
	}

end:
	if (is_signed) {
		sprintInt64From(num_signed);
	} else {
		sprintUint64From(num_unsigned);
	}
}

// Matches: i,u
static force_inline void matchShortType() {
	switch (*parser_state.format_string_head++) {
		// %hu -> unsigned short
		case 'u': {
			sprintUnsignedShortInt();
		} break;
		// %hi -> signed short
		case 'i': {
			sprintSignedShortInt();
		} break;
		default:
			sprintPreviousFormatChar();
	}
}

// Matches: %,c,f, h,i,l,s,u
static inline void matchType() {
	switch(*parser_state.format_string_head++) {
		// %u...
		case 'u':
			matchIntBitwidth(false);
			break;
		// %i...
		case 'i':
			matchIntBitwidth(true);
			break;
		// %s
		case 's':
			sprintCString();
			break;
		// %c
		case 'c':
			sprintChar();
			break;
		// %f
		case 'f':
			break;
		// %l
		case 'l':
			matchLongAndDoubleType();
			break;
		// %h...
		case 'h':
			matchShortType();
			break;
		// %%
		case '%':
			sprintPercentSign();
			break; 
		default:
			sprintPreviousFormatChar();
	}
}

static force_inline void matchStart() {
	if ('%' == *parser_state.format_string_head) {
		parser_state.format_string_head++;
		matchType();
	} else {
		*parser_state.output_buffer_head++ = *parser_state.format_string_head++;
	}
}

void loggerPrint_printData(const char *const format_string,
			   char *const output_buffer,
			   const void *const data,
			   uint16_t data_size) {
	parser_state.format_string_head = format_string;
	parser_state.output_buffer_head = output_buffer;
	parser_state.data_head = data;
	parser_state.data_tail = data + data_size;
	parser_state.base_type = LOGGER_PARSER_BASE_BINARY;

	while(*parser_state.format_string_head != '\0') {
		matchStart();

	}
	*parser_state.output_buffer_head = '\0';
}
