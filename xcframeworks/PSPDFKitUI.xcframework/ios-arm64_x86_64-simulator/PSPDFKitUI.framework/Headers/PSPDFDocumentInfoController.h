//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFDocument, PSPDFContainerViewController;

NS_ASSUME_NONNULL_BEGIN

/// Conforming to this protocol indicated, that the view controller can be used in the document info coordinator.
PSPDF_PROTOCOL_SWIFT(DocumentInfoController)
@protocol PSPDFDocumentInfoController

/// Initialize the controller with an optional document.
- (instancetype)initWithDocument:(nullable PSPDFDocument *)document;

/// Reference to the attached document. Should be set in the initializer. May reload the controller when changed.
@property (nonatomic, weak) PSPDFDocument *document;

@optional

/// Reference to the containing view controller.
@property (nonatomic, weak) PSPDFContainerViewController *container;

@end

NS_ASSUME_NONNULL_END
