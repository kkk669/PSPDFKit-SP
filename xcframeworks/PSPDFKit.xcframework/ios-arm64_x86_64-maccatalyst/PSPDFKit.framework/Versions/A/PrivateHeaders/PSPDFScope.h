//
//  Copyright © 2012-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFMacros.h>
#else
#import "PSPDFEnvironment.h"
#import "PSPDFMacros.h"
#endif

#pragma once

NS_ASSUME_NONNULL_BEGIN

/// Weak/Strong dance. Defines `object` as a `weakName` weak variable.
#define PSPDFWeakifyAs(object, weakName) typeof(object) __weak weakName = object

/// Weak/Strong dance. Inverse of PSPDFWeakifyAs.
/// Defines a strong variable `var` from `weakName`.
///
/// @note The variable dance here is necessary for the casting to a nullable type.
#define _PSPDFStrongifyFrom3(weakName, weakNName, var)      \
    _Pragma("clang diagnostic push")                        \
    _Pragma("clang diagnostic ignored \"-Wshadow\"")        \
    _Pragma("clang diagnostic ignored \"-Wauto-var-id\"")   \
    __strong typeof(var) weakNName = weakName;              \
    let _Nullable var = weakNName;                          \
    _Pragma("clang diagnostic pop")                         \
    do {} while (0)

/// Similar to PSPDFStrongifyFrom, however doesn't declare variable as nullable.
#define PSPDFStrongifyNNFrom(weakName, var)             \
    _Pragma("clang diagnostic push")                    \
    _Pragma("clang diagnostic ignored \"-Wshadow\"")    \
    const __strong typeof(var) var = weakName;          \
    _Pragma("clang diagnostic pop")                     \
    do {} while (0)

/// Weakens the given variable - use strongify to make it strong again.
#define weakify(var) __weak typeof(var) pspdfWeak_##var = var

/// Strongify variant that allows a custom backing name.
#define PSPDFStrongifyFrom(weakVar, var) _PSPDFStrongifyFrom3(weakVar, pspdfWeakN_##var, var)

/// Strongifies a variable that has previously been defined using `weakify`.
/// Shadows the variable in the current context.
#define strongify(var) PSPDFStrongifyFrom(pspdfWeak_##var, var)

/// Strongify the variable or return. Usually useful for `self`.
/// Also implies that var is not nullable.
#define strongify_or_return(var)                \
    PSPDFStrongifyNNFrom(pspdfWeak_##var, var); \
    if (var == nil) { return; }                 \
    do {} while (0)

/// strongify when you can ensure from your logic that var will never be nil.
#define strongify_nn(var) PSPDFStrongifyNNFrom(pspdfWeak_##var, var)

NS_ASSUME_NONNULL_END
