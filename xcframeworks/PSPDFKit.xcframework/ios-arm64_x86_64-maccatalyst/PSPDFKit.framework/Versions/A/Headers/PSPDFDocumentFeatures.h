//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <Foundation/Foundation.h>
#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFDocument, PSPDFDocumentFeatures;

NS_ASSUME_NONNULL_BEGIN

typedef SEL PSPDFDocumentFeature;
#define PSPDFDocumentFeatureMake(feature) @selector(feature)


/// A document feature source can disable various features if there are reasons within
/// its controlled scope that make this feature unavailable.
///
/// You can implement your own sources by conforming to this protocol. Besides the
/// required methods you should only implement the features that your source actually
/// control. The result of your source will be combined with the results of the framework's
/// sources through a logical AND. This means if your source disallows a feature this
/// feature is no longer available, however if your source allows a feature there might
/// still be other sources disallowing a feature. Only if all sources allow a feature,
/// the feature will be enabled.
///
/// # Caching
///
/// The results of all features you implement will be cached. Whenever the state of
/// a feature changes, you need to call `[features updateFeatures]` for changes to
/// take effect. This is also necessary to allow notifying interested observers about
/// the change in state.
///
/// # Threading
///
/// Your custom sources have to be thread safe. They are not guaranteed to be called
/// on any particular queue.
PSPDF_PROTOCOL_SWIFT(PDFDocumentFeaturesSource)
@protocol PSPDFDocumentFeaturesSource <NSObject>

/// A back reference to the `PSPDFDocumentFeatures` instance that owns this source.
///
/// You can use this reference when implementing you own custom sources to call `updateFeatures`
/// on it whenever a feature changes its state.
///
/// Ensure this is implemented as a weak property, otherwise you will have a memory leak
/// due to a retain cycle.
@property (nonatomic, weak) PSPDFDocumentFeatures *features;

@optional

/// Specifies whether the document this feature belongs to can be modified.
@property (nonatomic, readonly) BOOL canModify;

/// Specifies whether bookmarks can be added, removed or edited in the document this
/// feature belongs.
@property (nonatomic, readonly) BOOL canEditBookmarks;

/// Specifies whether the document can be printed on this device.
@property (nonatomic, readonly) BOOL canPrint;

/// Specifies whether annotation replies should be shown.
///
/// Disabling showing replies also disables showing annotation reviews.
@property (nonatomic, readonly) BOOL canShowAnnotationReplies;

/// Specifies whether annotation reviews should be shown.
///
/// Reviews are one of these author states: accepted, rejected, cancelled, or completed.
///
/// This feature will be never be enabled if the `canShowAnnotationReplies` feature is disabled.
@property (nonatomic, readonly) BOOL canShowAnnotationReviews;

/// Specifies whether the user can add, rotate, or delete pages.
@property (nonatomic, readonly) BOOL canUseDocumentEditor;

/// Specifies whether the user can fill interactive forms.
@property (nonatomic, readonly) BOOL canFillForms;

/// Specifies whether the user can add or modify annotations.
///
/// Returning `false` is equivalent to setting `PSPDFConfiguration.editableAnnotationTypes` to `nil`.
///
/// The user will still be able to fill forms if `canFillForms` is `true`, even if `canEditAnnotations` is `false`.
@property (nonatomic, readonly) BOOL canEditAnnotations;

/// Specifies whether the user can extract text and images from the document.
///
/// If `false`, the user won't be able to copy or share selected text or images.
@property (nonatomic, readonly) BOOL canExtractTextAndImages;

@end


/// An observer will be returned to you when you start observing a feature for state
/// changes. You can either keep the observer around for removing it later on or you
/// can bind it to the lifetime of another class which will then remove the observer
/// automatically when the other object gets deallocated.
PSPDF_PROTOCOL_SWIFT(PDFDocumentFeaturesObserver)
@protocol PSPDFDocumentFeaturesObserver <NSObject>

