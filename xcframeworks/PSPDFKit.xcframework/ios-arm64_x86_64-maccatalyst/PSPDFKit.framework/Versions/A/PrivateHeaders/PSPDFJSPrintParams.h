//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// Structure that models the print parameters sent via JavaScript.
PSPDF_SUBCLASSING_RESTRICTED
@interface PSPDFJSPrintParams : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

- (PSPDFJSPrintParams *)initWithUi:(nullable NSNumber *)ui
                             start:(nullable NSNumber *)start
                               end:(nullable NSNumber *)end
                            silent:(BOOL)silent
                       shrinkToFit:(BOOL)shrinkToFit
                      printAsImage:(BOOL)printAsImage
                           reverse:(BOOL)reverse
                  printAnnotations:(BOOL)printAnnotations NS_DESIGNATED_INITIALIZER;

/// If true (the default), will cause a UI to be presented to the
/// user to obtain printing information and confirm the action.
@property (nonatomic, readonly, nullable) NSNumber * ui;

/// A 0-based index that defines the start of an inclusive range of
/// pages. If "start" and "end" are not specified, all pages in the
/// document are printed. If only "start" is specified, the range of
/// pages is the single page specified by "start".
@property (nonatomic, readonly, nullable) NSNumber * start;

/// A 0-based index that defines the end of an inclusive page
/// range. If "start" and "end" are not specified, all pages in the
/// document are printed. If only "end" is specified, the range of a
/// pages is 0 to "end".
@property (nonatomic, readonly, nullable) NSNumber * end;

/// If true, suppresses the cancel dialog box while the document is
/// printing.
@property (nonatomic, readonly) BOOL silent;

/// If true, the page is shrunk (if necessary) to fit within the
/// imageable area of the printed page. If false, it is not.
@property (nonatomic, readonly) BOOL shrinkToFit;

/// If true, print pages as an image.
@property (nonatomic, readonly) BOOL printAsImage;

/// If true, print from "end" to "start".
@property (nonatomic, readonly) BOOL reverse;

/// If true (the default), annotations are printed.
@property (nonatomic, readonly) BOOL printAnnotations;

@end

NS_ASSUME_NONNULL_END
