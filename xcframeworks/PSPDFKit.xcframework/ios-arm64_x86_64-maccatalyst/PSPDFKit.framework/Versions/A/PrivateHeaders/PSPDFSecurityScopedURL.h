//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// Internal helper used to save us from doing the `startAccessingSecurityScopedResource` / `stopAccessingSecurityScopedResource` dance.
PSPDF_CLASS_SWIFT(SecurityScopedURL)
PSPDF_SUBCLASSING_RESTRICTED
@interface PSPDFSecurityScopedURL : NSObject <NSCopying>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// The security scoped NSURL.
@property (nonatomic, readonly) NSURL *fileURL;

/// Creates a PSPDFSecurityScopedURL using the passed NSURL.
///
/// @param url to security scope.
- (instancetype)initWithURL:(NSURL *)url;

@end

NS_ASSUME_NONNULL_END
