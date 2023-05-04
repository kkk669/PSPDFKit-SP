//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFFile.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFFile ()

/// A file name that always has a file extension.
/// Falling back to pdf if non could be determined.
@property (nonatomic, copy, readonly) NSString *qualifiedFileName;

/// Checks the file contains valid data.
/// This is more efficient than checking the data returned from fileDataMappedWithError:,
/// as it only queries the NSData buffer or reads file metadata.
/// YES if the file contains non-zero data, NO otherwise.
@property (nonatomic, readonly) BOOL hasData;

@end

NS_ASSUME_NONNULL_END
