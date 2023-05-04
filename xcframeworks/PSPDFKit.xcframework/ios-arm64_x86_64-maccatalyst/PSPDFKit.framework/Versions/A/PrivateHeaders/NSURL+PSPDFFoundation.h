//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#else
#import "PSPDFEnvironment.h"
#endif

NS_ASSUME_NONNULL_BEGIN

@interface NSURL (PSPDFAdditions)

/// Resolves a content URL. If the URL is of the form pspdfkit://localhost/Bundle/...,
/// it will be resolved to the appropriate file URL. Otherwise a copy of the unmodified
/// URL will be returned.
- (NSURL *)pspdf_resolveContentURLWithUnknownPathBlock:(nullable NS_NOESCAPE NSString * (^)(NSString *unknownPath))block;

/// Workaround for radar FB6120834 (Mac Catalyst)
///
/// Symlink resolving fails with Catalyst NSURL Document with iCloud sync.
- (NSURL *)pspdf_URLByResolvingSymlinks;

/// Returns the relative path that can be added to `baseURL` to reach `self`.
///
/// @param baseURL The base URL used to compute the relative path.
/// @return A string path that can be added to `baseURL` using
/// `URL` relative path initializers e.g., `fileURLWithPath:relativeToURL:`
/// to reach the URL represented in `self`.
- (NSString *)pspdf_relativePathToURL:(NSURL *)baseURL;

/// Access within security scope.  Will still run block if opening fails.
/// We have a separate generic Swift version that offers value pass-through.
///
/// Note: Apple recommends to run the block either way,
/// no matter if security scoping fails or succeeds. This is a "best effort" API.
- (void)pspdf_accessSecurityScopedResource:(dispatch_block_t)block NS_REFINED_FOR_SWIFT;

#if defined(__cplusplus)
/// RAII helper for simpler control flow in Objective-C++.
class PSPDF_CLASS_AVAILABLE PSPDFURLScopeGuard final {
public:
    explicit PSPDFURLScopeGuard(NSURL *_Nullable url);
    ~PSPDFURLScopeGuard();
    PSPDFURLScopeGuard(const PSPDFURLScopeGuard& other);
    PSPDFURLScopeGuard(PSPDFURLScopeGuard&& other);
    PSPDFURLScopeGuard& operator=(const PSPDFURLScopeGuard&) = default;
    PSPDFURLScopeGuard& operator=(PSPDFURLScopeGuard&&) = delete;
    PSPDFURLScopeGuard() = delete;

private:
    NSURL *_Nullable mURL;
};

/// Returns a RAII security scope for accessing the contents of the receiver.
///
/// In Objective-C++ code, this method has the benefit of simplified control flow over the block-based
/// `pspdf_accessSecurityScopedResource:`.
- (PSPDFURLScopeGuard)pspdf_makeScopeGuard;
#endif

@end

NS_ASSUME_NONNULL_END
