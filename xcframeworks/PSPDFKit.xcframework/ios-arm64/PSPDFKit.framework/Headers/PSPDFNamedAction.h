//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAction.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocument;

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFNamedActionType) {
    /// No named action.
    PSPDFNamedActionTypeNone,
    /// Go to the next page in the document.
    PSPDFNamedActionTypeNextPage,
    /// Go to the previous page in the document
    PSPDFNamedActionTypePreviousPage,
    /// Go to the first page in the document.
    PSPDFNamedActionTypeFirstPage,
    /// Go to the last page in the document.
    PSPDFNamedActionTypeLastPage,
    /// Go back using `BackForwardActionList`. Only possible after executing another navigation action.
    PSPDFNamedActionTypeGoBack,
    /// Go forward using `BackForwardActionList`. Only possible after executing a GoBack action.
    PSPDFNamedActionTypeGoForward,
    PSPDFNamedActionTypeGoToPage,
    PSPDFNamedActionTypeFind,
    /// Shows the UI to configure and start printing the document.
    PSPDFNamedActionTypePrint,
    /// Shows `OutlineViewController` for the document.
    PSPDFNamedActionTypeOutline,
    PSPDFNamedActionTypeSearch,
    PSPDFNamedActionTypeBrightness,
    /// Not implemented.
    PSPDFNamedActionTypeZoomIn,
    /// Not implemented.
    PSPDFNamedActionTypeZoomOut,
    /// Triggers `Document.save()`.
    PSPDFNamedActionTypeSaveAs,
    PSPDFNamedActionTypeInfo,
    PSPDFNamedActionTypeUnknown = NSUIntegerMax,
} PSPDF_ENUM_SWIFT(NamedActionType);

/// Transforms named actions to enum type and back.
///
/// @note The transformer is added in the class initialize phase.
/// Requires `PSPDFNamedAction` to be accessed at least once.
PSPDF_EXPORT NSValueTransformerName const PSPDFNamedActionTypeTransformerName NS_SWIFT_NAME(namedActionType);

/// Defines methods used to work with actions in PDF documents, some of which are named in the Adobe PDF Specification.
PSPDF_CLASS_SWIFT(NamedAction)
@interface PSPDFNamedAction : PSPDFAction

/// Initialize with string.
/// Will parse action, set to `PSPDFNamedActionTypeUnknown` if not recognized or nil.
- (instancetype)initWithActionNamedString:(nullable NSString *)actionNameString;

/// Initialize with a specific named action type.
- (instancetype)initWithNamedActionType:(PSPDFNamedActionType)namedActionType;

/// The type of the named action.
///
/// @note Will update `namedAction` if set.
@property (nonatomic, readonly) PSPDFNamedActionType namedActionType;

/// The string of the named action.
///
/// @note Will update `namedActionType` if set.
@property (nonatomic, copy, readonly, nullable) NSString *namedAction;

/// Returns the target page for certain named actions.
///
/// The named actions supported by this method are `.nextPage`, `.previousPage`, `.firstPage`, and `lastPage`.
/// For other types this will return `NSNotFound`.
/// This also returns `NSNotFound` if the provided current page is out of bounds or if the target page would be out of bounds.
/// This will not resolve the target page index for `goBack` and `goForward` actions because the navigation history
/// is part of the UI rather than part of the model. It will return `NSNotFound` for those.
///
/// @return The target page, or `NSNotFound` if there is no target page.
- (PSPDFPageIndex)pageIndexWithCurrentPage:(PSPDFPageIndex)currentPage fromDocument:(PSPDFDocument *)document;

@end

NS_ASSUME_NONNULL_END
