//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#else
#import "PSPDFEnvironment.h"
#endif

/// The log level.
///
/// Log levels are sorted by their severity, with `.critical` being the most
/// severe and `.verbose` being the least severe.
///
/// Setting a log level implies enabling all log levels with higher severity.
/// For example, setting `PSPDFKit.SDK.shared.logLevel = .warning` also enables
/// logging of messages with the level `.error` or `.critical`.
///
/// By default, PSPDFKit uses `OSLog` under the hood to send log messages to
/// the operating system. Such logs can be viewed in Xcode, in the Console app
/// or using the `log` command-line utility.
///
/// ### Viewing Logs in Xcode
///
/// Logs will appear in Xcode's Debug Area Console. If the console is not
/// visible, it can be brought back using View → Debug Area → Activate Console.
///
/// ### Viewing Logs in the Console app
///
/// To view the PSPDFKit logs in the Console app, set the Subsystem filter to
/// `com.pspdfkit.sdk`. To see `.debug` and `.info` logs, you must enable the
/// necessary options in the Action → Include Info/Debug Messages.
///
/// ### Viewing Logs in the Terminal
///
/// You can use the `log` command-line utility to steam logs from your Mac
/// Catalyst app or from your iOS app running in the iOS Simulator:
///
/// ```none
/// log stream --level debug --predicate 'subsystem == "com.pspdfkit.sdk"'
/// ```
///
/// In case you're not seeing the logs from your iOS app running in the iOS
/// Simulator, try prefixing the command with `xcrun`:
///
/// ```none
/// xcrun simctl spawn booted log stream --level debug --predicate 'subsystem == "com.pspdfkit.sdk"'
/// ```
///
/// If you're having troubles using the `log` command-line utility, or if it
/// produces ambiguous errors, we recommend using the Console app instead.
typedef NS_ENUM(NSInteger, PSPDFLogLevel) {

    /// Log critical issues that can break or limit the functionality of
    /// PSPDFKit.
    PSPDFLogLevelCritical,

    /// Log unrecoverable errors that are important but not critical.
    PSPDFLogLevelError,

    /// Log recoverable errors and warnings.
    PSPDFLogLevelWarning,

    /// Log important operations. This is the default log level.
    PSPDFLogLevelInfo,

    /// Log details about operations for debugging purposes. Enabling this level
    /// will have a performance impact on your app.
    ///
    /// @note By default, when using `OSLog` and running in iOS Simulator, this
    /// log level is automatically reclassified as `.info` as a workaround for
    /// log streaming not working in iOS Simulator (FB9028830).
    PSPDFLogLevelDebug,

    /// Log as much information as possible. Enabling this level will have a
    /// performance impact on your app.
    ///
    /// @warning Logs with this level can include security-sensitive or
    /// personally idenfitiable information. Don't enable it in release builds.
    ///
    /// @note By default, when using `OSLog`, this log level is automatically
    /// reclassified as `.debug`, unless running in iOS Simulator, in which
    /// case it's reclassified as `.info` as a workaround for log streaming not
    /// working in iOS Simulator (FB9028830).
    PSPDFLogLevelVerbose,

} PSPDF_ENUM_SWIFT(LogLevel);
