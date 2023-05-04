//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

@class PSPDFDocument;
@protocol PSPDFPageControls, PSPDFPresentationActions;

NS_ASSUME_NONNULL_BEGIN

/// Opens an alert view to choose to switch to another page.
/// Also accepts page labels.
///
/// This used to be a subclass of `UIActivity`, but it’s now something we call directly and don’t put in `UIActivityViewController`.
PSPDF_TEST_CLASS_SWIFT(GoToPageActivity)
@interface PSPDFGoToPageActivity : NSObject

/// The view controller that will present the go-to-page view controller.
@property (nonatomic, weak) UIViewController<PSPDFPresentationActions> *presentingController;

/// The document the user is viewing.
@property (nonatomic, nullable) PSPDFDocument *document;

/// The object that executes the go to page action after the user confirms which page they want.
@property (nonatomic, weak) id<PSPDFPageControls> pageControlsDelegate;

/// Match partial label string names. Defaults to YES.
@property (nonatomic) BOOL enablePartialLabelMatching;

/// The page index currently shown to the user.
///
/// Setting an invalid page index leads to undefined behavior.
///
/// This defaults to `NSNotFound` which results in no back link being created.
@property (nonatomic) NSInteger currentPageIndex;

/// Show the go to page UI.
- (void)performActivityAnimated:(BOOL)animated;

@end

NS_ASSUME_NONNULL_END
