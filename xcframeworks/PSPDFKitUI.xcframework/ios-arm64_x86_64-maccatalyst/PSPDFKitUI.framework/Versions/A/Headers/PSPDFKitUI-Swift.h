#if 1// Generated by Apple Swift version 5.7.1 (swiftlang-5.7.1.135.3 clang-1400.0.29.51)
#ifndef PSPDFKITUI_SWIFT_H
#define PSPDFKITUI_SWIFT_H
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgcc-compat"

#if !defined(__has_include)
# define __has_include(x) 0
#endif
#if !defined(__has_attribute)
# define __has_attribute(x) 0
#endif
#if !defined(__has_feature)
# define __has_feature(x) 0
#endif
#if !defined(__has_warning)
# define __has_warning(x) 0
#endif

#if __has_include(<swift/objc-prologue.h>)
# include <swift/objc-prologue.h>
#endif

#pragma clang diagnostic ignored "-Wduplicate-method-match"
#pragma clang diagnostic ignored "-Wauto-import"
#if defined(__OBJC__)
#include <Foundation/Foundation.h>
#endif
#if defined(__cplusplus)
#include <cstdint>
#include <cstddef>
#include <cstdbool>
#else
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#endif

#if !defined(SWIFT_TYPEDEFS)
# define SWIFT_TYPEDEFS 1
# if __has_include(<uchar.h>)
#  include <uchar.h>
# elif !defined(__cplusplus)
typedef uint_least16_t char16_t;
typedef uint_least32_t char32_t;
# endif
typedef float swift_float2  __attribute__((__ext_vector_type__(2)));
typedef float swift_float3  __attribute__((__ext_vector_type__(3)));
typedef float swift_float4  __attribute__((__ext_vector_type__(4)));
typedef double swift_double2  __attribute__((__ext_vector_type__(2)));
typedef double swift_double3  __attribute__((__ext_vector_type__(3)));
typedef double swift_double4  __attribute__((__ext_vector_type__(4)));
typedef int swift_int2  __attribute__((__ext_vector_type__(2)));
typedef int swift_int3  __attribute__((__ext_vector_type__(3)));
typedef int swift_int4  __attribute__((__ext_vector_type__(4)));
typedef unsigned int swift_uint2  __attribute__((__ext_vector_type__(2)));
typedef unsigned int swift_uint3  __attribute__((__ext_vector_type__(3)));
typedef unsigned int swift_uint4  __attribute__((__ext_vector_type__(4)));
#endif

#if !defined(SWIFT_PASTE)
# define SWIFT_PASTE_HELPER(x, y) x##y
# define SWIFT_PASTE(x, y) SWIFT_PASTE_HELPER(x, y)
#endif
#if !defined(SWIFT_METATYPE)
# define SWIFT_METATYPE(X) Class
#endif
#if !defined(SWIFT_CLASS_PROPERTY)
# if __has_feature(objc_class_property)
#  define SWIFT_CLASS_PROPERTY(...) __VA_ARGS__
# else
#  define SWIFT_CLASS_PROPERTY(...)
# endif
#endif

