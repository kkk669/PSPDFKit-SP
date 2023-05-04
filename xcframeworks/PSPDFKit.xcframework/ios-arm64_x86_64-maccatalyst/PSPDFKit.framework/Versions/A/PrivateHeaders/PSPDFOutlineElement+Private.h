//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFOutlineElement.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFOutlineElement ()

/// Used to keep the expanded state separate from the default one during search
@property (nonatomic, nullable) NSNumber *expandedForSearch;

// MARK: - Exposed for Tests

/// Returns the action only if it was already lazy-loaded by previously
/// accessing the `action` property.
@property (nonatomic, readonly, nullable) PSPDFAction *actionIfLoaded;

@end

NS_ASSUME_NONNULL_END
