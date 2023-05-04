//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <UIKit/UIKit.h>
#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKitUI/PSPDFAnnotationPlaceholder.h>

NS_ASSUME_NONNULL_BEGIN

/// View that displays a placeholder and updates according to that object’s state.
///
/// Instances of this class act as a surrogate for an annotation’s content while that isn’t available.
PSPDF_SDK_EXPORT @interface PSPDFAnnotationPlaceholderView : UIView

/// Text to display in addition to the placeholder content when deemed appropriate.
@property (nonatomic, nullable, copy) NSString *statusText;

/// Attributed text to display in addition to the placeholder content when deemed appropriate.
@property (nonatomic, nullable, copy) NSAttributedString *attributedStatusText;

/// The placeholder being displayed and observed by this view.
@property (nonatomic, nullable) PSPDFAnnotationPlaceholder *placeholder;

/// Whether or not the `statusText` should be displayed.
@property (nonatomic) BOOL showsStatus;

/// Whether or not a progress bar should be displayed.
@property (nonatomic) BOOL showsProgress;

@end

NS_ASSUME_NONNULL_END
