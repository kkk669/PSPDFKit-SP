//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

/// Views that show annotations can implement this protocol to show a cached image instead
/// of rendering the annotation. This results in a smooth transition when an annotation
/// is selected and moves from being rendered in the page view to the resizable view.
@protocol PSPDFAnnotationViewRendering <NSObject>

/// Attach an internally cached image to the image view.
- (void)attachImage;

/// Shows the view/layer that renders the annotation.
- (void)enableAnnotationRendering;

/// Hides the view/layer that renders the annotation.
- (void)disableAnnotationRendering;

@end
