//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// Helper class that constructs a mobile Wikipedia URL based on a search term.
PSPDF_SDK_CLASS_SWIFT(WikipediaHelper)
@interface PSPDFWikipediaHelper : NSObject

/// Shared helper that tracks the current user language.
@property (atomic, class, readonly) PSPDFWikipediaHelper *sharedHelper;

/// By default uses an autoupdating locale that maps to the currentdevice language.
@property (atomic) NSLocale *locale;

/// Builds a URL for given search term to mobile Wikipedia.
/// Will use the preferred user locale.
///
/// @return Always returns an URL.
- (NSURL *)wikipediaURLForSearchTerm:(NSString *)searchTerm;

@end

NS_ASSUME_NONNULL_END
