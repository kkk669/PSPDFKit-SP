//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFBaseViewController.h>

NS_ASSUME_NONNULL_BEGIN

@protocol PSPDFSimplePageViewControllerDelegate <NSObject>

@optional

// Sets scrollview property. Defaults to YES.
@property (nonatomic, readonly) BOOL shouldDelayContentTouches;

@end

/// Simple view controller that paginates a set of `viewControllers`.
@interface PSPDFSimplePageViewController : PSPDFBaseViewController <UIScrollViewDelegate>

/// Designated initializer.
- (instancetype)initWithViewControllers:(NSArray<__kindof UIViewController *> *)viewControllers NS_DESIGNATED_INITIALIZER;

PSPDF_DEFAULT_VIEWCONTROLLER_INIT_UNAVAILABLE

/// View controllers this controller was initialized with.
@property (nonatomic, copy, readonly) NSArray<__kindof UIViewController *> *viewControllers;

/// Get/set current page, optionally animated. Page starts at 0.
@property (nonatomic) PSPDFPageIndex pageIndex;
- (void)setPageIndex:(PSPDFPageIndex)pageIndex animated:(BOOL)animated;

@end

NS_ASSUME_NONNULL_END
