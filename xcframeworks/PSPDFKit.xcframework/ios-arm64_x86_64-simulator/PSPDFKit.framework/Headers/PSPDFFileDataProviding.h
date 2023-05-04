//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFDataProviding.h>
#else
#import "PSPDFDataProviding.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// A more specialized protocol for data providers backed by local files.
NS_SWIFT_NAME(FileDataProviding)
@protocol PSPDFFileDataProviding <PSPDFDataProviding>

/// The local file URL that the data provider reads from.
///
/// This can only be nil when the data provider supplies a `progress` and that progress is not
/// completed. When implementing a custom class that conforms to `FileDataProviding`, where the
/// value of this property may change over time — maybe because the file has become available after
/// loading from the network, moved on disk, or deleted — it is your responsibility to post the KVO
/// notifications. The simplest way to achieve this is by re-declaring the property as `readwrite`, and
/// always using the (synthesized) setter.
///
/// @warning Changing the value of this property without posting the appropriate KVO notifications
/// leads to undefined behavior in `Document`.
@property (nonatomic, readonly, nullable) NSURL *fileURL;

@end

NS_ASSUME_NONNULL_END
