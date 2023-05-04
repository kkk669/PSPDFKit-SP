//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKitUI/PSPDFAnnotationView.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFNoteAnnotation;

/// Renders a note annotation’s icon on its page.
/// Note annotations are handled as subviews to be draggable.
PSPDF_CLASS_SWIFT(NoteAnnotationView)
@interface PSPDFNoteAnnotationView : PSPDFAnnotationView<PSPDFOverridable>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Designated initializer.
- (instancetype)initWithAnnotation:(PSPDFAnnotation *)noteAnnotation;

/// Image of the rendered annotation.
@property (nonatomic, nullable) UIImageView *annotationImageView;

@end

/// The methods in this category provide entry points so that you can override or supplement this class' behavior.
///
/// @warning These methods are not meant to be called directly from your code. Subclassing hooks can change without prior deprecation. If you're using them, please double check that they are still available after a PSPDFKit update.
@interface PSPDFNoteAnnotationView (SubclassingHooks)

/// Override to customize the image tinting.
@property (nonatomic, readonly, nullable) UIImage *renderNoteImage;

/// Force image re-render.
- (void)updateImageAnimated:(BOOL)animated;

@end

NS_ASSUME_NONNULL_END
