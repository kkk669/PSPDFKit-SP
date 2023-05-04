//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDocumentFeatures.h>

@interface PSPDFDocumentFeatures ()

/// This adds fundamental sources to the list of sources to be queried when evaluating
/// features.
///
/// A fundamental source is a source that can not be removed by the user (i.e. by calling
/// `removeSource:`). Instead to remove a fundamental source you need to call `removeFundamentalSource:`.
/// Fundamental sources can be used to add elementary functionality that should not
/// be controllable by the user, such as our license source or a file system source.
/// Currently all default framework sources are added as fundamental sources.
///
/// @param sources The sources to add.
- (void)addFundamentalSources:(NSArray<id<PSPDFDocumentFeaturesSource>> *)sources;

/// Removes sources that were previously added by calling `addFundamentalSources:`.
///
/// @param source The sources to remove.
- (void)removeFundamentalSources:(NSArray<id<PSPDFDocumentFeaturesSource>> *)source;

@end
