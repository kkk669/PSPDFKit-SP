//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

#import <PSPDFKit/PSPDFApplicationPolicy.h>
#import <PSPDFKit/PSPDFAnnotationStyleManager.h>
#import <PSPDFKit/PSPDFDatabaseEncryptionProvider.h>
#import <PSPDFKit/PSPDFFeatureMask.h>
#import <PSPDFKit/PSPDFFileManager.h>
#import <PSPDFKit/PSPDFLogging.h>
#import <PSPDFKit/PSPDFRenderManager.h>

@class PSPDFLibrary, PSPDFCache, PSPDFSignatureManager, PSPDFAnnotationStyleManager;

NS_ASSUME_NONNULL_BEGIN

typedef NSString *PSPDFSettingKey NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(SDK.Setting);

/// X-Callback URL, see http://x-callback-url.com
///
/// @note This is used for the Chrome activity in `PSPDFWebViewController`.
/// Example: `PSPDFKitGlobal.sharedInstance[PSPDFSettingKeyXCallbackURLString] = @"pspdfcatalog://";`
PSPDF_EXPORT PSPDFSettingKey const PSPDFSettingKeyXCallbackURLString;

/// Custom PSPDFApplicationPolicy instance that can be configured with `setLicenseKey:options:`.
PSPDF_EXPORT PSPDFSettingKey const PSPDFSettingKeyApplicationPolicy;

/// Custom PSPDFFileManager instance that can be configured with `setLicenseKey:options:`.
PSPDF_EXPORT PSPDFSettingKey const PSPDFSettingKeyFileManager;

/// Custom coordinated PSPDFFileManager instance that can be configured with `setLicenseKey:options:`.
PSPDF_EXPORT PSPDFSettingKey const PSPDFSettingKeyCoordinatedFileManager;

/// Specifies whether coordinated file operations are used by default in `Document`.
/// Creates `PSPDFCoordinatedFileDataProvider`s when initializing documents with local URLs.
/// Expects a boolean `NSNumber`. Defaults to `@YES`. Set to `@NO` to disable.
PSPDF_EXPORT PSPDFSettingKey const PSPDFSettingKeyFileCoordinationEnabled;

/// Specifies the indexing priority that the shared `PSPDFLibrary` instance must use.
/// Must be a valid `PSPDFLibraryIndexingPriority` value wrapped in a `NSNumber`.
/// See `PSPDFLibraryIndexingPriority` for details.
PSPDF_EXPORT PSPDFSettingKey const PSPDFSettingKeyLibraryIndexingPriority;

/// Enables various debug UI options. (e.g. more settings)
PSPDF_EXPORT PSPDFSettingKey const PSPDFSettingKeyDebugMode;

/// Allows specifying additional font directories at initialization time. Expects an array of strings.
///
/// Some PDFs don’t contain embedded fonts and sometimes the system fonts don’t provide a good enough replacement.
/// In that case, you can ship your own fonts and point PSPDFKit to your additional font directories when you initialize the `SDK` object.
///
/// Example:
/// ```
/// let pdfSDK = PSPDFKit.SDK(licenseKey: "Your License goes here", options: [
///     .additionalFontDirectories: [/* your directory paths */],
///     /* any other customisations */
///  ])
/// ``` 
PSPDF_EXPORT PSPDFSettingKey const PSPDFSettingKeyAdditionalFontDirectories;

/// Specifies whether `Document` permissions are honored in the PSPDFKit UI.
///
/// `PSPDFKit` will honor certain PDF permissions and prevent corresponding UI actions, such as editing annotations,
/// if the document disallows them. This option can be used to globally disable this behavior and instead
/// allow all configured UI actions regardless of document permissions.
///
/// @note This option will affect the output of `PSPDFDocument.features` while `PSPDFDocument.permissions`
/// will still reflect the actual values configured in the PDF document. For documents that were instantiated
/// before changing this option, `[document.features updateFeatures]` needs to be invoked to ensure the changes
/// are correctly reflected in the features system.
///
/// Expects a boolean `NSNumber`. Defaults to `@YES`. Set to `@NO` to disable.
PSPDF_EXPORT PSPDFSettingKey const PSPDFSettingKeyHonorDocumentPermissions;

/// This option will reduce memory usage at the expense of performance.
///
/// When enabled PSPDFKit will reduce memory caches and disable optimizations
/// such as parallel document rendering. This option should be avoided, unless
/// you're working with extreme memory constraints.
///
/// @note Set this before the framework is initialized, as part of the license key call.
PSPDF_EXPORT PSPDFSettingKey const PSPDFSettingKeyLowMemoryMode;

/// PSPDFKit - The Leading PDF Framework for iOS, Android and the Web.
/// This is the configuration object for framework-global settings.
///
/// @note The PSPDFKit shared object is a global, thread-safe key/value store.
/// Use `setValue:forKey:` and `valueForKey:` or the subscripted variants to set/get properties.
///
/// Subclassing notes:
/// In PSPDFKit various classes can be subclassed and registered as subclasses via
/// `overrideClass:withClass:` on `Document` (model) and `PDFConfiguration` (view/controller).
/// See https://pspdfkit.com/guides/ios/getting-started/overriding-classes/ for details.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(SDK)
@interface PSPDFKitGlobal : NSObject

/// The shared PSPDFKit configuration instance.
///
/// @note This is the default instance used in document and pdf controller instances.
@property (atomic, class, readonly) PSPDFKitGlobal *sharedInstance NS_SWIFT_NAME(shared);

/// Activate PSPDFKit with your license key from https://customers.pspdfkit.com
+ (void)setLicenseKey:(NSString *)licenseKey;

