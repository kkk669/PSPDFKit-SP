//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFFilePresenterCoordinator.h>
#else
#import "PSPDFFilePresenterCoordinator.h"
#endif

@interface PSPDFFilePresenterCoordinator () // Testing

/// Received when the application will enter into the foreground state.
- (void)applicationWillEnterForegroundNotification:(NSNotification *)notification;

/// Received when the application entered into the background state.
- (void)applicationDidEnterBackgroundNotification:(NSNotification *)notification;

@end
