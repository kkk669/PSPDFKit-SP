//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// An input stream that concatenates the contents of its `inputStreams` when polled.
///
/// NOTE: Instances of this class do not support reading/setting of stream properties, or
/// access to an underlying raw buffer. They also do not support scheduling on a runloop!
///
/// Instead, the contents have to be consumed by repeatedly calling `-read:maxLength:`
/// while `streamStatus` is `NSStreamStatusOpen`.
@interface PSPDFSerialInputStream : NSInputStream

- (instancetype)initWithInputStreams:(NSArray<NSInputStream *> *)inputStreams;

@property (nonatomic, readonly) NSArray<NSInputStream *> *inputStreams;

@end

NS_ASSUME_NONNULL_END
