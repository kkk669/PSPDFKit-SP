//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFApplication.h>
#import <PSPDFKitUI/PSPDFFeedbackGenerator.h>
#import <PSPDFKitUI/PSPDFKitGlobal+PSPDFUI.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFFeedbackGenerator;
@protocol PSPDFAppKitUIObjcBridge;

@interface PSPDFKitGlobal (PSPDFUIPrivate)

/// Performance: allows checking if the lazy loaded property is actually initialized.
@property (nonatomic, getter=isSpeechControllerLoaded, readonly) BOOL speechControllerLoaded;

/// Contains various internal application-specific characteristics and actions.
- (void)updateApplicationForExtensionContext:(nullable NSExtensionContext *)extensionContext;

/// The global feedback generator object
@property (nonatomic, readonly) PSPDFFeedbackGenerator *feedbackGenerator;

#if TARGET_OS_MACCATALYST
/// AppKit wrapper for Mac Catalyst
@property (nonatomic, readonly) id<PSPDFAppKitUIObjcBridge> appKitUIBridge;
#endif

/// Cancels any thread operations that are not handled by the model.
/// Implies calling `- (void)cancelThreadOperationsAndWait:(BOOL)wait`
- (void)cancelUIThreadOperationsAndWait:(BOOL)wait;

/// Blocks until UI operations are complete.
- (void)waitForUIThreadOperationsToFinish;

@end

NS_ASSUME_NONNULL_END
