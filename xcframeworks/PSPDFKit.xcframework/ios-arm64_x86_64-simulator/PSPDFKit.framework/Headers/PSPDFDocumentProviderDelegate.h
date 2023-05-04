//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFDocumentProvider;

/// Delegate for writing annotations.
PSPDF_PROTOCOL_SWIFT(DocumentProviderDelegate)
@protocol PSPDFDocumentProviderDelegate<NSObject>

@optional

/// Called before we append data to a PDF. Return NO to stop writing annotations.
/// Defaults to YES if not implemented, and will set a new `Data` object.
- (BOOL)documentProvider:(PSPDFDocumentProvider *)documentProvider shouldAppendData:(NSData *)data;

/// Called after the write is completed.
- (void)documentProvider:(PSPDFDocumentProvider *)documentProvider didAppendData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
