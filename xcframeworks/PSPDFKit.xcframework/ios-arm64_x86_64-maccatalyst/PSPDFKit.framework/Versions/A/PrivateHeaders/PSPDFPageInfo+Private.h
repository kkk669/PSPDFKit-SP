//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKit/PSPDFPageInfo.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFCPageInfo, PSPDFDocumentProvider;

@interface PSPDFPageInfo ()

/// Creates a new object from Core.
- (instancetype)initWithCorePageInfo:(PDFCPageInfo *)corePageInfo pageIndex:(PSPDFPageIndex)pageIndex documentProvider:(PSPDFDocumentProvider *)documentProvider;

/// Creates a new object with property values.
- (instancetype)initWithPageIndex:(PSPDFPageIndex)pageIndex size:(CGSize)size untransformedRect:(CGRect)untransformedRect savedRotation:(PSPDFRotation)savedRotation rotationOffset:(PSPDFRotation)rotationOffset transform:(CGAffineTransform)transform allowAnnotationCreation:(BOOL)allowAnnotationCreation additionalActions:(nullable NSDictionary<NSNumber *, PSPDFAction *> *)additionalActions documentProvider:(nullable PSPDFDocumentProvider *)documentProvider NS_DESIGNATED_INITIALIZER;

@property (nonatomic, weak) PSPDFDocumentProvider *documentProvider;

@end

/// Helper for portrait/landscape conversion
PSPDF_SDK_EXPORT NSUInteger PSPDFPortraitSpreadIndexForLandscapeSpreadIndex(NSUInteger spreadIndex, BOOL isFirstPageAlwaysSingle);

PSPDF_SDK_EXPORT NSUInteger PSPDFLandscapeSpreadIndexForPortraitSpreadIndex(NSUInteger spreadIndex, BOOL isFirstPageAlwaysSingle);

NS_ASSUME_NONNULL_END
