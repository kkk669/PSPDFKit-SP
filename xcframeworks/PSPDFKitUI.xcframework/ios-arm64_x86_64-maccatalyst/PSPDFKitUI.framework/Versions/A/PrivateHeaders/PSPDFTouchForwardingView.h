//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

/// A view that modifies hit testing to forward touch events.
/// Useful for making non-modal view controller presentations, where otherwise the presentation container view prevents touches from reaching the presenting view.
/// https://stackoverflow.com/a/31291421/2207249
PSPDF_APP_CLASS_SWIFT(TouchForwardingView)
@interface PSPDFTouchForwardingView : UIView

/// The views that touch events should be forwarded to.
/// These views will be hit tested in order, so views at the start of the array take priority.
@property (nonatomic, copy) NSArray<UIView *> *passthroughViews;

@end
