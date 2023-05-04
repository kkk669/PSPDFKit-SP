//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFLinkAnnotation;

/// Notification. Posted when the `contentState` of a `PSPDFGalleryItem` changes.
PSPDF_EXPORT NSNotificationName const PSPDFGalleryItemContentStateDidChangeNotification;

typedef NS_CLOSED_ENUM(NSUInteger, PSPDFGalleryItemContentState) {
    /// The item is waiting to load its content.
    PSPDFGalleryItemContentStateWaiting,

    /// The item is currently loading its content.
    PSPDFGalleryItemContentStateLoading,

    /// The item's content is ready.
    PSPDFGalleryItemContentStateReady,

    /// The item has encountered an error while loading its content.
    PSPDFGalleryItemContentStateError
} PSPDF_ENUM_SWIFT(GalleryItem.ContentState);

/// Returns a string from `PSPDFGalleryItemContentState`.
PSPDF_EXPORT NSString *NSStringFromPSPDFGalleryItemContentState(PSPDFGalleryItemContentState state);

/// The abstract class for an item in a gallery. Most items will have content that needs to be loaded,
/// hence this class allows for asynchronous state changes. It is the responsibility of the subclass
/// to implement loading, for example by implementing the `PSPDFRemoteContentObject` protocol.
PSPDF_CLASS_SWIFT(GalleryItem)
@interface PSPDFGalleryItem : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

// MARK: Item Properties

/// The content URL of the item.
@property (nonatomic, readonly) NSURL *contentURL;

/// The caption of the item.
@property (nonatomic, readonly, nullable) NSString *caption;

/// Available Keys used in the `option` dictionary of PSPDFGalleryItem.
typedef NSString *PSPDFGalleryOption NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(GalleryItem.Option);

/// The options dictionary of the item. Subclasses should implement dedicated setters to access the supported options.
@property (nonatomic, readonly) NSDictionary<PSPDFGalleryOption, id> *options;

// MARK: Content

/// The state of the item's content. Defaults to `PSPDFGalleryItemContentStateWaiting`.
@property (nonatomic, readonly) PSPDFGalleryItemContentState contentState;

/// The content of the item. Defaults to `nil`.
@property (nonatomic, readonly, nullable) id content;

/// Indicates if the content of contentURL is considered valid.
@property (nonatomic, readonly, getter=hasValidContent) BOOL validContent;

/// The error that occurred while loading the content. Only valid if `contentState`
/// is `PSPDFGalleryItemContentStateError`.
///
/// @note This property is not related to the error pointer that can be provided when creating
/// an `PSPDFGalleryItem`.
@property (nonatomic, readonly, nullable) NSError *error;

/// The progress of loading the content. Only valid if `contentState`
/// is `PSPDFGalleryItemContentStateLoading`.
@property (nonatomic, readonly) CGFloat progress;

// MARK: Creating Items

/// Factory method to create an array of items from JSON data. Returns `nil` in case of an error.
///
/// @warning This method may return unresolved gallery items of type `PSPDFGalleryUnknownItem`. It
/// may also not support all features of the gallery. You are strongly encouraged to use
/// `PSPDFGalleryManifest` to instantiate gallery items!
+ (nullable NSArray<PSPDFGalleryItem *> *)itemsFromJSONData:(NSData *)data error:(NSError **)error;

/// Factory method that creates a single gallery item directly from a link annotation.
/// Returns `nil` in case of an error.
///
/// @warning This method may return unresolved gallery item of type `PSPDFGalleryUnknownItem`. It
/// may also not support all features of the gallery. You are strongly encouraged to use
/// `PSPDFGalleryManifest` to instantiate gallery items!
+ (nullable PSPDFGalleryItem *)itemFromLinkAnnotation:(PSPDFLinkAnnotation *)annotation error:(NSError **)error;

/// Available Keys used create a dictionary for initializing PSPDFGalleryItem. Constants correspond to the PSPDFGalleryItem properties.
typedef NSString *PSPDFGalleryItemProperty NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(GalleryItem.Property);

/// Creates an item from a given dictionary. The dictionary will usually be parsed JSON.
///
/// @warning This method triggers an assertion if `contentURL` is invalid.
/// @note This is the designated initializer.
- (instancetype)initWithDictionary:(NSDictionary<PSPDFGalleryItemProperty, id> *)dictionary NS_DESIGNATED_INITIALIZER;

/// Creates an item with the given `contentURL`, `caption` and `options`.
/// `contentURL` is required.
/// `option` takes `PSPDFGalleryItem*` keys.
- (instancetype)initWithContentURL:(NSURL *)contentURL caption:(nullable NSString *)caption options:(nullable NSDictionary<PSPDFGalleryOption, id> *)options;

// MARK: Options

/// Indicates if the playback controls should be visible. Defaults to `true`.
@property (nonatomic) BOOL controlsEnabled;

/// Indicates if the content can be presented fullscreen. Defaults to `true`.
@property (nonatomic, getter=isFullscreenEnabled) BOOL fullscreenEnabled;

@end

// MARK: PSPDFGalleryItem Dictionary Keys

/// String. The type of an item.
PSPDF_EXPORT PSPDFGalleryItemProperty const PSPDFGalleryItemPropertyType;

/// String. The content URL of an item.
PSPDF_EXPORT PSPDFGalleryItemProperty const PSPDFGalleryItemPropertyContentURL;

/// String. The caption of an item.
PSPDF_EXPORT PSPDFGalleryItemProperty const PSPDFGalleryItemPropertyCaption;

/// String. The options of an item.
PSPDF_EXPORT PSPDFGalleryItemProperty const PSPDFGalleryItemPropertyOptions;

// MARK: Options

/// Boolean. Indicates if the content should automatically start playing.
PSPDF_EXPORT PSPDFGalleryOption const PSPDFGalleryOptionAutoplay;

/// Boolean. Indicates if controls should be displayed.
PSPDF_EXPORT PSPDFGalleryOption const PSPDFGalleryOptionControls;

/// Boolean. Indicates if the content should loop forever.
PSPDF_EXPORT PSPDFGalleryOption const PSPDFGalleryOptionLoop;

/// Boolean. Indicates that the content can be presented fullscreen.
PSPDF_EXPORT PSPDFGalleryOption const PSPDFGalleryOptionFullscreen;

NS_ASSUME_NONNULL_END
