//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>

NS_ASSUME_NONNULL_BEGIN

/// Available policy events.
typedef NSString *PSPDFPolicyEvent NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(PolicyEvent);

/// Policy for Open In.
PSPDF_EXPORT PSPDFPolicyEvent const PSPDFPolicyEventOpenIn;
/// Policy for print.
PSPDF_EXPORT PSPDFPolicyEvent const PSPDFPolicyEventPrint;
/// Policy for mail.
PSPDF_EXPORT PSPDFPolicyEvent const PSPDFPolicyEventEmail;
/// Policy for message.
PSPDF_EXPORT PSPDFPolicyEvent const PSPDFPolicyEventMessage;
/// Policy for Quick Look.
PSPDF_EXPORT PSPDFPolicyEvent const PSPDFPolicyEventQuickLook;
/// Policy for audio recording.
PSPDF_EXPORT PSPDFPolicyEvent const PSPDFPolicyEventAudioRecording;
/// Policy for the camera.
PSPDF_EXPORT PSPDFPolicyEvent const PSPDFPolicyEventCamera;
/// Policy for the photo library.
PSPDF_EXPORT PSPDFPolicyEvent const PSPDFPolicyEventPhotoLibrary;
/// Policy for the pasteboard. Includes Copy/Paste.
PSPDF_EXPORT PSPDFPolicyEvent const PSPDFPolicyEventPasteboard;
/// Policy for submitting forms.
PSPDF_EXPORT PSPDFPolicyEvent const PSPDFPolicyEventSubmitForm;
/// Policy for the network.
PSPDF_EXPORT PSPDFPolicyEvent const PSPDFPolicyEventNetwork;

/// The security auditor protocol defines a custom set of overrides for various security related tasks.
PSPDF_PROTOCOL_SWIFT(ApplicationPolicy)
@protocol PSPDFApplicationPolicy

/// Returns YES when the `PSPDFPolicyEvent` is allowed.
/// `isUserAction` is a hint that indicates if we're in a user action or an automated test.
/// If it's a user action, it is appropriate to present an alert explaining the lack of permissions.
- (BOOL)hasPermissionForEvent:(PSPDFPolicyEvent)event isUserAction:(BOOL)isUserAction;

@end

/// The default security auditor simply returns YES for every request.
PSPDF_CLASS_SWIFT(DefaultApplicationPolicy)
@interface PSPDFDefaultApplicationPolicy : NSObject<PSPDFApplicationPolicy>
@end

NS_ASSUME_NONNULL_END
