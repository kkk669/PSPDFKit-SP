//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFTableViewCell.h>

NS_ASSUME_NONNULL_BEGIN

/// Shows multiple annotation sets within a table cell.
PSPDF_CLASS_SWIFT(AnnotationSetsCell)
@interface PSPDFAnnotationSetsCell : PSPDFTableViewCell<UICollectionViewDelegate, UICollectionViewDataSource>

/// Allows `PSPDFAnnotation` or `PSPDFAnnotationSet` objects.
@property (nonatomic, copy, nullable) NSArray *annotations;

/// The internal collection view.
@property (nonatomic, readonly) UICollectionView *collectionView;

/// The item border. Convenience setter for the internal flow layout.
@property (nonatomic) CGFloat border;

/// Edge insets of the individual annotation sets.
@property (nonatomic) UIEdgeInsets edgeInsets;

/// Called when the collection view selection changes.
@property (nonatomic, copy, nullable) void (^collectionViewUpdateBlock)(PSPDFAnnotationSetsCell *cell);

@end

NS_ASSUME_NONNULL_END
