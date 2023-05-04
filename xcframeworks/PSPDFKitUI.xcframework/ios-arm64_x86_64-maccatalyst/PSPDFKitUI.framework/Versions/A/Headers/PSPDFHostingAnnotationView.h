//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOverridable.h>
#import <PSPDFKit/PSPDFRenderTask.h>
#import <PSPDFKitUI/PSPDFAnnotationView.h>

NS_ASSUME_NONNULL_BEGIN

/// View that will render an annotation.
PSPDF_CLASS_SWIFT(HostingAnnotationView)
@interface PSPDFHostingAnnotationView : PSPDFAnnotationView<PSPDFRenderTaskDelegate, PSPDFOverridable>

/// Image View that shows the rendered annotation.
/// Added lazily when the view is added to the window.
@property (nonatomic, readonly, nullable) UIImageView *annotationImageView;

@end

NS_ASSUME_NONNULL_END
