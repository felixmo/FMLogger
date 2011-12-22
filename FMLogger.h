//
//  FMLogger.h
//  
//  Created by Felix Mo on 11-08-21.
//
//  Copyright (c) 2011 Felix Mo. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
// 
//  
//   Log Levels
//  ------------
//
//  -> FMLoggerTrace(fmt, ...)    - for tracing program flow
//  -> FMLoggerDebug(fmt, ...)    - for temporary use during debugging; will not be compiled in non-debug builds
//  -> FMLoggerInfo(fmt, ...)     - for general information messages
//  -> FMLoggerError(fmt, ...)    - for use when there is an error to be logged
//


#import <Foundation/Foundation.h>


//  Settings
// ----------

#define TRACE_ENABLED 1                         // Default: 1 | Enable [TRACE] logging
#define LOGS_SAVE_ENABLED 1                     // Default: 1 | Enable saving of logs to disk
#define LOGS_KEEP_LAST_DAYS 14                  // Default: 14 | Number of days of logs to keep; older logs are purged
#define PATH_LOGS_FOLDER @"/Documents/Logs"     // Default: "/Documents/Logs" | Path to logs folder


//  Output formatting
// -------------------

#define FORMAT_MSG @"%@ | [%@] | %@"                                 // Default: "[%@] | %@" | Standard message (ex. "2011-08-22 15:02:39 +0000 | [INFO] | Entry named "Untitled" was created")
#define FORMAT_FUNC_LINE_MSG @"%@ | [%@] | %@ | %s @ (line %d)"      // Default: "[%@] | %s @ (line %d) | %@" | Message with function and line number (ex. "2011-08-22 15:02:39 +0000 | [DEBUG] | Msg: "Hello World!" | -(void)outputMsg: @ (line 8)")


//  Log level type
// ----------------

typedef enum {
    
    kFMLoggerLevelTrace,
    kFMLoggerLevelDebug,
    kFMLoggerLevelInfo,
    kFMLoggerLevelError
    
} kFMLoggerLevel;


//  FMLogger interface
// --------------------

@interface FMLogger : NSObject

// Returns a reference to the shared FMLogger instance
+ (id)sharedLogger;

// -- Logging methods --
- (void)logLevel:(kFMLoggerLevel)level withMessage:(NSString *)fmt, ...NS_FORMAT_FUNCTION(2, 3);
- (void)logLevel:(kFMLoggerLevel)level forFunction:(const char *)func atLine:(int)line withMessage:(NSString *)fmt, ...NS_FORMAT_FUNCTION(4, 5);

@property (nonatomic, retain) NSMutableArray *sessionLogEntries;

@end // FMLogger


//  C macros
// ----------

// Trace
#define FMLoggerTrace(...) \
[[FMLogger sharedLogger] logLevel:kFMLoggerLevelTrace forFunction:__PRETTY_FUNCTION__ atLine:__LINE__ withMessage:__VA_ARGS__];

// Debug
#define FMLoggerDebug(...) \
[[FMLogger sharedLogger] logLevel:kFMLoggerLevelDebug forFunction:__PRETTY_FUNCTION__ atLine:__LINE__ withMessage:__VA_ARGS__];

// Error
#define FMLoggerError(...) \
[[FMLogger sharedLogger] logLevel:kFMLoggerLevelError forFunction:__PRETTY_FUNCTION__ atLine:__LINE__ withMessage:__VA_ARGS__];

// Info
#define FMLoggerInfo(...) \
[[FMLogger sharedLogger] logLevel:kFMLoggerLevelInfo forFunction:__PRETTY_FUNCTION__ atLine:__LINE__ withMessage:__VA_ARGS__];


// Remove FMLoggerDebug statements outside of non-debug builds
#ifdef DEBUG
    #undef FMLoggerDebug
    #define FMLoggerDebug(...) do {} while (0)
#endif


// Remove FMLoggerTrace statements if not enabled
#if TRACE_ENABLED == 0
    #undef FMLoggerTrace
    #define FMLoggerTrace(...) do {} while (0)
#endif
