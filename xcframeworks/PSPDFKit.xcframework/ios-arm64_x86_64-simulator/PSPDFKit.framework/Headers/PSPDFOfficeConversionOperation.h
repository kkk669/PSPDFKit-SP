//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFConversionOperation.h>

NS_ASSUME_NONNULL_BEGIN

/// Operation that converts a local Office file to PDF by sending it to a server.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(OfficeConversionOperation)
@interface PSPDFOfficeConversionOperation : PSPDFConversionOperation <NSProgressReporting>

/// URL of the Office file to be converted.
@property (nonatomic, readonly) NSURL *inputURL;

/// URL of the Office conversion endpoint.
@property (nonatomic, readonly) NSURL *serverURL;

/// JSON Web Token used to authenticate the document conversion request.
@property (nonatomic, readonly) NSString *JWT;

/// Progress object for the conversion operation. Does not support pausing.
/// It does support cancellation, although you can also cancel the operation directly.
@property (nonatomic, readonly) NSProgress *progress;

@end

NS_ASSUME_NONNULL_END
