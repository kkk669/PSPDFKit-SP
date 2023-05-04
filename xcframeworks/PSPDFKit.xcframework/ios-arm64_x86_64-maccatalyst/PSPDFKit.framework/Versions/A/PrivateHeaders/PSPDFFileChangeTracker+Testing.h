//
//  Copyright © 2019-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFFileChangeTracker.h>
#else
#import "PSPDFEnvironment+Private.h"
#import "PSPDFFileChangeTracker.h"
#endif


@interface PSPDFFileChangeTracker ()

/// The last encountered modification date.
///
/// This reflects the last value of `NSURLContentModificationDateKey`.
///
/// @note Should always be accessed inside file coordination blocks and
/// `NSFilePresenter` methods to ensure proper locking (except for debugging output).
@property (atomic, nullable) NSDate *recordedModificationDate;

/// The last encountered generation ID.
///
/// This reflects the last value of `NSURLGenerationIdentifierKey`.
///
/// @note Should always be accessed inside file coordination blocks and
/// `NSFilePresenter` methods to ensure proper locking (except for debugging output).
@property (atomic, nullable) id <NSCopying, NSCoding, NSObject> recordedGenerationID;

@end
