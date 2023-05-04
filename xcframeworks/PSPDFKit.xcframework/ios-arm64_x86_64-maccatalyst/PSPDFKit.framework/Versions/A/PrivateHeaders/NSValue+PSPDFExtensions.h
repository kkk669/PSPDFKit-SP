//
//  Copyright © 2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Initialize a value that contains a selector.
#define PSPDFValueFromSelector(sel) \
    [NSValue pspdf_valueWithSelector:@selector(sel)]

@interface NSValue (PSPDFExtensions)

/// Initialize a value that conains a selector.
+ (instancetype)pspdf_valueWithSelector:(SEL)selector NS_SWIFT_NAME(init(selector:));

/// Returns the selector contained in the value.
@property (nonatomic, readonly, nullable) SEL pspdf_selectorValue NS_SWIFT_NAME(selectorValue);

@end

NS_ASSUME_NONNULL_END