#if __has_attribute(objc_runtime_name)
# define SWIFT_RUNTIME_NAME(X) __attribute__((objc_runtime_name(X)))
#else
# define SWIFT_RUNTIME_NAME(X)
#endif
#if __has_attribute(swift_name)
# define SWIFT_COMPILE_NAME(X) __attribute__((swift_name(X)))
#else
# define SWIFT_COMPILE_NAME(X)
#endif
#if __has_attribute(objc_method_family)
# define SWIFT_METHOD_FAMILY(X) __attribute__((objc_method_family(X)))
#else
# define SWIFT_METHOD_FAMILY(X)
#endif
#if __has_attribute(noescape)
# define SWIFT_NOESCAPE __attribute__((noescape))
#else
# define SWIFT_NOESCAPE
#endif
#if __has_attribute(ns_consumed)
# define SWIFT_RELEASES_ARGUMENT __attribute__((ns_consumed))
#else
# define SWIFT_RELEASES_ARGUMENT
#endif
#if __has_attribute(warn_unused_result)
# define SWIFT_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
# define SWIFT_WARN_UNUSED_RESULT
#endif
#if __has_attribute(noreturn)
# define SWIFT_NORETURN __attribute__((noreturn))
#else
# define SWIFT_NORETURN
#endif
#if !defined(SWIFT_CLASS_EXTRA)
# define SWIFT_CLASS_EXTRA
#endif
#if !defined(SWIFT_PROTOCOL_EXTRA)
# define SWIFT_PROTOCOL_EXTRA
#endif
#if !defined(SWIFT_ENUM_EXTRA)
# define SWIFT_ENUM_EXTRA
#endif
#if !defined(SWIFT_CLASS)
# if __has_attribute(objc_subclassing_restricted)
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_CLASS_EXTRA
#  define SWIFT_CLASS_NAMED(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
# else
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
#  define SWIFT_CLASS_NAMED(SWIFT_NAME) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
# endif
#endif
#if !defined(SWIFT_RESILIENT_CLASS)
# if __has_attribute(objc_class_stub)
#  define SWIFT_RESILIENT_CLASS(SWIFT_NAME) SWIFT_CLASS(SWIFT_NAME) __attribute__((objc_class_stub))
#  define SWIFT_RESILIENT_CLASS_NAMED(SWIFT_NAME) __attribute__((objc_class_stub)) SWIFT_CLASS_NAMED(SWIFT_NAME)
# else
#  define SWIFT_RESILIENT_CLASS(SWIFT_NAME) SWIFT_CLASS(SWIFT_NAME)
#  define SWIFT_RESILIENT_CLASS_NAMED(SWIFT_NAME) SWIFT_CLASS_NAMED(SWIFT_NAME)
# endif
#endif

#if !defined(SWIFT_PROTOCOL)
# define SWIFT_PROTOCOL(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA
# define SWIFT_PROTOCOL_NAMED(SWIFT_NAME) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA
#endif

#if !defined(SWIFT_EXTENSION)
# define SWIFT_EXTENSION(M) SWIFT_PASTE(M##_Swift_, __LINE__)
#endif

