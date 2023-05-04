//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFBaseViewController.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument;

/// A view controller that shows Reader View, which reformats document text into
/// an easy-to-read, single-column view that’s optimized for mobile devices.
///
/// Reader View is typically shown using the `readerViewButtonItem` of a `PDFViewController`,
/// but it may also be created and presented programatically.
///
/// This class does not support being created from a Storyboard or Interface Builder archive.
///
/// This requires the Reader View component to be enabled for your license.
///
/// See https://pspdfkit.com/guides/ios/features/reader-view/ for further documentation.
PSPDF_CLASS_SWIFT(ReaderViewController)
@interface PSPDFReaderViewController : PSPDFBaseViewController

PSPDF_DEFAULT_VIEWCONTROLLER_INIT_UNAVAILABLE

/// Initializes a new view controller for Reader View with a given document.
///
/// This is the designated initializer and the only supported initializer.
- (instancetype)initWithDocument:(PSPDFDocument *)document NS_DESIGNATED_INITIALIZER;

/// The document the view controller was initialized with.
@property (nonatomic, readonly) PSPDFDocument *document;

@end

NS_ASSUME_NONNULL_END
