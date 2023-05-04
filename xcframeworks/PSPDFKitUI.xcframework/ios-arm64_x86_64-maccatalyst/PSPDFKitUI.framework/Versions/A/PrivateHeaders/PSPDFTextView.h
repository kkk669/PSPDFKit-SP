//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// Subclass of `UITextView` that fixes the most glaring bugs in iOS 7 and 8.
/// Also adds support for showing placeholder text like UITextField.
PSPDF_APP_CLASS_SWIFT(TextView)
@interface PSPDFTextView : UITextView

/// Scrolls to caret position, considering insets.
- (void)scrollToVisibleCaretAnimated:(BOOL)animated;

/// If set, the text view will keep the caret (insertion point) visible by scrolling this scroll view.
/// If nil, the text view will scroll itself.
@property (nonatomic, weak) UIScrollView *scrollViewForCaretVisibility;

/// A string that is displayed when there is no other text in the text view.
/// This is nil by default.
///
/// Prefixed as name conflicts seem possible.
///
/// Currently copes with the needs of PSPDFCommentCell and not tested for any more than that.
@property (nonatomic, copy, nullable, setter=pspdf_setPlaceholder:) NSString *pspdf_placeholder;

@end

NS_ASSUME_NONNULL_END
