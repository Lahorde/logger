/******************************************************************************
 * @file    logging.c
 * @author  Rémi Pincent - INRIA
 * @date    20/03/2018
 *
 * @brief Implementation of Logging class using printf
 *
 * Project : logger library
 * Contact:  Rémi Pincent - remi.pincent@inria.fr
 *
 * Revision History:
 * TODO_revision history
 *****************************************************************************/
/**************************************************************************
 * Include Files
 **************************************************************************/
#include "logging.h"
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

/**************************************************************************
 * Manifest Constants
 **************************************************************************/
#define  ERROR_STR "ERROR: "
#define  BL "\n"

/**************************************************************************
 * Type Definitions
 **************************************************************************/

/**************************************************************************
 * Global Variables
 **************************************************************************/

/**************************************************************************
 * Static Variables
 **************************************************************************/
static uint8_t _u8_logLevel = LOG_LEVEL_NOOUTPUT;

/**************************************************************************
 * Macros
 **************************************************************************/

/**************************************************************************
 * Local Functions Declarations
 **************************************************************************/

/**************************************************************************
 * Global Functions Definitions
 **************************************************************************/
extern void
__attribute__((noreturn))
__assert_func (const char *file, int line, const char *func,
               const char *failedexpr);

void Logging_Init(uint8_t level)
{
	assert(level <= LOG_LEVEL_VERBOSE);
	_u8_logLevel = level;
}

/**
 * MAP assert on Logging_Assert
 * @param __func
 * @param __file
 * @param __lineno
 * @param __sexp
 */
void __assert_func (const char *file, int line, const char *func, const char *failedexpr)
{
	Logging_Assert(func, file, line, failedexpr);
}

void __attribute__((noreturn)) Logging_Assert(const char* func, const char* file, int lineno, const char* expr)
{
	printf("ASSERTION FAILED : %s %sAt %s in %s l.%d", expr, BL, func, file, lineno);
	// abort program execution.
	abort();
}

void Logging_Error(const char* msg, ...){
	if (LOG_LEVEL_ERRORS <= _u8_logLevel) {
		va_list args;
		va_start(args, msg);
		printf(ERROR_STR);
		vprintf(msg,args);
		va_end(args);
	}
}


void Logging_Info(const char* msg, ...){
	if (LOG_LEVEL_INFOS <= _u8_logLevel) {
		va_list args;
		va_start(args, msg);
		vprintf(msg,args);
		va_end(args);
	}
}

void Logging_InfoLn(const char* msg, ...){
	if (LOG_LEVEL_INFOS <= _u8_logLevel) {
		va_list args;
		va_start(args, msg);
		vprintf(msg,args);
		va_end(args);
		printf(BL);
	}
}

void Logging_Debug(const char* msg, ...){
	if (LOG_LEVEL_DEBUG <= _u8_logLevel) {
		va_list args;
		va_start(args, msg);
		vprintf(msg,args);
		va_end(args);
	}
}

void Logging_DebugLn(const char msg[], ...){
	if (LOG_LEVEL_DEBUG <= _u8_logLevel) {
			va_list args;
			va_start(args, msg);
			vprintf(msg,args);
			va_end(args);
			printf(BL);
		}
}

void Logging_Verbose(const char msg[], ...){
	if (LOG_LEVEL_VERBOSE <= _u8_logLevel) {
		va_list args;
		va_start(args, msg);
		vprintf(msg,args);
		va_end(args);
	}
}

/**************************************************************************
* Local Functions Definitions
**************************************************************************/
