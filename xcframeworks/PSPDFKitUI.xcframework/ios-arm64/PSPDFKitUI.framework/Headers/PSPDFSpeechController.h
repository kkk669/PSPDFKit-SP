//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString *PSPDFSpeechControllerOption NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(SpeechController.Option);

/// Automatically tries to detect the language.
PSPDF_EXPORT PSPDFSpeechControllerOption const PSPDFSpeechControllerOptionAutoDetectLanguage;

/// Force a specific language. Value is expected to be a BCP-47 language string.
PSPDF_EXPORT PSPDFSpeechControllerOption const PSPDFSpeechControllerOptionLanguage;

/// Provide text to sample a language. Value is expected to be a string.
/// Typically 200-400 characters are required to reliably guess the language of a string.
/// Language-detection can differ depending on platform and os version and relies on built-in helpers such as `NLLanguageRecognizer`.
PSPDF_EXPORT PSPDFSpeechControllerOption const PSPDFSpeechControllerOptionLanguageHint;

/// Controls text-to-speech features.
///
/// @note This class can only be used from the main thread.
///
/// Voice availability depends on user settings, platform and os version.
/// High-quality voices might need to be manually downloaded
/// https://support.apple.com/en-us/HT203077
///
/// Voice selection uses `[AVSpeechSynthesisVoice voiceWithLanguage:]`.
/// This will return enhanced quality voice if available, default quality otherwise.
///
/// The Siri isn't part of the voice selection list, Apple has "no plan to change" this. (rdar://42656565)
PSPDF_CLASS_SWIFT(SpeechController)
@interface PSPDFSpeechController : NSObject

/// Speaks the given string.
/// Will use the default system language, unless otherwise configured in `options`.
///
/// @note Must be called on main thread. Delegate calls always happen on the main thread.
- (void)speakText:(NSString *)speechString options:(nullable NSDictionary<PSPDFSpeechControllerOption, id> *)options delegate:(nullable id<AVSpeechSynthesizerDelegate>)delegate;

/// If this delegate is set, stop current text.
- (BOOL)stopSpeakingForDelegate:(nullable id<AVSpeechSynthesizerDelegate>)delegate;

/// The internally used speech synthesizer.
@property (nonatomic, readonly) AVSpeechSynthesizer *speechSynthesizer;

/// Speech language. Defaults to `PSPDFSpeechSynthesizerAutoDetectLanguage`.
@property (nonatomic, copy) NSString *selectedLanguage;

/// Available language codes, use for `selectedLanguage`.
@property (nonatomic, copy, readonly) NSArray<NSString *> *languageCodes;

/// Speech rate. Defaults to AVSpeechUtteranceDefaultSpeechRate.
@property (nonatomic) float speakRate;

/// Speech pitch. Defaults to 1.0.
@property (nonatomic) float pitchMultiplier;

@end

NS_ASSUME_NONNULL_END
