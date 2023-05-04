//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

/// Defines all the available options for types of annotation replies.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFAnnotationReplyType) {
    /// Matches annotation replies that are only text replies.
    PSPDFAnnotationReplyTypeText,
    /// Matches annotation replies that are only state replies.
    PSPDFAnnotationReplyTypeState,
    /// Matches annotation replies that are either text or state replies.
    PSPDFAnnotationReplyTypeTextAndState,
} NS_SWIFT_NAME(AnnotationReplyType);
