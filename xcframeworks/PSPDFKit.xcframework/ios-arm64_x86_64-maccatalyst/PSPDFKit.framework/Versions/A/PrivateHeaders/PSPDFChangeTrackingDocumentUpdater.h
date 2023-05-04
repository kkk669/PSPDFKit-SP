//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDocumentProvider.h>

NS_ASSUME_NONNULL_BEGIN

/// Updates the structures that may have changed after an action is executed by Core.
///
/// If an action, like a JavaScript action, is executed by Core, the framework does not have any
/// clear idea of what's changed, and the structures won't be up to date. This class observes PDF action events and
/// makes use of the annotation/form field tracking structures we generate from the Core document provider to update the
/// corresponding framework data structures.
NS_SWIFT_NAME(ChangeTrackingDocumentUpdater)
@interface PSPDFChangeTrackingDocumentUpdater : NSObject

- (instancetype)initWithDocumentProvider:(PSPDFDocumentProvider *)documentProvider;

PSPDF_EMPTY_INIT_UNAVAILABLE

// The document provider where the changes will be applied, weakly held.
@property (nonatomic, weak) PSPDFDocumentProvider *documentProvider;

@end

NS_ASSUME_NONNULL_END
