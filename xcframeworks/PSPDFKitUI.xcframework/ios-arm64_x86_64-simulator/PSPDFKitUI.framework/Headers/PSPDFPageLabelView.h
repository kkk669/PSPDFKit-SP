//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFLabelView.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument, PSPDFPageLabelView, PSPDFPageLabelFormatter;

/// Handles touches of the thumbnail grid button in the page label view.
PSPDF_PROTOCOL_SWIFT(PageLabelViewDelegate)
@protocol PSPDFPageLabelViewDelegate<NSObject>

/// Callback when the thumbnail grid button in the page label view has been tapped.
- (void)pageLabelView:(PSPDFPageLabelView *)pageLabelView didPressThumbnailGridButton:(UIButton *)sender;

@end

/// Displays the current page position at the bottom of the screen.
///
/// @note This class connects to the pdfController via KVO.
PSPDF_CLASS_SWIFT(PageLabelView)
@interface PSPDFPageLabelView : PSPDFLabelView<PSPDFOverridable>

/// Action delegate.
@property (nonatomic, weak) id<PSPDFPageLabelViewDelegate> delegate;

/// Show button to show the thumbnail grid on the right side of the label. Defaults to NO.
@property (nonatomic) BOOL showThumbnailGridButton;

/// The thumbnail grid button, if `showThumbnailGridButton` is enabled.
/// Manually wire up to a target/selector.
@property (nonatomic) UIButton *thumbnailGridButton;

/// Equal to `thumbnailButton.tintColor`, but can also be used with `UIAppearance`.
/// Defaults to black.
@property (nonatomic) UIColor *thumbnailButtonColor UI_APPEARANCE_SELECTOR;

/// The custom label formatter. If reset to `nil`, the default formatter is used.
@property (nonatomic, copy, null_resettable) PSPDFPageLabelFormatter *labelFormatter;

@end

NS_ASSUME_NONNULL_END