#if !defined(OBJC_DESIGNATED_INITIALIZER)
# if __has_attribute(objc_designated_initializer)
#  define OBJC_DESIGNATED_INITIALIZER __attribute__((objc_designated_initializer))
# else
#  define OBJC_DESIGNATED_INITIALIZER
# endif
#endif
#if !defined(SWIFT_ENUM_ATTR)
# if defined(__has_attribute) && __has_attribute(enum_extensibility)
#  define SWIFT_ENUM_ATTR(_extensibility) __attribute__((enum_extensibility(_extensibility)))
# else
#  define SWIFT_ENUM_ATTR(_extensibility)
# endif
#endif
#if !defined(SWIFT_ENUM)
# define SWIFT_ENUM(_type, _name, _extensibility) enum _name : _type _name; enum SWIFT_ENUM_ATTR(_extensibility) SWIFT_ENUM_EXTRA _name : _type
# if __has_feature(generalized_swift_name)
#  define SWIFT_ENUM_NAMED(_type, _name, SWIFT_NAME, _extensibility) enum _name : _type _name SWIFT_COMPILE_NAME(SWIFT_NAME); enum SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_ENUM_ATTR(_extensibility) SWIFT_ENUM_EXTRA _name : _type
# else
#  define SWIFT_ENUM_NAMED(_type, _name, SWIFT_NAME, _extensibility) SWIFT_ENUM(_type, _name, _extensibility)
# endif
#endif
#if !defined(SWIFT_UNAVAILABLE)
# define SWIFT_UNAVAILABLE __attribute__((unavailable))
#endif
#if !defined(SWIFT_UNAVAILABLE_MSG)
# define SWIFT_UNAVAILABLE_MSG(msg) __attribute__((unavailable(msg)))
#endif
#if !defined(SWIFT_AVAILABILITY)
# define SWIFT_AVAILABILITY(plat, ...) __attribute__((availability(plat, __VA_ARGS__)))
#endif
#if !defined(SWIFT_WEAK_IMPORT)
# define SWIFT_WEAK_IMPORT __attribute__((weak_import))
#endif
#if !defined(SWIFT_DEPRECATED)
# define SWIFT_DEPRECATED __attribute__((deprecated))
#endif
#if !defined(SWIFT_DEPRECATED_MSG)
# define SWIFT_DEPRECATED_MSG(...) __attribute__((deprecated(__VA_ARGS__)))
#endif
#if __has_feature(attribute_diagnose_if_objc)
# define SWIFT_DEPRECATED_OBJC(Msg) __attribute__((diagnose_if(1, Msg, "warning")))
#else
# define SWIFT_DEPRECATED_OBJC(Msg) SWIFT_DEPRECATED_MSG(Msg)
#endif
#if defined(__OBJC__)
#if !defined(IBSegueAction)
# define IBSegueAction
#endif
#endif
#if !defined(SWIFT_EXTERN)
# if defined(__cplusplus)
#  define SWIFT_EXTERN extern "C"
# else
#  define SWIFT_EXTERN extern
# endif
#endif
#if !defined(SWIFT_CALL)
# define SWIFT_CALL __attribute__((swiftcall))
#endif
#if defined(__cplusplus)
#if !defined(SWIFT_NOEXCEPT)
# define SWIFT_NOEXCEPT noexcept
#endif
#else
#if !defined(SWIFT_NOEXCEPT)
# define SWIFT_NOEXCEPT 
#endif
#endif
#if defined(__cplusplus)
#if !defined(SWIFT_CXX_INT_DEFINED)
#define SWIFT_CXX_INT_DEFINED
namespace swift {
using Int = ptrdiff_t;
using UInt = size_t;
}
#endif
#endif
#if defined(__OBJC__)
#if __has_feature(modules)
#if __has_warning("-Watimport-in-framework-header")
#pragma clang diagnostic ignored "-Watimport-in-framework-header"
#endif
@import CoreFoundation;
@import Foundation;
@import ObjectiveC;
@import PSPDFKit;

@import UIKit;
#endif

#import <PSPDFKitUI/PSPDFKitUI.h>

#endif
#pragma clang diagnostic ignored "-Wproperty-attribute-mismatch"
#pragma clang diagnostic ignored "-Wduplicate-method-arg"
#if __has_warning("-Wpragma-clang-attribute")
# pragma clang diagnostic ignored "-Wpragma-clang-attribute"
#endif
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wnullability"
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"

#if __has_attribute(external_source_symbol)
# pragma push_macro("any")
# undef any
# pragma clang attribute push(__attribute__((external_source_symbol(language="Swift", defined_in="PSPDFKitUI",generated_declaration))), apply_to=any(function,enum,objc_interface,objc_category,objc_protocol))
# pragma pop_macro("any")
#endif


@class PSPDFAnnotationSet;

/// A protocol implemented by types that can store annotation sets somewhere and
/// load them later. Annotation set stores are used for the Saved Annotations
/// feature.
/// PSPDF_EXPORT(PSPDFAnnotationSetStore)
SWIFT_PROTOCOL_NAMED("AnnotationSetStore")
@protocol PSPDFAnnotationSetStore
/// Get the annotation sets currently stored in the store.
///
/// returns:
/// An array of annotation sets.
- (NSArray<PSPDFAnnotationSet *> * _Nullable)fetchAnnotationSetsWithError:(NSError * _Nullable * _Nullable)error SWIFT_WARN_UNUSED_RESULT;
/// Set the annotation sets in the store.
/// \param newValue The new array of annotation sets.
///
- (BOOL)setAnnotationSets:(NSArray<PSPDFAnnotationSet *> * _Nonnull)newValue error:(NSError * _Nullable * _Nullable)error;
/// All annotation sets currently stored in the store.
/// warning:
/// If an error occurs when retrieving the stored annotation sets,
/// it will be logged to the console and an empty array will be returned.
/// When storing fails, the logged message is the only indication that the
/// operation failed. Therefore, it is recommended to use the throwing
/// functions instead.
@property (nonatomic, copy) NSArray<PSPDFAnnotationSet *> * _Nonnull annotationSets SWIFT_DEPRECATED_MSG("Deprecated in PSPDFKit 11.3 for iOS. Use `fetchAnnotationSets()` and `setAnnotationSets(_:)` instead.");
@end



