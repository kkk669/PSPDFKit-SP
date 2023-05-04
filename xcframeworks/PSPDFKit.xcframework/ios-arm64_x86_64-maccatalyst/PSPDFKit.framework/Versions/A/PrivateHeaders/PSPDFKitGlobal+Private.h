//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFKitGlobal.h>
#import <PSPDFKit/PSPDFMacros+Private.h>
#import <PSPDFKit/PSPDFRenderManager+Private.h>

// feature flags
#define PSPDFEnableShapeAnnotationHost 1 // Enables faster annotation editing for shapes.
#define PSPDFAllowDownloadableFonts 1 // Enable lookup for unknown fonts on Apple's servers.

// debug flags
#define PSPDFTextGlyphDebug 0 // Show all glyphs.
#define PSPDFTestExternalURLsInTheSimulator 0 // Allows better action Simulator testing.

@class PDFCFilesCache, PSPDFAudioSessionManager, PSPDFCorePageRenderer, PSPDFShapeDetector;
@protocol PSPDFAppKitObjcBridge;

NS_ASSUME_NONNULL_BEGIN

/// Set before the framework is initialized. Will require more memory but operates faster.
/// Right now this is basically a mode that makes the iPad 3 faster.
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFSettingKeyFastMemoryMode;

/// Shows colors and borders for the scroll views.
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFSettingKeyDebugScrollViews;

/// Annotations have a border and better visualize rotation.
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFSettingKeyAnnotationXRay;

/// Can be used to slow down PDF rendering.
/// This must be set via subscript access or KVC. It can’t be set in `setLicenseKey:options:`.
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFSettingKeyDelayPDFRenderingInSeconds;

/// Will result in faster ink annotation rendering.
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFSettingKeyReduceInkAnnotationRenderQuality;

/// Hides alerts such as the status bar configuration alert.
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFSettingKeySuppressDevelopmentWarningAlerts;

/// NSNumber; saves the minimum search length. Defaults to 1.
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFSettingKeyMinimumSearchLength;

/// Default image compression key when saved via appearance streams. Defaults to 0.8.
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFSettingKeyDefaultImageCompression;

/// May be used to put the PSPDFKit.bundle into a different folder or even rename it.
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFSettingKeyResourceBundlePath;

/// Specifies a limit of how big a image we will try to load. Defaults to 0.25 of the physical memory. Valid values are 0. to 1.
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFSettingKeyMaxImageMemoryLimit;

/// This key can be used to always send statistics, even though the license would not require it.
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFSettingKeySendStatistics;

/// Specifies the Hybrid environment PSPDFKit should be running on.
/// In addition to this key, the current hybrid technology is dynamically detected as well.
/// This option is used as a tie-breaker when we detect multiple hybrid technologies.
///
/// @note This option is set by our hybrid SDKs.
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFSettingKeyHybridEnvironment;

/// Enables JavaScript processing. Set to @YES by default.
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFSettingKeyJavaScriptEnabled;

/// Set to an string specifying the path to the loaded image in which the SQLite you want PSPDFKit to use is statically linked.
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFSettingKeySQLiteImagePath;

/// Defines the render extension size as `CGSize` packed in an `NSValue` box.
/// Values should be the same for width and height to better compensate against rotation
///
/// Example: PSPDFKitGlobal.sharedInstance[@"com.pspdfkit.render-view-extension-size"] = @(CGSizeMake(400, 400));
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFSettingKeyRenderViewExtensionSize;

/// Enables read copies for conflict resolution for coordinated file provider instances created by PSPDFDocument.
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFSettingKeyReadCopiesEnabled;

/// Disable resigning of first responder status when pages move offscreen.
/// Setting this key re-introduces: https://openradar.appspot.com/39604024
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFSettingKeyDisableCollectionViewFirstResponderResign;

/// Forces the legacy color picker on OS versions where `UIColorPickerViewController` is available.
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFForceUseLegacyColorPicker;

/// Forces the more limited signature UI that was previously included as part of Annotations.
/// This can be given to customers if they accidentally upgraded from the older signature UI
/// to Electronic Signatures but then they find they find they like the older UI better for some reason.
/// It’s also appropriate if an existing customer buys a new license (new bundle ID) in May 2021
/// or later and wants it work work the same as their other license bought in April 2021 or earlier.
/// The license must include Electronic Signatures for this option to be useful. Using this option if the
/// license doesn’t have Annotations is completely untested so ensure the customer also has that feature.
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFForceUseLegacySignatureFeature;

