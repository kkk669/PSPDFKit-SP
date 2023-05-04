//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// Defines what page(s) are currently visible.
PSPDF_PROTOCOL_SWIFT(VisiblePagesDataSource)
@protocol PSPDFVisiblePagesDataSource<NSObject>

/// The first page of the spread currently being displayed.
@property (nonatomic, readonly) PSPDFPageIndex pageIndex;

/// All visible page indexes.
@property (nonatomic, readonly) NSIndexSet *visiblePageIndexes;

@end

NS_ASSUME_NONNULL_END
