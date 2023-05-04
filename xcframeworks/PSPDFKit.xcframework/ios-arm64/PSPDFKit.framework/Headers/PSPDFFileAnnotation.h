//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFEmbeddedFile.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

/// Defines how the attachment looks. Supported are PushPin, Paperclip, Graph and Tag.
typedef NSString *PSPDFFileIconName NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(FileAnnotation.IconName);

/// Paperclip icon.
PSPDF_EXPORT PSPDFFileIconName const PSPDFFileIconNamePaperclip;
/// Graph icon.
PSPDF_EXPORT PSPDFFileIconName const PSPDFFileIconNameGraph;
/// Tag icon.
PSPDF_EXPORT PSPDFFileIconName const PSPDFFileIconNameTag;
/// Pushpin icon.
PSPDF_EXPORT PSPDFFileIconName const PSPDFFileIconNamePushPin;

/// PDF File Attachment Annotation (see 12.5.6.15, "File attachment annotations").
/// A file attachment annotation (PDF 1.3) contains a reference to a file, which typically shall be embedded in the PDF file (see 7.11.4, "Embedded file streams").
PSPDF_CLASS_SWIFT(FileAnnotation)
@interface PSPDFFileAnnotation : PSPDFAnnotation<PSPDFOverridable>

/// File icon name. Defines how the attachment looks. Supported are PushPin, Paperclip, Graph and Tag.
///
/// @note Defaults to `PSPDFFileIconNamePaperclip` if not specified.
@property (nonatomic, copy) PSPDFFileIconName iconName;

/// The embedded file.
@property (nonatomic, nullable) PSPDFEmbeddedFile *embeddedFile;

@end

NS_ASSUME_NONNULL_END
