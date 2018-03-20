/******************************************************************************
 * @file    Logger.h 
 * @author  Rémi Pincent - INRIA
 * @date    29 janv. 2014   
 *
 * @brief LOG macros. Memory calls do not occupy memory space
 * when log level below application log level.
 * 
 * Project : logger library
 * Contact:  Rémi Pincent - remi.pincent@inria.fr
 * 
 * Revision History:
 * TODO_revision history
 *****************************************************************************/

#ifndef LOGGER_H_
#define LOGGER_H_

#include <logging.h>

#ifndef LOG_LEVEL
	#warning "No log level defined "
#endif

#if (LOG_LEVEL >= LOG_LEVEL_NOOUTPUT)
    #define	 LOG_INIT(level) Logging_Init(level)
    #define	 ASSERT(expr) ((expr) ? (void)0 : Logging_Assert(__func__, F(__FILE__), __LINE__, F(#expr)))
#else
    #define	 LOG_INIT(level)
    #define	 ASSERT(expr)
#endif

#if (LOG_LEVEL >= LOG_LEVEL_ERRORS)
	#define LOG_ERROR(msg, 	arguments...) Logging_Error(msg, ## arguments)
#else
	#define LOG_ERROR(msg, arguments...)
#endif

#if (LOG_LEVEL >= LOG_LEVEL_INFOS)
	#define LOG_INFO(msg, 	arguments...) Logging_Info(msg, ## arguments)
	#define LOG_INFO_LN(msg, 	arguments...) Logging_InfoLn(msg, ## arguments)
#else
	#define LOG_INFO(msg, arguments...)
	#define LOG_INFO_LN(msg, 	arguments...)
	#define LOG_INFO_STR(msg)
	#define LOG_INFO_STR_LN(msg)
#endif

#if (LOG_LEVEL >= LOG_LEVEL_DEBUG)
	#define LOG_DEBUG(msg, 	arguments...) Logging_Debug(msg, ## arguments)
	#define LOG_DEBUG_LN(msg, 	arguments...) Logging_DebugLn(msg, 	##arguments)
#else
	#define LOG_DEBUG(msg, arguments...)
	#define LOG_DEBUG_LN(msg, 	arguments...)
#endif

#if (LOG_LEVEL >= LOG_LEVEL_VERBOSE)
	#define LOG_VERBOSE(msg, 	arguments...) Logging_Verbose(msg, ## arguments)
	#define LOG_VERBOSE_LN(msg, 	arguments...) Logging_VerboseLn(msg, ## arguments)
#else
	#define LOG_VERBOSE(msg, arguments...)
	#define LOG_VERBOSE_LN(msg, arguments...)
#endif

#endif /* LOGGER_H_ */
