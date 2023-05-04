//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// Contains an option that a PDF form can have.
PSPDF_CLASS_SWIFT(PDFFormOption)
@interface PSPDFFormOption : NSObject <NSSecureCoding>

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Initializes an instance of this class with a label and value.
- (instancetype)initWithLabel:(NSString *)label value:(NSString *)value NS_DESIGNATED_INITIALIZER;

/// The label of the option which should be presented to the user.
@property (nonatomic, readonly) NSString *label;

/// The value that gets exported for the given option. Can be the same as `label`
@property (nonatomic, readonly) NSString *value;

@end

NS_ASSUME_NONNULL_END
