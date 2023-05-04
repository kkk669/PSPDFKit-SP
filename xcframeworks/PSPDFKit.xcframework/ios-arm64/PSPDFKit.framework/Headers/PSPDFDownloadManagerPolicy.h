//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

/// Specifies download related permissions.
PSPDF_PROTOCOL_SWIFT(DownloadManagerPolicy)
@protocol PSPDFDownloadManagerPolicy<NSObject>

/// Returns YES when we're allowed to use the network.
@property (nonatomic, readonly) BOOL hasPermissionForNetworkEvent;

@end
