//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKitUI/PSPDFContainerView.h>

/// The user interface view will relay touches of subviews, but won't react on touches on this actual view itself.
///
/// @note This is achieved with overriding `pointInside:withEvent:`.
PSPDF_CLASS_SWIFT(RelayTouchesView)
@interface PSPDFRelayTouchesView : PSPDFContainerView
@end
