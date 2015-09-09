/******************************************************************************
 * @file    logger_test.cpp 
 * @author  Rémi Pincent - INRIA
 * @date    3 sept. 2015   
 *
 * @brief simple test for logger lib
 * 
 * Project : logger
 * Contact:  Rémi Pincent - remi.pincent@inria.fr
 * 
 * Revision History:
 * TODO_revision history
 *****************************************************************************/
#include "logger.h"
#include "logger_test.h"
#include <chrono>

void logger_test(void){
	LOG_INIT_STREAM(LOG_LEVEL_VERBOSE, &cout);
	LOG_ERROR("this is an error log - display %d as binary %B", 0xFFFF, 0xFFFF);
	LOG_INFO("this is an info log - display %d as hexa %X", 0xFFFF, 0xFFFF);
	LOG_DEBUG("this is a debug log - display a long %l", -2111222333);
	LOG_VERBOSE("this is a verbose log - display %d as binary %b", 0xFFFF, 0xFFFF);

	LOG_INIT_STREAM(LOG_LEVEL_DEBUG, &cout);
	LOG_ERROR("this is an error log - display %d as binary %B", 0xFFFF, 0xFFFF);
	LOG_INFO("this is an info log - display %d as hexa %X", 0xFFFF, 0xFFFF);
	LOG_DEBUG("this is a debug log - display a long %l", 2111222333);
	LOG_VERBOSE("this is a verbose log - it must not be displayed ! - display %d as binary %b", 0xFFFF, 0xFFFF);

	LOG_INIT_STREAM(LOG_LEVEL_INFOS, &cout);
	LOG_ERROR("this is an error log - display %d as binary %B", 0xFFFF, 0xFFFF);
	LOG_INFO("this is an info log - display %d as hexa %X", 0xFFFF, 0xFFFF);
	LOG_DEBUG("this is a debug log - it must not be displayed ! - display a long %l", 2111222333);
	LOG_VERBOSE("this is a verbose log - it must not be displayed ! - display %d as binary %b", 0xFFFF, 0xFFFF);


	LOG_INIT_STREAM(LOG_LEVEL_ERRORS, &cout);
	LOG_ERROR("this is an error log - display %d as binary %B", 0xFFFF, 0xFFFF);
	LOG_INFO("this is an info log - it must not be displayed ! - display %d as hexa %X", 0xFFFF, 0xFFFF);
	LOG_DEBUG("this is a debug log - it must not be displayed ! - display a long %l", -2111222333);
	LOG_VERBOSE("this is a verbose log - it must not be displayed ! - display %d as binary %b", 0xFFFF, 0xFFFF);

	LOG_INIT_STREAM(LOG_LEVEL_NOOUTPUT, &cout);
	LOG_ERROR("this is an error log - it must not be displayed ! - display %d as binary %B", 0xFFFF, 0xFFFF);
	LOG_INFO("this is an info log - it must not be displayed ! - display %d as hexa %X", 0xFFFF, 0xFFFF);
	LOG_DEBUG("this is a debug log - it must not be displayed ! - display a long %l", -21112223333);
	LOG_VERBOSE("this is a verbose log - it must not be displayed ! - display %d as binary %b", 0xFFFF, 0xFFFF);

	LOG_DEBUG("program will exit soon on an assertion...");
	ASSERT(true == false);
}

