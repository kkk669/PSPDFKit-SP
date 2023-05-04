//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKitUI/PSPDFPointerHoverEffect.h>

NS_ASSUME_NONNULL_BEGIN

/// Returns either `.custom` or `.system` as button types. Use to disable AppKit type buttons in Catalyst
PSPDF_EXPORT UIButtonType PSPDFCatalystSystemButtonType(void);

@interface UIButton (PSPDFAdditions)

- (void)pspdf_configureWithDefaultPointerStyle;

/// Convenience to set UIPointerHighlightEffect using the whole button for the preview. Use a highlight effect for transparent views roughly the size of the pointer.
- (void)pspdf_configurePointerStyleWithHighlightEffect;

/// Convenience to set UIPointerLiftEffect using the whole button for the preview. Use a lift effect for opaque views that are roughly the size of the pointer.
- (void)pspdf_configurePointerStyleWithLiftEffect;

/// Convenience to set UIPointerHoverEffect using the whole button for the preview. Use a hover effect for views that are larger than the pointer.
- (void)pspdf_configurePointerStyleWithHoverEffect:(PSPDFPointerHoverEffect)preferredEffect;

@end

NS_ASSUME_NONNULL_END
