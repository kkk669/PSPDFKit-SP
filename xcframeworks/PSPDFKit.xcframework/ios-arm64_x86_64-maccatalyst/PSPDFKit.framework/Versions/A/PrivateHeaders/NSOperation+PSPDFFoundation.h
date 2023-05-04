//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <Foundation/Foundation.h>

@interface NSOperation (PSPDFFoundation)

/// Forwards to `name` and sets our `PSPDF_URL_PREFIX` in front of the string.
///
/// Example: Set `library.spotlight.start-indexing-operation` and the resulting name will be:
/// `com.pspdfkit.library.spotlight.start-indexing-operation` (based on `PSPDF_URL_PREFIX`)
@property (nullable, copy) NSString *pspdf_name;

@end
