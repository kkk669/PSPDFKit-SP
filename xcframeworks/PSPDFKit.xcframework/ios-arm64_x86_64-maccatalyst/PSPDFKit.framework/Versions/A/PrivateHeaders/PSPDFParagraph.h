//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// A section of text on a page. May span multiple lines. Inferred from information such as the locations of glyphs.
PSPDF_SDK_CLASS_SWIFT(Paragraph)
@interface PSPDFParagraph : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// The bounding rectangle of the glyphs in the paragraph in the PDF page coordinate space.
@property (nonatomic, readonly) CGRect frame;

/// The text in the paragraph.
@property (nonatomic, readonly) NSString *text;

/// This is for the UI to attach a UIAccessibilityElement to the paragraph.
/// The UI could also use associated objects or some other approach, but having a property here seemed neater.
@property (nonatomic) id accessibilityElementStorage;

@end

NS_ASSUME_NONNULL_END
