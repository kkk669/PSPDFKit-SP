//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFFileDataProvider.h>
#import <PSPDFKit/PSPDFCoordinatedFileDataProviding.h>
#else
#import "PSPDFFileDataProvider.h"
#import "PSPDFCoordinatedFileDataProviding.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// An implementation of `DataProviding` that acts upon a file. All file access is coordinated
/// with file coordination (`NSFileCoordinator`).
/// This class implements the optional conflict resolution methods of `CoordinatedFileDataProviding`.
PSPDF_CLASS_SWIFT(CoordinatedFileDataProvider)
@interface PSPDFCoordinatedFileDataProvider : PSPDFFileDataProvider<PSPDFCoordinatedFileDataProviding, NSFilePresenter>

@end

NS_ASSUME_NONNULL_END
