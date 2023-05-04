//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFStatefulViewState) {
    /// Controller is querying data.
    PSPDFStatefulViewStateLoading,
    /// Controller finished loading, has no data.
    PSPDFStatefulViewStateEmpty,
    /// Controller has data.
    PSPDFStatefulViewStateFinished
} PSPDF_ENUM_SWIFT(StatefulViewState);

/// Shows a message when the controller is empty.
PSPDF_PROTOCOL_SWIFT(StatefulViewControlling)
@protocol PSPDFStatefulViewControlling<UIContentContainer>

/// Empty view.
@property (nonatomic, nullable) UIView *emptyView;

/// Loading view.
@property (nonatomic, nullable) UIView *loadingView;

/// Receives the current controller state.
///
/// @note This is KVO observable.
@property (nonatomic) PSPDFStatefulViewState controllerState;

@optional

/// Sets the controller state and shows/hides the `emptyView`/`loadingView` depending on the state.
- (void)setControllerState:(PSPDFStatefulViewState)controllerState animated:(BOOL)animated;

@end

NS_ASSUME_NONNULL_END
