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

void Logging::Init(int level, Stream*  arg_p_output_stream)
{
	_p_output_stream = arg_p_output_stream;
	_level = constrain(level,LOG_LEVEL_NOOUTPUT,LOG_LEVEL_VERBOSE);
}

void Logging::Error(char* msg, ...){
	if (LOG_LEVEL_ERRORS <= _level) {
		print ("ERROR: ",0);
		va_list args;
		va_start(args, msg);
		print(msg,args);
	}
}

void Logging::Error(const __FlashStringHelper * msg, ...){
	if (LOG_LEVEL_ERRORS <= _level) {
		print ("ERROR: ",0);
		va_list args;
		va_start(args, msg);
		print(msg,args);
	}
}

void Logging::Info(char* msg, ...){
	if (LOG_LEVEL_INFOS <= _level) {
		va_list args;
		va_start(args, msg);
		print(msg,args);
	}
}

void Logging::Info(const __FlashStringHelper * msg, ...){
	if (LOG_LEVEL_INFOS <= _level) {
		va_list args;
		va_start(args, msg);
		print(msg,args);
	}
}

void Logging::Debug(char* msg, ...){
	if (LOG_LEVEL_DEBUG <= _level) {
		va_list args;
		va_start(args, msg);
		print(msg,args);
	}
}

void Logging::Debug(const __FlashStringHelper * msg, ...){
	if (LOG_LEVEL_DEBUG <= _level) {
		va_list args;
		va_start(args, msg);
		print(msg,args);
	}
}


void Logging::Verbose(char* msg, ...){
	if (LOG_LEVEL_VERBOSE <= _level) {
		va_list args;
		va_start(args, msg);
		print(msg,args);
	}
}

void Logging::Verbose(const __FlashStringHelper * msg, ...){
	if (LOG_LEVEL_VERBOSE <= _level) {
		va_list args;
		va_start(args, msg);
		print(msg,args);
	}
}

void Logging::printArg(char arg_s8Char, va_list& args) {
	if (arg_s8Char == '%') {
		_p_output_stream->print(arg_s8Char);
	}
	if( arg_s8Char == 's' ) {
		register char *s = (char *)va_arg( args, int );
		_p_output_stream->print(s);
	}
	if( arg_s8Char == 'd' || arg_s8Char == 'i') {
		_p_output_stream->print(va_arg( args, int ),DEC);
	}
	if( arg_s8Char == 'u') {
		_p_output_stream->print((unsigned int) va_arg( args, int ),DEC);
	}
	if( arg_s8Char == 'x' ) {
		_p_output_stream->print(va_arg( args, int ),HEX);
	}
	if( arg_s8Char == 'X' ) {
		_p_output_stream->print("0x");
		_p_output_stream->print(va_arg( args, int ),HEX);
	}
	if( arg_s8Char == 'b' ) {
		_p_output_stream->print(va_arg( args, int ),BIN);
	}
	if( arg_s8Char == 'B' ) {
		_p_output_stream->print("0b");
		_p_output_stream->print(va_arg( args, int ),BIN);
	}
	if( arg_s8Char == 'l' ) {
		_p_output_stream->print(va_arg( args, long ),DEC);
	}

	if( arg_s8Char == 'c' ) {
		char s = (char)va_arg( args, int );
		_p_output_stream->print(s);
	}
	if( arg_s8Char == 't' ) {
		if (va_arg( args, int ) == 1) {
			_p_output_stream->print("T");
		}
		else {
			_p_output_stream->print("F");
		}
	}
	if( arg_s8Char == 'T' ) {
		if (va_arg( args, int ) == 1) {
			_p_output_stream->print("true");
		}
		else {
			_p_output_stream->print("false");
		}
	}
	if( arg_s8Char == 'f' ) {
		_p_output_stream->print((float) va_arg( args, double ), 8);
	}
}

void Logging::print(const __FlashStringHelper * arg_ps8FlashString, va_list args) {
	const char *loc_ps8CurrByte = (const char *)arg_ps8FlashString;
	char loc_s8CurrentChar;

	// loop through format string
	while(1)
	{
		loc_s8CurrentChar = pgm_read_byte(loc_ps8CurrByte++);
		if (loc_s8CurrentChar == 0) break;
		if (loc_s8CurrentChar == '%') {
			loc_s8CurrentChar = pgm_read_byte(loc_ps8CurrByte++);
			if (loc_s8CurrentChar == '\0') break;
			printArg(loc_s8CurrentChar, args);
		}
		else
		{
			_p_output_stream->print(loc_s8CurrentChar);
		}
	}
	_p_output_stream->flush();
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
			_p_output_stream->print(*format);
		}
	}
	_p_output_stream->flush();
}

Logging Log = Logging();
