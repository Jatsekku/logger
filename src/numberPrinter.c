#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/* TODO: Optimize it one day
 * Resources:
 * https://jk-jeon.github.io/posts/2022/02/jeaiii-algorithm/
 * https://github.com/jeaiii/itoa
 * https://github.com/amdn/itoa
 */
uint8_t numberPrinter_u64ToDecimalAscii(char *const out_buffer, uint64_t num) {
	assert((NULL != out_buffer)
	       && "out_buffer cannot be NULL");

	char *destination_buffer = out_buffer;
	char buffer_tmp[20]; // max: 18 446 744 073 709 551 615
	uint8_t i = 0;

	do {
		buffer_tmp[i] = '0' + num % 10;
		num /= 10;
		i++;
	} while (num != 0);

	const uint8_t digit_count = i; 
	while (i--) {
		(*destination_buffer++) = buffer_tmp[i];
	}

	return digit_count;
}

uint8_t numberPrinter_i64ToDecimalAscii(char *const out_buffer, int64_t num) {
	assert((NULL != out_buffer)
	       && "out_buffer cannot be NULL");

	char *destination_buffer = out_buffer;
	uint8_t char_count = 0;

	if (num < 0) {
		(*destination_buffer++) = '-';
		num = -num;
		char_count++;
	}

	char_count += numberPrinter_u64ToDecimalAscii(destination_buffer, (uint64_t)num);
	return char_count;
}

uint8_t numberPrinter_u8ToHexAscii(char *const out_buffer, uint8_t byte) {
	static const char halfbyte_hex_table[] = {
		'0', '1', '2', '3',
		'4', '5', '6', '7',
		'8', '9', 'A', 'B',
		'C', 'D', 'E', 'F'
	};

	assert((NULL != out_buffer)
	       && "out_buffer cannot be NULL");
	char *destination_buffer = out_buffer;

	*destination_buffer++ = halfbyte_hex_table[byte >> 4];
	*destination_buffer = halfbyte_hex_table[byte & 0x0F];

	return 2;
}

uint8_t numberPrinter_u8ToBinAscii(char *const out_buffer, uint8_t byte) {
	static const uint32_t halfbyte_bin_table[] = {
		'0' | '0' << 8 | '0' << 16 | '0' << 24,
		'0' | '0' << 8 | '0' << 16 | '1' << 24,
		'0' | '0' << 8 | '1' << 16 | '0' << 24,
		'0' | '0' << 8 | '1' << 16 | '1' << 24,
		'0' | '1' << 8 | '0' << 16 | '0' << 24,
		'0' | '1' << 8 | '0' << 16 | '1' << 24,
		'0' | '1' << 8 | '1' << 16 | '0' << 24,
		'0' | '1' << 8 | '1' << 16 | '1' << 24,
		'1' | '0' << 8 | '0' << 16 | '0' << 24,
		'1' | '0' << 8 | '0' << 16 | '1' << 24,
		'1' | '0' << 8 | '1' << 16 | '0' << 24,
		'1' | '0' << 8 | '1' << 16 | '1' << 24,
		'1' | '1' << 8 | '0' << 16 | '0' << 24,
		'1' | '1' << 8 | '0' << 16 | '1' << 24,
		'1' | '1' << 8 | '1' << 16 | '0' << 24,
		'1' | '1' << 8 | '1' << 16 | '1' << 24,

	};

	assert((NULL != out_buffer)
	       && "out_buffer cannot be NULL");
	uint32_t *destination_buffer = (uint32_t*)out_buffer;

	*destination_buffer++ = halfbyte_bin_table[byte >> 4];
	*destination_buffer = halfbyte_bin_table[byte & 0x0F];

	return 8;
}

uint8_t numberPrinter_u64toHexBigEndianAsciiAligned(char *const out_buffer, uint64_t num) {
	assert((NULL != out_buffer)
	       && "out_buffer cannot be NULL");

	char *destination_buffer = out_buffer;
	int i = 7;
	bool leading_zeros = true;

	while(i--) {
		const uint8_t byte_value = (num >> i*8);
		if (byte_value == 0x00 && leading_zeros) {
			continue;
		}
		leading_zeros = false;

		if (!leading_zeros) {
			destination_buffer += numberPrinter_u8ToHexAscii(destination_buffer, byte_value);
		}
	}

	return destination_buffer - out_buffer;
}

uint8_t numberPrinter_u64toBinBigEndianAsciiAligned(char *const out_buffer, uint64_t num) {
	assert((NULL != out_buffer)
	       && "out_buffer cannot be NULL");

	char *destination_buffer = out_buffer;
	int i = 7;
	bool leading_zeros = true;

	while(i--) {
		const uint8_t byte_value = (num >> i*8);
		if (byte_value == 0x00 && leading_zeros) {
			continue;
		}
		leading_zeros = false;

		if (!leading_zeros) {
			destination_buffer += numberPrinter_u8ToBinAscii(destination_buffer, byte_value);
			*destination_buffer++ = ' ';
		}
	}

	return (destination_buffer - out_buffer) - 1;
}
