//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKitUI/PSPDFInteractionComponentCore.h>

NS_ASSUME_NONNULL_BEGIN

/// An interaction component core that encapsulates multiple interaction component
/// cores.
PSPDF_SUBCLASSING_RESTRICTED
@interface PSPDFInteractionComponentCompositeCore : NSObject <PSPDFInteractionComponentCore>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes a new instance with the given array of underlying interaction
/// component cores.
- (instancetype)initWithOtherCores:(NSArray<id<PSPDFInteractionComponentCore>> *)cores NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
