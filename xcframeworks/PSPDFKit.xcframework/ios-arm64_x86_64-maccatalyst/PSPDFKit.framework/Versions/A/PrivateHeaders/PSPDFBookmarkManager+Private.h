//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFBookmark.h>
#import <PSPDFKit/PSPDFBookmarkManager.h>
#import <PSPDFKit/PSPDFBookmarkProvider.h>
#import <PSPDFKit/PSPDFOverrideProvider.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFBookmarkManager () <PSPDFOverrideProvider>

/// This method should only be called when the document's annotation save mode does
/// not allow embedding. In this case we want to still call save on all custom document
/// providers but not on ours.
- (void)workaround10665_saveCustomBookmarkProvider;

/// Used to clear out the bookmarks array so that it gets fetched from core next time
/// it is accessed. Effectively reloads the bookmark list from core.
- (void)setNeedsUpdateBookmarksArray;

@end

@interface PSPDFPrivateBookmarkProvider : NSObject <PSPDFBookmarkProvider>
@end

NS_ASSUME_NONNULL_END
