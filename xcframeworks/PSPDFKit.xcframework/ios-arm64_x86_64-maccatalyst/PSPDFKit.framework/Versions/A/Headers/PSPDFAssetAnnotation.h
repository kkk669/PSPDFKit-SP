//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFLinkAnnotation.h>

NS_ASSUME_NONNULL_BEGIN

/// Abstract subclass that contains an asset from a link
PSPDF_CLASS_SWIFT(AssetAnnotation)
@interface PSPDFAssetAnnotation : PSPDFLinkAnnotation

/// The name of the embedded asset.
@property (atomic, copy, readonly, nullable) NSString *assetName;

/// Extracts the asset into a file and returns the file URL.
- (nullable NSURL *)fileURLWithError:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
