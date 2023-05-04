//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAction.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFCPDFObject, PSPDFAnnotation, PSPDFCoreAnnotation;
@protocol PSPDFPropertyMapReader;

/// A reference to an Annotation
@interface PSPDFAnnotationReference : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

- (instancetype)initWithFieldName:(nullable NSString *)fieldName objNum:(NSInteger)objNum genNum:(NSInteger)genNum NS_DESIGNATED_INITIALIZER;

/// The optional fieldName.
@property (nonatomic, readonly, nullable) NSString *fieldName;

/// The optional objNum.
@property (nonatomic, readonly) NSInteger objNum;

/// The optional generation number.
@property (nonatomic, readonly) NSInteger genNum;

@end

/// Actions implementing this protocol need to run through a second pass to resolve annotations.
@protocol PSPDFResolvableAction <NSObject>

@property (nonatomic, copy, readonly, nullable) NSArray<PSPDFAnnotationReference *> *annotationReferences;
@property (nonatomic, weak) PSPDFAnnotation *hostingAnnotation;

@end

/// Resolves the `annotationReferences` of a Hide-, Rendition-, or RichMediaExecuteAction to
/// annotations obtained from the `documentProvider`’s `annotationManager`.
///
/// @param resolvableAction The action whose annotation references should be resolved.
/// @param documentProvider The document provider from which annotations are fetched in order to resolve the reference(s).
/// @param pageIndex The page index where the action is invoked from.
/// @return Resolved annotations.
PSPDF_EXTERN NSArray<PSPDFAnnotation *> * PSPDFResolveAnnotationReferencesForAction(PSPDFAction<PSPDFResolvableAction> *resolvableAction, PSPDFDocumentProvider *documentProvider, PSPDFPageIndex pageIndex);

/// A helper to process actions when they are associated with an annotation.
///
/// This will update the action and recursively iterate over all subActions and:
/// - invoke `updateURLWithAnnotationManager:` for URL actions
/// - set `hostingAnnotation` for actions conforming to `PSPDFResolvableAction`,
///   enabling later use of `PSPDFResolveAnnotationReferencesForAction`
///
/// @param actions The actions to be processed.
/// @param annotation The annotation that is used for the association and annotation manager fetching.
PSPDF_EXTERN void PSPDFProcessActionsForAnnotation(NSArray<PSPDFAction *> *actions, PSPDFAnnotation *annotation);

@interface PSPDFAction ()

/// Is inside the option dictionary if a `pspdfkit://` URL has been detected.
PSPDF_EXTERN NSString *const PSPDFActionIsPSPDFPrefixedURL;
PSPDF_EXTERN NSString *const PSPDFURLActionProcessed;

/// Init for subclasses.
- (instancetype)initWithType:(PSPDFActionType)actionType;

/// Parses a action from the core annotation.
///
/// @return Will return the appropriate subclass of `PSPDFAction` or nil if action couldn't be resolved.
+ (nullable instancetype)actionWithPropertyReader:(id<PSPDFPropertyMapReader>)coreAnnotation;

/// Writeable parentAction
@property (atomic, weak) PSPDFAction *parentAction;

/// Writable variants
@property (nonatomic, copy, nullable) NSDictionary<NSString *, id> *options;

/// A manually set inverse action (used by the back / forward navigation).
@property (nonatomic, nullable) PSPDFAction *inverseAction;

@end

NS_ASSUME_NONNULL_END
