//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFAnnotationPlaceholder.h>

@class PSPDFAnnotation;

NS_ASSUME_NONNULL_BEGIN

@protocol PSPDFAnnotationPlaceholderContentResolver <NSObject>

/// Tells the receiver that it should begin resolving the actual content for the placeholder.
///
/// When implementing this method, you should either call `beginWithProgress:` or `failWithError:` at
/// some point.
- (void)resolveContentForAnnotationPlaceholder:(PSPDFAnnotationPlaceholder *)placeholder;

/// Requests a replacement for the given placeholder, and cancellation of its running resolution.
///
/// @return A new placeholder in the initial state that shall replace the sender, which has reached its end of life.
- (nullable PSPDFAnnotationPlaceholder *)cancelContentResolutionForAnnotationPlaceholder:(PSPDFAnnotationPlaceholder *)placeholder error:(NSError **)error;

/// Requests a replacement for the given placeholder, in order to retry content resolution.
///
/// @return A new placeholder to replace the failed sender, which has reached its end of life, so that
/// content resolution can be retried.
- (nullable PSPDFAnnotationPlaceholder *)retryContentResolutionForAnnotationPlaceholder:(PSPDFAnnotationPlaceholder *)placeholder error:(NSError **)error;

@end

@interface PSPDFAnnotationPlaceholder ()

/// Designated initializer
///
/// Sets up an idle placeholder with some content to be displayed while the actual content isn’t
/// available.
- (instancetype)initWithPlaceholderContentIcon:(UIImage *)contentIcon forAnnotation:(PSPDFAnnotation *)annotation contentResolver:(id<PSPDFAnnotationPlaceholderContentResolver>)contentResolver NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly) PSPDFAnnotation *annotation;

/// The object responsible for resolving the actual content.
@property (nonatomic, readonly, weak) id<PSPDFAnnotationPlaceholderContentResolver> contentResolver;

/// Associates an action name with the given state.
///
/// Call this method repeatedly to associate appropriate titles for any state that should have an
/// interaction.
- (void)setLocalizedAction:(nullable NSString *)actionName forState:(PSPDFAnnotationPlaceholderState)state;

/// Atomically transitions the receiver to state `PSPDFAnnotationPlaceholderStateProgressing` and
/// populates its `progress` property.
///
/// You should call this when implementing `resolveContentForAnnotationPlaceholder:`, once you’ve
/// successfully started to resolve the content. E.g. fired off the network request to fetch it.
///
/// @warning Shall only be called on an object in state `PSPDFAnnotationPlaceholderStateIdle`!
- (void)beginWithProgress:(NSProgress *)progress;

/// Atomically transitions the receiver to state `PSPDFAnnotationPlaceholderStateFailed` and populates
/// its `error` property.
///
/// This method _may_ update the `contentIcon` property.
///
/// You should call this method in `resolveContentForAnnotationPlaceholder:` when you cannot start
/// resolving the content, or when a successfully started resolution fails (e.g. the network connection
/// drops while you are still receiving data).
///
/// When you call this method, expect a call to `retryContentResolutionForAnnotationPlaceholder:error:`
/// — possibly even before the method returns!
///
/// @warning Shall only be called on an object in states `PSPDFAnnotationPlaceholderStateIdle` or
/// `PSPDFAnnotationPlaceholderStateProgressing`!
- (void)failWithError:(NSError *)error;

/// Atomically transitions the receiver to state `PSPDFAnnotationPlaceholderStateCompleted`.
///
/// @warning Shall only be called on an object in state `PSPDFAnnotationPlaceholderStateProgressing`!
- (void)complete;

@end

NS_ASSUME_NONNULL_END
