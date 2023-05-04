//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFReaderViewController.h>
#import <PSPDFKit/PSPDFOverrideProvider.h>
#import <PSPDFKitUI/PSPDFPresentationManager.h>

@interface PSPDFReaderViewController ()

/// Indicates when the web view finished loading to stabilize testability.
@property (nonatomic) BOOL didLoadContent;

/// Delegate for overriding.
@property (nonatomic, weak) id<PSPDFOverrideProvider> overrideDelegate;

/// Access internal presentation manager
@property (nonatomic, readonly) PSPDFPresentationManager *presentationManager;

@end
