//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFAnnotationGridViewController.h>
#import <PSPDFKitUI/PSPDFStyleable.h>

@protocol PSPDFAnnotationSetStore;

NS_ASSUME_NONNULL_BEGIN

/// A view controller that shows a grid of saved annotation sets. It allows
/// to save and load saved annotations.
PSPDF_CLASS_SWIFT(SavedAnnotationsViewController)
@interface PSPDFSavedAnnotationsViewController : PSPDFAnnotationGridViewController<PSPDFAnnotationGridViewControllerDataSource, PSPDFStyleable, PSPDFOverridable>

/// The default annotation store to use, if no custom `annotationStore` is set.
/// Default: `PersistentAnnotationSetStore`.
@property(class, atomic, readonly) id<PSPDFAnnotationSetStore> sharedAnnotationStore;

/// The annotation store to use to read and write the saved annotations. If not
/// set, `sharedAnnotationStore` is used.
@property (nonatomic) id<PSPDFAnnotationSetStore> annotationStore;

@end

NS_ASSUME_NONNULL_END
