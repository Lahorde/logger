# Logging library

## Overview
Logging library, supports a variable list of arguments and its format specifiers. 
Log level can be modified according to user needs. 
Using preprocessor logging macros defined in `logger.h` reduces code size depending on selected logger level.

## Supported targets

  * any target implementing `printf` and `vprintf`

## Log levels
 * LOG_LEVEL_NOOUTPUT 
 * LOG_LEVEL_ERRORS 
 * LOG_LEVEL_INFOS 
 * LOG_LEVEL_DEBUG 
 * LOG_LEVEL_VERBOSE 

## Code snippet

	/** Global defined must be defined here or in compilation flags */
    #define LOG_LEVEL LOG_LEVEL_DEBUG
        
    /** On your code initialize logger */   
    #include "logger.h"
    ...  
  	LOG_INIT(LOG_LEVEL);
  	LOG_INFO_LN("test logger!", 52);

