//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

// MARK: Associated Types/Forward Declarations

@class PSPDFDocument;
@protocol PSPDFScrubberBarAdornmentSource;

NS_ASSUME_NONNULL_BEGIN

/// Metadata group for an adornment.
NS_SWIFT_NAME(ScrubberBarAdornment)
@protocol PSPDFScrubberBarAdornment<NSObject, NSCopying>

/// Must not change once the adornment has been associated with a scrubber bar!
@property (nonatomic, readonly) NSString *adornmentKind;

/// The pages that this adornment refers to.
@property (nonatomic, readonly, assign) NSRange adornmentPageRange;

/// Must not change once the adornment has been associated with a scrubber bar, must not depend on pageRange!
@property (atomic, readonly) NSUInteger hash;

/// Must not depend on pageRange!
- (BOOL)isEqual:(id)object;

@optional

/// By default, the adornments are positioned “above” the centroid of their corresponding page/spread.
/// In certain configurations, this can look off.
/// Implement this property if you need to tweak the positioning.
@property (nonatomic, readonly) CGPoint centerOffset;

@end

// MARK: - Actual Class

/// View that manages adornments for the scrubber bar.
NS_SWIFT_NAME(AdornmentContainerView)
@interface PSPDFAdornmentContainerView : UIView

/// All adornments known to the receiver.
@property (nonatomic, readonly) NSArray<id<PSPDFScrubberBarAdornment>> *currentAdornments;

/// Your chance of supplying adornments.
@property (nonatomic, weak) id<PSPDFScrubberBarAdornmentSource> adornmentSource;

/// Informs the receiver of a new adornment.
/// Will cause a call to `scrubberBar:viewForAdornment:` at an appropriate time.
///
/// @throw Raises an `NSInvalidArgumentException` if any of the adornments have already been added to the receiver.
- (void)addAdornments:(NSArray<id<PSPDFScrubberBarAdornment>> *)adornments;

/// Informs the receiver that the adornment has become invalid and will remove the corresponding view at an appropriate time.
///
/// @throw Raises an `NSInvalidArgumentException` if any of the adornments is unknown to the receiver.
- (void)removeAdornments:(NSArray<id<PSPDFScrubberBarAdornment>> *)adornments;

/// (Batch-)Update block for adornment views.
///
/// @param adornment    The adornment that defines what should be displayed in the view.
/// @param view         The view that needs to be updated.
/// @note If you update the view’s frame, be aware that _only changes in size_ will be preserved.
typedef void (^PSPDFScrubberBarAdornmentUpdater)(id<PSPDFScrubberBarAdornment> adornment, __kindof UIView *view);

/// Causes the receiver to update the views for the specified adornments by calling the block (once for each element).
- (void)updateAdornments:(NSArray<id<PSPDFScrubberBarAdornment>> *)adornments usingBlock:(PSPDFScrubberBarAdornmentUpdater)updateBlock;

/// Removes all adornments for the receiver and will remove the corresponding views at an appropriate time.
///
/// @param adornmentKind    The kind of the adornments to remove. If nil, all adornments are removed.
- (void)removeAllAdornmentsOfKind:(nullable NSString *)adornmentKind;

@end

// MARK: - Data Source API

/// The datasource that supplies an adornment container view with the adornments, and views to represent them.
NS_SWIFT_NAME(ScrubberBarAdornmentSource)
@protocol PSPDFScrubberBarAdornmentSource<NSObject>

/// Returns adornments that the scrubber bar should display for the given document.
/// The scrubber bar will call this method whenever the document changes or similar things happen.
///
/// @note You might find it useful to keep the array you return here around for bookkeeping.
/// E.g. the scrubber bar won’t like it if you try to add an adornment that is already displayed within it.
- (NSArray<id<PSPDFScrubberBarAdornment>> *)adornmentContainerView:(PSPDFAdornmentContainerView *)container adornmentsForDocument:(PSPDFDocument *)document;

/// The view returned from this method should have a well–defined size, which will be respected by the scrubber bar.
///
/// @note Important: Avoid making assumtions about how this view will be placed by the scrubber bar.
/// Especially, **do not form** autolayout constraints that escape this view!
- (UIView *)adornmentContainerView:(PSPDFAdornmentContainerView *)container viewForAdornment:(id<PSPDFScrubberBarAdornment>)adornment;

@optional
/// Informs the receiver that the specified view has been removed.
/// If you plan on implementing a reuse scheme for your views, this is when you safely can do so.
- (void)adornmentContainerView:(PSPDFAdornmentContainerView *)container didRemoveView:(__kindof UIView *)view forAdornment:(id<PSPDFScrubberBarAdornment>)adornment;

@end

NS_ASSUME_NONNULL_END
