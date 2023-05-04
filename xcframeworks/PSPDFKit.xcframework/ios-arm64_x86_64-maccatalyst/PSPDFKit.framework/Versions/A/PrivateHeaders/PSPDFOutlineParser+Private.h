//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOutlineParser.h>

@interface PSPDFOutlineParser ()

/// Initialize outline parser with the `documentProvider`.
- (instancetype)initWithDocumentProvider:(PSPDFDocumentProvider *)documentProvider NS_DESIGNATED_INITIALIZER;

/// Parses the outline if it's not yet parsed.
- (void)parseOutlineIfNeeded;

/// Remembers the first visible outline element.
@property (nonatomic) NSUInteger firstVisibleElement;

@end
