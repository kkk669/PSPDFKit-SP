//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAbstractFormAction.h>

NS_ASSUME_NONNULL_BEGIN

/// Flags for reset-form actions, matching bit positions in the PDF specification.
typedef NS_OPTIONS(NSUInteger, PSPDFResetFormActionFlag) {
    PSPDFResetFormActionFlagIncludeExclude = 1 << (1 - 1),
} PSPDF_ENUM_SWIFT(ResetFormAction.Flag);

/// Reset Form Action.
PSPDF_CLASS_SWIFT(ResetFormAction)
@interface PSPDFResetFormAction : PSPDFAbstractFormAction

/// Designated initializer with reset form action `flags`.
- (instancetype)initWithFlags:(PSPDFResetFormActionFlag)flags;

/// The reset form action flags.
@property (nonatomic, readonly) PSPDFResetFormActionFlag flags;

@end

NS_ASSUME_NONNULL_END
