//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFAction.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFScreenAnnotation;

typedef NS_CLOSED_ENUM(NSInteger, PSPDFRenditionActionType) {
    PSPDFRenditionActionTypeUnknown = -1,
    PSPDFRenditionActionTypePlayStop,
    PSPDFRenditionActionTypeStop,
    PSPDFRenditionActionTypePause,
    PSPDFRenditionActionTypeResume,
    PSPDFRenditionActionTypePlay,
} PSPDF_ENUM_SWIFT(RenditionAction.Kind);

/// Transforms a rendition action type enum to string and back.
///
/// @note The transformer is added in the class initialize phase.
/// Requires `PSPDFRenditionAction` to be accessed at least once.
PSPDF_EXPORT NSValueTransformerName const PSPDFRenditionActionTypeTransformerName NS_SWIFT_NAME(renditionActionType);

/// A rendition action (PDF 1.5) controls the playing of multimedia content (see PDF Reference 1.7, 13.2, “Multimedia”).
///
/// @note JavaScript actions are not supported.
PSPDF_CLASS_SWIFT(RenditionAction)
@interface PSPDFRenditionAction : PSPDFAction

/// Designated initializer.
- (instancetype)initWithActionType:(PSPDFRenditionActionType)actionType javaScript:(nullable NSString *)javaScript annotation:(nullable PSPDFScreenAnnotation *)annotation;

/// The rendition action type.
@property (nonatomic, readonly) PSPDFRenditionActionType actionType;

/// The associated screen annotation. Optional. Will link to an already existing annotation.
@property (nonatomic, weak, readonly) PSPDFScreenAnnotation *annotation;

/// Optional. A JavaScript script that shall be executed when the action is triggered.
@property (nonatomic, readonly, nullable) NSString *javaScript;

@end

NS_ASSUME_NONNULL_END
