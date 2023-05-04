//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFAnnotationProvider.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// Writes an .fdf file from PSPDFKit annotations.
PSPDF_SDK_CLASS_SWIFT(FDFWriter)
@interface PSPDFFDFWriter : NSObject

/// Writes the given annotations to the given output stream.
- (BOOL)writeFormElements:(NSArray<__kindof PSPDFAnnotation *> *)annotations toOutputStream:(NSOutputStream *)outputStream error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
