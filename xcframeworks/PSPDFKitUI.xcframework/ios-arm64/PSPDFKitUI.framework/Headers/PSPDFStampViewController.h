//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFAnnotationGridViewController.h>
#import <PSPDFKitUI/PSPDFTextStampViewController.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFStampAnnotation;

/// Allows adding signatures or drawings as ink annotations.
PSPDF_CLASS_SWIFT(StampViewController)
@interface PSPDFStampViewController : PSPDFAnnotationGridViewController<PSPDFAnnotationGridViewControllerDataSource, PSPDFTextStampViewControllerDelegate, PSPDFOverridable>

/// The default available set of stamp annotations. Thread safe.
/// Setting `nil` will restore the default set of stamp annotations.
@property (class, atomic, null_resettable) NSArray<PSPDFStampAnnotation *> *defaultStampAnnotations;

/// Available stamp types. Set before showing controller.
@property (nonatomic, copy) NSArray<PSPDFStampAnnotation *> *stamps;

/// Adds a button that forwards to an interface (`PSPDFTextStampViewController`) where custom stamps can be created.
/// Defaults to YES.
///
/// @warning Changing this will reset the `stamps` array.
@property (nonatomic) BOOL customStampEnabled;

/// Adds date stamps. They are recreated every time the `PSPDFStampViewController` is created
/// to present the current date and thus not a part of the `defaultStampAnnotations` array.
/// Defaults to YES.
///
/// @warning Changing this will reset the `stamps` array.
@property (nonatomic) BOOL dateStampsEnabled;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFStampViewController (SubclassingHooks)

/// Creates the default date fonts - Revised and Rejected.
- (NSArray<PSPDFStampAnnotation *> *)defaultDateStamps;

@end

NS_ASSUME_NONNULL_END
