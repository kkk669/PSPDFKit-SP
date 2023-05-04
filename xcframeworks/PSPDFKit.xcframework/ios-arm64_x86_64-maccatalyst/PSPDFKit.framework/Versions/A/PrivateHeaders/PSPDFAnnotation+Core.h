//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotation+Private.h>

#import <PSPDFKit/PSPDFCoreAnnotationSyncOption.h>

@class PSPDFCoreAnnotation, PDFCAnnotation;
@protocol PSPDFPropertyMapAccessor, PSPDFPropertyMapReader;

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFAnnotation ()

/// Designated initializer for core annotation support.
/// Implement this in your core annotation subclass.
- (instancetype)initWithCoreAnnotation:(PSPDFCoreAnnotation *)coreAnnotation NS_DESIGNATED_INITIALIZER;

typedef void (^PSPDFAnnotationPropertyInitializationBlock)(id<PSPDFPropertyMapReader> propertyReader);
- (void)performCoreInitializationBlock:(PSPDFAnnotationPropertyInitializationBlock)block;

/// Tries to extract a platform annotation from the core annotation.
/// This is accomplished by setting a `PSPDFWeakAnnotationHolder` in the base annotation on construction time.
+ (nullable PSPDFAnnotation *)platformAnnotationFromCoreAnnotation:(PDFCAnnotation *)coreAnnotation;

/// Used to sync properties to core, using a lock on `PSPDFPropertyMap`.
///
/// @note This method is guaranteed to be called while the property lock is held.
- (void)syncToCoreLockedWithPropertyMap:(id<PSPDFPropertyMapAccessor>)propertyMap NS_REQUIRES_SUPER;

/// Syncs all properties to the core layer.
///
/// @note This method provides the property lock to its callee `syncToCoreLockedWithPropertyMap:`.
/// @note Subclasses must perform the sync to core using `-[PSPDFPropertyMap syncToCoreLockedWithPropertyMap:]`. That is,
/// all properties must be in the core annotation when this method returns.
- (void)syncToCoreWithOption:(PSPDFCoreAnnotationSyncOption)option;

/// Does the exact opposite of `syncToCore`: refreshes all values _from_ a core annotation.
///
/// @note This method takes care of providing the required locks to its callee.
/// @warning Do not override this method! If you have to perform some additional setup, override
/// `implementation_refreshFromCoreAnnotation:additionalWork:` instead!
- (void)refreshFromCoreAnnotation:(PSPDFCoreAnnotation *)coreAnnotation;

/**
 Implementation for `refreshFromCoreAnnotation:` — DO NOT CALL DIRECTLY!

 If you set additional state in `initWithCoreAnnotation:` based on the core annotation, override this method and call super.
 Your implementation should look like the following:
 ```
 - (void)refreshFromCoreAnnotation:(PSPDFCoreAnnotation *)coreAnnotation additionalWork:(dispatch_block_t)additionalWork {
     [super refreshFromCoreAnnotation:coreAnnotation additionalWork:^{
         // Additional setup code goes here! Example:
         self.myFancyProperty = ...; // extract value from coreAnnotation.propertyMap
         // Do not forget to call the block that _you_ are being passed at the end!
         additionalWork();
     }];
 }
 ```

 @warning This method is for overriding in subclasses only! In any other scenario, call
 `refreshFromCoreAnnotation:` instead.
 */
- (void)implementation_refreshFromCoreAnnotation:(PSPDFCoreAnnotation *)coreAnnotation additionalWork:(PSPDFAnnotationPropertyInitializationBlock)additionalWork NS_REQUIRES_SUPER;

/// Attaches the annotation to the core using `PSPDFCoreAnnotation`.
///
/// @param coreAnnotation A core annotation object that will represent this annotation. This can be created using `+[PSPDFCoreAnnotation createCoreAnnotationWithPSPDFAnnotation]`
- (void)attachToCoreWithoutSyncing:(PSPDFCoreAnnotation *)coreAnnotation;

/// Attaches the annotation to the core using `PSPDFCoreAnnotation`, and syncs the current state using the given option.
///
/// @param coreAnnotation A core annotation object that will represent this annotation. This can be created using `+[PSPDFCoreAnnotation createCoreAnnotationWithPSPDFAnnotation]`
/// @param syncOption How the current state should be synced to core.
- (void)attachToCore:(PSPDFCoreAnnotation *)coreAnnotation syncingWithOption:(PSPDFCoreAnnotationSyncOption)syncOption;

/// Syncs the object number from the core annotation.
- (void)syncObjectNumberFromCoreAnnotation;

/// This detaches the annotation from the core.
///
/// @note This does NOT remove the core annotation in the core, we only break the connection between iOS and the core.
- (void)detachFromCore;

/// The core annotation that was used to initialize this instance.
@property (nonatomic, readonly, nullable) PSPDFCoreAnnotation *coreAnnotation;

@end

@interface PSPDFAnnotation (CoreWritingSupport)

/// Syncs the font attributes to the core annotation property map.
///
/// @param attributes      The attributes to sync.
/// @param propertyWriter  The core property map to sync to.
+ (void)syncFontAttributes:(NSDictionary *)attributes toPropertyWriter:(id<PSPDFPropertyMapAccessor>)propertyWriter;

/// Extracts the attributes for drawing the annotation’s text from the given property reader.
///
/// The annotation object is used as a context parameter for the case that the font needs to be
/// downloaded. This allows informing the object later on — given that it’s still alive.
///
/// @param propertyReader The object from which to extract the font and layout attributes for the text.
/// @param annotation The object for which the font and layout attributes should be extracted. Will be
/// informed if a substituted font can be replaced with the real deal.
+ (NSDictionary *)parseTextPropertiesFromReader:(id<PSPDFPropertyMapReader>)propertyReader forAnnotation:(PSPDFAnnotation *)annotation;

@end

NS_ASSUME_NONNULL_END
