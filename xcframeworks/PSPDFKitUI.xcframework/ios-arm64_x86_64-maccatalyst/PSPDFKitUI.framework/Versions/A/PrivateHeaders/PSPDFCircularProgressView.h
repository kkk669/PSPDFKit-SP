//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//
//  Based on code by  Fabiano Francesconi, MIT licensed.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// Shows a circular progress indicator with optional controls.
/// The content color is based on `tintColor`.
PSPDF_APP_CLASS_SWIFT(CircularProgressView)
@interface PSPDFCircularProgressView : UIView

/// The progress of the view.
@property (nonatomic) CGFloat progress;

// The width of the line used to draw the progress view.
@property (nonatomic) CGFloat lineWidth UI_APPEARANCE_SELECTOR;

/// Indicates if the control symbols (start download, stop, done) should be drawn. Defaults to `true`.
@property (nonatomic) BOOL drawControls;

/// Make the background layer to spin around its center. This should be called in the main thread.
- (void)startSpinProgressBackgroundLayer;

/// Stop the spinning of the background layer. This should be called in the main thread.
- (void)stopSpinProgressBackgroundLayer;

@end

NS_ASSUME_NONNULL_END
