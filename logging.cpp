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

#define LOG_ENABLED

void Logging::Init(int level){
    _level = constrain(level,LOG_LEVEL_NOOUTPUT,LOG_LEVEL_VERBOSE);
    _baud = DEFAULT_LOG_SPEED;
    Serial.begin(DEFAULT_LOG_SPEED);
}

/* Serial speed cannot be changed at run time on ATtiny */
#if defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
#else
void Logging::Init(int level, long baud){
    _level = constrain(level,LOG_LEVEL_NOOUTPUT,LOG_LEVEL_VERBOSE);
    _baud = baud;
    Serial.begin(_baud);
}
#endif

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
    if (LOG_LEVEL_INFOS <= _level) {
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
    if (LOG_LEVEL_INFOS <= _level) {
        va_list args;
        va_start(args, msg);
        print(msg,args);
    }
}

void Logging::printArg(char arg_s8Char, va_list& args) {
	if (arg_s8Char == '%') {
		Serial.print(arg_s8Char);
	}
	if( arg_s8Char == 's' ) {
		register char *s = (char *)va_arg( args, int );
		Serial.print(s);
	}
	if( arg_s8Char == 'd' || arg_s8Char == 'i') {
		Serial.print(va_arg( args, int ),DEC);
	}
	if( arg_s8Char == 'x' ) {
		Serial.print(va_arg( args, int ),HEX);
	}
	if( arg_s8Char == 'X' ) {
		Serial.print("0x");
		Serial.print(va_arg( args, int ),HEX);
	}
	if( arg_s8Char == 'b' ) {
		Serial.print(va_arg( args, int ),BIN);
	}
	if( arg_s8Char == 'B' ) {
		Serial.print("0b");
		Serial.print(va_arg( args, int ),BIN);
	}
	if( arg_s8Char == 'l' ) {
		Serial.print(va_arg( args, long ),DEC);
	}

	if( arg_s8Char == 'c' ) {
		char s = (char)va_arg( args, int );
		Serial.print(s);
	}
	if( arg_s8Char == 't' ) {
		if (va_arg( args, int ) == 1) {
			Serial.print("T");
		}
		else {
			Serial.print("F");
		}
	}
	if( arg_s8Char == 'T' ) {
		if (va_arg( args, int ) == 1) {
			Serial.print("true");
		}
		else {
			Serial.print("false");
		}
	}
	if( arg_s8Char == 'f' ) {
		Serial.print((float) va_arg( args, double ));
	}
}

void Logging::print(const __FlashStringHelper * arg_ps8FlashString, va_list args) {
	const char PROGMEM *loc_ps8CurrByte = (const char PROGMEM *)arg_ps8FlashString;

	char loc_s8CurrentChar;
	loc_ps8CurrByte = (const char PROGMEM *)arg_ps8FlashString;

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
			Serial.print(loc_s8CurrentChar);
		}
	}
	Serial.flush();
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
        	Serial.print(*format);
        }
    }
    Serial.flush();
 }

 Logging Log = Logging();
