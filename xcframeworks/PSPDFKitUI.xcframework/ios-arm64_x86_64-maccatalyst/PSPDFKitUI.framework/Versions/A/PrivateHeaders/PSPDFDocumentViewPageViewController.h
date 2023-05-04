//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <UIKit/UIKit.h>
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFReusableObjectCache.h>

@class PSPDFDocumentViewLayout, PSPDFSpreadView, PSPDFPageView;

NS_ASSUME_NONNULL_BEGIN

/// The document view page view controller is responsible for showing a single page.
/// This is required specifically for `PSPDFPageCurlViewController`.
@interface PSPDFDocumentViewPageViewController : UIViewController

PSPDF_DEFAULT_VIEWCONTROLLER_INIT_UNAVAILABLE

/// Creates a new document view page view controller with the given layout.
///
/// @param layout The layout used by the document view creating this page view controller.
- (instancetype)initWithLayout:(PSPDFDocumentViewLayout *)layout pageViewCache:(PSPDFReusableObjectCache<PSPDFPageView *> *)pageViewCache NS_DESIGNATED_INITIALIZER;

/// The page index of the page this view controller represents.
@property (nonatomic) NSInteger pageIndex;

/// The spread view used by this view controller. Calling this method will load the view controllers view.
@property (nonatomic, readonly) PSPDFSpreadView *spreadView;

@end

NS_ASSUME_NONNULL_END
