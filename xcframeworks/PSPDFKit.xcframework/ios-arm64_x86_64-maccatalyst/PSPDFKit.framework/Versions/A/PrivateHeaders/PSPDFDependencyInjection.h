//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#else
#import "PSPDFEnvironment+Private.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/// Simple dependency injector. Iterates over `dependencies` which are property names as NSString* and calls
/// `dependencyGetter` if the current value in `target` is nil and set-able.
/// Return nil in `dependencyGetter` for no action.
///
/// @note Will not do anything if target is nil.
/// @returns Number of properties updated.
PSPDF_SDK_EXPORT NSInteger PSPDFInjectDependencies(id target, id<NSFastEnumeration> dependencies, id _Nullable (^_Nullable dependencyGetter)(NSString *dependencyName));

NS_ASSUME_NONNULL_END
