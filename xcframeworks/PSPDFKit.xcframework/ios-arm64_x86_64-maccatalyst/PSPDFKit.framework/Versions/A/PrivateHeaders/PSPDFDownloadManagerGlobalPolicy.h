//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFDownloadManagerPolicy.h>

/// Uses the global policy set in `PSPDFKit` to allow or disallow network access to the
PSPDF_SDK_CLASS_SWIFT(DownloadManagerGlobalPolicy)
@interface PSPDFDownloadManagerGlobalPolicy : NSObject <PSPDFDownloadManagerPolicy>

@end
