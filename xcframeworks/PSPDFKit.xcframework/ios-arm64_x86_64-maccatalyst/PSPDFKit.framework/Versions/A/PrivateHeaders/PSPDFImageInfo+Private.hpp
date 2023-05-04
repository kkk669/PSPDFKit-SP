//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFImageInfo.h>

#ifdef __cplusplus
#include <vector>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFImageInfo ()

/// Init object with page and rotation.
- (instancetype)initWithIndex:(NSUInteger)index pixelSize:(CGSize)pixelSize transform:(CGAffineTransform)transform vertices:(const std::vector<CGPoint> &)vertices pageIndex:(PSPDFPageIndex)pageIndex documentProvider:(nullable PSPDFDocumentProvider *)documentProvider NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
#endif
