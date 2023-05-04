//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <Foundation/Foundation.h>
#import <PSPDFKit/PSPDFAnnotationAuthorState.h>

NS_ASSUME_NONNULL_BEGIN

/// Summarizes the information about an annotation’s review state. Exactly the info we want in our UI.
@protocol PSPDFAnnotationReviewSummary <NSObject>

/// The names of users who left the specified review state.
/// Only the most recent review from each user is considered.
/// This will only contain review states, not marked/unmarked state.
- (nullable NSArray<NSString *> *)usernamesForState:(PSPDFAnnotationAuthorState)state;

/// The latest review state from the current user (by matching the annotation’s `t` entry).
/// This will only contain review states, not marked/unmarked state.
/// If no review state has been set by the current user yet this will be `none`.
@property (nonatomic, readonly) PSPDFAnnotationAuthorState currentUserState;

@end

NS_ASSUME_NONNULL_END
