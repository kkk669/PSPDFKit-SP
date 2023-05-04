//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFRenderOptions.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString *PSPDFLegacyRenderOption NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(LegacyRenderOption);

/// Applies the non-default values from source to target, and returns a new `PSPDFRenderOptions` instance.
PSPDF_EXPORT PSPDFRenderOptions *PSPDFUpdateTargetRenderOptionsWithUpdatedValuesFromSource(PSPDFRenderOptions * _Nullable target, PSPDFRenderOptions * _Nullable source);

@interface PSPDFRenderOptions ()

/// Used by the `PSPDFRenderManager` (`PSPDFPageRendererPageInfoKey`) to pass page info into the core page renderer.
@property (nonatomic, nullable) NSDictionary<NSString *, id> *extraInfo;

/// MARK: Annotation Drawing

/// Whether we are currently drawing in order to generate a new appearance stream. Defaults to `false`.
///
/// When generating a new appearance stream, we set this property to `true` internally, in order to suppress a potential
/// old value.
@property (nonatomic) BOOL isGeneratingAppearanceStream;

/// Disables the AP stream generator.
///
/// This is needed when the AP stream generator delegates generating an AP stream
/// to core, otherwise we end up in an endless loop.
@property (nonatomic) BOOL disableAPStreamGenerator;

/// Used when rendering annotations in overlay mode to keep the information around whether or not refreshing the
/// completed render should be animated.
@property (nonatomic) BOOL shouldAnimate;

/// Set to `true` to skip the rendering of the annotations text. Defaults to `false`.
@property (nonatomic) BOOL skipTextRendering;

/// Forces the note annotation to draw as text.
@property (nonatomic) BOOL drawNoteAnnotationAsText;

/// Whether the blend mode should be ignored when rendering annotations to avoid dual blending.
@property (nonatomic) BOOL shouldIgnoreAnnotationBlendMode;

// MARK: Debug Options

/// Set to `true` to draw the current absolute tab order in each element. Defaults to `false`.
@property (nonatomic) BOOL drawTabOrder;

/// Debug flag for rendering an annotation for QuickLook.
///
/// Allows overriding or ignoring visibility flags, so that there’s still something to see — even when the annotation is
/// deleted, hidden, etc.
@property (nonatomic) BOOL isRenderingForQuickLook;

// MARK: Text Rendering

/// Whether text objects should be rendered.
/// This should be disabled when text is rendered in a different manner.
/// E.g. this is the case for Content Editing.
/// Enabled by default.
@property (nonatomic) BOOL renderTextObjects;

// MARK: Decoding from the Legacy Format

/// Tries to convert a legacy render options dictionary (PSPDFKit 8.x and below) into a
/// PSPDFRenderOptions object, and returns it.
///
/// @param dictionary The dictionary that contains the legacy keys. See `-[PSPDFDocument initWithCoder:]`.
- (nullable instancetype)initWithLegacyDictionary:(nullable NSDictionary<PSPDFLegacyRenderOption, id> *)dictionary;

/// Returns a set of the classes required for decoding the legacy property map from PSPDFKit 8.x and earlier.
+ (NSSet<Class> *)classesRequiredForDecodingLegacyPropertyMap;

@end

NS_ASSUME_NONNULL_END
