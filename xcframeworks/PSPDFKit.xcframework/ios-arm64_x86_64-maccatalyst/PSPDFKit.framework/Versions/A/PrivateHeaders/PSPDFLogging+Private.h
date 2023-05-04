//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFLogging.h>
#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKit/PSPDFError+Private.h>
#import <PSPDFKit/PSPDFAssert.h>
#else
#import "PSPDFLogging.h"
#import "PSPDFMacros+Private.h"
#import "Error/PSPDFError+Private.h"
#import "PSPDFAssert.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// Make a string representation of the log level.
PSPDF_EXTERN NSString * PSPDFStringFromLogLevel(PSPDFLogLevel level);

/// Internal global variable for the log level. Controlled via
/// `PSPDFKit.SDK.shared.logLevel`.
PSPDF_EXTERN PSPDFLogLevel PSPDFGlobalLogLevel;

/// The type of log handlers.
typedef void (^PSPDFLogHandler)(PSPDFLogLevel level, const char *_Nullable tag, NS_NOESCAPE NSString * (^message)(void), const char *_Nullable file, const char *_Nullable function, NSUInteger line);

/// Default log handler.
PSPDF_APP_EXPORT PSPDFLogHandler PSPDFLogHandlerBlock;

/// Internal logging function to make setting breakpoints easier.
PSPDF_EXTERN void _PSPDFLog(PSPDFLogLevel level, const char *_Nullable tag, NS_NOESCAPE NSString * (^message)(void));

NS_ASSUME_NONNULL_END

// Logging

#if defined(PSPDF_BLOCK_LOGGING)
#define PSPDF_LOG_USE_ONLY __unused
#else
#define PSPDF_LOG_USE_ONLY
#endif

#if defined(PSPDF_BLOCK_LOGGING)
#define PSPDFLogMacro(_level, _tag, _message)
#else
#define PSPDFLogMacro(_level, _tag, _message) PSPDFLogHandlerBlock(_level, _tag, _message, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__)
#endif

// MARK: - Classic Logging

// Classic logging macros that aren't tagged. These are for legacy use only.
// Prefer using `TLog` for new code instead.

#define PSPDFLogVerbose(format, ...) \
    PSPDFLogMacro(PSPDFLogLevelVerbose, NULL, (^{ \
        return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
    }))
#define PSPDFLogDebug(format, ...) \
    PSPDFLogMacro(PSPDFLogLevelDebug, NULL, (^{ \
        return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
    }))
#define PSPDFLog(format, ...) \
    PSPDFLogMacro(PSPDFLogLevelInfo, NULL, (^{ \
        return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
    }))
#define PSPDFLogWarning(format, ...) \
    PSPDFLogMacro(PSPDFLogLevelWarning, NULL, (^{ \
        return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
    }))
#define PSPDFLogError(format, ...) \
    PSPDFLogMacro(PSPDFLogLevelError, NULL, (^{ \
        return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
    }))
#define PSPDFLogCritical(format, ...) \
    PSPDFLogMacro(PSPDFLogLevelCritical, NULL, (^{ \
        return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
    }))

// Uses `dispatch_once`. Useful for warning about misconfigured set up.

#if defined(PSPDF_BLOCK_LOGGING)
#define PSPDFLogWarningOnce(format, ...)
#else
#define PSPDFLogWarningOnce(format, ...) \
    do { \
        static dispatch_once_t onceToken; \
        dispatch_once(&onceToken, ^{ \
            PSPDFLogWarning(format, ##__VA_ARGS__); \
        }); \
    } while (0)
#endif

// MARK: - Tagged Logging

// Logging macros that include a tag next to the log message. Use these when
// you need a one-off log without wanting to define a file-wide tag. If you use
// a tag more than once, prefer using `TLog` instead.

#define PSPDFTLogVerbose(tag, format, ...) \
    PSPDFLogMacro(PSPDFLogLevelVerbose, tag, (^{ \
        return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
    }))
#define PSPDFTLogDebug(tag, format, ...) \
    PSPDFLogMacro(PSPDFLogLevelDebug, tag, (^{ \
        return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
    }))
#define PSPDFTLog(tag, format, ...) \
    PSPDFLogMacro(PSPDFLogLevelInfo, tag, (^{ \
        return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
    }))
#define PSPDFTLogWarning(tag, format, ...) \
    PSPDFLogMacro(PSPDFLogLevelWarning, tag, (^{ \
        return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
    }))
#define PSPDFTLogError(tag, format, ...) \
    PSPDFLogMacro(PSPDFLogLevelError, tag, (^{ \
        return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
    }))
#define PSPDFTLogCritical(tag, format, ...) \
    PSPDFLogMacro(PSPDFLogLevelCritical, tag, (^{ \
        return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
    }))

// MARK: - Statically Tagged Logging

// Logging macros that use a file-wide tag.
//
// ```
// Logger("MyTag");
//
// @implementation Subsystem
//
// - (void)somethingDidHappen {
//     TLog(@"Something happened.") // Will prepend [MyTag].
// }
//
// @end
// ```

#define Logger(tag) static let LogTag = tag

#define TLogVerbose(format, ...) \
    PSPDFLogMacro(PSPDFLogLevelVerbose, LogTag, (^{ \
        return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
    }))
#define TLogDebug(format, ...) \
    PSPDFLogMacro(PSPDFLogLevelDebug, LogTag, (^{ \
        return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
    }))
#define TLog(format, ...) \
    PSPDFLogMacro(PSPDFLogLevelInfo, LogTag, (^{ \
        return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
    }))
#define TLogWarning(format, ...) \
    PSPDFLogMacro(PSPDFLogLevelWarning, LogTag, (^{ \
        return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
    }))
#define TLogError(format, ...) \
    PSPDFLogMacro(PSPDFLogLevelError, LogTag, (^{ \
        return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
    }))
#define TLogCritical(format, ...) \
    PSPDFLogMacro(PSPDFLogLevelCritical, LogTag, (^{ \
        return [NSString stringWithFormat:(@"" format), ##__VA_ARGS__]; \
    }))
