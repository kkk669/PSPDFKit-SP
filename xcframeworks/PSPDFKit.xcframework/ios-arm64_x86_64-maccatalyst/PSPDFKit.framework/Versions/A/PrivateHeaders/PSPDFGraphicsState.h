//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// Defines a subset of the extended graphics state in the PDF specification 'ExtGState'
PSPDF_SDK_CLASS_SWIFT(GraphicsState)
@interface PSPDFGraphicsState : NSObject <NSCopying>

/// Initialize with a blend mode.
- (instancetype)initWithCGBlendMode:(CGBlendMode)blendMode;

/// Defines a custom blend mode. Supported values include
/// `kCGBlendModeNormal` to `kCGBlendModeExclusion`.
@property (nonatomic, readonly) CGBlendMode blendMode;

@end

NS_ASSUME_NONNULL_END
