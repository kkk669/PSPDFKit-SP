//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFSignatureContents.h>

NS_ASSUME_NONNULL_BEGIN

/// A `PSPDFSignatureContents` instance that returns zeroed data.
PSPDF_CLASS_SWIFT(BlankSignatureContents)
@interface PSPDFBlankSignatureContents : NSObject<PSPDFSignatureContents>

@end

NS_ASSUME_NONNULL_END
