//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFAnnotationToolbar.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFAnnotationToolbar ()

/// Method called when tapping a tool button.
/// Exposed for PDF Viewer to lock some tools as Pro features.
- (void)buttonPressedToEnterState:(PSPDFAnnotationString)state variant:(nullable PSPDFAnnotationVariantString)variant;

/// Used only for UI tests to always show undo redo button.
- (BOOL)shouldAddRedoButtonForToolbarPosition:(PSPDFFlexibleToolbarPosition)position;

@end

NS_ASSUME_NONNULL_END
