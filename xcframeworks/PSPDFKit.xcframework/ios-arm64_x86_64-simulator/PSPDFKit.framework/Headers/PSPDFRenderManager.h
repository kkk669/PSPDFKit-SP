//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// This notification is triggered if something happens that changes the way a page looks.
///
/// The user info dictionary of this notification always contains the key `PSPDFRenderManagerRenderResultChangedDocumentKey`
/// which contains the document that changed and optionally `PSPDFRenderManagerRenderResultChangedPagesKey`
/// which contains an index set of the pages that changed within this document.
///
/// If a document was changed e.g. by adding or removing an annotation, this notification
/// tells you that the render engine and the cache have been updated and scheduling
/// a new render task is guaranteed to return the new state of the document.
///
/// In other words: If you constantly want to show up to date data, observe this notification
/// and request a new image when this notification is posted.
///
/// @note This notification is posted on an arbitrary queue. If you need to react on
/// this on the main queue, you need to switch to the main queue yourself.
PSPDF_EXPORT NSNotificationName const PSPDFRenderManagerRenderResultDidChangeNotification;

/// The key of a `PSPDFRenderManagerRenderResultDidChangeNotification` userInfo's dictionary,
/// containing the `Document` that was changed.
PSPDF_EXPORT NSString *const PSPDFRenderManagerRenderResultChangedDocumentKey;

/// The key of a `PSPDFRenderManagerRenderResultDidChangeNotification` userInfo's dictionary,
/// containing an `NSIndexSet` with all the relevant pages. If the entry for this
/// key in the user info dictionary is `nil`, the whole document should be treated as
/// changed.
PSPDF_EXPORT NSString *const PSPDFRenderManagerRenderResultChangedPagesKey;

/// The `PSPDFPageInfo` object containing page info.
PSPDF_EXPORT NSString *const PSPDFPageRendererPageInfoKey;

@class PSPDFAnnotation, PSPDFRenderQueue, PSPDFDocumentProvider, PSPDFPageInfo;

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFRenderType) {
    /// Renders a single page.
    PSPDFRenderTypePage,

    /// Exports or transforms a document
    PSPDFRenderTypeProcessor,

    /// Useful to apply settings to all render types.
    PSPDFRenderTypeAll = NSUIntegerMax
} PSPDF_ENUM_SWIFT(RenderType);

/// The PDF render manager coordinates the PDF renderer used.
PSPDF_PROTOCOL_SWIFT(RenderManager)
@protocol PSPDFRenderManager<NSObject>

/// Setup the graphics context to the current PDF.
- (void)setupGraphicsContext:(CGContextRef)context rectangle:(CGRect)displayRectangle pageInfo:(PSPDFPageInfo *)pageInfo;

/// The render queue that manages render jobs.
@property (nonatomic, readonly) PSPDFRenderQueue *renderQueue;

@end

NS_ASSUME_NONNULL_END