/// Instead of retaining the observer yourself to be able to later on remove the observer
/// again you can also bind it to the lifetime of another object so that the observer
/// is automatically removed when this object gets deallocated.
///
/// @note This is not guaranteed to be thread safe: if the object is being deallocated
/// while observers are being called, the call registered with this observer
/// might get called again but the observer will be removed at some point.
/// @param object The object to bind the observer's lifetime to.
- (void)bindToObjectLifetime:(id)object;

@end


/// PSPDFDocumentFeatures provides the main interface for querying features and registering
/// observers.
///
/// It conforms to `PSPDFDocumentFeaturesSource` itself, but additionally to the document
/// features source protocol it also guarantees that it implements all methods of this
/// protocol. Therefore it is save to query every feature on an instance of this class
/// without checking its availability for.
///
/// Usually you access this class through `Document`'s `features` property. So
/// if you, for example, want to check if a document can be modified, you can check
/// `document.features.canModify`.
///
/// @see `-[PSPDFDocument features]`
///
/// # Threading
///
/// `PSPDFDocumentFeatures` is thread safe and can be used from any thread. This also
/// means that your custom sources will be called from various threads and queues.
/// Do not rely on being called on a particular thread in your custom sources.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(PDFDocumentFeatures)
@interface PSPDFDocumentFeatures : NSObject <PSPDFDocumentFeaturesSource>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes a document feature for a given document.
///
/// Usually you do not initialize this yourself but instead use the features provided
/// to you by the document, but you can create your own instance of this if you like.
///
/// @param document The document this features set is created for.
- (instancetype)initWithDocument:(PSPDFDocument *)document NS_DESIGNATED_INITIALIZER;

/// The document this class was initialized with.
@property (atomic, weak, readonly) PSPDFDocument *document;

// MARK: Managing Custom Sources

/// Adds custom sources to the document features. These sources will be taken into
/// account for all features they implement.
///
/// @param sources The sources to add to the list of sources.
- (void)addSources:(NSArray<id<PSPDFDocumentFeaturesSource>> *)sources;

/// Removes custom sources from the document features.
///
/// @param sources Sources to remove from the list of sources.
- (void)removeSources:(NSArray<id<PSPDFDocumentFeaturesSource>> *)sources;

/// Updates the cache of the states of features.
///
/// If you add a custom source and the state of a feature changes in this source, you
/// must call `updateFeatures` on the `features` object assigned to the source to tell
/// it that a feature changed. Otherwise this change might not be reflected in the
/// value returned when checking the state of a feature.
- (void)updateFeatures;

// MARK: Observing Features

/// Add an observer for the given feature. Each time the feature's value changes the
/// update handler is invoked.
///
/// You should retain the returned observer to be able to remove the observer again
/// later. Alternatively you can bind the observer to the lifetime of an object by
/// calling `bindToObjectLifetime` on it. Doing neither of these will result in an
/// observer that is not removable and that will continue calling your update handler
/// until the receiver itself gets deallocated.
///
/// @note You can only add observers for features that don't require any arguments.
/// @warning Modifying observers inside an update handler will result in a deadlock.
/// @param feature The feature to observe.
/// @param handler The handler to be called when the feature's state changes.
/// @return An observer object you can use to unregister the observer again.
- (id<PSPDFDocumentFeaturesObserver>)addObserverForFeature:(PSPDFDocumentFeature)feature updateHandler:(void(^)(BOOL value))handler;

/// Removes an observer previously added through `addObserverForFeature:updateHandler:`.
///
/// @param observer The observer to remove.
- (void)removeObserver:(id<PSPDFDocumentFeaturesObserver>)observer;

// MARK: Debugging

/// Outputs in the console which sources allow or disallow the feature passed in.
///
/// @note This only works for features that do not require any arguments.
/// @param selector The selector you would call to access this feature.
- (void)traceFeature:(SEL)selector;

@end

NS_ASSUME_NONNULL_END
