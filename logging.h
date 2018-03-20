/******************************************************************************
 * @file    logging.h
 * @author  Rémi Pincent - INRIA
 * @date    15 janv. 2014
 *
 * @brief Helper class to get logs over Arduino serial interface
 * based on https://github.com/mrRobot62/Arduino-logging-library
 *
 * Project : logger library
 * Contact:  Rémi Pincent - remi.pincent@inria.fr
 *
 * All methods are able to handle any number of output parameters.
 * All methods print out a formated string (like printf).<br>
 * To reduce output and program size, reduce loglevel.
 * <br>
 * Output format string can contain below wildcards. Every wildcard
 * must be start with percent sign (\%)
 *
 * <b>Depending on loglevel, source code is excluded from compile !</b><br>
 * <br>
 * <b>Wildcards</b><br>
 * <ul>
 * <li><b>\%s</b>	replace with an string (char*)</li>
 * <li><b>\%c</b>	replace with an character</li>
 * <li><b>\%d</b>	replace with an integer value</li>
 * <li><b>\%l</b>	replace with an long value</li>
 * <li><b>\%f</b>	replace with a float value</li>
 * <li><b>\%x</b>	replace and convert integer value into hex</li>
 * <li><b>\%X</b>	like %x but combine with <b>0x</b>123AB</li>
 * <li><b>\%b</b>	replace and convert integer value into binary</li>
 * <li><b>\%B</b>	like %x but combine with <b>0b</b>10100011</li>
 * <li><b>\%t</b>	replace and convert boolean value into <b>"t"</b> or <b>"f"</b></li>
 * <li><b>\%T</b>	like %t but convert into <b>"true"</b> or <b>"false"</b></li>
 * </ul><br>
 * <b>Loglevels</b><br>
 * <table border="0">
 * <tr><td>0</td><td>LOG_LEVEL_NOOUTPUT</td><td>no output </td></tr>
 * <tr><td>1</td><td>LOG_LEVEL_ERRORS</td><td>only errors </td></tr>
 * <tr><td>2</td><td>LOG_LEVEL_INFOS</td><td>errors and info </td></tr>
 * <tr><td>3</td><td>LOG_LEVEL_DEBUG</td><td>errors, info and debug </td></tr>
 * <tr><td>4</td><td>LOG_LEVEL_VERBOSE</td><td>all </td></tr>
 * </table>
 *
 * Revision History:
 * TODO_revision history
 *****************************************************************************/
#ifndef LOGGING_H
#define LOGGING_H

#ifdef __cplusplus
extern "C"
{
#endif
/**************************************************************************
 * Include Files
 **************************************************************************/
#include <stdint.h>

/**************************************************************************
 * Manifest Constants
 **************************************************************************/
#define LOG_LEVEL_NOOUTPUT 0
#define LOG_LEVEL_ERRORS 1
#define LOG_LEVEL_INFOS 2
#define LOG_LEVEL_DEBUG 3
#define LOG_LEVEL_VERBOSE 4

/**************************************************************************
 * Type Definitions
 **************************************************************************/

/**************************************************************************
 * Global variables
 **************************************************************************/

/**************************************************************************
 * Macros
 **************************************************************************/

/**************************************************************************
 * Global Functions Declarations
 **************************************************************************/

/**
 * Initiale logigng
 * \param void
 * \return void
 *
 */
void Logging_Init(uint8_t level);

/**
 * Assert given expression. Abort in case of failure
 * @param func
 * @param file
 * @param lineno
 * @param failedexpr
 */
void Logging_Assert(const char* func, const char* file, int lineno, const char* expr);


/**
 * Output an error message. Output message contains
 * ERROR: followed by original msg
 * Error messages are printed out, at every loglevel
 * except 0 ;-)
 * \param msg format string to output
 * \param ... any number of variables
 * \return void
 */
void Logging_Error(const char msg[], ...);

/**
 * Output an info message. Output message contains
 * Info messages are printed out at l
 * loglevels >= LOG_LEVEL_INFOS
 *
 * \param msg format string to output
 * \param ... any number of variables
 * \return void
 */

void Logging_Info(const char* msg, ...);
void Logging_InfoLn(const char* msg, ...);

/**
 * Output an debug message. Output message contains
 * Debug messages are printed out at l
 * loglevels >= LOG_LEVEL_DEBUG
 *
 * \param msg format string to output
 * \param ... any number of variables
 * \return void
 */

void Logging_Debug(const char* msg, ...);
void Logging_DebugLn(const char* msg, ...);

/**
 * Output an verbose message. Output message contains
 * Debug messages are printed out at l
 * loglevels >= LOG_LEVEL_VERBOSE
 *
 * \param msg format string to output
 * \param ... any number of variables
 * \return void
 */

void Logging_Verbose(const char msg[], ...);
void Logging_VerboseLn( const char * msg, ...);

#ifdef __cplusplus
}
#endif

#endif /* LOGGING_H */
