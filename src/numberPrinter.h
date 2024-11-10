#pragma once
#include <stdint.h>

/**
 * @brief Print u8 as hex number to given string ('\0' will not be added at the end)
 *
 * @param[out] out_buffer Pointer to buffer where result string will be stored
 * @param[in]  num Number that has to be printed
 * @return     Size of produced string
 */
uint8_t numberPrinter_u8ToHexAscii(char *const out_buffer, uint8_t byte);

/**
 * @brief Print u64 as decimal number to given string ('\0' will not be added at the end)
 *
 * @param[out] out_buffer Pointer to buffer where result string will be stored
 * @param[in]  num Number that has to be printed
 * @return     Size of produced string
 */
uint8_t numberPrinter_u64ToDecimalAscii(char *const out_buffer, uint64_t num);

/**
 * @brief Print i64 as decimal number to given string ('\0' will not be added at the end)
 *
 * @param[out] out_buffer Pointer to buffer where result string will be stored
 * @param[in]  num Number that has to be printed
 * @return     Size of produced string
 */
uint8_t numberPrinter_i64ToDecimalAscii(char *const out_buffer, int64_t num);

/**
 * @brief Print u64 as hex number to given string ('\0' will not be added at the end)
 *	  Numbers will be aligned to full bytes ie. 2137, 0345
 *
 * @param[out] out_buffer Pointer to buffer where result string will be stored
 * @param[in]  num Number that has to be printed
 * @return     Size of produced string
 */
uint8_t numberPrinter_u64toHexBigEndianAsciiAligned(char *const out_buffer, uint64_t num);


uint8_t numberPrinter_u64toBinBigEndianAsciiAligned(char *const out_buffer, uint64_t num);