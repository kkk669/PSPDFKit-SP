//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

@class PSPDFRenderOptions;

NS_ASSUME_NONNULL_BEGIN

/// Helper class that manages filter chains where available.
///
/// For optimal resource utilization, create one instance and pass that into all components that need the functionality.
@interface PSPDFContextPostProcessor : NSObject

/// Attempts to apply the filters corresponding to `renderOptions` to the entire `context`.
///
/// If CoreImage is supported, this method will take the contents of the context, turn it into a bitmap, and pipe it
/// through a filter chain, described by the renderOptions. The result then replaces the contents of the context.
/// If CoreImage isn’t supported, this method does nothing.
///
/// This method can safely be called from any thread. It is stateless, in that several threads can call it concurrently
/// without blocking each other, or corrupting each other’s data — with one limitation:
/// If the `renderOptions` holds `additionalCIFilters`, the inputs and outputs of these filters will be accessed. **As
/// such, it is the caller’s responsibility** that the filter objects are disjoint for any two concurrent calls to this
/// method!
- (void)applyFiltersForRenderOptions:(PSPDFRenderOptions *)renderOptions toContext:(CGContextRef)context;

@end

NS_ASSUME_NONNULL_END
