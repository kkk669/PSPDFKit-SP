//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

/// The spread mode determines the conversion between spreads and pages.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFDocumentViewLayoutSpreadMode) {
    /// Each spread corresponds to one page.
    PSPDFDocumentViewLayoutSpreadModeSingle,
    /// Each spread corresponds to two pages.
    PSPDFDocumentViewLayoutSpreadModeDouble,
    /// The first spread has a single page, similar a book cover, all other spreads
    /// have two pages.
    PSPDFDocumentViewLayoutSpreadModeBook,
} PSPDF_ENUM_SWIFT(PDFDocumentViewLayout.SpreadMode);

/// The page mode determines how a page is displayed relative to its neighboring pages.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFDocumentViewLayoutPageMode) {
    /// The corresponding page is a single page.
    PSPDFDocumentViewLayoutPageModeSingle,
    /// The corresponding page is the leading page of a double page.
    PSPDFDocumentViewLayoutPageModeLeading,
    /// The corresponding page is the trailing page of a double page.
    PSPDFDocumentViewLayoutPageModeTrailing,
    /// The corresponding page is placed in the center, between leading and trailing pages.
    PSPDFDocumentViewLayoutPageModeCenter,
} PSPDF_ENUM_SWIFT(PDFDocumentViewLayout.PageMode);
