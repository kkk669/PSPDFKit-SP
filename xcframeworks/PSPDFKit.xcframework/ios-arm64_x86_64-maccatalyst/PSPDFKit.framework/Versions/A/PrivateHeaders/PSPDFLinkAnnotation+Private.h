//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFLinkAnnotation.h>

@interface PSPDFLinkAnnotation ()

/// Some link annotations may point to items that need to be extracted from the document
/// and stored in a temporary location before they can be accessed. In this case this
/// property will return the file URL pointing to the local file.
///
/// @note If you want to access the resolved URL and it is `nil` this can be loaded
/// through `-[PSPDFGalleryManifest loadItemsWithCompletionBlock:]`.
@property (nonatomic, copy, nullable) NSURL *resolvedURL;

// MARK: - Tests

// Whether action lazy loading was already triggered.
@property (nonatomic, readonly) BOOL actionLoaded;

@end
