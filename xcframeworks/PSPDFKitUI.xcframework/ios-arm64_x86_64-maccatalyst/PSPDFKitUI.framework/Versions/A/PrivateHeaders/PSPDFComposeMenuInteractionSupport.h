//
//  Copyright © 2022-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

#import <PSPDFKitUI/PSPDFViewController.h>
#import <PSPDFKitUI/PSPDFPageView.h>

@class PSPDFAnnotation;
@class PSPDFMenuItem;

// README
//
// `ComposeMenuInteraction` needs to call deprecated methods to support legacy
// customizations, but it creates warnings that we can't get rid of in Swift. We
// need this Objective-C shim to re-expose deprecated API to Swift without
// triggering warnings.
//
// This file is implicitly deprecated since PSPDFKit 12 for iOS and can be
// removed once we drop the referenced deprecations.

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFViewController (PSPDFComposeMenuInteractionSupport)

/// The boolean value that indicates whether the view controller's delegate
/// implements the deprecated legacy method to customize the compose menu.
@property (nonatomic, readonly) BOOL delegateHasLegacyComposeMenuCustomization;

/// Ask the delegate to customize the compose menu using the legacy method.
- (nullable NSArray<PSPDFMenuItem *> *)delegateLegacyComposeMenuAtPoint:(CGPoint)point onPageView:(PSPDFPageView *)pageView suggestedItems:(NSArray<PSPDFMenuItem *> *)suggestedItems;

/// The array of deprecated methods for customizing the annotation menu that the
/// delegate implements.
@property (nonatomic, readonly) NSArray<NSString *> *delegateLegacyAnnotationMenuCustomizations;

/// Ask the delegate to customize the legacy annotation menu.
- (nullable NSArray<PSPDFMenuItem *> *)delegateLegacyAnnotationMenuForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations onPageView:(PSPDFPageView *)pageView suggestedItems:(NSArray<PSPDFMenuItem *> *)suggestedItems;

@end

@interface PSPDFPageView (PSPDFComposeMenuInteractionSupport)

/// The boolean value that indicates whether the page view subclass implements
/// the deprecated legacy subclassing hook to customize the compose menu.
@property (nonatomic, readonly) BOOL hasLegacyComposeMenuCustomization;

/// Ask the page view for legacy compose menu items.
- (NSArray<PSPDFMenuItem *> *)legacyComposeMenuAtPoint:(CGPoint)point;

/// The array of deprecated methods for customizing the annotation menu that the
/// page view subclass implements.
@property (nonatomic, readonly) NSArray<NSString *> *legacyAnnotationMenuCustomizations;

/// Ask the page view for the legacy annotation menu items.
- (NSArray<PSPDFMenuItem *> *)legacyAnnotationMenuForAnnotations:(NSArray<PSPDFAnnotation *> *)annotations;

@end

NS_ASSUME_NONNULL_END
