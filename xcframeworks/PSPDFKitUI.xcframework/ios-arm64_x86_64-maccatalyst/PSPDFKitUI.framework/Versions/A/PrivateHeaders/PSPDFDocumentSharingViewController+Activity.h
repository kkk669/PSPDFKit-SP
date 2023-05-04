//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFDocumentSharingViewController.h>

NS_ASSUME_NONNULL_BEGIN

/// Implements logic required for presenting and managing `UIActivityViewController`.
@interface PSPDFDocumentSharingViewController (Activity)

/// Checks and blocks printing, if printing is not a supported action for these document(s).
@property (nonatomic, readonly) NSArray<UIActivityType> *effectiveExcludedActivityTypes;

/// Starts the file crunching and sends the resulted files to an UIActivityViewController.
///
/// @param sender  The action sender. Usually an UIBarButtonItem.
- (void)shareToActivityWithSender:(id)sender;

@end

NS_ASSUME_NONNULL_END
