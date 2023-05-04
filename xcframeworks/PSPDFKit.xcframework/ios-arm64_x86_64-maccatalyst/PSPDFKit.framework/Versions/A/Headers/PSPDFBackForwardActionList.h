//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>

@class PSPDFAction, PSPDFBackForwardActionList;

NS_ASSUME_NONNULL_BEGIN

/// An object to handle events from a `BackForwardActionList`.
PSPDF_PROTOCOL_SWIFT(BackForwardActionListDelegate)
@protocol PSPDFBackForwardActionListDelegate<NSObject>

/// Should execute the provided back actions in reverse order and also call `registerAction:`
/// to register the inverse actions.
///
/// This method will become required when the deprecated variant without the `animated` parameter is removed.
- (void)backForwardList:(PSPDFBackForwardActionList *)list requestedBackActionExecution:(NSArray<PSPDFAction *> *)actions animated:(BOOL)animated;

/// Should execute the provided forward actions in reverse order and also call `registerAction:`
/// to register the inverse actions.
///
/// This method will become required when the deprecated variant without the `animated` parameter is removed.
- (void)backForwardList:(PSPDFBackForwardActionList *)list requestedForwardActionExecution:(NSArray<PSPDFAction *> *)actions animated:(BOOL)animated;

@optional

/// Called whenever `backList` or `forwardList` get updated.
- (void)backForwardListDidUpdate:(PSPDFBackForwardActionList *)list;

@end

/// Keeps track of executed `Action` instances, allowing us to navigate through the action history.
///
/// @note This class is conceptually similar to `WKBackForwardList`.
PSPDF_CLASS_SWIFT(BackForwardActionList)
@interface PSPDFBackForwardActionList : NSObject<PSPDFOverridable>

/// The delegate is recommended. @see delegate
- (instancetype)initWithDelegate:(nullable id<PSPDFBackForwardActionListDelegate>)delegate NS_DESIGNATED_INITIALIZER;

/// Required for normal operation of `requestBack(animated:)` and `requestForward(animated:)`.
@property (nonatomic, weak) id<PSPDFBackForwardActionListDelegate> delegate;

/// Registers a new back or forward action, depending on the context (actions added from inside of
/// `backForwardList(_:requestedBackActionExecution:animated:)` will be added to the forward list).
- (void)registerAction:(PSPDFAction *)action;

/// Requests execution of the top back action.
/// Doesn't do anything if `backAction` is `nil`.
///
/// @see requestBackToAction:animated:
- (void)requestBackAnimated:(BOOL)animated;

/// Updates internal state and calls the `backForwardList(_:requestedBackActionExecution:animated:)` delegate message.
- (void)requestBackToAction:(PSPDFAction *)action animated:(BOOL)animated;

/// Requests execution of the top forward action.
/// Doesn't do anything if `forwardAction` is `nil`.
///
/// @see requestForwardToAction:animated:
- (void)requestForwardAnimated:(BOOL)animated;

/// Updates internal state and calls the `backForwardList:requestedForwardActionExecution:` delegate message.
- (void)requestForwardToAction:(PSPDFAction *)action animated:(BOOL)animated;

/// Removes all back actions.
- (void)resetBackList;

/// Removes all forward actions.
- (void)resetForwardList;

/// Removes all back and forward actions.
- (void)reset;

/// The maximum number of actions allowed in `backList`.
/// No cap will be enforced if set to 0 (the default).
@property (nonatomic) NSUInteger backListCap;

/// The current top back action, if any.
@property (nonatomic, readonly, nullable) PSPDFAction *backAction;

/// The current top forward action, if any.
@property (nonatomic, readonly, nullable) PSPDFAction *forwardAction;

/// A list of all tracked back actions.
@property (nonatomic, copy, readonly) NSArray<__kindof PSPDFAction *> *backList;

/// A list of all tracked forward actions.
@property (nonatomic, copy, readonly) NSArray<__kindof PSPDFAction *> *forwardList;

@end

NS_ASSUME_NONNULL_END
