//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFKeyboardHandlingView;

@protocol PSPDFKeyboardHandlerDataSource <NSObject>

@property (nonatomic, readonly, nullable) NSArray<PSPDFAnnotation *> *selectedAnnotations;

@end

@protocol PSPDFKeyboardHandlerDelegate <NSObject>

@optional
- (void)keyboardHandlerDidResignKeyboard:(PSPDFKeyboardHandlingView *)keyboardHandler;

/// Fetches the input accessory view from the delegate.
@property (nonatomic, readonly, nullable) UIView *inputAccessoryView;

@end

/// Used to control keyboard showing/hiding.
PSPDF_APP_CLASS_SWIFT(KeyboardHandlingView)
@interface PSPDFKeyboardHandlingView : UIView

/// Data source - helps in deciding who should get the focus.
@property (nonatomic, weak) id<PSPDFKeyboardHandlerDataSource> dataSource;

/// Registers a delegate. The last delegate to register will receive all delegate messages from the receiver
- (void)registerKeyboardDelegate:(id<PSPDFKeyboardHandlerDelegate>)delegate;

/// Unregisters a delegate from the receiver. The view will no longer send any messages to `delegate`.
- (void)unregisterKeyboardDelegate:(id<PSPDFKeyboardHandlerDelegate>)delegate;

/// Registers the delegate, and makes the receiver the first responder (or the text view if keyboard was up)
- (void)activateKeyboardWithDelegate:(id<PSPDFKeyboardHandlerDelegate>)delegate;

/// If delegate still matches, resign.
- (void)resignKeyboardWithDelegate:(id<PSPDFKeyboardHandlerDelegate>)delegate;

/// Returns YES if the keyboard is visible.
@property (nonatomic, getter=isKeyboardVisible, readonly) BOOL keyboardVisible;

@end

NS_ASSUME_NONNULL_END
