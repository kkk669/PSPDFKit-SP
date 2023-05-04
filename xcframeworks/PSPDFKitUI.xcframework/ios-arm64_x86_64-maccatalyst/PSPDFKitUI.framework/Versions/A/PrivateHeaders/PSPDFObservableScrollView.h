//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFAvoidingScrollView.h>

@class PSPDFObservableScrollView;

NS_ASSUME_NONNULL_BEGIN

@protocol PSPDFScrollViewObserver<NSObject>

/// Called whenever the scroll view did scroll, zoom or do any other activity that
/// requires a layout path.
///
/// @param scrollView The scroll view that updated.
- (void)scrollViewDidLayoutSubviews:(PSPDFObservableScrollView *)scrollView;

@end

@interface PSPDFObservableScrollView : PSPDFAvoidingScrollView

/// Start observing the receiver.
///
/// @param observer The observer that wants to be notified of updates. Hold weakly
/// by the receiver.
- (void)addScrollObserver:(id<PSPDFScrollViewObserver>)observer;

/// Stop observing the receiver.
///
/// @param observer The observer that no longer wants to receive updates.
- (void)removeScrollObserver:(id<PSPDFScrollViewObserver>)observer;

@end

NS_ASSUME_NONNULL_END