/// Activate PSPDFKit with your license key from https://customers.pspdfkit.com
///
/// This can also be used for passing options when trialing PSPDFKit. Simply pass `nil` as the `licenseKey`.
///
/// Variant that may be used to set options.
/// These can also later be changed via subscripting access.
+ (void)setLicenseKey:(nullable NSString *)licenseKey options:(nullable NSDictionary<PSPDFSettingKey, id> *)options;

/// Returns the full PSPDFKit product version string
/// (e.g. "PSPDFKit 9.0.0 for iOS (90000)")
@property (atomic, class, readonly) NSString *versionString;

/// Returns just the framework version. (e.g. 9.0.0)
@property (atomic, class, readonly) NSString *versionNumber;

/// Returns the PSPDFKit version date.
@property (atomic, class, readonly) NSDate *compiledAt;

/// The internal build number. Increments with every version.
@property (atomic, class, readonly) NSUInteger buildNumber;

/// Checks if any of the specified features are enabled.
///
/// @param feature A bitmask of features, which may be combined with the bitwise or operator (|).
/// @return YES if any of the features in the passed in bitmask are enabled. NO if all of the features are not enabled.
+ (BOOL)isFeatureEnabled:(PSPDFFeatureMask)feature;

/// Allow generic array access.
- (nullable id)objectForKeyedSubscript:(PSPDFSettingKey)key;

/// Shortcut that returns booleans.
- (BOOL)boolForKey:(PSPDFSettingKey)key;

/// Allow direct dictionary-like access.
- (void)setObject:(nullable id)object forKeyedSubscript:(PSPDFSettingKey)key;

/// The shared memory/file cache.
@property (nonatomic, readonly) PSPDFCache *cache;

/// The common file manager object.
@property (nonatomic, readonly) id<PSPDFFileManager> fileManager;

/// The PDF render coordinator.
@property (nonatomic, readonly) id<PSPDFRenderManager> renderManager;

/// The annotation style manager.
@property (nonatomic, readonly) id<PSPDFAnnotationStyleManager> styleManager;

/// The shared signature handler for digital signature management.
@property (nonatomic, readonly) PSPDFSignatureManager *signatureManager;

/// Controls various security-related aspects and allows enabling/disabling features based on the security settings.
@property (nonatomic, readonly) id<PSPDFApplicationPolicy> policy;

/// The default library. You can override this property to use a custom `PSPDFLibrary` as the default
/// library. It is recommended that you do this early in your application launch. Defaults to an
/// unencrypted library by default or to `nil` if the FTS feature is not enabled in the license.
///
/// If you want to change the indexing priority of the library, set the `PSPDFSettingKeyLibraryIndexingPriority` in the
/// options dictionary passed into `+[PSPDFKitGlobal setLicenseKey:options:]`.
@property (atomic, nullable) PSPDFLibrary *library;

/// An encryption provider for databases. Defaults to `nil`. You must set this property
/// before using any database encryption features. See `PSPDFDatabaseEncryptionProvider` for more
/// information on how to implement this.
@property (atomic, nullable) id<PSPDFDatabaseEncryptionProvider> databaseEncryptionProvider;

/// Various PSPDFKit objects require dependencies.
/// Use this helper to automatically connect them.
/// Will only set known objects that are not already set.
///
/// @returns Number of properties updated.
- (NSInteger)injectDependentProperties:(id)object;

@end

@interface PSPDFKitGlobal (ImageLoading)

/// Loads images from the PSPDFKit.bundle.
///
/// @note Calls `imageLoadingHandler` if one is set, else falls back to internal loading logic.
+ (nullable UIImage *)imageNamed:(NSString *)name;

/// Register a custom block to return custom images.
/// If this block is NULL or returns nil, PSPDFKit.bundle will use for the lookup.
/// If your custom handler returns no image, the default lookup will be used as well.
///
/// @note Images are cached, so don't return different images for the same `imageName` during an app session.
/// This was exposed as `PSPDFSetBundleImageBlock` in earlier versions.
@property (atomic, null_resettable) UIImage *_Nullable (^imageLoadingHandler)(NSString *imageName);

@end

@interface PSPDFKitGlobal (Logging)

/// The global log level for PSPDFKit. Default: `.info`.
///
/// Setting a log level implies enabling all log levels with higher severity.
/// For example, setting `.warning` also enables logging of messages with the
/// level `.error` or `.critical`.
///
/// See the documentation of `LogLevel` to learn more about individual log
/// levels and how to view them in Xcode, in the Console app or in the Terminal.
///
/// @warning Setting the log level to `.debug` or `.verbose` will have a
/// significant performance impact on your app.
@property (nonatomic) PSPDFLogLevel logLevel;

/// The custom log handler that can be used to forward logging to a different
/// service. Setting this to `nil` will reset the default behavior.
///
/// By default, PSPDFKit uses `os_log` to send logs to the operating system.
/// You can override this behavior and use your own logging service instead of
/// or in addition to `os_log`.
///
/// ```objc
/// [PSPDFKitGlobal.sharedInstance setLogHandler:^(PSPDFLogLevel level, const char *tag, NSString * (^message)(void), const char *file, const char *function, NSUInteger line) {
///     NSLog(@"PSPDFKit says from %s: %@", function, message());
/// }];
/// ```
///
/// - Parameters:
///   - level The log level.
///   - tag The tag associated with the message.
///   - message The block that produces the message, without a tag.
///   - file The file in which the log occurred.
///   - function The function in `file` in which the log occurred.
///   - line The line in `file` in which the log occurred.
@property (nonatomic, null_resettable) void (^logHandler)(PSPDFLogLevel level, const char *_Nullable tag, NS_NOESCAPE NSString * (^message)(void), const char *_Nullable file, const char *_Nullable function, NSUInteger line) NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
