//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// This class is a helper to deserialize the previous iOS only `PSPDFFormElement` into our new core backed system.
@interface PSPDFiOSToCoreDeserializationHelper : NSObject

/// Deserializes the legacy `PSPDFFileAnnotationProvider` archival format and extracts annotation object number -> value.
/// Using this information we can easily connect our current `PSPDFFormElement` to the core ones.
///
/// @param serializedData The serialized data.
/// @return A dictionary mapping annotation object number to value.
+ (nullable NSDictionary<NSNumber *, id> *)deserializeLegacyToObjectNumberAndFQNWithData:(NSData *)serializedData;

@end

NS_ASSUME_NONNULL_END
