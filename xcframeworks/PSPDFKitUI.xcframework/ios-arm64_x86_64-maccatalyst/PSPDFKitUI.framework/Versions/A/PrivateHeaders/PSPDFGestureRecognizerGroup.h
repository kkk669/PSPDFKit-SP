//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// Signature of a dynamic gesture recognizer failure requirement block.
typedef BOOL (^PSPDFGestureRecognizerGroupFailureRequirementBlock)(UIGestureRecognizer *otherGestureRecognizer);

/// An object that wraps several gesture recognizers in a group allowing you to set
/// up failure requirements and simultaneous recognition requirements will all of
/// them at once.
PSPDF_SUBCLASSING_RESTRICTED
@interface PSPDFGestureRecognizerGroup : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes an instance with the given array of gesture recognizers.
- (instancetype)initWithGestureRecognizers:(NSArray<UIGestureRecognizer *> *)gestureRecognizers;

/// Initializes an instance with all gesture recognizers in the given array of
/// gesture recognizer groups.
- (instancetype)initWithGestureRecognizerGroups:(NSArray<PSPDFGestureRecognizerGroup *> *)gestureRecognizerGroups;

// MARK: Accessing the Underlying Gesture Recognizers

/// Checks if this group contains any gesture recognizer at all.
@property (nonatomic, readonly, getter = isEmpty) BOOL empty;

/// Checks if this group contains the given gesture recognizer.
- (BOOL)containsGestureRecognizer:(UIGestureRecognizer *)gestureRecognizer;

// MARK: Configuring the Failure Requirements

/// Creates a relationship with another gesture recognizer that will prevent the
/// gesture recognizers in this group from transitioning from `Possible` state
/// until `otherGestureRecognizer` transitions to `Failed` state.
///
/// If `otherGestureRecognizer` transitions to `Began` or `Ended` state then the
/// gesture recognizers in this group will instead transition to `Failed` state.
///
/// @param otherGestureRecognizer Another gesture recognizer.
- (void)requireGestureRecognizerToFail:(UIGestureRecognizer *)otherGestureRecognizer;

/// Creates a relationship with a group of other gesture recognizers that will
/// prevent the gesture recognizers in this group from transitioning from
/// `Possible` state until all gesture recognizers in `otherGestureRecognizers`
/// transition to `Failed` state.
///
/// If any gesture recognizer in `otherGestureRecognizers` transitions to `Began`
/// or `Ended` state then the gesture recognizers in this group will instead
/// transition to `Failed` state.
///
/// @param otherGestureRecognizerGroup A group of other gesture recognizers.
- (void)requireGestureRecognizerGroupToFail:(PSPDFGestureRecognizerGroup *)otherGestureRecognizerGroup;

/// Adds a block that will be used to set up failure requirements with other gesture
/// recognizers dynamically at runtime.
///
/// If the block returns `true` for the given `otherGestureRecognizer`, the gesture
/// recognizers in this group will be prevented from transitioning from `Possible`
/// state until `otherGestureRecognizer` transitions to `Failed` state. If
/// `otherGestureRecognizer` transitions to `Began` or `Ended` state then the
/// gesture recognizers in this group will instead transition to `Failed` state.
///
/// @param failureRequirementBlock A failure requirement block to add.
- (void)requireGestureRecognizerToFailDynamically:(PSPDFGestureRecognizerGroupFailureRequirementBlock)failureRequirementBlock;

// MARK: Configuring the Simultaneous Recognition Requirements

/// Creates a relationship with another gesture recognizer that will allow the
/// gesture recognizers in this group to transition out of `Possible` state at the
/// same time as `otherGestureRecognizer`.
///
/// @param otherGestureRecognizer Another gesture recognizer.
- (void)allowSimultaneousRecognitionWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer;

/// Creates a relationship with a group of other gesture recognizers that will allow
/// the gesture recognizers in this group to transition out of `Possible` state at
/// the same time as any gesture recognizer in `otherGestureRecognizers`.
///
/// @param otherGestureRecognizerGroup A group of other gesture recognizers.
- (void)allowSimultaneousRecognitionWithGestureRecognizerGroup:(PSPDFGestureRecognizerGroup *)otherGestureRecognizerGroup;

// MARK: Evaluating Gesture Recognizer Requirements

/// Evaluates failure requirements between two gesture recognizers. Must be called
/// from the `UIGestureRecognizerDelegate` method of the same name.
- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRequireFailureOfGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer;

/// Evaluate simultaneous recognition requirements between two gesture recognizers.
/// Must be called from the `UIGestureRecognizerDelegate` method of the same name.
- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer;

@end

// MARK: -

@interface UIGestureRecognizer (PSPDFGestureRecognizerGroupSupport)

// MARK: Configuring the Failure Requirements

/// Creates a relationship with a group of other gesture recognizers that will
/// prevent this gesture recognizer from transitioning from `Possible` state until
/// all gesture recognizers in `otherGestureRecognizers` transition to `Failed`
/// state.
///
/// If any gesture recognizer in `otherGestureRecognizers` transitions to `Began`
/// or `Ended` state then this gesture recognizer will instead transition to
/// `Failed` state.
///
/// @param otherGestureRecognizerGroup A group of other gesture recognizers.
- (void)pspdf_requireGestureRecognizerGroupToFail:(PSPDFGestureRecognizerGroup *)otherGestureRecognizerGroup;

@end

NS_ASSUME_NONNULL_END
