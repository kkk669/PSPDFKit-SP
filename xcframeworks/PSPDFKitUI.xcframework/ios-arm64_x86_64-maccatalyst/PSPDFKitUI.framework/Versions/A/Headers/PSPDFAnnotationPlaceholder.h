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

/// A fully KVO observable stand in for actual annotation content that is loaded on demand.
///
/// Custom annotation providers may need to resolve certain annotation types using external sources.
/// Instant, for example, only loads image annotations separately from the document and other
/// annotations on demand, thus giving users the quickest possible time to display and sync, without
/// sacrificing high fidelity for high bandwidth media.
///
/// This, however, requires a mechanism to display placeholder content for annotations whose media is
/// not readily available. `PSPDFAnnotationPlaceholder` fulfills that role by offering a state machine
/// that tracks the process towards replacing a suitable placeholder with the actual content.
///
/// ## States and Allowed Transitions
///
/// Each annotation placeholder starts in an idle state. Any `PSPDFAnnotationPresenting` view that
/// implements the `annotationPlaceholder` property can use that object’s `content` to display a
/// suitable placeholder until the actual content has become available.
///
/// In order to provide feedback as to when the actual content will be available, it can observe the
/// placeholder’s `placeholderState`, which will change to “progressing” or “failed” when the process
/// of providing the actual content starts or has failed.
///
/// @note **Important:** In the context of `PSPDFAnnotationPlaceholder`, cancellation is considered an
/// error. It will be signaled by an `NSUserCancelled` error in combination with state “failed”.
///
/// While the actual content for the placeholder instance is loaded, the object remains in state
/// “progressing” until the process completes — which results in a transition to state “completed” — or
/// fails — which results in a transition to state “failed”. Both of these states are final, meaning
/// there will not be any further state transitions.
///
/// Upon transition to state “completed”, any `PSPDFAnnotationPresenting` view tracking a placeholder
/// should dispose of the object, and use its new `content` property instead.
///
/// Upon transition to state “failed”, any such view should update based on the placeholder object’s
/// error, which (in many cases) will provide a `localizedRecoverySuggestion`, alongside a
/// `recoveryAttempter`.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(AnnotationPlaceholder)
@interface PSPDFAnnotationPlaceholder : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

typedef NS_CLOSED_ENUM(NSInteger, PSPDFAnnotationPlaceholderState) {
    /// The placeholder is still dormant.
    ///
    /// Its `progress` and `error` properties are both `nil`.
    PSPDFAnnotationPlaceholderStateIdle,

    /// The placeholder has become active.
    ///
    /// Its `progress` property is populated with an object that can be used to display the progress of
    /// replacing the placeholder with actual content. The placeholder’s `error` property is `nil`.
    PSPDFAnnotationPlaceholderStateProgressing,

    /// The process of replacing the placeholder with actual content has failed.
    ///
    /// The `progress` property is `nil`. The `error` property holds an object detailing why/in which
    /// way replacing the placeholder with actual content failed.
    PSPDFAnnotationPlaceholderStateFailed,

    /// The process of replacing the placeholder with actual content has been cancelled.
    PSPDFAnnotationPlaceholderStateCancelled,

    /// The actual content has become available.
    ///
    /// The placeholder has become obsolete, so neither its `progress`, not its `error` property matter
    /// anymore.
    PSPDFAnnotationPlaceholderStateCompleted,
};

/// The current state of the receiver — KVO observable.
@property (atomic, readonly) PSPDFAnnotationPlaceholderState placeholderState;

/// The current (placeholder) content of the receiver. Can change upon failure.
@property (atomic, readonly) UIImage *contentIcon;

/// The progress towards replacing the receiver with actual content — `nil` unless it is progressing.
///
/// @see placeholderState
@property (atomic, readonly, nullable) NSProgress *progress;

/// The error that caused replacing the receiver with actual content to fail — `nil` unless it failed.
///
/// @see placeholderState
@property (atomic, readonly, nullable) NSError *error;

/// The localized name of the appropriate action to take when interacting with the receiver.
///
/// This KVO observable property is updated whenever the `placeholderState` changes. Will be nil if
/// no action has been configured for the current state.
@property (atomic, readonly, nullable) NSString *localizedAction;

/// Tells an idle placeholder that the actual content should be retrieved.
///
/// This method has no effect if the placeholder is in any other state than
/// `PSPDFAnnotationPlaceholderStateIdle`. If the placeholder is idle, it will transition to state
/// progressing or failed.
///
/// @note The caller should not make any assumption on when the transition away from the idle state is
/// completed!
- (void)resolveActualContent;

/// Asks a progressing placeholder to cancel the ongoing resolution, and provide a suitable replacement
/// for a new resolution attempt at a later time.
///
/// Will return `nil` if the receiver is not in state `PSPDFAnnotationPlaceholderStateProgressing`, or
/// no suitable replacement could be provided. Otherwise, it will return a suitable replacement in
/// `PSPDFAnnotationPlaceholderStateIdle`.
- (nullable PSPDFAnnotationPlaceholder *)cancelResolution:(NSError **)error;

/// Asks a failed placeholder to provide a suitable replacement for a new resolution attempt at a later
/// time.
///
/// Will return `nil` if the receiver is not in state `PSPDFAnnotationPlaceholderStateFailed`, or no
/// suitable replacement could be provided. Otherwise, it will return a suitable replacement object
/// that has already begun to resolve the actual content.
- (nullable PSPDFAnnotationPlaceholder *)replacementForReattemptingResolution:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
