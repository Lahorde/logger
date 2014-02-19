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

/**
 * Default log level
 */
#ifndef LOGLEVEL
	#define LOGLEVEL LOG_LEVEL_INFOS
#endif

#if (LOGLEVEL >= LOG_LEVEL_NOOUTPUT)
	#define	 LOG_INIT_STATIC_SPEED(level) Log.Init(level)
#else
	#define	 LOG_INIT(level)
#endif

#if (LOGLEVEL >= LOG_LEVEL_NOOUTPUT)
	#define	 LOG_INIT(level, baud) Log.Init(level, baud)
#else
	#define	 LOG_INIT(level, baud)
#endif

#if (LOGLEVEL >= LOG_LEVEL_ERRORS)
	#define LOG_ERROR(msg, 	arguments...) Log.Error(msg, ## arguments)
#else
	#define LOG_ERROR(msg, arguments...)
#endif

#if (LOGLEVEL >= LOG_LEVEL_INFOS)
	#define LOG_INFO(msg, 	arguments...) Log.Info(msg, ## arguments)
#else
	#define LOG_INFO(msg, arguments...)
#endif

#if (LOGLEVEL >= LOG_LEVEL_DEBUG)
	#define LOG_DEBUG(msg, 	arguments...) Log.Debug(msg, ## arguments)
#else
	#define LOG_DEBUG(msg, arguments...)
#endif

#if (LOGLEVEL >= LOG_LEVEL_VERBOSE)
	#define LOG_VERBOSE(msg, 	arguments...) Log.Verbose(msg, ## arguments)
#else
	#define LOG_VERBOSE(msg, arguments...)
#endif

#endif /* LOGGER_H_ */
