//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDocument.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFDocument (Validation)

/// YES if the PDF contains a `%%EOF` marker according to the PDF specification.
@property (nonatomic, readonly) BOOL isLikelyComplete;

@end

NS_ASSUME_NONNULL_END