/// A button that you can add to your user interface to allow users to initiate
/// the document alignment process.
/// <h1>Displaying the Document Alignment Button</h1>
/// The document alignment button can be added to the <code>userInterfaceView</code> of
/// your PDF view controller, or to any other view in your app.
/// \code
/// let button = DocumentAlignmentButton()
/// pdfViewController.userInterfaceView.addSubview(button)
/// NSLayoutConstraint.activate([...])
///
/// \endcode<h1>Customizing the Document Alignment Button</h1>
/// To customize the title and the image used in the document alignment button,
/// use the standard <code>setTitle(_:for:)</code> and <code>setImage(_:for:)</code> functions of the
/// <code>UIButton</code> class. The document alignment button also provides a convenience
/// <code>init(title:image:)</code> initializer that does this automatically.
/// The document alignment button uses <code>tintColor</code> as its background color and
/// <code>foregroundColor</code> as the color of the title and the image. By default, the
/// document alignment button chooses a foreground color such that is has the
/// highest possible contrast with the tint color.
/// warning:
/// Don’t call <code>setTitleColor(_:for:)</code> or set the <code>backgroundColor</code>
/// or the <code>imageView.tintColor</code> properties directly. Use <code>tintColor</code> and
/// <code>foregroundColor</code> instead.
/// PSPDF_EXPORT(PSPDFDocumentAlignmentButton)
SWIFT_CLASS_NAMED("DocumentAlignmentButton")
@interface PSPDFDocumentAlignmentButton : PSPDFButton
/// Initialize the document alignment button with the default title and
/// image.
- (nonnull instancetype)init;
- (nullable instancetype)initWithCoder:(NSCoder * _Nonnull)coder OBJC_DESIGNATED_INITIALIZER SWIFT_UNAVAILABLE;
- (void)tintColorDidChange;
- (void)traitCollectionDidChange:(UITraitCollection * _Nullable)previousTraitCollection;
@property (nonatomic, getter=isEnabled) BOOL enabled;
@property (nonatomic, getter=isHighlighted) BOOL highlighted;
@property (nonatomic, getter=isSelected) BOOL selected;
- (nonnull instancetype)initWithFrame:(CGRect)frame SWIFT_UNAVAILABLE;
@end


@class PSPDFComparisonConfiguration;
@protocol PSPDFDocumentAlignmentViewControllerDelegate;

