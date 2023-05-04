//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation.h>
#import <PSPDFKit/PSPDFOverridable.h>

#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

/// List of available encodings. Used in `PSPDFSoundAnnotation.encoding`.
typedef NSString *PSPDFSoundAnnotationEncoding NS_TYPED_ENUM NS_SWIFT_NAME(SoundAnnotation.Encoding);

PSPDF_EXPORT PSPDFSoundAnnotationEncoding const PSPDFSoundAnnotationEncodingRaw;
PSPDF_EXPORT PSPDFSoundAnnotationEncoding const PSPDFSoundAnnotationEncodingSigned;
PSPDF_EXPORT PSPDFSoundAnnotationEncoding const PSPDFSoundAnnotationEncodingMuLaw;
PSPDF_EXPORT PSPDFSoundAnnotationEncoding const PSPDFSoundAnnotationEncodingALaw;

@class PSPDFSoundAnnotationController;

/// A sound annotation (PDF 1.2) shall analogous to a text annotation except that instead of a text
/// note, it contains sound recorded from the iOS device's microphone or imported from a file.
///
/// To ensure maximum compatibility set the `boundingBox` for sound annotations to the same size Adobe Acrobat uses (20x15pt).
/// PSPDFKit will always render sound annotations at a fixed size of 74x44pt, centered in the provided `boundingBox`.
///
/// @note Make sure you configured Microphone Permissions in your app.
/// See https://pspdfkit.com/guides/ios/getting-started/permissions/#toc_microphone-permissions for further documentation.
PSPDF_CLASS_SWIFT(SoundAnnotation)
@interface PSPDFSoundAnnotation : PSPDFAnnotation<PSPDFOverridable>

/// The annotation controller.
@property (atomic, readonly) PSPDFSoundAnnotationController *controller;

// MARK: Customizing the Appearance

/// The sound icon name.
@property (atomic, copy, nullable) NSString *iconName;

// MARK: Determining Capabilities

/// Determines if recording annotations are available.
///
/// Recording sound annotations are not available in all environments. E.g. when
/// running inside an App Extension, sound annotations are unavailable as microphone
/// access is disabled.
///
/// @see -initWithRecorderOptions:
///
/// @return `true` if sound annotations are available, `false` otherwise.
@property (nonatomic, class, readonly) BOOL recordingAnnotationAvailable;

/// If the annotation is able to record audio
@property (atomic, readonly) BOOL canRecord;

// MARK: Accessing the Audio Metadata

/// The number of bits per sample value per channel. Default value: 16.
/// 8 or 16 bits per channel are supported.
@property (atomic, readonly) NSUInteger bits;

/// The sampling rate, in samples per second.
///
/// Based on the PDF spec, 8000, 11,025, or 22,050 samples per second are most widely supported.
/// Based on empiric testing, 44100 works great as well.
@property (atomic, readonly) NSUInteger rate;

/// The number of sound channels. Default value: 1.
/// The PDF spec supports 1 or 2 channels.
@property (atomic, readonly) NSUInteger channels;

/// Encoding of the sound stream. Use `PSPDFSoundAnnotationEncoding*` for values.
@property (atomic, copy, readonly, nullable) PSPDFSoundAnnotationEncoding encoding;

// MARK: Accessing the Audio Data

/// URL to the sound content.
@property (atomic, copy, readonly, nullable) NSURL *soundURL;

/// Loads bits, sample rate, channels, encoding from sound file.
- (BOOL)loadAttributesFromAudioFile:(NSError **)error;

/// Get the direct sound data.
@property (atomic, readonly, nullable) NSData *soundData;

// MARK: Creating Instances from a Sound File

/// Initializes a sound annotation with the sound file located at the given URL.
///
/// Use this method if you want to initialize a sound annotation that already has an existing sound file.
///
/// @param soundURL The file URL to the sound file.
/// @param error    Upon return contains an error if the creation was not possible.
- (nullable instancetype)initWithURL:(NSURL *)soundURL error:(NSError **)error;

// MARK: Creating Instances by Recording a Sound

/// Initializes an empty sound annotation that can be recorded into.
///
/// Pass `nil` to use the default recording options.
///
/// @warning Calling this initializer will throw an exception if `+recordingAnnotationAvailable`
/// returns `false`. Check this method before calling `-initWithRecorderOptions:`.
///
/// @see +recordingAnnotationAvailable
- (instancetype)initWithRecorderOptions:(nullable NSDictionary<NSString *, id> *)recorderOptions NS_REFINED_FOR_SWIFT;

// MARK: Conversions

/// Returns the supported format identifier that corresponds to the given encoding.
+ (AudioFormatID)audioFormatIDFromEncoding:(nullable PSPDFSoundAnnotationEncoding)encoding;

@end

NS_ASSUME_NONNULL_END
