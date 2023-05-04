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

typedef NS_CLOSED_ENUM(NSInteger, PSPDFJSButtonImportIconResult) {
    /// The user cancelled the dialog.
    PSPDFJSButtonImportIconResultCancelled,
    /// The import finished successfully.
    PSPDFJSButtonImportIconResultNoError,
    /// The selected file could not be opened.
    PSPDFJSButtonImportIconResultFileCannotBeOpened,
    /// The selected page was invalid.
    PSPDFJSButtonImportIconResultInvalidPage,
};

/// Represents the parameters that platforms need to implement the `field.buttonImportIconParams` JS call properly.
PSPDF_OBJC_DIRECT_MEMBERS_EXCEPT_TESTS
@interface PSPDFJSButtonImportIconParams : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes a `PSPDFJSButtonImportIconParams` with the path to a PDF document and a page number.
- (instancetype)initWithPath:(nullable NSString *)path pageNumber:(PSPDFPageIndex)pageNumber NS_DESIGNATED_INITIALIZER;

/// Path to the PDF document that should be imported into the button.
@property (nonatomic, readonly, nullable, copy) NSString *path;

/// Page number of the document pointed to by `path` that will be imported.
@property (nonatomic, readonly) PSPDFPageIndex pageIndex;

@end

@interface PSPDFJSButtonImportIconFormElementInfo : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes a `PSPDFJSButtonImportIconFormElementInfo` with the page index and bounding box of the form element that originated
/// the button import action.
- (instancetype)initWithFormElementPageIndex:(PSPDFPageIndex)formElementPageIndex formElementBoundingBox:(CGRect)formElementBoundingBox NS_DESIGNATED_INITIALIZER;

/// The page index of the form element that originated the
/// "buttonImportIcon" action.
@property (nonatomic, readonly) PSPDFPageIndex formElementPageIndex;

/// The bounding box of the form element that originated the
/// "buttonImportIcon" action.
@property (nonatomic, readonly) CGRect formElementBoundingBox;

@end

NS_ASSUME_NONNULL_END