/// A view controller that provides the user interface for aligning two versions
/// of a document.
/// <h1>Customizing the Document Alignment View Controller</h1>
/// The document alignment view controller’s view hierarchy uses <code>tintColor</code> to
/// configure the look of the crosshair and the progress bar. You can customize
/// this look by setting a custom tint color.
/// You may use <code>ComparisonConfiguration</code> to customize the contents and the look
/// of the generated comparison document. See its documentation for more
/// information.
/// <h1>Receiving the Generated Comparison Document</h1>
/// Once the user aligns both versions of a document, the document alignment
/// view controller will notify the <code>delegate</code> object that a comparison document
/// was generated, or failed to be generated because of an error. You may
/// implement the two methods to hide the document alignment view controller and
/// update your app’s user interface accordingly.
/// The document alignment view controller also offers an alternative Swift-only
/// API based on the Combine framework that you can use to receive the generated
/// comparison document. It’s equivalent to the delegate protocol and may be
/// used when Combine bindings are more manageable, e.g. in SwiftUI.
/// PSPDF_EXPORT(PSPDFDocumentAlignmentViewController)
SWIFT_CLASS_NAMED("DocumentAlignmentViewController")
@interface PSPDFDocumentAlignmentViewController : UIViewController
/// Initialize the document alignment view controller with the given two
/// versions of a document and indices of the pages on which the points
/// should be selected in both versions of a document.
/// note:
/// Initializing the document alignment view controller requires the
/// Comparison component to be enabled for your license.
/// \param oldDocument The old version of a document.
///
/// \param oldPageIndex The index of the page in the old version of a
/// document.
///
/// \param newDocument The new version of a document.
///
/// \param newPageIndex The index of the page in the new version of a
/// document.
///
/// \param configuration The configuration that will be used to generate a
/// comparison document.
///
- (nonnull instancetype)initWithOldDocument:(PSPDFDocument * _Nonnull)oldDocument pageIndex:(PSPDFPageIndex)oldPageIndex newDocument:(PSPDFDocument * _Nonnull)newDocument pageIndex:(PSPDFPageIndex)newPageIndex configuration:(PSPDFComparisonConfiguration * _Nonnull)configuration OBJC_DESIGNATED_INITIALIZER;
/// Initialize the document alignment view controller with the given two
/// versions of a document. The points will be selected on the first pages
/// of both versions of a document.
/// note:
/// Initializing the document alignment view controller requires the
/// Comparison component to be enabled for your license.
/// \param oldDocument The old version of a document.
///
/// \param newDocument The new version of a document.
///
/// \param configuration The configuration that will be used to generate a
/// comparison document.
///
- (nonnull instancetype)initWithOldDocument:(PSPDFDocument * _Nonnull)oldDocument newDocument:(PSPDFDocument * _Nonnull)newDocument configuration:(PSPDFComparisonConfiguration * _Nonnull)configuration;
- (nullable instancetype)initWithCoder:(NSCoder * _Nonnull)coder OBJC_DESIGNATED_INITIALIZER SWIFT_UNAVAILABLE;
/// The delegate of the document alignment controller.
@property (nonatomic, weak) id <PSPDFDocumentAlignmentViewControllerDelegate> _Nullable delegate;
- (void)viewDidLoad;
- (void)viewWillLayoutSubviews;
- (void)viewSafeAreaInsetsDidChange;
- (nonnull instancetype)initWithNibName:(NSString * _Nullable)nibNameOrNil bundle:(NSBundle * _Nullable)nibBundleOrNil SWIFT_UNAVAILABLE;
@end



/// A delegate protocol of the document alignment view controller.
/// PSPDF_EXPORT(PSPDFDocumentAlignmentViewControllerDelegate)
SWIFT_PROTOCOL_NAMED("DocumentAlignmentViewControllerDelegate")
@protocol PSPDFDocumentAlignmentViewControllerDelegate
@optional
/// Notify the delegate that a comparison document was generated.
/// \param sender The calling view controller.
///
/// \param comparisonDocument The generated comparison document.
///
- (void)documentAlignmentViewController:(PSPDFDocumentAlignmentViewController * _Nonnull)sender didFinishWithComparisonDocument:(PSPDFDocument * _Nonnull)comparisonDocument;
/// Notify the delegate that a comparison document failed to be generated.
/// \param sender The calling view controller.
///
/// \param error The error that occurred when generating a comparison
/// document.
///
- (void)documentAlignmentViewController:(PSPDFDocumentAlignmentViewController * _Nonnull)sender didFailWithError:(NSError * _Nonnull)error;
@end



/// An annotation set store that saves annotation sets in the Keychain.
/// warning:
/// The keychain store can safely store only up to 4 KB of data. This
/// much data can be easily filled by storing a high-quality image annotation,
/// a complex ink annotation or a sound annotation. As such, it’s recommended
/// to use <code>PersistentAnnotationSetStore</code> instead.
/// PSPDF_EXPORT(PSPDFKeychainAnnotationSetsStore)
SWIFT_CLASS_NAMED("KeychainAnnotationSetsStore")
@interface PSPDFKeychainAnnotationSetsStore : NSObject <PSPDFAnnotationSetStore>
- (NSArray<PSPDFAnnotationSet *> * _Nullable)fetchAnnotationSetsWithError:(NSError * _Nullable * _Nullable)error SWIFT_WARN_UNUSED_RESULT;
- (BOOL)setAnnotationSets:(NSArray<PSPDFAnnotationSet *> * _Nonnull)newValue error:(NSError * _Nullable * _Nullable)error;
@property (nonatomic, copy) NSArray<PSPDFAnnotationSet *> * _Nonnull annotationSets SWIFT_DEPRECATED_MSG("Deprecated in PSPDFKit 11.3 for iOS. Use `fetchAnnotationSets()` and `setAnnotationSets(_:)` instead.");
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end






