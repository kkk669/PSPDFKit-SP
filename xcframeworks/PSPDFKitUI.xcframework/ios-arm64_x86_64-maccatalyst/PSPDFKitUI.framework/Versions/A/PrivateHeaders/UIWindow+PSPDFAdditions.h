//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <UIKit/UIKit.h>
#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIWindow (PSPDFAdditions)

#if TARGET_OS_MACCATALYST

/// Finds the `NSWindow` hosting the `UIWindow`.
///
/// @warning This uses private API.
@property (nonatomic, readonly, nullable) NSObject *pspdf_nsWindow NS_SWIFT_NAME(nsWindow);

/// Finds the `UIWindow` from an `NSWindow`.
+ (nullable instancetype)pspdf_uiWindowFromNSWindow:(id)nsWindow NS_SWIFT_NAME(uiWindowFromNSWindow(window:));

/// Sets the restorable property of the corresponding `UIWindow`.
@property (nonatomic) BOOL pspdf_restorable NS_SWIFT_NAME(restorable);

/// Make the window the key window and move it to the front.
- (void)pspdf_makeKeyAndOrderFront NS_SWIFT_NAME(makeKeyAndOrderFront());

/// Center the window on the current screen.
- (void)pspdf_center NS_SWIFT_NAME(center());

/// See NSWindowStyleMask for documentation.
typedef NS_OPTIONS(NSUInteger, PSPDFNSWindowStyleMask) {
    PSPDFNSWindowStyleMaskBorderless = 0,
    PSPDFNSWindowStyleMaskTitled = 1 << 0,
    PSPDFNSWindowStyleMaskClosable = 1 << 1,
    PSPDFNSWindowStyleMaskMiniaturizable = 1 << 2,
    PSPDFNSWindowStyleMaskResizable = 1 << 3,
    PSPDFNSWindowStyleMaskUnifiedTitleAndToolbar = 1 << 12,
    PSPDFNSWindowStyleMaskFullScreen = 1 << 14,
    PSPDFNSWindowStyleMaskFullSizeContentView = 1 << 15,
    PSPDFNSWindowStyleMaskUtilityWindow = 1 << 4,
    PSPDFNSWindowStyleMaskDocModalWindow = 1 << 6,
    PSPDFNSWindowStyleMaskNonactivatingPanel = 1 << 7,
    PSPDFNSWindowStyleMaskHUDWindow = 1 << 13
} NS_SWIFT_NAME(NSWindowStyleMask);

/// Wrapper for NSWindow's styleMask.
@property (nonatomic) PSPDFNSWindowStyleMask pspdf_styleMask NS_SWIFT_NAME(styleMask);

/// See NSWindowCollectionBehavior for documentation.
typedef NS_OPTIONS(NSUInteger, PSPDFNSWindowCollectionBehavior) {
    PSPDFNSWindowCollectionBehaviorDefault = 0,
    PSPDFNSWindowCollectionBehaviorCanJoinAllSpaces = 1 << 0,
    PSPDFNSWindowCollectionBehaviorMoveToActiveSpace = 1 << 1,
    PSPDFNSWindowCollectionBehaviorManaged = 1 << 2,
    PSPDFNSWindowCollectionBehaviorTransient = 1 << 3,
    PSPDFNSWindowCollectionBehaviorStationary = 1 << 4,
    PSPDFNSWindowCollectionBehaviorParticipatesInCycle = 1 << 5,
    PSPDFNSWindowCollectionBehaviorIgnoresCycle = 1 << 6,
    PSPDFNSWindowCollectionBehaviorFullScreenPrimary = 1 << 7,
    PSPDFNSWindowCollectionBehaviorFullScreenAuxiliary = 1 << 8,
    PSPDFNSWindowCollectionBehaviorFullScreenNone = 1 << 9,
    PSPDFNSWindowCollectionBehaviorFullScreenAllowsTiling = 1 << 11,
    PSPDFNSWindowCollectionBehaviorFullScreenDisallowsTiling = 1 << 12
} NS_SWIFT_NAME(NSWindowCollectionBehavior);

/// Wrapper for NSWindow's collectionBehavior.
@property (nonatomic) PSPDFNSWindowCollectionBehavior pspdf_collectionBehavior NS_SWIFT_NAME(collectionBehavior);

#endif

@end

NS_ASSUME_NONNULL_END
