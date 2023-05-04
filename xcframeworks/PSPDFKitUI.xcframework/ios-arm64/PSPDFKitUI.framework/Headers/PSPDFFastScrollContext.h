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

/// An enum representing the direction of fast scroll.
typedef NS_CLOSED_ENUM(NSInteger, PSPDFFastScrollDirection) {
    /// A scroll backwards.
    PSPDFFastScrollDirectionBackward = -1,
    /// A scroll forwards.
    PSPDFFastScrollDirectionForward = 1,
} PSPDF_ENUM_SWIFT(FastScrollDirection);

// MARK: -

/// An object used as an activation context of `PSPDFFastScrollInteraction` that
/// contains additional information about the direction of fast scroll.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(FastScrollContext)
@interface PSPDFFastScrollContext : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Direction of fast scroll.
@property (nonatomic, readonly) PSPDFFastScrollDirection direction;

@end

NS_ASSUME_NONNULL_END
