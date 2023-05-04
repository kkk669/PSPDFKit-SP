//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFMacros.h>
#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFJSResult, PSPDFJSScriptDescriptor;
@protocol PSPDFJSPlatformDelegate;

/// This class is an interface to our custom JavaScript API implementation.
/// The implementation contains a JS virtual machine (VM).
/// A VM is an environment with one or more execution contexts (although,
/// for simplicity, we currently only support one) and with methods that
/// let clients execute JavaScript snippets or files.
///
/// Thread-safety: This class is thread-safe and protects access to the
/// execution context by multiple threads concurrently.
PSPDF_OBJC_DIRECT_MEMBERS_EXCEPT_TESTS
@interface PSPDFJavaScriptAPI : NSObject

/// Evaluates a script on this API's virtual machine.
///
/// @param scriptDescriptor  The descriptor of the script that should be executed in this API.
/// @param delegate          The optional platform delegate that implements part of the API that cannot be implemented by Core.
- (PSPDFJSResult *)evaluateScript:(PSPDFJSScriptDescriptor *)scriptDescriptor platformDelegate:(nullable id<PSPDFJSPlatformDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END
