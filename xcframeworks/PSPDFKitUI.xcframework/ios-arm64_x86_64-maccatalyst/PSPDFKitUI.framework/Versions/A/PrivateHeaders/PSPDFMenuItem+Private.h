//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKitUI/PSPDFMenuItem.h>

NS_ASSUME_NONNULL_BEGIN

/// Executes invokable menu items and returns the execution count.
PSPDF_EXTERN NSUInteger PSPDFExecuteInvokableMenuItems(NSArray<PSPDFMenuItem *> * _Nullable menuItems) NS_REFINED_FOR_SWIFT;

/// Wraps string to allow image support.
PSPDF_EXTERN NSString * PSPDFWrapStringWithInvisibleIdentifier(NSString *string) NS_REFINED_FOR_SWIFT;

/// Removes the special invisible identifier from the given string.
PSPDF_EXTERN NSString * PSPDFRemoveInvisibleIdentifierFromString(NSString *string) NS_REFINED_FOR_SWIFT;

@interface PSPDFMenuItem ()

/// A convenience initializer that: (1) puts block as the last parameter, (2)
/// falls back to using UUID if given no identifier, and (3) infers whether
/// colors should be allowed in the image based on the image's rendering mode.
+ (instancetype)menuItemWithTitle:(NSString *)title image:(nullable UIImage *)image identifier:(nullable NSString *)identifier block:(void (^)(void))block;

@end

NS_ASSUME_NONNULL_END