@class PSPDFInkAnnotation;
@class PSPDFFreeTextAnnotation;
@class PSPDFLinkAnnotation;

@interface PSPDFPageView (SWIFT_EXTENSION(PSPDFKitUI))
/// Check if the annotation inspector can be presented for the given
/// annotations.
/// \param annotations The array of potentially inspectable annotations.
///
///
/// returns:
/// A boolean value that indicates whether the annotation
/// inspector can be presented for the given annotations.
- (BOOL)canPresentInspectorForAnnotations:(NSArray<PSPDFAnnotation *> * _Nonnull)annotations SWIFT_WARN_UNUSED_RESULT;
/// Present the annotation inspector for the given annotations. This will
/// also select the given annotations if they aren’t already.
/// \param annotations The array of annotations to inspect.
///
/// \param options The presentation options.
///
/// \param animated Whether to animate the presentation.
///
/// \param completion The closure to execute when animation finishes.
///
///
/// returns:
/// An instance of the annotation inspector view controller or
/// <code>nil</code> if the annotation inspector couldn’t be presented for the given
/// annotations.
- (UIViewController * _Nullable)presentInspectorForAnnotations:(NSArray<PSPDFAnnotation *> * _Nonnull)annotations options:(NSDictionary<PSPDFPresentationOption, id> * _Nonnull)options animated:(BOOL)animated completion:(void (^ _Nullable)(void))completion;
/// Present comments for the given annotations. This will also select the
/// given annotation if it isn’t already.
/// \param annotation The annotation with comments.
///
/// \param options The presentation options.
///
/// \param animated Whether to animate the presentation.
///
/// \param completion The closure to execute when animation finishes.
///
///
/// returns:
/// An instance of the note annotation view controller or <code>nil</code>
/// if comments couldn’t be presented for the given annotations.
- (UIViewController * _Nullable)presentCommentsForAnnotation:(PSPDFAnnotation * _Nonnull)annotation options:(NSDictionary<PSPDFPresentationOption, id> * _Nonnull)options animated:(BOOL)animated completion:(void (^ _Nullable)(void))completion;
/// Present the color picker for the given property of the given annotation.
/// This will also select the given annotation if it isn’t already.
/// \param annotation The annotation to modify.
///
/// \param property A color property of the annotation.
///
/// \param options The presentation options.
///
/// \param animated Whether to animate the presentation.
///
/// \param completion The closure to execute when animation finishes.
///
///
/// returns:
/// An instance of the color picker view controller or <code>nil</code>
/// if the color picker couldn’t be presented for the given property of
/// the given annotation.
- (UIViewController * _Nullable)presentColorPickerForAnnotation:(PSPDFAnnotation * _Nonnull)annotation property:(PSPDFAnnotationStyleKey _Nonnull)property options:(NSDictionary<PSPDFPresentationOption, id> * _Nonnull)options animated:(BOOL)animated completion:(void (^ _Nullable)(void))completion;
/// Present the font picker for the given free text annotation. This will
/// also select the given annotation if it isn’t already.
/// \param annotation The free text annotation to modify.
///
/// \param options The presentation options.
///
/// \param animated Whether to animate the presentation.
///
/// \param completion The closure to execute when animation finishes.
///
///
/// returns:
/// An instance of the font picker view controller or <code>nil</code>
/// if the font picker couldn’t be presented for the given free text
/// annotation.
- (UIViewController * _Nullable)presentFontPickerForAnnotation:(PSPDFFreeTextAnnotation * _Nonnull)annotation options:(NSDictionary<PSPDFPresentationOption, id> * _Nonnull)options animated:(BOOL)animated completion:(void (^ _Nullable)(void))completion;
/// Present the action sheet for the given link annotation. This will also
/// select the given annotation, if it isn’t already.
/// \param annotation The link annotation to present actions for.
///
/// \param options The presentation options.
///
/// \param animated Whether to animate the presentation.
///
/// \param completion The closure to execute when animation finishes.
///
///
/// returns:
/// An instance of the action sheet view controller or <code>nil</code>
/// if the action sheet couldn’t be presented for the given link
/// annotation.
- (UIViewController * _Nullable)presentLinkActionSheetForAnnotation:(PSPDFLinkAnnotation * _Nonnull)annotation options:(NSDictionary<PSPDFPresentationOption, id> * _Nonnull)options animated:(BOOL)animated completion:(void (^ _Nullable)(void))completion;
@end


