//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFBaseConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/// Defines the types of items that are dragged.
typedef NS_OPTIONS(NSUInteger, PSPDFDragType) {
    /// No type.
    PSPDFDragTypeNone = 0,
    /// Text types.
    PSPDFDragTypeText = 1 << 0,
    /// Image types.
    PSPDFDragTypeImage = 1 << 1,
    /// All supported item types.
    PSPDFDragTypeAll = NSUIntegerMax
} PSPDF_ENUM_SWIFT(DragAndDropConfiguration.DragType);

/// Defines the types of items that are dropped.
typedef NS_OPTIONS(NSUInteger, PSPDFDropType) {
    /// No type.
    PSPDFDropTypeNone = 0,
    /// Text types.
    PSPDFDropTypeText = 1 << 0,
    /// Image types.
    PSPDFDropTypeImage = 1 << 1,
    /// PDF files.
    PSPDFDropTypePDF = 1 << 2,
    /// All supported item types.
    PSPDFDropTypeAll = NSUIntegerMax
} PSPDF_ENUM_SWIFT(DragAndDropConfiguration.DropType);

/// Defines targets where drops can happen.
typedef NS_OPTIONS(NSUInteger, PSPDFDropTarget) {
    /// No target.
    PSPDFDropTargetNone = 0,
    /// Drops from external apps.
    PSPDFDropTargetExternalApp = 1 << 0,
    /// Drops that originated on the same page.
    /// Only honored in local drag sessions, and if there is only one item in the drop session.
    PSPDFDropTargetSamePage = 1 << 1,
    /// Drops that originated on another page.
    /// Only honored in local drag sessions, and if there is only one item in the drop session.
    PSPDFDropTargetOtherPages = 1 << 2,
    /// All targets.
    PSPDFDropTargetAll = NSUIntegerMax
} PSPDF_ENUM_SWIFT(DragAndDropConfiguration.DropTarget);

/// This configuration builder offers all properties of `PSPDFDragAndDropConfiguration`
/// in a writable version.
///
/// @see `PSPDFDragAndDropConfiguration`
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(DragAndDropConfigurationBuilder)
@interface PSPDFDragAndDropConfigurationBuilder : PSPDFBaseConfigurationBuilder
@end

/// Used to configure various drag and drop options, on how and where it should work.
/// Set the object you create here on `PSPDFConfiguration.dragAndDropConfiguration`.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(DragAndDropConfiguration)
@interface PSPDFDragAndDropConfiguration : PSPDFBaseConfiguration<PSPDFDragAndDropConfigurationBuilder *>

/// Configures what items from a document should be draggable. Defaults to `PSPDFDragTypeAll`.
@property (nonatomic, readonly) PSPDFDragType allowedDragTypes;

/// Configures what drops should accepted on the document. Defaults to `PSPDFDropTypeAll`.
@property (nonatomic, readonly) PSPDFDropType acceptedDropTypes;

/// Configures from where a drop should be handled. Defaults to `PSPDFDropTargetOtherPages | PSPDFDropTargetExternalApp`.
@property (nonatomic, readonly) PSPDFDropTarget allowedDropTargets;

/// Defines if the drag should be valid outside of the originating app. Defaults to `true`.
@property (nonatomic, readonly) BOOL allowDraggingToExternalApps;

@end

@interface PSPDFDragAndDropConfigurationBuilder ()

/// @see PSPDFDragAndDropConfiguration.allowedDragTypes.
@property (nonatomic) PSPDFDragType allowedDragTypes;
/// @see PSPDFDragAndDropConfiguration.acceptedDropTypes.
@property (nonatomic) PSPDFDropType acceptedDropTypes;
/// @see PSPDFDragAndDropConfiguration.allowedDropTargets.
@property (nonatomic) PSPDFDropTarget allowedDropTargets;
/// @see PSPDFDragAndDropConfiguration.allowDraggingToExternalApps.
@property (nonatomic) BOOL allowDraggingToExternalApps;

@end

NS_ASSUME_NONNULL_END
