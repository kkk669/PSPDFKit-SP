//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

#import <PSPDFKit/PSPDFAppearanceStreamGenerating.h>

NS_ASSUME_NONNULL_BEGIN

/// An appearance stream generator that makes sure to retain the current appearance stream.
PSPDF_CLASS_SWIFT(RetainExistingAppearanceStreamGenerator)
@interface PSPDFRetainExistingAppearanceStreamGenerator : NSObject<PSPDFAppearanceStreamGenerating>

@end

NS_ASSUME_NONNULL_END
