//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFBaseViewController.h>
#import <PSPDFKitUI/PSPDFStyleable.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAnnotationGridViewController, PSPDFAnnotationSetCell, PSPDFAnnotationSet;

/// Delegate to be notified on signature actions.
PSPDF_PROTOCOL_SWIFT(AnnotationGridViewControllerDelegate)
@protocol PSPDFAnnotationGridViewControllerDelegate<NSObject>

@optional

/// Cancel button has been pressed.
///
/// @warning The popover can also disappear without any button pressed, in that case the delegate is not called.
- (void)annotationGridViewControllerDidCancel:(PSPDFAnnotationGridViewController *)annotationGridController;

/// Save/Done button has been pressed.
- (void)annotationGridViewController:(PSPDFAnnotationGridViewController *)annotationGridController didSelectAnnotationSet:(PSPDFAnnotationSet *)annotationSet;

@end

PSPDF_PROTOCOL_SWIFT(AnnotationGridViewControllerDataSource)
@protocol PSPDFAnnotationGridViewControllerDataSource<NSObject>

/// Returns number of sections.
- (NSInteger)numberOfSectionsInAnnotationGridViewController:(PSPDFAnnotationGridViewController *)annotationGridController;

/// Returns number of annotation sets per `section`.
- (NSInteger)annotationGridViewController:(PSPDFAnnotationGridViewController *)annotationGridController numberOfAnnotationsInSection:(NSInteger)section;

/// Returns the annotation set for `indexPath`.
- (PSPDFAnnotationSet *)annotationGridViewController:(PSPDFAnnotationGridViewController *)annotationGridController annotationSetForIndexPath:(NSIndexPath *)indexPath;

@end

/// Shows a grid of annotations.
///
/// This is the superclass of `PSPDFStampViewController` and `PSPDFSavedAnnotationsViewController`
/// and is not intended to be used directly.
PSPDF_CLASS_SWIFT(AnnotationGridViewController)
@interface PSPDFAnnotationGridViewController : PSPDFBaseViewController<PSPDFStyleable>

/// Internally used collection view.
@property (nonatomic, readonly, nullable) UICollectionView *collectionView;

/// Delegate.
@property (nonatomic, weak) IBOutlet id<PSPDFAnnotationGridViewControllerDelegate> delegate;

/// Data Source.
@property (nonatomic, weak) IBOutlet id<PSPDFAnnotationGridViewControllerDataSource> dataSource;

/// Reloads from the dataSource.
- (void)reloadData;

@end

@interface PSPDFAnnotationGridViewController (SubclassingHooks) <UICollectionViewDelegate, UICollectionViewDataSource>

/// To make custom buttons.
- (void)close:(nullable id)sender;

/// Customize cell configuration.
- (void)configureCell:(PSPDFAnnotationSetCell *)annotationSetCell forIndexPath:(NSIndexPath *)indexPath;

/// Trigger popover size recalculation.
- (void)updatePopoverSize;

@end

NS_ASSUME_NONNULL_END