@class NSURL;

/// An annotation set store that stores the saved annotation sets on disk,
/// using file protection.
/// PSPDF_EXPORT(PSPDFPersistentAnnotationSetStore)
SWIFT_CLASS_NAMED("PersistentAnnotationSetStore")
@interface PSPDFPersistentAnnotationSetStore : NSObject <PSPDFAnnotationSetStore>
/// Initialize the persistent annotation set store with the given store
/// directory URL.
/// \param directoryURL The root directory URL. This must be a local file
/// URL. If there is no directory at this URL, it will be created
/// automatically.
///
- (nonnull instancetype)initWithDirectoryURL:(NSURL * _Nonnull)directoryURL OBJC_DESIGNATED_INITIALIZER;
/// Initialize the persistent annotation set store with a default store
/// directory URL in the Application Support directory.
- (nonnull instancetype)init;
/// The URL of the directory containing an index file and individual
/// annotation set archives.
@property (nonatomic, readonly, copy) NSURL * _Nonnull directoryURL;
- (NSArray<PSPDFAnnotationSet *> * _Nullable)fetchAnnotationSetsWithError:(NSError * _Nullable * _Nullable)error SWIFT_WARN_UNUSED_RESULT;
- (BOOL)setAnnotationSets:(NSArray<PSPDFAnnotationSet *> * _Nonnull)newValue error:(NSError * _Nullable * _Nullable)error;
@property (nonatomic, copy) NSArray<PSPDFAnnotationSet *> * _Nonnull annotationSets SWIFT_DEPRECATED_MSG("Deprecated in PSPDFKit 11.3 for iOS. Use `fetchAnnotationSets()` and `setAnnotationSets(_:)` instead.");
/// Move the annotation sets stored in the given <code>otherStore</code> to this store.
/// Each successfully moved annotation set will be removed from the
/// <code>otherStore</code>.
/// \param otherStore A different annotation set store.
///
- (void)moveAnnotationSetsFromStore:(id <PSPDFAnnotationSetStore> _Nonnull)otherStore;
@end


@protocol PSPDFSignatureCreationViewControllerDelegate;
@class PSPDFDrawView;
@class PSPDFSignatureViewModel;

