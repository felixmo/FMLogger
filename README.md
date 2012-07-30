FMLogger
========

Simple logging for iOS 4.0+.


### Usage

To begin using FMLogger, just drop the class into your project and import where used.

Logs files, by default, are saved to .../Documents/Logs

Use the following in place of NSLog:

	FMLoggerVerbose(fmt, ...)  // for detailed informational messages used for debugging
	
	FMLoggerInfo(fmt, ...)     // for general informational messages that highlight the progress of the application

	FMLoggerWarning(fmt, ...)  // for informational messages that highlight potential error events

	FMLoggerError(fmt, ...)    // for informational messages pretaining to error events
	
#### Example usage

	FMLoggerVerbose(@"Processing list with name: %@", list.name);


### Sample output

	2011-12-28 18:11:43 -0500 | [VERB.] | Began refreshing | -[FMSyncManager refresh] @ (line 350)
	2011-12-28 18:11:43 -0500 | [VERB.] | Began getting lists | -[FMSyncManager getObjectsOfType:] @ (line 448)
	2011-12-28 18:11:44 -0500 | [VERB.] | Processing list with name: Reminders | __34-[FMSyncManager getObjectsOfType:]_block_invoke_0 @ (line 469)
	2011-12-28 18:11:44 -0500 | [VERB.] | Finished getting lists | __34-[FMSyncManager getObjectsOfType:]_block_invoke_0 @ (line 554)


### Copyright and License

Copyright (c) 2011-2012 Felix Mo. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.