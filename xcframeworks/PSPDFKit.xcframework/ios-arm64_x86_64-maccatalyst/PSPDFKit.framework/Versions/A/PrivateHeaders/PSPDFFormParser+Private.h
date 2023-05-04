//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFFormElement.h>
#import <PSPDFKit/PSPDFFormParser.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFFormElementResolver;

@interface PSPDFFormParser ()

/// Initializes the annotation parser with the associated `documentProvider`.
- (instancetype)initWithDocumentProvider:(PSPDFDocumentProvider *)documentProvider NS_DESIGNATED_INITIALIZER;

/// Parse using `documentRef`.
- (NSArray<__kindof PSPDFFormElement *> *)parseForms;

/// Finds a form element with the given objNum. nil if not found.
- (nullable __kindof PSPDFFormElement *)findAnnotationWithObjNum:(NSInteger)objNum;

/// Finds a form field that has the given obj num as a linked annotation
- (nullable __kindof PSPDFFormField *)findFormFieldLinkedWithObjNum:(NSUInteger)objNum;

/// Helps resolve form elements.
@property (nonatomic, readonly) PSPDFFormElementResolver *formElementResolver;

/// Returns the root JavaScript form field.
@property (nonatomic, readonly, nullable) PSPDFJavaScriptFormField *rootJavaScriptFormField;

@end

NS_ASSUME_NONNULL_END
