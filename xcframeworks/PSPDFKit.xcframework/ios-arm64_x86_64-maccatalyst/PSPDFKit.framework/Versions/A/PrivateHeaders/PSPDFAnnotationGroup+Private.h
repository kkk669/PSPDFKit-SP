//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAnnotationGroup.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFAnnotationGroupItem;

@interface PSPDFAnnotationGroup ()

@property (nonatomic, copy, nullable) NSSet<PSPDFAnnotationString> *editableTypes;

/// Items filtered with editableTypes
@property (nonatomic) NSArray<__kindof PSPDFAnnotationGroupItem *> *editableItems;

/// Nil when editableItems.count == 0
@property (nonatomic, nullable) PSPDFAnnotationGroupItem *chosenItem;

- (BOOL)updateChoiceToItemWithIdentifier:(NSString *)identifier;

@end

NS_ASSUME_NONNULL_END
