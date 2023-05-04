//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#else
#import "PSPDFEnvironment+Private.h"
#endif

@interface NSPointerArray (PSPDFFoundation)

/// Removes all occurences of `pointer`.
- (void)pspdf_removePointer:(void *)pointer;

/// Performs `block` for each pointer.
- (void)pspdf_enumeratePointersUsingBlock:(void (^)(void *pointer, NSUInteger index, BOOL *stop))block;

/// Performs `block` for each pointer with the given `options`.
- (void)pspdf_enumeratePointersWithOptions:(NSEnumerationOptions)options usingBlock:(void (^)(void *pointer, NSUInteger index, BOOL *stop))block;

/// Performs `block` for each pointer at the specified indexes with the given `options`.
- (void)pspdf_enumeratePointersAtIndexes:(NSIndexSet *)indexes options:(NSEnumerationOptions)options usingBlock:(void (^)(void *pointer, NSUInteger index, BOOL *stop))block;

@end
