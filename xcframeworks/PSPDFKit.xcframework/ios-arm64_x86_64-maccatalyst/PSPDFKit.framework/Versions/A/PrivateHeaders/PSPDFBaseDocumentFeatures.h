//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <Foundation/Foundation.h>
#import <PSPDFKit/PSPDFDocumentFeatures.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>

@class PSPDFDocument;

NS_ASSUME_NONNULL_BEGIN

/// The base document features class is an abstract base class meant for subclassing.
/// It does not implement any features. It's purpose is to provide a base for sources
/// that require a reference to the document.
PSPDF_SDK_CLASS_SWIFT(BaseDocumentFeatures)
@interface PSPDFBaseDocumentFeatures : NSObject <PSPDFDocumentFeaturesSource>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes the feature source with a given document.
///
/// The document will be held weakly.
///
/// @param document The document this source should act upon, held weakly.
- (instancetype)initWithDocument:(PSPDFDocument *)document NS_DESIGNATED_INITIALIZER;

/// The document the source was initialized with or `nil` if the document has been deallocated.
@property (nonatomic, weak, readonly) PSPDFDocument *document;

@end

NS_ASSUME_NONNULL_END
