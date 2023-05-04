//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
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

@interface NSCoder (PSPDFSecureCoding)

/// Decodes a collection, which must conform to `NSFastEnumeration`, restricted to containing objects of the specified inner class.
///
/// Returns nil + calls failWithError: on NSCoder if there is invalid content.
- (id)pspdf_decodeCollectionOfClass:(Class)collectionClass innerClass:(Class)innerClass forKey:(NSString *)key;

/// Decodes a dictionary, restricted to containing keys and values of the specified classes.
///
/// Returns nil + calls failWithError: on NSCoder if there is invalid content.
- (NSDictionary *)pspdf_decodeDictionaryWithKeyClass:(Class)keyClass valueClass:(Class)valueClass forKey:(NSString *)key;

@end

NS_ASSUME_NONNULL_END
