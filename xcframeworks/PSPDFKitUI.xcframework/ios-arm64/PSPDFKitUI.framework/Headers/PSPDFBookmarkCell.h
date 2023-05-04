//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFThumbnailTextCell.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFBookmark, PSPDFBookmarkCell;

/// Delegate when we use inline cell editing.
PSPDF_PROTOCOL_SWIFT(BookmarkTableViewCellDelegate)
@protocol PSPDFBookmarkTableViewCellDelegate<NSObject>

/// Called when the bookmark cell did update the text.
- (void)bookmarkCell:(PSPDFBookmarkCell *)cell didUpdateBookmarkString:(NSString *)bookmarkString;

@end

/// Custom cell used for bookmarks.
PSPDF_CLASS_SWIFT(BookmarkCell)
@interface PSPDFBookmarkCell : PSPDFThumbnailTextCell<UITextFieldDelegate, PSPDFOverridable>

/// Delegate to communicate with the controller.
@property (nonatomic, weak) id<PSPDFBookmarkTableViewCellDelegate> delegate;

/// Indicates if the bookmark's page index is the currently viewed page.
/// If this is set, it causes the page number label to be stylized differently.
@property (nonatomic) BOOL isCurrentPage;

@end

NS_ASSUME_NONNULL_END
