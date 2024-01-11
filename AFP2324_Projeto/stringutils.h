#pragma once 

/**
 * @brief Right trims a string.
 * 
 * Removes (by placing a nul terminator) unwanted terminating in a string.
 * Useful to right trim a CSV file line, that can contain unwanted 
 * terminating characters, e.g., \r or \n.
 * 
 * @param str [in] string to right trim.
 */
void rtrim(char *str);

/**
 * @brief Replaces all occurences of a character in a string.
 * 
 * @param str [in] string to replace characters.
 * @param what [in] character to replace.
 * @param replace [in] character to replace with.
 */
void replace(char *str, char what, char replace);