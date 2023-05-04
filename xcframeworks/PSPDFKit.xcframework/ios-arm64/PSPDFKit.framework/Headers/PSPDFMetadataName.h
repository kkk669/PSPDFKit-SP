//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// Common PDF metadata keys.
typedef NSString *PSPDFMetadataName NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(PDFMetadata.Key);

/// Metadata key for the document title. Object will be of type String.
PSPDF_EXPORT PSPDFMetadataName const PSPDFMetadataTitleKey NS_SWIFT_NAME(title);
/// Metadata key for the document author. Object will be of type String.
PSPDF_EXPORT PSPDFMetadataName const PSPDFMetadataAuthorKey NS_SWIFT_NAME(author);
/// Metadata key for the document subject. Object will be of type String.
PSPDF_EXPORT PSPDFMetadataName const PSPDFMetadataSubjectKey NS_SWIFT_NAME(subject);
/// Metadata key for the document keywords. Object will be of type String.
PSPDF_EXPORT PSPDFMetadataName const PSPDFMetadataKeywordsKey NS_SWIFT_NAME(keywords);
/// Metadata key for the document creator. Object will be of type String.
PSPDF_EXPORT PSPDFMetadataName const PSPDFMetadataCreatorKey NS_SWIFT_NAME(creator);
/// Metadata key for the document producer. Object will be of type String.
PSPDF_EXPORT PSPDFMetadataName const PSPDFMetadataProducerKey NS_SWIFT_NAME(producer);
/// Metadata key for the document creation date. Object will be of type Date.
PSPDF_EXPORT PSPDFMetadataName const PSPDFMetadataCreationDateKey NS_SWIFT_NAME(creationDate);
/// Metadata key for the document modification date. Object will be of type Date.
PSPDF_EXPORT PSPDFMetadataName const PSPDFMetadataModDateKey NS_SWIFT_NAME(modificationDate);
/// Metadata key for the document's trapped value. Object will be of type String.
PSPDF_EXPORT PSPDFMetadataName const PSPDFMetadataTrappedKey NS_SWIFT_NAME(trapped);

NS_ASSUME_NONNULL_END
