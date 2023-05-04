//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFDataSink.h>
#else
#import "PSPDFDataSink.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// A `PSPDFDataSink` that works with `PSPDFDataContainerProvider`.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(DataContainerSink)
@interface PSPDFDataContainerSink : NSObject<PSPDFDataSink>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes the `PSPDFDataContainerSink` with the initial data.
- (instancetype)initWithData:(NSData *_Nullable)data NS_DESIGNATED_INITIALIZER;

/// Access to the data.
@property (nonatomic, readonly) NSData *data;

@end

NS_ASSUME_NONNULL_END
