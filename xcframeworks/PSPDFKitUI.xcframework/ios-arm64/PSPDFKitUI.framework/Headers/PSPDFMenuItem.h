//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

// `UIMenuItem` has been deprecated in iOS 16 and `PSPDFMenuItem` will be
// deprecated in a future version of PSPDFKit. Until then, we silence the
// deprecation warning in case PSPDFKitUI is imported into a project with the
// deployment target of iOS 16 or newer.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

/// This subclass adds support for a block-based action on `UIMenuItem`.
/// If you are as annoyed about the missing target/action pattern, you will love this.
///
/// If you use `PSPDFMenuItem` with the classic `initWithTitle:selector:` initializer,
/// this will work and be handled just like a regular `UIMenuItem`.
///
/// @warning By design, `PSPDFMenuItem` will only work with *different* title names. If no identifier is set, then title is required to be unique when converted to lowercase and non-ASCII characters are stripped, even when images are used.
PSPDF_CLASS_SWIFT(MenuItem)
@interface PSPDFMenuItem : UIMenuItem

#pragma clang diagnostic pop

/// Initialize `PSPDFMenuItem` with a block. Do not use this initializer unless your titles are unique when converted to lowercase and non-ASCII characters are stripped, because an `identifier` must be specified in that case.
- (instancetype)initWithTitle:(NSString *)title block:(void (^)(void))block;

/// Initialize `PSPDFMenuItem` with a block and an non-localized unique identifier for later manipulation.
- (instancetype)initWithTitle:(NSString *)title block:(void (^)(void))block identifier:(nullable NSString *)identifier;

/// Initialize `PSPDFMenuItem` with an image, a block and an non-localized unique identifier for later manipulation.
/// Will not allow image colors.
- (instancetype)initWithTitle:(NSString *)title image:(nullable UIImage *)image block:(void (^)(void))block identifier:(nullable NSString *)identifier;

/// Initialize PSPDFMenuItem with an image, a block and an non-localized unique identifier for later manipulation.
- (instancetype)initWithTitle:(NSString *)title image:(nullable UIImage *)image block:(void (^)(void))block identifier:(nullable NSString *)identifier allowImageColors:(BOOL)allowImageColors NS_DESIGNATED_INITIALIZER;

/// Menu item can be enabled/disabled. (disable simply hides it from the UIMenuController)
@property (nonatomic, getter=isEnabled) BOOL enabled;

/// If this is set to YES, we will invoke the menu item automatically, instead of presenting it.
@property (nonatomic) BOOL shouldInvokeAutomatically;

/// Helper to identify the current action. Not localized.
@property (nonatomic, copy, nullable, readonly) NSString *identifier;

/// Image of the menu item.
/// 24x24px is a good size. Images larger than 32x32px are automatically resized.
///
/// If set the image will hide the title.
/// This is prefixed to make sure it will work even when Apple decides to add support for images in future releases.
///
/// @warning Due to implementation details, this will actually change `title`. Use `identifier` to compare menu items instead.
@property (nonatomic, nullable) UIImage *ps_image;

// Action block.
@property (nonatomic, copy) void (^actionBlock)(void);

/// Installs the menu handler. Needs to be called once per class.
/// (A good place is the +load method)
///
/// Following methods will be swizzled:
/// `- canBecomeFirstResponder` (if object doesn't already return YES)
/// `- canPerformAction:withSender:`
/// `- methodSignatureForSelector:`
/// `- forwardInvocation:`
///
/// The original implementation will be called if the `PSPDFMenuItem` selector is not detected.
///
/// @param object can be an instance or a class.
+ (void)installMenuHandlerForObject:(id)object;

/// @name Unavailable Inherited API
/// The parent designated initializer is not available in this subclass.
- (instancetype)initWithTitle:(NSString *)title action:(SEL)action PSPDF_NOT_DESIGNATED_INITIALIZER_ATTRIBUTE;

@end

@interface PSPDFMenuItem (PSPDFAnalytics)

// This is called when a menu item is being called.
// Swizzle this and fetch the `identifier` to add analytics for menu actions.
- (void)performBlock;

@end

// `PSPDFMenuItem` also adds support for images. This doesn't use private API but requires some method swizzling.
// Disable the image feature by setting this variable to NO before you set any image (e.g. in your AppDelegate)
// Defaults to YES.
PSPDF_EXPORT BOOL PSPDFAllowImagesForMenuItems;

NS_ASSUME_NONNULL_END
