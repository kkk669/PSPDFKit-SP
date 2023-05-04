//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIResponder (PSPDFFoundation)

/// Fast way to find the current first responder.
///
/// This only finds an explicitly set first responder. If this is nil, there may still
/// be a `responderForKeyEvents` that UIKit infers from the view controller hierarchy.
///
/// Usage in lldb: expression -l objc -O -- [UIResponder pspdf_firstResponder]
+ (nullable UIResponder *)pspdf_firstResponder;

/// Checks if the receiver is has an instance of any of the classes in `responderClasses` as a parent in the responder chain.
///
/// @param responderClasses The classes to check for.
/// @return `true` if an instance of any of `responderClasses` is above the receiver in the chain.
- (BOOL)pspdf_isInsideAnyInstanceOfResponderClasses:(NSArray<Class> *)responderClasses;

#if DEBUG
/// Debug feature to print the full responder chain.
///
/// Usage:
/// 
/// (lldb) e (void)[UIResponder pspdf_printResponderChainWithFullDescriptions:YES]
+ (void)pspdf_printResponderChainWithFullDescriptions:(BOOL)withDescriptions;

/// Prints only the class and address of each object on the responder chain.
///
/// Usage:
///
/// (lldb) e (void)[UIResponder pspdf_printResponderChain]
+ (void)pspdf_printResponderChain;

/// Prints the responder chain, and after each responder it prints all key commands from that responder, alongside which
/// responder would end up receiving each action of the key commands
///
/// Usage:
///
/// (lldb) e (void)[UIResponder pspdf_printKeyCommandsOnResponderChain]
+ (void)pspdf_printKeyCommandsOnResponderChain;
#endif

@end

@interface UIView (PSPDFFirstResponder)

/// Finds the first responder if it's inside a subview.
@property (nonatomic, readonly, nullable) UIView *pspdf_firstResponderInsideView;

/// Checks if the first responder is a text input.
///
/// This method only returns true for native text inputs. E.g. it returns `false` for
/// text input inside a web view.
@property (nonatomic, readonly) BOOL pspdf_firstResponderIsTextInput;

@end

/// This is a workaround for the unfortunate way UIKit decides between text input and UIKeyCommands.
///
/// On iOS 14 and earlier, key commands from the responder chain take precedence over sending the event to a
/// UITextField or UITextView. This function is a best effort to return an array by removing items from the
/// input so that the key commands do not conflict with text input. Call this in an implementation of keyCommands
/// when you don’t know whether text input is happening and you don’t want to interfere with text editing.
///
/// Do not call this function if you do want your commands to take precedence over text input.
///
/// This is mostly not needed on iOS 15 and later because by default text input takes precedence over key
/// commands. However some key commands like arrow keys need to have wantsPriorityOverSystemBehavior set
/// to YES in order to have priority over the UIKit focus system, but this undesirably also grants them
/// priority over text input, so we may still need to apply manual filtering.
///
/// @param commands The proposed key commands.
/// @return Filtered input to exclude commands that would interfere with text input.
PSPDF_EXTERN NSArray<UIKeyCommand *> *PSPDFKeyCommandsByRemovingTextInputConflictsIfRequired(NSArray<UIKeyCommand *> *commands) NS_SWIFT_NAME(KeyCommandsByRemovingTextInputConflictsIfRequired(_:));

NS_ASSUME_NONNULL_END
