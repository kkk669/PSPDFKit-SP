//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKitUI/PSPDFNetworkActivityIndicatorManager.h>

NS_ASSUME_NONNULL_BEGIN

/// This class handles opening URLs for other applications
/// and coordinates access to the network indicator manager since this is restricted in an iOS extension case.
PSPDF_PROTOCOL_SWIFT(Application)
@protocol PSPDFApplication<NSObject>

///  Returns a Boolean value indicating whether or not the URL’s scheme
///  can be handled by some app installed on the device.
///
///  @param url The URL to check.
///
///  @return YES if the URL can be opened by an application on the system.
- (BOOL)canOpenURL:(NSURL *)url;

///  Asks the host to open an URL on the extension's behalf if we are
///  in an extension context.
///
///  @param url               The URL to open
///  @param options           Open options.
///  @param completionHandler Calls the completion handler.
- (void)openURL:(NSURL *)url options:(nullable NSDictionary<NSString *, id> *)options completionHandler:(nullable void (^)(BOOL success))completionHandler;

/// Coordinates access to the network indicator manager.
@property (nonatomic, readonly) id<PSPDFNetworkActivityIndicatorManager> networkIndicatorManager;

@end

/// Default implementation that forwards calls to the app delegate.
PSPDF_CLASS_SWIFT(DefaultApplication)
@interface PSPDFDefaultApplication : NSObject<PSPDFApplication>
@end

/// Default extension implementation that interacts and requires an `NSExtensionContext` to work.
PSPDF_CLASS_SWIFT(ExtensionApplication)
@interface PSPDFExtensionApplication : PSPDFDefaultApplication<PSPDFApplication>
PSPDF_EMPTY_INIT_UNAVAILABLE
- (instancetype)initWithExtensionContext:(NSExtensionContext *)extensionContext NS_DESIGNATED_INITIALIZER;
@end

NS_ASSUME_NONNULL_END
