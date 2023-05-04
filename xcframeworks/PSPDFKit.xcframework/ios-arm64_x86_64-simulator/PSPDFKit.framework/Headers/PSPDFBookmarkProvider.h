//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFBookmark;

/// A Bookmark Provider is used to store and read bookmarks from a data source.
///
/// If you need to store bookmarks in a file format other than what PSPDFKit supports
/// by default, you can create your own bookmark provider and attach it to a document's
/// bookmark manager.
///
/// @see BookmarkManager
/// @see PSPDFBookmarksChangedNotification for change notifications.
PSPDF_PROTOCOL_SWIFT(BookmarkProvider)
@protocol PSPDFBookmarkProvider<NSObject>

/// Contains all bookmarks that are currently owned by the bookmark provider.
@property (nonatomic, readonly) NSArray<PSPDFBookmark *> *bookmarks;

/// Adds a bookmark to the bookmark provider if the given bookmark should be owned
/// by the receiver.
///
/// The receiver should decide if it wants to manage this bookmark. If it does, it
/// should add the bookmark to its list and return `true`. If it returns `false` the next
/// bookmark provider in the list is asked.
///
/// @note You will receive calls to `addBookmark:` with updated bookmarks that already
/// exist in a provider in an outdated version. You can determine if you are
/// already the owner of a bookmark by comparing its `identifier` property with
/// the ones from your list of bookmarks.
///
/// @param bookmark The bookmark that should be added to the receiver.
///
/// @return `true` if the receiver successfully added the bookmark, `false` otherwise.
- (BOOL)addBookmark:(PSPDFBookmark *)bookmark;

/// Removes a bookmark from the bookmark provider if the given bookmark is owned
/// by the receiver.
///
/// The receiver should check if the given bookmark is owned by itself. If this is
/// the case, it should remove the bookmark from the list and return `true`. If this
/// method returns `false` the next bookmark provider in the list is asked.
///
/// @param bookmark The bookmark that should be removed from the receiver.
///
/// @return `true` if the receiver successfully removed the bookmark, `false` otherwise.
- (BOOL)removeBookmark:(PSPDFBookmark *)bookmark;

/// Tells the bookmark provider to persist the bookmarks it is managing.
///
/// Most likely this method is called because the associated document is about to be
/// saved.
- (void)save;

@end

NS_ASSUME_NONNULL_END
