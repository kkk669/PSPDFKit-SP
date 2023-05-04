//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

@protocol PSPDFAnnotationReviewSummary;

NS_ASSUME_NONNULL_BEGIN

/// A snapshot of the properties needed to display a comment.
///
/// Can be backed by an annotation (Annotation Replies feature) or an Instant Comment.
NS_SWIFT_NAME(CommentProtocol)
@protocol PSPDFComment <NSObject>

/// The name of the author/user that added comment.
@property (nonatomic, readonly, nullable) NSString *author;

/// The date/time the comment was last modified.
@property (nonatomic, readonly, nullable) NSDate *lastModificationDate;

/// The text content of the comment.
@property (nonatomic, readonly, nullable) NSString *text;

/// Text to display if `text` is empty.
@property (nonatomic, readonly, nullable) NSString *placeholderText;

/// The review summary of the comment, containing all the names of users that set a status,
/// as well as the latest status of the current user for this comment.
/// Only set if the containing documents features allow showing annotation replies.
@property (nonatomic, readonly, nullable) id<PSPDFAnnotationReviewSummary> reviewSummary;

/// Whether the user is allowed to edit the comment.
@property (nonatomic, readonly, getter=isEditable) BOOL editable;

/// The operations supported by this comment.
/// Just uses NSUInteger to expose this privately. Internally this uses PSPDFInstantRecordOperations.
@property (nonatomic, readonly) NSUInteger instantRecordOperations;

/// Record group of the annotation for use in Instant Collaboration Permissions.
@property (nonatomic, readonly, nullable) NSString *instantRecordGroup;

@end

NS_ASSUME_NONNULL_END
