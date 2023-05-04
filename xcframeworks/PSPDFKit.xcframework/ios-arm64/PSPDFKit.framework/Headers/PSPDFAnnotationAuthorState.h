//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

/// Categories for the author-specific state that may be associated with an annotation.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFAnnotationAuthorStateModel) {
    /// The annotation is not a state annotation. Think of this as nil.
    PSPDFAnnotationAuthorStateModelUnspecified,
    /// Specifies that the state is a marked state.
    PSPDFAnnotationAuthorStateModelMarked,
    /// Specifies that the state is a review state.
    PSPDFAnnotationAuthorStateModelReview,
} NS_REFINED_FOR_SWIFT;

/// The types of author-specific state that may be associated with an annotation.
/// States are grouped into categories defined by `PSPDFAnnotationAuthorStateModel`.
/// See the Annotation States section in the PDF specification.
typedef NS_CLOSED_ENUM(NSUInteger, PSPDFAnnotationAuthorState) {
    /// The value when `PSPDFAnnotationAuthorStateModel` is `PSPDFAnnotationAuthorStateModelUnspecified`. Think of this as nil.
    PSPDFAnnotationAuthorStateUnspecified,
    /// The annotation has been marked by the user.
    PSPDFAnnotationAuthorStateMarked,
    /// The annotation has not been marked by the user (the default for `PSPDFAnnotationAuthorStateModelMarked`).
    PSPDFAnnotationAuthorStateUnmarked,
    /// The user agrees with the change.
    PSPDFAnnotationAuthorStateAccepted,
    /// The user disagrees with the change.
    PSPDFAnnotationAuthorStateRejected,
    /// The change has been cancelled.
    PSPDFAnnotationAuthorStateCancelled,
    /// The change has been completed.
    PSPDFAnnotationAuthorStateCompleted,
    /// The user has indicated nothing about the change (the default for `PSPDFAnnotationAuthorStateModelReview`).
    PSPDFAnnotationAuthorStateNone,
} NS_REFINED_FOR_SWIFT;
