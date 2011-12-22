//
//  FMLogger.m
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


#import "FMLogger.h"


@interface FMLogger ()
    
- (NSString *)stringForLevel:(kFMLoggerLevel)level;

@end


@implementation FMLogger


#pragma mark - Property synthesizations

@synthesize sessionLogEntries;


#pragma mark - Static variables

static FMLogger *sharedLogger = nil;


#pragma mark - Memory management

- (void)dealloc {
    
    [sessionLogEntries release];
}


#pragma mark - Initalization

- (id)init {
    
    self = [super init];
    if (self) {
        
        sessionLogEntries = [[NSMutableArray alloc] init];
        
        return self; 
    }
    
    return nil;
}


#pragma mark - Class methods

+ (id)sharedLogger {
    
    if (sharedLogger == nil) {
        @synchronized(self) {
            sharedLogger = [[self alloc] init];
        }
    }
    
    return sharedLogger;
}


#pragma mark - Private helper methods

- (NSString *)stringForLevel:(kFMLoggerLevel)level {
    
    switch (level) {
        case kFMLoggerLevelTrace:
            return @"TRACE";
            break;
        case kFMLoggerLevelDebug:
            return @"DEBUG";
            break;
        case kFMLoggerLevelError:
            return @"ERROR";
            break;
        case kFMLoggerLevelInfo:
            return @"INFO";
            break;
            
        default:
            return @"UNDEFINED";
            break;
    }
}


#pragma mark - Logger methods

- (void)logLevel:(kFMLoggerLevel)level withMessage:(NSString *)fmt, ... {
    
    va_list args;
    va_start(args, fmt);
    NSString *msg = [[NSString alloc] initWithFormat:fmt arguments:args];
    va_end(args);
    
    NSString *output = [[NSString alloc] initWithFormat:FORMAT_MSG, [NSDate date], [self stringForLevel:level], msg];
    
    NSLog(@"%@", output);
    
    [self.sessionLogEntries addObject:output];
    
    [msg release];
    [output release];
}

- (void)logLevel:(kFMLoggerLevel)level forFunction:(const char *)func atLine:(int)line withMessage:(NSString *)fmt, ... {

    if (!func || !line) {
        
        [self logLevel:level withMessage:fmt];
        return;
    }
    
    va_list args;
    va_start(args, fmt);
    NSString *msg = [[NSString alloc] initWithFormat:fmt arguments:args];
    va_end(args);
    
    NSString *output = [[NSString alloc] initWithFormat:FORMAT_FUNC_LINE_MSG, [NSDate date], [self stringForLevel:level], msg, func, line];
    
    NSLog(@"%@", output);
    
    [self.sessionLogEntries addObject:output];
    
    [msg release];
    [output release];
}

@end
