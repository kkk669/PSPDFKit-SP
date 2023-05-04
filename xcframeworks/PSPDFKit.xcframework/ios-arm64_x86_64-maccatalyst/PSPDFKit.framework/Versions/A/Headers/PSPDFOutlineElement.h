//
//  Copyright © 2011-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFBookmark.h>
#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// Represents a single outline/table of contents element.
PSPDF_CLASS_SWIFT(OutlineElement)
@interface PSPDFOutlineElement : PSPDFModel

/// Init with title, page, child elements and indentation level.
- (instancetype)initWithTitle:(nullable NSString *)title color:(nullable UIColor *)color fontTraits:(UIFontDescriptorSymbolicTraits)fontTraits action:(nullable PSPDFAction *)action children:(nullable NSArray<PSPDFOutlineElement *> *)children level:(NSUInteger)level NS_DESIGNATED_INITIALIZER;

/// Returns all elements + flattened subelements if they are expanded
@property (nonatomic, readonly) NSArray<PSPDFOutlineElement *> *flattenedChildren;

/// All elements, ignores expanded state.
@property (nonatomic, readonly) NSArray<PSPDFOutlineElement *> *allFlattenedChildren;

/// Outline elements parent. `nil` if it has no parent.
@property (nonatomic, readonly, weak) PSPDFOutlineElement *parent;

/// Outline title.
@property (nonatomic, copy, readonly, nullable) NSString *title;

/// Outline action (page change, URL)
///
/// @note As a performance optimization, the action will be
/// resolved lazily on first access in most cases. You should
/// avoid accessing this property in large batches to avoid
/// lag in complex PDF documents.
@property (nonatomic, readonly, nullable) PSPDFAction *action;

/// Unique identifier, created at parse time.
@property (nonatomic, readonly) NSString *uuid;

/// Convenience shortcut for self.action.pageIndex (if action is of type `PSPDFGoToAction`)
///
/// Page is set to `NSNotFound` if action is nil or a different type.
///
/// @note As a performance optimization, the action will be
/// resolved lazily on first access in most cases. You should
/// avoid accessing this property in large batches to avoid
/// lag in complex PDF documents.
@property (nonatomic, readonly) PSPDFPageIndex pageIndex;

/// Bookmark can have a color. (Optional; PDF 1.4)
/// PSPDFKit defaults to system text color when presenting if nil.
@property (nonatomic, readonly, nullable) UIColor *color;

/// A bookmark can be optionally bold or italic. (Optional; PDF 1.4)
@property (nonatomic, readonly) UIFontDescriptorSymbolicTraits fontTraits;

/// Child elements.
@property (nonatomic, copy, readonly, nullable) NSArray<PSPDFOutlineElement *> *children;

/// Current outline level.
@property (nonatomic, readonly) NSUInteger level;

/// Expansion state of current outline element (will not be persisted)
@property (atomic, getter=isExpanded) BOOL expanded;

@end

NS_ASSUME_NONNULL_END
