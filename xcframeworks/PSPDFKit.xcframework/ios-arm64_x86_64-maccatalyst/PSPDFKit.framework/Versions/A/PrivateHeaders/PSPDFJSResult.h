//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFJavaScriptActionEvent;

/// Possible JavaScript result types from script evaluation.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFJSType) {
    PSPDFJSString,
    PSPDFJSBoolean,
    PSPDFJSNumber,
    PSPDFJSArray,
    PSPDFJSObject,
    PSPDFJSUndefined,
    PSPDFJSNull,
} NS_SWIFT_NAME(PSPDFJSValue.Kind);

/// Structure that represents the result of a JavaScript script
/// evaluation.
@interface PSPDFJSValue : NSObject

- (instancetype)initWithString:(NSString *)string;

@property (nonatomic, readonly) PSPDFJSType type;

@property (nonatomic, readonly, copy, nullable) NSString *stringValue;

@property (nonatomic, readonly) BOOL boolValue;

@property (nonatomic, readonly, nullable) NSNumber *numberValue;

@end

PSPDF_EXPORT NSString *const PSPDFJavascriptErrorDomain;

// List of JavaScript error codes.
typedef NS_ERROR_ENUM(PSPDFJavascriptErrorDomain, PSPDFJavascriptErrorCode) {
    /// JavaScript is disabled by the platform.
    PSPDFJavaScriptErrorJavaScriptDisabled = 100,
    /// An action script was not executed correctly (bad syntax, missing API, etc.).
    PSPDFJavaScriptErrorScriptExecutionFailed = 101,
    /// An action script was executed correctly but it rejected the change (the event return code is false).
    PSPDFJavascriptErrorScriptValidationFailed = 102,
} NS_SWIFT_NAME(JavascriptError);

/// Structure that represents the result of evaluating JS. It can be a
/// JS value, or an evaluation error.
@interface PSPDFJSResult : NSObject

- (instancetype)initWithEvent:(PSPDFJavaScriptActionEvent *)event;

@property (nonatomic, readonly, nullable) PSPDFJavaScriptActionEvent *event;

@property (nonatomic, readonly, nullable) PSPDFJSValue *value;

@property (nonatomic, readonly, nullable) NSError *error;

@end

NS_ASSUME_NONNULL_END
