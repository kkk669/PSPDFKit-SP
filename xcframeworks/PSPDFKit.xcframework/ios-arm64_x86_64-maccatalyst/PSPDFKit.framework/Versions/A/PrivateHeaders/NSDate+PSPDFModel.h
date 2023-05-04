//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSDate (PSPDFModel)

/// Converts a string formatted after PDF Reference 7.9.4 to an NSDate.
/// See DateUtilities.cpp in Core
+ (nullable NSDate *)pspdf_dateFromPDFDateString:(nullable NSString *)PDFDateString;

/// Converts a date to a PDF formatted date string.
@property (nonatomic, readonly) NSString *pspdf_PDFDateString;

@end

NS_ASSUME_NONNULL_END
