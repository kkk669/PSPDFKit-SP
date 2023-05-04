//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFDocumentSharingConfiguration+Private.h>
#import <PSPDFKitUI/PSPDFDocumentSharingContext.h>

NS_ASSUME_NONNULL_BEGIN

/// Coordinates the page selection flow between `PDFDocumentSharingViewController` and
/// `PSPDFDocumentSharingPageSelectionViewController` instances.
///
/// An instance of this object represents a "snapshot" of the state of `PDFDocumentSharingViewController` that the
/// `PSPDFDocumentSharingPageSelectionViewController` can use to provide a suitable set of options to offer to the user.
NS_SWIFT_NAME(PDFDocumentSharingPageSelectionDataSource)
@interface PSPDFDocumentSharingPageSelectionDataSource : NSObject

/// Instantiate a new data source with contextual information.
- (instancetype)initWithSharingContext:(PSPDFDocumentSharingContext *)sharingContext baseSharingConfiguration:(PSPDFDocumentSharingConfiguration *)sharingConfiguration sharingState:(PSPDFDocumentSharingConfiguration *)sharingState NS_DESIGNATED_INITIALIZER;

/// Convenience accessor. Returns the first document in `documents.`
@property (nonatomic, readonly) PSPDFDocument *mainDocument;

/// Convenience accessor. Returns the context's documents.
@property (nonatomic, readonly) NSArray<PSPDFDocument *> *documents;

/// The sharing context on this sharing session.
@property (nonatomic, readonly) PSPDFDocumentSharingContext *sharingContext;

/// The sharing configuration that defines the options that are available.
@property (nonatomic, readonly) PSPDFDocumentSharingConfiguration *baseSharingConfiguration;

/// The sharing configuration that acts as the selection state.
@property (nonatomic, readonly) PSPDFDocumentSharingConfiguration *sharingState;

/// The selected page range to take into account for presenting the options.
@property (nonatomic) NSRange selectedPageRange;

/// Returns a title suitable to represent the selected option based on the current context.
- (NSString *)localizedValueForPageRangeFromOptions:(PSPDFDocumentSharingPagesOptions)options;

/// Returns a valid `NSRange` for the given option considering the context.
///
/// `option` should have exactly one bit enabled.
- (NSRange)preferredRangeForOption:(PSPDFDocumentSharingPagesOptions)option;

@end

NS_ASSUME_NONNULL_END
