//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

#import <PSPDFKitUI/PSPDFResizableView+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// View for displaying a crop rect and a dark border around it. Used in `PSPDFImageEditViewController`.
@interface PSPDFImageCropView : UIView

/// Updates the border for the current view frame and crop rect.
- (void)updateBorder;

/// The currently displayed crop rect.
@property (nonatomic) CGRect cropRect;

/// The resizable view used to resize the crop rect.
@property (nonatomic) PSPDFResizableView *resizableView;

/// Used to track the frame of the resizable view.
@property (nonatomic) UIView *trackingView;
@end

NS_ASSUME_NONNULL_END
