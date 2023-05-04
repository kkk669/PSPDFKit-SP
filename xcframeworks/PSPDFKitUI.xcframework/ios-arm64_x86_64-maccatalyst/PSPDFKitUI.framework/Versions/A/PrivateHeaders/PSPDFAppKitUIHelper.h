//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_CLOSED_ENUM(NSInteger, PSPDFCursorMode) {
    /// The "normal" cursor
    PSPDFCursorModeArrow,
    /// The "pointingHand/link" cursor
    PSPDFCursorModePointingHand,
    /// The iBeam cursor for text selection
    PSPDFCursorModeTextSelection,
    /// An open hand cursor for moving items
    PSPDFCursorModeOpenHand,
    /// A closed hand cursor for pressing mouse while moving items
    PSPDFCursorModeClosedHand,
    /// Cursor to indicate rotation
    PSPDFCursorModeRotate,
    /// Resize top-down
    PSPDFCursorModeResizeNorthSouth,
    /// Resize left-right
    PSPDFCursorModeResizeEastWest,
    /// Resize top-left or bottom-right edge
    PSPDFCursorModeResizeNorthWestSouthEast,
    /// Resize top-right or bottom-left edge
    PSPDFCursorModeResizeNorthEastSouthWest
} PSPDF_ENUM_SWIFT(CursorMode);

#if TARGET_OS_MACCATALYST

@protocol PSPDFAppKitUIObjcBridge <NSObject>

/// Gets/Sets the cursor. Uses NSCursor API.
@property (nonatomic) PSPDFCursorMode cursorMode;

@end

PSPDF_EXTERN @interface PSPDFAppKitUIHelper : NSObject <PSPDFAppKitUIObjcBridge>

@end

PSPDF_APP_EXPORT @interface PSPDFMacSavePanel : NSObject

/// Invoke Save Panel.
///
/// If the user cancelled the saving, then `targetURL` will be nil.
+ (void)showPanelWithFileName:(NSString *)fileName allowedFileExtensions:(NSArray *)allowedFileExtensions completionHandler:(void(^)(NSURL *_Nullable targetURL))completionHandler NS_SWIFT_DISABLE_ASYNC;

@end

#endif

NS_ASSUME_NONNULL_END
