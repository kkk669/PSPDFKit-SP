//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#else
#import "PSPDFEnvironment.h"
#endif

NS_ASSUME_NONNULL_BEGIN

@protocol PSPDFFastEnumeration <NSFastEnumeration>
- (id)pspdf_enumeratedType;
@end

// Usage: foreach (s, strings) { ... }

#if defined(__cplusplus)

namespace PSPDF {
// Not part of PSPDFObjectiveCppBridge as it's most likely not a good idea to call that manually.
template <typename T>
inline T _Nonnull _nn_noassert(T _Nullable o) noexcept {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnullable-to-nonnull-conversion"
    return o;
#pragma clang diagnostic pop
}
}

#define foreach(element, collection) for (typeof((PSPDF::_nn_noassert(collection)).pspdf_enumeratedType) element in (collection))
#else
#define foreach(element, collection) for (typeof((collection).pspdf_enumeratedType) element in (collection))
#endif

@interface NSArray <ElementType> (PSPDFFastEnumeration)
<PSPDFFastEnumeration>

    - (ElementType)pspdf_enumeratedType;

@end

@interface NSSet <ElementType> (PSPDFFastEnumeration)
<PSPDFFastEnumeration>

    - (ElementType)pspdf_enumeratedType;

@end

@interface NSDictionary <KeyType, ValueType> (PSPDFFastEnumeration)
<PSPDFFastEnumeration>

    - (KeyType)pspdf_enumeratedType;

@end

@interface NSOrderedSet <ElementType> (PSPDFFastEnumeration)
<PSPDFFastEnumeration>

    - (ElementType)pspdf_enumeratedType;

@end

@interface NSPointerArray (PSPDFFastEnumeration) <PSPDFFastEnumeration>

- (void *)pspdf_enumeratedType;

@end

@interface NSHashTable <ElementType> (PSPDFFastEnumeration)
<PSPDFFastEnumeration>

    - (ElementType)pspdf_enumeratedType;

@end

@interface NSMapTable <KeyType, ValueType> (PSPDFFastEnumeration)
<PSPDFFastEnumeration>

    - (KeyType)pspdf_enumeratedType;

@end

@interface NSEnumerator <ElementType> (PSPDFFastEnumeration)
<PSPDFFastEnumeration>

    - (ElementType)pspdf_enumeratedType;

@end

NS_ASSUME_NONNULL_END
