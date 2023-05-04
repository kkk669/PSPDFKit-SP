//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFOverridable.h>
#else
#import "PSPDFEnvironment.h"
#import "PSPDFOverridable.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// Provides information about overrides of `PSPDFOverridable` classes.
NS_SWIFT_UI_ACTOR
@protocol PSPDFOverrideProvider<NSObject>

@required

/// Might return `originalClass` or its subclass. **Must not** return `Nil`.
///
/// Classes implementing this protocol form a chain leading up to either
/// the `Document` or the `PDFConfiguration`. The next object in the chain
/// is typically a `delegate` or `overrideDelegate` property. Since
/// `PSPDFOverrideProvider` is private, conformance to this might not be
/// exposed. Therefore it may be necessary to check conformance at runtime.
///
/// Calling `PSPDFOverrideClassWithProvider` does not work in Swift so
/// we just forward to `class(forClass:)` directly instead. Therefore
/// to implement this in Swift if `delegate`’s conformance is exposed:
///
/// ```
/// func `class`(forClass originalClass: Overridable.Type) -> AnyClass {
///     delegate?.class(forClass: originalClass) ?? originalClass
/// }
/// ```
///
/// If conformance is not exposed:
///
/// ```
/// func `class`(forClass originalClass: Overridable.Type) -> AnyClass {
///     (delegate as? PSPDFOverrideProvider)?.class(forClass: originalClass) ?? originalClass
/// }
/// ```
///
/// In Objective-C we have macros wrapping a function wrapping the
/// call to `classForClass:` with some additional assertions.
/// So to implement this with `delegate` if conformance is exposed:
///
/// ```
/// PSPDF_FORWARD_OVERRIDES_TO(self.delegate)
/// ```
///
/// If conformance is not exposed:
///
/// ```
/// PSPDF_FORWARD_OVERRIDES_TO_UNCHECKED(self.delegate)
/// ```
- (Class)classForClass:(Class<PSPDFOverridable>)originalClass;

@end

NS_ASSUME_NONNULL_END
