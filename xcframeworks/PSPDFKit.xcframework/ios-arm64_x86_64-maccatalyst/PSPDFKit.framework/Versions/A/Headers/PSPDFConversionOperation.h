//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// `PSPDFConversionOperation` is the base class for all PDF conversion operations.
///
/// @warning Do not create instances of this class or its subclasses. They are intended to be initiated internally by `PSPDFProcessor`.
PSPDF_CLASS_SWIFT(ConversionOperation)
@interface PSPDFConversionOperation : NSOperation

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Output URL, if any. Must be a file URL.
@property (nullable, nonatomic, readonly, copy) NSURL *outputURL;

/// Output data, if no `outputURL` was given and no error occurred.
@property (nullable, nonatomic, readonly) NSData *outputData;

/// Error, if something went wrong.
@property (nullable, nonatomic, readonly) NSError *error;

@end

NS_ASSUME_NONNULL_END
