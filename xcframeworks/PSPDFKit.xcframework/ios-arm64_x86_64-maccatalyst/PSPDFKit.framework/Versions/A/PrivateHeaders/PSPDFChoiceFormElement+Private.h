//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFChoiceFormElement.h>

#import <PSPDFKit/PSPDFFormElement+Private.h>

@class PSPDFCoreAnnotation;

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFChoiceFormElement ()

/// So we can set this property when decoding objects.
@property (atomic, copy, nullable) NSArray<PSPDFFormOption *> *options;

// Designated initializer.
- (instancetype)initWithCoreAnnotation:(PSPDFCoreAnnotation *)coreAnnotation formField:(PSPDFFormField *)formField documentProvider:(PSPDFDocumentProvider *)documentProvider;

- (NSString *_Nullable)optionTextAtIndex:(NSUInteger)index;

/// Executes any attached JavaScript and updates Contents if necessary.
- (void)executeJavaScriptFormChangedHandlerAndUpdateContents;

@end

NS_ASSUME_NONNULL_END
