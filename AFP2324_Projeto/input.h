/**
 * @file input.h
 * @author Bruno Silva (bruno.silva@estsetubal.ips.pt)
 * @brief Provides simple standard inputs. Usage is similar to the scanf function.
 * 
 * @version 1
 * @date 2021-02-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <stdbool.h>

/**
 * @brief Read an integer from standard input.
 * 
 * @param ptVal [out] address of variable to hold the value
 * 
 * @return true if a valid integer was parsed
 * @return false otherwise
 */
bool readInteger(int *ptVal);

/**
 * @brief Read a double from standard input.
 * 
 * @param ptVal [out] address of variable to hold the value
 * 
 * @return true if a valid double was parsed
 * @return false otherwise
 */
bool readDouble(double *ptVal);

/**
 * @brief Read a char from standard input.
 * 
 * Only the first character is consumed.
 * 
 * @param ptVal [out] address of variable to hold the value
 * 
 * @return true if a valid char was parsed
 * @return false otherwise
 */
bool readChar(char *ptVal);

/**
 * @brief Reads a "string" from standard input.
 * 
 * @param charArr [out] address of array to hold the text
 * @param maxChars [in] maximum characters to read. 
 *                      charArray must have at least this size.
 */
void readString(char *charArr, unsigned int maxChars);

/**
 * @brief Splits a string given a delimiter.
 * 
 * This function modifies the parameter 'string', replacing
 * delimiter occurrences by '\0' and returns and array of pointers
 * to each invidual tokens.
 * 
 * This array must be free'd by the caller.
 * 
 * @param string [in] the string to split
 * @param nTokens [in] number of required tokens. If there are
 *                      less tokens than specified, then NULL
 *                      is used for subsequent tokens.
 * @param delim [in] delimiter, usually a single character
 * @return char** pointer array (of size nFields) to string "tokens".
 */
char** splitString(char *string, int nTokens, const char *delim);

