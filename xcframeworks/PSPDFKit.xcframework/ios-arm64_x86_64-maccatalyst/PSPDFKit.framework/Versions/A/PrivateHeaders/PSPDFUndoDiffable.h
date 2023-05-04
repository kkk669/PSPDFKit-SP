//
//  Copyright © 2021-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// A protocol that defines a common interface for types that can be diffed
/// against each other for undo purposes.
///
/// @note This has to be an Objective-C protocol because declaring conformance
/// to this protocol in header files produces a build dependency cycle (Obj-C
/// headers depend on Swift sources, which depend on Obj-C headers, and so on).
PSPDF_PROTOCOL_SWIFT(UndoDiffable)
@protocol PSPDFUndoDiffable <NSObject>

/// A dictionary containing a snapshot of values to be used when diffing.
///
/// @warning This dictionary must contain read-write KVC keys (that is, keys
/// accepted by both `valueForKey:` and `setValue:forKey:`). Failure to satisfy
/// this requirement will result in an exception being thrown at some point.
@property (nonatomic, readonly) NSDictionary<NSString *, id> *dictionaryValueForDiffing;

@end

NS_ASSUME_NONNULL_END
