/******************************************************************************
 * @file    logging.cpp
 * @author  Rémi Pincent - INRIA
 * @date    15 janv. 2014
 *
 * @brief Implementation of Logging class
 *
 * Project : logger library
 * Contact:  Rémi Pincent - remi.pincent@inria.fr
 *
 * Revision History:
 * TODO_revision history
 *****************************************************************************/

#include "logging.h"
#include <assert.h>
#include <cstdlib>
#include <bitset>

static const char* ERROR_STR = "ERROR: ";
static const char* BL = "\n";
static const char* IN_FILE = "\nfile: ";
static const char* LINE = "-l";

extern void __assert(const char *__func, const char *__file,
		     int __lineno, const char *__sexp);

void Logging::Init(uint8_t arg_level, ostream*  arg_p_output_stream)
{
	_p_output_stream = arg_p_output_stream;

	//_output_stream = arg_output_stream;
    if(arg_level < LOG_LEVEL_NOOUTPUT) {
    	_u8_logLevel = LOG_LEVEL_NOOUTPUT;
    }
    else if(LOG_LEVEL_VERBOSE < arg_level) {
    	_u8_logLevel = LOG_LEVEL_VERBOSE;
    }
    else
    	_u8_logLevel = arg_level;
}

/**
 * MAP assert on Logging::Assert
 * @param __func
 * @param __file
 * @param __lineno
 * @param __sexp
 */
void __assert(const char *__func, const char *__file,
	     int __lineno, const char *__sexp)
{
	Log.Assert(__func, __file, __lineno, __sexp);
}

void Logging::Assert(const char* func, const char* file, int lineno, const char* expr)
{
	 // transmit diagnostic informations through serial link.
	*_p_output_stream << "ASSERTION FAILED :";
	*_p_output_stream << expr;
	*_p_output_stream << BL;
	*_p_output_stream << "At ";
	*_p_output_stream << func;
	*_p_output_stream << " in ";
	*_p_output_stream << file;
	*_p_output_stream << " l.";
	*_p_output_stream << lineno;
	*_p_output_stream << endl;
	// abort program execution.
	abort();
}

void Logging::Error(const char* msg, ...){
	if (LOG_LEVEL_ERRORS <= _u8_logLevel) {
		*_p_output_stream << ERROR_STR;
		va_list args;
		va_start(args, msg);
		print(msg,args);
		*_p_output_stream << BL;
		*_p_output_stream << endl;
	}
}

void Logging::Error(char errorId, const char * file, int line){
	if (LOG_LEVEL_ERRORS <= _u8_logLevel) {
		*_p_output_stream << ERROR_STR;
		*_p_output_stream << "id = ";
		*_p_output_stream << (int)errorId;
		*_p_output_stream << IN_FILE;
		*_p_output_stream << file;
		*_p_output_stream << LINE;
		*_p_output_stream << line;
		*_p_output_stream << BL;
		*_p_output_stream << endl;
	}
}

void Logging::Info(const char msg[], ...){
	if (LOG_LEVEL_INFOS <= _u8_logLevel) {
		va_list args;
		va_start(args, msg);
		print(msg,args);
		*_p_output_stream << endl;
	}
}

void Logging::InfoLn(const char msg[], ...){
	if (LOG_LEVEL_INFOS <= _u8_logLevel) {
		va_list args;
		va_start(args, msg);
		print(msg,args);
		*_p_output_stream << "\n";
		*_p_output_stream << endl;
	}
}

void Logging::Debug(const char* msg, ...){
	if (LOG_LEVEL_DEBUG <= _u8_logLevel) {
		va_list args;
		va_start(args, msg);
		print(msg,args);
		*_p_output_stream << endl;
	}
}

void Logging::DebugLn(const char* msg, ...){
	if (LOG_LEVEL_DEBUG <= _u8_logLevel) {
		va_list args;
		va_start(args, msg);
		print(msg,args);
		*_p_output_stream << "\n";
		*_p_output_stream << endl;
	}
}

void Logging::Verbose(const char* msg, ...){
	if (LOG_LEVEL_VERBOSE <= _u8_logLevel) {
		va_list args;
		va_start(args, msg);
		print(msg,args);
		*_p_output_stream << endl;
	}
}

void Logging::printArg(const char arg_s8Char, va_list args) {
	if (arg_s8Char == '%') {
		*_p_output_stream << arg_s8Char;
	}
	if( arg_s8Char == 's' ) {
		register char *s = (char *)va_arg( args, int );
		*_p_output_stream << s;
	}
	if( arg_s8Char == 'd' || arg_s8Char == 'i') {
		*_p_output_stream << va_arg( args, int );
	}
	if( arg_s8Char == 'u') {
		*_p_output_stream << (unsigned int) va_arg( args, int );
	}
	if( arg_s8Char == 'x' ) {
		*_p_output_stream << std::hex << va_arg( args, int );
	}
	if( arg_s8Char == 'X' ) {
		*_p_output_stream << "0x";
		*_p_output_stream << std::hex << va_arg( args, int );
	}
	if( arg_s8Char == 'b' ) {
		*_p_output_stream << std::bitset<sizeof(int)*8>(va_arg( args, int ));
	}
	if( arg_s8Char == 'B' ) {
		*_p_output_stream << "0b";
		*_p_output_stream << std::bitset<sizeof(int)*8>(va_arg( args, int ));
	}
	if( arg_s8Char == 'l' ) {
		*_p_output_stream << va_arg( args, long );
	}

	if( arg_s8Char == 'c' ) {
		*_p_output_stream << (char)va_arg( args, int );
	}
	if( arg_s8Char == 't' ) {
		if (va_arg( args, int ) == 1) {
			*_p_output_stream << "T";
		}
		else {
			*_p_output_stream << "F";
		}
	}
	if( arg_s8Char == 'T' ) {
		if (va_arg( args, int ) == 1) {
			*_p_output_stream << "true";
		}
		else {
			*_p_output_stream << "false";
		}
	}
	if( arg_s8Char == 'f' ) {
		*_p_output_stream << (float) va_arg( args, double );
	}
}

void Logging::print(const char *format, va_list args) {
	//
	// loop through format string
	for (; *format != 0; ++format) {
		if (*format == '%') {
			++format;
			if (*format == '\0') break;
				printArg(*format, args);
		}
		else
		{
			*_p_output_stream << *format;
		}
	}
}

Logging Log = Logging();
