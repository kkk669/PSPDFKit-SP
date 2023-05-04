//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFGoToAction.h>

NS_ASSUME_NONNULL_BEGIN

/// Defines an action to go to a specific page index in another PDF document.
/// Can be either used directly via a page index, or via a named destination, which will be resolved before executing the action.
/// This covers both RemoteGoTo and Launch actions.
PSPDF_CLASS_SWIFT(RemoteGoToAction)
@interface PSPDFRemoteGoToAction : PSPDFGoToAction

/// Will create a `PSPDFActionTypeRemoteGoTo` linking to another document with a page index.
- (instancetype)initWithRelativePath:(nullable NSString *)remotePath pageIndex:(PSPDFPageIndex)pageIndex;

/// Will create a `PSPDFActionTypeRemoteGoTo` linking to another document with a named destination.
- (instancetype)initWithRelativePath:(nullable NSString *)remotePath namedDestination:(NSString *)namedDestination;

/// Path to the remote PDF, if any.
@property (nonatomic, copy, readonly, nullable) NSString *relativePath;

/// A named destination.
/// Use `-[PSPDFDocumentProvider resolveNamedDestination:]` to resolve this to a page index.
@property (atomic, copy, readonly, nullable) NSString *namedDestination;

@end

NS_ASSUME_NONNULL_END
