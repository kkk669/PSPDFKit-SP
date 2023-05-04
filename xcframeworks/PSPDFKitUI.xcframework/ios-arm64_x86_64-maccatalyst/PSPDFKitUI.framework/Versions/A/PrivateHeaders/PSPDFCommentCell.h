//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFTableViewCell.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFSecureTextView, PSPDFCommentReviewCountView, PSPDFCommentReviewSummaryView;

/// Margin around the comment bubbles.
extern const CGFloat PSPDFCommentCellOuterMargin;

/// A cell for displaying a comment, which is some text with an author and a date.
/// Designed for use with `PSPDFNoteAnnotationViewController`.
@interface PSPDFCommentCell : PSPDFTableViewCell

/// The label that displays the comment’s author’s name.
@property (nonatomic, readonly) UILabel *authorLabel;

/// The label that displays the date/time the comment was sent.
@property (nonatomic, readonly) UILabel *dateLabel;

/// The view that displays the message content.
@property (nonatomic, readonly) PSPDFSecureTextView *messageView;

/// The view that displays the count of a review summary for each state.
@property (nonatomic, readonly) PSPDFCommentReviewCountView *reviewCountView;

/// The view that displays the names of the users that set a status, grouped by state.
@property (nonatomic, readonly) PSPDFCommentReviewSummaryView *reviewSummaryView;

/// Button that is shown only in the expanded state, that enables the user to set or change a status.
@property (nonatomic, readonly) UIButton *setStatusButton;

/// Button that triggers an action sheet with options like setting the status,
/// deleting the comment and copying the comments text.
@property (nonatomic, readonly) UIButton *moreButton;

/// The view that contains everything related to reviews.
/// Should be hidden if there are no reviews set on the comment.
@property (nonatomic, readonly) UIView *reviewsView;

/// The note's rounded frame background color.
@property (nonatomic, nullable) UIColor *bubbleViewBackgroundColor;

/// Setting this expands or collapses the cell to show or hide the review summary and the set status button.
/// Defaults to NO.
@property (nonatomic) BOOL expanded;

/// Set this to hide `setStatusButton` and the separator above it.
@property (nonatomic) BOOL setStatusButtonHidden;

/// Whether the date label should be shown.
@property (nonatomic) BOOL showsTimestamps;

/// Whether the author name label should be shown.
@property (nonatomic) BOOL showsAuthorName;

/// The default layout constraints set up by the cell.
/// Subclasses can disable these constraints to use a custom layout.
@property (nonatomic, readonly) NSArray<NSLayoutConstraint *> *defaultConstraints;

/// This enables setting a custom font on `messageView.font`, without it being overwritten.
/// If this is set, `messageView.font` won't be updated on content size changes.
/// Defaults to NO.
@property (nonatomic) BOOL usesCustomMessageFont;

@end

/// View for showing the text field-like button for adding a new annotation reply.
PSPDF_APP_CLASS_SWIFT(AddReplyView)
@interface PSPDFAddReplyView : UITableViewHeaderFooterView

PSPDF_INIT_WITH_CODER_UNAVAILABLE

@property (nonatomic, readonly) UIButton *button;

@end

NS_ASSUME_NONNULL_END
