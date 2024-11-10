#pragma once

#include <stdint.h>

#include "logger_common.h"

// typedef void loggerEmitLogCallbackFunction(const char *const log, uint16_t log_size);
                           
// void logger_printParamsList(const struct loggerMessage *const message);
// void logger_printMessage(const struct loggerMessage *const message);

/**
 * @brief Print 
 * 
 * @param[out] config Pointer to virtualLink configuration
 * @param[in]  interface_ipv4_address_string String representin interface IPv4 address
 * @param[in]  tx_socket_address_string String representing TX socket address
 * @param[in]  tx_socket_address_string String representing RX socket address
 * @return     Bool infroming if config has been successfully filled with data
 */
void logger_printModulesInfo(void);

/**
 * @brief Fill config structure by providing appropriate strings
 * 
 * @param[out] config Pointer to virtualLink configuration
 * @param[in]  interface_ipv4_address_string String representin interface IPv4 address
 * @param[in]  tx_socket_address_string String representing TX socket address
 * @param[in]  tx_socket_address_string String representing RX socket address
 * @return     Bool infroming if config has been successfully filled with data
 */
void logger_setModuleLogLevelByIndex(uint16_t module_index, uint8_t log_level);

/**
 * @brief Fill config structure by providing appropriate strings
 * 
 * @param[out] config Pointer to virtualLink configuration
 * @param[in]  interface_ipv4_address_string String representin interface IPv4 address
 * @param[in]  tx_socket_address_string String representing TX socket address
 * @param[in]  tx_socket_address_string String representing RX socket address
 * @return     Bool infroming if config has been successfully filled with data
 */
void logger_setModuleLogLevelByName(char *module_name, uint8_t log_level);
