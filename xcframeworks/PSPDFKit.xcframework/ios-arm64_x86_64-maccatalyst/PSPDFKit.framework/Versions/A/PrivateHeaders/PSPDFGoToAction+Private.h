//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFGoToAction.h>
#import <CoreGraphics/CoreGraphics.h>

@interface PSPDFGoToAction ()

/// Returns the `pageIndex` adjusted for the document provider's location in the `Document`
/// (`pageOffsetForDocument`). If `documentProvider` is nil, returns the same value as `pageIndex`.
/// Prefer this over using `pageIndex` directly in multi document provider documents.
- (PSPDFPageIndex)pageIndexWithDocumentProvider:(nullable PSPDFDocumentProvider *)documentProvider;

@end
