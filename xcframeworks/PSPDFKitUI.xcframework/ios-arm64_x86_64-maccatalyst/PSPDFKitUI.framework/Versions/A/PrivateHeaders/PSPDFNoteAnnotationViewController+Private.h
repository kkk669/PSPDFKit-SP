//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFNoteAnnotationViewController.h>

@class PSPDFConfiguration, PSPDFNoteAnnotationViewControllerDataProvider, PSPDFAddReplyView;

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFNoteAnnotationViewController ()

/// The configuration that should be used, coming from the `PDFViewController`.
@property (nonatomic, nullable) PSPDFConfiguration *configuration;

/// The object that provides comment data to the view controller, and handles operations like posting comments.
@property (nonatomic, readonly) PSPDFNoteAnnotationViewControllerDataProvider *dataProvider;

/// Returns the add reply view shown at the bottom of the table view, allowing users to add a new comment.
/// This must only be called inside the UITableViewDelegate method viewForFooterInSection.
- (PSPDFAddReplyView *)dequeueAddReplyViewFromTableView:(UITableView *)tableView;

/// Internal table view used to show the replies and the add reply view.
@property (nonatomic, readonly) UITableView *tableView;

/// Can be used to customize the text view. (If UIAppearance rules are not enough)
///
/// @note The text view delegate must not be changed. Instead subclass and implement the required delegate methods.
/// Subclasses must not call super when implementing `UITextViewDelegate` methods.
/// Internal logic takes care of that automatically as needed.
///
/// TODO: This is used in a nasty hack in PSPDFViewController.mm that we should try to remove.
@property (nonatomic, readonly, nullable) UITextView *textView;

/// Sets the text view as first responder and enables editing if allowed.
/// Returns YES on success, false if not editable or first responder couldn't be set.
///
/// TODO: This is a hack and we should think how to get rid of it.
- (BOOL)beginEditing;

@end

NS_ASSUME_NONNULL_END
