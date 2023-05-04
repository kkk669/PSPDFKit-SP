//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFAnnotationViewMapper.h>
#import <PSPDFKit/PSPDFMacros+Private.h>

NS_ASSUME_NONNULL_BEGIN

/// The default implementation of an annotation view mapper used by PSPDFKitUI.
///
/// This class sets itself as the `defaultAnnotationViewMapper` of the `PSPDFAnnotationManager` class
/// at load time.
PSPDF_TEST_CLASS_SWIFT(DefaultAnnotationViewMapper)
@interface PSPDFDefaultAnnotationViewMapper : NSObject <PSPDFAnnotationViewMapper>

+ (PSPDFDefaultAnnotationViewMapper *)defaultMapper;

@end

NS_ASSUME_NONNULL_END
