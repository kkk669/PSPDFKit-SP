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

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFJSAlertResult) {
    /// The user accepted the alert message.
    PSPDFJSAlertResultOK,

    /// The user cancelled the alert message and does not expect a
    /// further action to occur.
    PSPDFJSAlertResultCancel,

    /// The user rejected the alert message.
    PSPDFJSAlertResultNo,

    /// The user accepted the alert message.
    PSPDFJSAlertResultYes,
} NS_SWIFT_NAME(JSAlertResult);

/// A `PSPDFJSAlert` is the data model of an alert message shown by the JS engine.
@interface PSPDFJSAlert : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes a `PSPDFJSAlert` with a given title and body message.
- (instancetype)initWithTitle:(NSString *)title message:(NSString *)message NS_DESIGNATED_INITIALIZER;

/// Title of this JS alert.
@property (nonatomic, readonly, copy) NSString *title;

/// Message of this JS alert.
@property (nonatomic, readonly, copy) NSString *message;

@end

NS_ASSUME_NONNULL_END
