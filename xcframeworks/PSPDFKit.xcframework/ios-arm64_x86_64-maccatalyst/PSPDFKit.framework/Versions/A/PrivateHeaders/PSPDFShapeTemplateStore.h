//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFMacros+Private.h>

@class PSPDFShapeTemplate;

NS_ASSUME_NONNULL_BEGIN

/// This class handles the loading and saving of a set of templates.
PSPDF_SDK_CLASS_SUBCLASSING_RESTRICTED_SWIFT(ShapeTemplateStore)
@interface PSPDFShapeTemplateStore : NSObject

/// Returns the shared template store object. This store loads PSPDFKit's default set of templates.
/// Note that calling -save: on this store will always fail.
@property (class, nonatomic, readonly) PSPDFShapeTemplateStore *defaultStore NS_SWIFT_NAME(default);

/// Instantiates a template store by loading and parsing the template data stored at `fileURL`.
///
/// @param fileURL The file URL at which the template data is stored. This may point to a file that does
/// not exist yet, in which case the returned instance will have no templates.
- (instancetype)initWithTemplatesAtURL:(NSURL *)fileURL NS_DESIGNATED_INITIALIZER;

PSPDF_EMPTY_INIT_UNAVAILABLE

/// The URL at which the receiver stores its templates.
@property (nonatomic, readonly) NSURL *templatesURL;

/// Adds the passed in template to the store.
///
/// @param shapeTemplate The shape template to be added.
- (void)addTemplate:(PSPDFShapeTemplate *)shapeTemplate;

/// Removes the passed in template from the store, if it exists.
///
/// @param shapeTemplate The shape template that is to be removed.
- (void)removeTemplate:(PSPDFShapeTemplate *)shapeTemplate;

/// The templates in the store.
@property (nonatomic, readonly) NSArray<PSPDFShapeTemplate *> *templates;

/// Writes the current templates to the receiver's `fileURL`.
///
/// @param error The error to be set if the write fails.
/// @return `true` if the write succeeded, else `false`.
- (BOOL)saveTemplates:(NSError *_Nullable*)error;

@end

NS_ASSUME_NONNULL_END