/// Controls if touch prediction for drawing is used. Expects a (wrapped) boolean.
///
/// Touch prediction is a feature that can create additional touches based on mathematical models to create the illusion of an even more responsive touch processing.
///
/// This feature is enabled by default and especially effective on modern hardware
/// (iPad Pro/Apple Pencil)
///
/// Learn more here:
/// - https://developer.apple.com/videos/play/wwdc2015/233/
/// - https://developer.apple.com/videos/play/wwdc2016/220/
/// - https://developer.apple.com/reference/uikit/uievent/1613814-predictedtouches
/// - https://developer.apple.com/library/prerelease/content/samplecode/TouchCanvas/Introduction/Intro.html
/// - https://developer.apple.com/library/prerelease/content/samplecode/SpeedSketch/Introduction/Intro.html
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFSettingKeyTouchPredictionDisabled;

/// Set this key to YES to disable render cancellation calls.
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFSettingKeyRenderCancellationDisabled;

/// Set this key to NO to disable multi-document rendering.
/// This must be set via subscript access or KVC. It can’t be set in `setLicenseKey:options:`.
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFSettingKeyMultiDocumentRenderingDisabled;

/// Disables accessing the actual UIPasteboard when we have internal alternatives.
/// This is useful as the Simulator sometimes freezes when accessing the pasteboard as of iOS 13.
PSPDF_APP_EXPORT PSPDFSettingKey const PSPDFSettingKeyConcretePasteboardDisabled;

@interface PSPDFKitGlobal ()

@property (atomic, class, readonly) NSUInteger instantCompatibilityNumber;

/// Helper for registration checks.
+ (BOOL)boolForKey:(NSString *)key;

/// The audio session manager.
@property (nonatomic, readonly) PSPDFAudioSessionManager *audioSessionManager;

/// File cache used by multimedia additions.
@property (nonatomic, readonly, nullable) PDFCFilesCache *fileCache;

/// File manager variant that uses a file coordinator.
@property (nonatomic, readonly) id<PSPDFFileManager> coordinatedFileManager;

/// Either the same as `fileManager` or `coordinatedFileManager`,
/// based on the value of `PSPDFSettingKeyFileCoordinationEnabled`.
@property (nonatomic, readonly) id<PSPDFFileManager> defaultFileManager;

/// Page renderer
@property (nonatomic, readonly) PSPDFCorePageRenderer *renderer;

/// The render manager for internal use.
@property (nonatomic, readonly) id<PSPDFRenderManagerPrivate> privateRenderManager;

/// The shape detector that is used to transform drawings into annotations by the Magic Ink tool.
@property (atomic, null_resettable) PSPDFShapeDetector *shapeDetector;

/// Returns the framework bundle version. (e.g. 60910 for version 6.9.1)
@property (atomic, class, readonly) NSUInteger bundleVersion;

#if TARGET_OS_MACCATALYST
/// Model-related macOS code wrapper for Mac Catalyst
@property (nonatomic, readonly) id<PSPDFAppKitObjcBridge> appKitBridge;
#endif

@end

@interface PSPDFKitGlobal (TestVisibility)

/// Resets the internal option dictionary.
///
/// @note Only required for testing.
- (void)resetSettingsWithOptions:(nullable NSDictionary<PSPDFSettingKey, id> *)options;

/// Ensures all thread operations are cancelled and optionally also waits until teardown is complete.
/// Use this to better isolate tests to ensure a background crash does not affect another test
///
/// @note Only required for testing.
/// However might also be something we give to customers as they will face the same issue.
- (void)cancelThreadOperationsAndWait:(BOOL)wait;

/// Waits for render thread operations to finish for up to `seconds`.
- (void)waitForThreadOperationsToFinishWithTimeout:(NSTimeInterval)seconds;

/// Show alert if a debugger is attached and unless `PSPDFSettingKeySuppressDevelopmentWarningAlerts` is set.
+ (BOOL)alertOnDevelopmentBuildWithTitle:(nullable NSString *)title message:(nullable NSString *)message;

@end

/// Evaluates if devices is modern enough to support proper animation.
PSPDF_SDK_EXPORT BOOL PSPDFShouldAnimate(void) NS_SWIFT_NAME(ShouldAnimate());

/// Feature checks.
PSPDF_TEST_EXPORT BOOL PSPDFIsFeatureEnabled(PSPDFFeatureMask feature, BOOL warn) NS_SWIFT_NAME(IsFeatureEnabled(_:_:));

NS_ASSUME_NONNULL_END
