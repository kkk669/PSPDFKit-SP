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

/// Adds support for defining a hardware keyboard equivalent command for the bar button item.
/// Automatically sets up a key equivalent for `UIBarButtonSystemItemCancel`.
///
/// Key commands are nil-targeted: the first object on the responder chain responding to the selector will handle it.
/// Therefore be careful when naming the action selector of any bar button item with a key equivalent.
@interface PSPDFBarButtonItem : UIBarButtonItem

/// The string of characters corresponding to the keys that must be pressed for this button’s hardware keyboard equivalent command.
@property (nonatomic, copy, nullable) NSString *keyEquivalentInput;

/// The modifier flags of this button’s hardware keyboard equivalent command.
@property (nonatomic) UIKeyModifierFlags keyEquivalentModifierFlags;

/// Creates a key command from the bar button item if a `keyEquivalentInput` has been set, otherwise returns nil.
/// The `UIKeyCommand`'s action is set to the same selector as the receiver.
@property (nonatomic, readonly, nullable) UIKeyCommand *keyCommand;

@end

/// Returns `sender` if `sender` is a view or a bar button item, and if not, returns `fallbackItem`.
PSPDF_APP_EXPORT id PSPDFPresentingSenderOrFallbackItem(id _Nullable sender, UIBarButtonItem *fallbackItem);

NS_ASSUME_NONNULL_END
