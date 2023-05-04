//
//  Copyright © 2018-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFJavaScriptActionEvent, PSPDFDocumentProvider;

/// Represents the environment of execution of a particular script. This
/// contains a reference to the platform classes that need to be manipulated by scripts.
PSPDF_OBJC_DIRECT_MEMBERS
@interface PSPDFJSEnvironment : NSObject

@property (nonatomic, nullable) PSPDFJavaScriptActionEvent *event;
@property (nonatomic, nullable) PSPDFDocumentProvider *documentProvider;

@end

PSPDF_OBJC_DIRECT_MEMBERS
@interface PSPDFJSScriptDescriptor : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

- (instancetype)initWithUuid:(NSString *)uuid environment:(PSPDFJSEnvironment *)environment NS_DESIGNATED_INITIALIZER;

/// Identifier for a script that will be tracked internally by the
/// VM. When execution completes successfully, fails, or requires
/// platform attention, this identifier will be provided to
/// evaluation observers so that a particular execution on a VM can
/// be identified. The simplest implementation could be based on a
/// hash of the script contents.
@property (nonatomic, readonly, copy) NSString *uuid;

/// Contents of the script. This property should be `nil` if the
/// script is loaded from a file, that is, the filePath property is
/// not `nil`. If both properties are present, the contents
/// property has precedence and that's what will be executed by the
/// virtual machine.
@property (nonatomic, copy, nullable) NSString *contents;

/// File path pointing to a JavaScript resource file.
@property (nonatomic, copy, nullable) NSString *filePath;

/// Evaluation environment of this script. That is, the Core context
/// that will be manipulated by the Adobe JS API.
@property (nonatomic, readonly) PSPDFJSEnvironment *environment;

@end

NS_ASSUME_NONNULL_END