/// A signature creation view controller can be used to add a signature to a document by drawing, selecting an image, or typing.
/// This class requires the Electronic Signatures feature to be enabled in your license.
/// To cryptographically sign a document with a certificate, please use the <code>PDFSigner</code> class from PSPDFKit’s Digital Signatures component.
/// Check out https://pspdfkit.com/guides/ios/signatures/overview/ for more general information about signatures.
/// PSPDF_EXPORT(PSPDFSignatureCreationViewController)
SWIFT_CLASS_NAMED("SignatureCreationViewController")
@interface PSPDFSignatureCreationViewController : UIViewController <PSPDFOverridable>
/// Signature controller delegate.
@property (nonatomic, weak) id <PSPDFSignatureCreationViewControllerDelegate> _Nullable delegate;
/// The view used internally for drawing the signature.
/// Use the draw view to access additional drawing data, including biometric values.
@property (nonatomic, readonly, strong) PSPDFDrawView * _Nonnull drawView;
/// Whether the “Save Signature” toggle is enabled, if <code>showSaveToggle</code> is true. If <code>showSaveToggle</code> is false then this property should be ignored.
@property (nonatomic, readonly) BOOL isSaveSignatureEnabled;
/// Whether to show the “Save Signature” toggle.
/// When presented within PSPDFKit, this value depends on the <code>signatureSavingStrategy</code> and <code>signatureStore</code>
/// availability on the <code>PDFViewController</code> that presented this controller.
/// This is true iff the <code>signatureStore</code> is available and <code>signatureSavingStrategy</code> is set to <code>saveIfSelected</code>.
/// When this controller is created manually, this value defaults to false.
@property (nonatomic) BOOL showSaveToggle;
/// All state associated with the view. Can be used to create a signature annotation.
@property (nonatomic, readonly, strong) PSPDFSignatureViewModel * _Nonnull model;
- (nonnull instancetype)initWithNibName:(NSString * _Nullable)nibNameOrNil bundle:(NSBundle * _Nullable)nibBundleOrNil OBJC_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder * _Nonnull)coder OBJC_DESIGNATED_INITIALIZER;
/// Creates a signature annotation if a signature is added in either forms — ink drawing, image or text.
/// You should use this API whenever you need to access the signature added by the user once the controller has finished creating the signature.
/// We recommend calling this API in the implementation of <code>signatureCreationViewControllerDidFinish(_:)</code> but you can
/// call this API wherever you see fit.
/// note:
/// Annotation created will be created with the default class and not the subclass override registered with a <code>Document</code> instance
/// if the <code>SignatureCreationViewController</code> is presented manually instead of interactions with the PSPDFKit UI.
/// This is because the view controller presented is detached from the <code>Document</code> instance whenever it is presented manually
/// \param size Size of the page where the signature is intended to be added.
///
///
/// returns:
/// Ink annotation for drawn signatures otherwise a stamp annotation for image and text type signatures. Returns nil if the signature creation is not done.
- (PSPDFAnnotation * _Nullable)signatureAnnotationForPageWithSize:(CGSize)size SWIFT_WARN_UNUSED_RESULT;
- (void)loadView;
- (void)viewDidLoad;
@property (nonatomic, getter=isModalInPresentation) BOOL modalInPresentation;
@end


@class PSPDFSignatureCreationConfiguration;

@interface PSPDFSignatureCreationViewController (SWIFT_EXTENSION(PSPDFKitUI))
@property (nonatomic, strong) PSPDFSignatureCreationConfiguration * _Nonnull configuration;
@end


/// The possible ways in which the user can input their signature.
/// PSPDF_EXPORT(PSPDFSignatureCreationMode)
typedef SWIFT_ENUM_NAMED(NSInteger, PSPDFSignatureCreationMode, "Mode", open) {
/// The user draws their signature. For example using a finger or Apple Pencil.
  PSPDFSignatureCreationModeDraw = 0,
/// The user selects an existing image of their signature from their photo library or files, or takes a photo of their signature written on a piece of paper.
  PSPDFSignatureCreationModeImage = 1,
/// The user types their name and selects a style for their signature from a small number of fonts.
  PSPDFSignatureCreationModeType = 2,
};



/// An object that receives callbacks from a signature creation view controller.
/// PSPDF_EXPORT(PSPDFSignatureCreationViewControllerDelegate)
SWIFT_PROTOCOL_NAMED("SignatureCreationViewControllerDelegate")
@protocol PSPDFSignatureCreationViewControllerDelegate <NSObject>
/// Cancel button has been pressed.
- (void)signatureCreationViewControllerDidCancel:(PSPDFSignatureCreationViewController * _Nonnull)signatureController;
/// Save/Done button has been pressed.
- (void)signatureCreationViewControllerDidFinish:(PSPDFSignatureCreationViewController * _Nonnull)signatureController;
@end

#if defined(__cplusplus)
#endif
#if __has_attribute(external_source_symbol)
# pragma clang attribute pop
#endif
#pragma clang diagnostic pop
#endif

#else
#error unsupported Swift architecture
#endif
