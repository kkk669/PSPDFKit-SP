//
//  Copyright © 2022-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKitUI/PSPDFInteractionComponentCore.h>

NS_ASSUME_NONNULL_BEGIN

/// Type-erased signature of a context transformation block.
typedef id _Nonnull (^PSPDFInteractionComponentTransformedCoreTransformBlock)(id context);

// MARK: -

/// An interaction component core that transforms the activation context of
/// another core.
PSPDF_SUBCLASSING_RESTRICTED
@interface PSPDFInteractionComponentTransformedCore<SourceType, ResultType> : NSObject <PSPDFInteractionComponentCore>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes a new instance with the given core and a block that transforms
/// the given core's activation context.
- (instancetype)initWithCore:(id<PSPDFInteractionComponentCore>)core transform:(ResultType (^)(SourceType context))transform NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
