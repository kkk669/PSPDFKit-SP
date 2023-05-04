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

/// Structure that models the information required to send a mail using JavaScript.
PSPDF_SUBCLASSING_RESTRICTED
@interface PSPDFJSMail : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

- (PSPDFJSMail *)initWithUi:(nullable NSNumber *)ui
                         to:(nullable NSString *)to
                         cc:(nullable NSString *)cc
                        bcc:(nullable NSString *)bcc
                    subject:(nullable NSString *)subject
                    message:(nullable NSString *)message NS_DESIGNATED_INITIALIZER;

/// If true (the default), the rest of the parameters are used in a
/// compose-new-message window that is displayed to the user. If
/// false, the cTo parameter is required and all others are
/// optional.
@property (nonatomic, readonly, nullable) NSNumber *ui;

/// The semicolon-delimited list of recipients for the message.
@property (nonatomic, readonly, nullable) NSString *to;

/// The semicolon-delimited list of CC recipients for the message.
@property (nonatomic, readonly, nullable) NSString *cc;

/// The semicolon-delimited list of BCC recipients for the message.
@property (nonatomic, readonly, nullable) NSString *bcc;

/// The subject of the message. The length limit is 64 KB.
@property (nonatomic, readonly, nullable) NSString *subject;

/// The content of the message. The length limit is 64 KB.
@property (nonatomic, readonly, nullable) NSString *message;

@end

NS_ASSUME_NONNULL_END
