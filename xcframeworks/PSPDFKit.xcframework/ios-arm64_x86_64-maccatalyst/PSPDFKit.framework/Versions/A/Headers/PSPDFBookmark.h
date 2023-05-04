//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFModelObject.h>
#import <PSPDFKit/PSPDFOverridable.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAction;

/// A bookmark encapsulates a PDF action and a name. It is managed by a document's
/// bookmark manager.
///
/// @see BookmarkManager
PSPDF_CLASS_SWIFT(Bookmark)
@interface PSPDFBookmark : PSPDFModel<NSCopying, NSMutableCopying, PSPDFOverridable>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initialize with an action object.
///
/// @note Subclassing: This might not be called when bookmarks are created internally from the PDF.
- (nullable instancetype)initWithAction:(PSPDFAction *)action NS_DESIGNATED_INITIALIZER;

/// Initialize a bookmark that was previously serialized with a coder.
///
/// @param aDecoder The decoder to decode the bookmark data.
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/// The PDF action. Usually this will be of type `PSPDFGoToAction`, but all action types are possible.
@property (nonatomic, copy, readonly) PSPDFAction *action;

/// A bookmark can have a name. This is optional.
@property (nonatomic, copy, readonly, nullable) NSString *name;

/// Contains the name of the bookmark or, if the bookmark does not have a valid name,
/// a default name.
@property (nonatomic, readonly) NSString *displayName;

@end

PSPDF_CLASS_SWIFT(MutableBookmark)
@interface PSPDFMutableBookmark : PSPDFBookmark

/// The PDF action. Usually this will be of type `PSPDFGoToAction`, but all action types are possible.
@property (nonatomic, copy) PSPDFAction *action;

/// A bookmark can have a name. This is optional.
@property (nonatomic, copy, nullable) NSString *name;

@end

/// The ProviderSupport category gives you access to some internal properties that
/// are needed when writing a custom `BookmarkProvider` that stores bookmarks
/// in a database.
///
/// If possible, use the `NSCoding` support provided by `Bookmark` to store and
/// read bookmarks as in this case the bookmark ensures to properly store all internal
/// states and migrate old versions of it automatically.
///
/// If this is not possible, the methods in this category provide you with some properties
/// that need to be stored together with the other informations to properly restore
/// a bookmark. Treat all properties in this category as opaque values and do not make
/// any assumptions about what a value may or may not contain. Do not create such values
/// on your own, only restore what you previously got from an instance of `Bookmark`.
@interface PSPDFBookmark (ProviderSupport)

/// A string uniquely identifying the bookmark.
///
/// Two bookmarks with an equal identifier are considered equal.
///
/// @note You should treat this as an opaque value and don't make any assumptions about
/// it. This property is just meant for custom bookmark providers to properly
/// store a bookmark.
@property (nonatomic, readonly) NSString *identifier;

/// A number used for the custom sorting option.
///
/// @note You should treat this as an opaque value and don't make any assumptions about
/// it. This property is just meant for custom bookmark providers to properly
/// store a bookmark.
@property (nonatomic, readonly, nullable) NSNumber *sortKey;

/// Initializes a new bookmark with the given identifier, action, name and sort key.
///
/// This initializer is meant to be used from inside a bookmark provider only, when
/// loading bookmarks.
///
/// @warning Only pass values into the `identifier` and `sortKey` initializer that
/// you previously got from another bookmark during a save operation. Passing
/// other values to this identifier leads to undefined behavior.
///
/// @param identifier The identifier of a bookmark, previously read from a bookmark's `identifier` property.
/// @param action The action the bookmark executes when selected.
/// @param name The name of the bookmark or `nil` if the bookmark does not have a name.
/// @param sortKey The sortKey of a bookmark, previously read from a bookmark's `sortKey` property or `nil`.
- (instancetype)initWithIdentifier:(NSString *)identifier action:(PSPDFAction *)action name:(nullable NSString *)name sortKey:(nullable NSNumber *)sortKey;

@end

NS_ASSUME_NONNULL_END
