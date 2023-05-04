//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFTableViewCell.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAnnotation;

/// Displays information about an annotation.
PSPDF_CLASS_SWIFT(AnnotationCell)
@interface PSPDFAnnotationCell : PSPDFNonAnimatingTableViewCell<PSPDFOverridable>

/// Calculates the size.
+ (CGFloat)heightForAnnotation:(PSPDFAnnotation *)annotation inTableView:(UITableView *)tableView;

/// :nodoc:
- (UILabel *)textLabel NS_UNAVAILABLE;

/// :nodoc:
- (UILabel *)detailTextLabel NS_UNAVAILABLE;

@property (nonatomic, readonly) UILabel *nameLabel;
@property (nonatomic, readonly) UILabel *dateAndUserLabel;
/// Style cell for disabled state
@property (nonatomic, getter=isDisabledStyle) BOOL disabledStyle;

/// The annotation that will be displayed. The setter may be overridden, but setting this property is not supported.
@property (nonatomic, nullable) PSPDFAnnotation *annotation;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFAnnotationCell (SubclassingHooks)

/// Builds the string for the `detailTextLabel`.
+ (NSString *)dateAndUserStringForAnnotation:(PSPDFAnnotation *)annotation;

@end

NS_ASSUME_NONNULL_END
