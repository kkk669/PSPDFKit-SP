//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

@class PSPDFAnnotation;

NS_ASSUME_NONNULL_BEGIN

/// Renders one or multiple annotations.
@interface PSPDFAnnotationsRenderView : UIView

/// Annotations that are rendered.
@property (nonatomic) NSArray<PSPDFAnnotation *> *annotations;

/// Indicates if the annotations are highlighted. Can be set e.g. when tapped.
/// Will lower the opacity of the annotations if enabled.
/// Defaults to NO.
@property(nonatomic, getter=isHighlighted) BOOL highlighted;

/// Indicates if the annotations are selected. Since during selection
/// `highlighted` is usually set as well, setting this property
/// ensures we don't render with lower opacity while selected.
/// Defaults to NO.
@property(nonatomic, getter=isSelected) BOOL selected;

/// Can be used to add padding to the rendered annotations.
@property (nonatomic) UIEdgeInsets edgeInsets;

@end

NS_ASSUME_NONNULL_END
