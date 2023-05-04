//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//  Based on work of Ryan Sullivan. BSD licensed.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <QuartzCore/QuartzCore.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFColorPickerView, PSPDFLoupeLayer, PSPDFBrightnessSlider;

/// Color Picker delegate.
@protocol PSPDFColorPickerViewDelegate <NSObject>

@optional

/// Color selection has been changed.
- (void)colorPickerViewDidChangeSelection:(PSPDFColorPickerView *)colorPicker finishedSelection:(BOOL)finished;

/// Called when hue selection begins (touches began).
- (void)colorPickerViewWillBeginSelection:(PSPDFColorPickerView *)colorPicker;

/// Called when hue selection ends (touches ended).
- (void)colorPickerViewDidEndSelection:(PSPDFColorPickerView *)colorPicker;

@end

/// Color Picker view control. (circle)
PSPDF_TEST_CLASS_SWIFT(ColorPickerView)
@interface PSPDFColorPickerView : UIControl

/// The gesture recognizer used to detect swipes on the color wheel.
///
/// @note You should not modify the gesture recognizer. You should only use it
/// to pass it into other recognizer's `requiresGestureRecognizerToFail:` method.
@property (nonatomic, readonly) UIGestureRecognizer *panGestureRecognizer;

/// The gesture recognizer used to detect taps on the color wheel.
///
/// @note You should not modify the gesture recognizer. You should only use it
/// to pass it into other recognizer's `requiresGestureRecognizerToFail:` method.
@property (nonatomic, readonly) UIGestureRecognizer *tapGestureRecognizer;

/// Current selection point.
@property (nonatomic, readonly) CGPoint selection;

/// Set to YES to show a square with saturation on Y axis, No for saturation on radial axis.
@property (nonatomic) BOOL cropToCircle;

/// Changes color distribution mode to orthogonal. Defaults to NO.
@property (nonatomic) BOOL isOrthogonal;

/// Set to YES to show a loupe. Defaults to YES, unless old device.
@property (nonatomic, getter=isLoupeEnabled) BOOL loupeEnabled;

@property (nonatomic, nullable) UIColor *selectionColor;

@property (nonatomic) CGFloat brightness;

/// Picker delegate
@property (nonatomic, weak) IBOutlet id<PSPDFColorPickerViewDelegate> delegate;

/// The internally used brightness slider.
@property (nonatomic, weak) IBOutlet PSPDFBrightnessSlider *brightnessSlider;

/// Conversion helper.
- (void)selectionToHue:(nullable CGFloat *)pH saturation:(nullable CGFloat *)pS brightness:(nullable CGFloat *)pV;

/// Returns `UIColor` at a point in the `PSPDFColorPickerView`.
/// Returns the backgroundColor if the point is outside bounds.
- (nullable UIColor *)colorAtPoint:(CGPoint)point;

@end

NS_ASSUME_NONNULL_END
