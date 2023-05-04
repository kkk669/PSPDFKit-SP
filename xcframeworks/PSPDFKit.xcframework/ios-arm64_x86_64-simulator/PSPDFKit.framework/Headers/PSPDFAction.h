//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFModelObject.h>

/// Defines the type of an action that is defined in the PDF spec.
/// See the Adobe PDF Specification for more about actions and action types.
typedef NS_CLOSED_ENUM(UInt8, PSPDFActionType) {
    /// Go to a destination in the current document. (Resolve a uniform resource identifier)
    PSPDFActionTypeURL,

    /// (“Go-to remote”) Go to a destination in another document.
    PSPDFActionTypeGoTo,

    /// Similar to GoTo, defines an action to go to a specific page in another PDF document.
    /// Either via a specific page index or via a named destination.
    PSPDFActionTypeRemoteGoTo,

    /// (PDF1.2) Execute an action predefined by the conforming reader.
    /// (some that change page, some that execute other actions).
    ///
    /// @see `PSPDFNamedActionType` for possible values.
    PSPDFActionTypeNamed,

    /// Launch an application, usually to open a file.
    /// Current handled similar to `PSPDFRemoteGoToAction`.
    PSPDFActionTypeLaunch,

    /// (PDF 1.3) Execute a JavaScript script.
    PSPDFActionTypeJavaScript,

    /// (PDF 1.5) Controls the playing of multimedia content.
    PSPDFActionTypeRendition,

    /// (ISO 32000, ExtensionLevel 3; RichMedia annotation only)
    /// Specifies a command to be sent to the annotation’s handler.
    PSPDFActionTypeRichMediaExecute,

    /// (PDF 1.2) Send data to a uniform resource locator.
    PSPDFActionTypeSubmitForm,

    /// (PDF 1.2) Set fields to their default values.
    PSPDFActionTypeResetForm,

    /// (PDF 1.2) Play a sound. Not implemented.
    PSPDFActionTypeSound,

    /// (PDF 1.2) Play a movie. Not implemented.
    PSPDFActionTypeMovie,

    /// (PDF 1.2) Set an annotation’s Hidden flag.
    PSPDFActionTypeHide,

    /// Begin reading an article thread. Not implemented.
    PSPDFActionTypeThread,

    /// (PDF 1.2) Import field values from a file. Not implemented.
    PSPDFActionTypeImportData,

    /// (PDF 1.5) Set the states of optional content groups. Not implemented.
    PSPDFActionTypeSetOCGState,

    /// (PDF 1.5) Updates the display of a document, using a transition dictionary. Not implemented.
    PSPDFActionTypeTrans,

    /// (PDF 1.6) Set the current view of a 3D annotation. Not implemented.
    PSPDFActionTypeGoTo3DView,

    /// (“Go-to embedded”; PDF 1.6) Go to a destination in an embedded file.
    PSPDFActionTypeGoToEmbedded,

    PSPDFActionTypeUnknown = UINT8_MAX
} PSPDF_ENUM_SWIFT(Action.Kind);

@class PSPDFDocumentProvider;

NS_ASSUME_NONNULL_BEGIN

typedef NSString *PSPDFActionOption NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(Action.Option);

/// Set to @YES in the options dictionary to make links modal.
PSPDF_EXPORT PSPDFActionOption const PSPDFActionOptionModalKey;

/// Enable Autoplay if target is a video.
PSPDF_EXPORT PSPDFActionOption const PSPDFActionOptionAutoplayKey;

/// Enable/Disable controls. (e.g. Browser back/next buttons)
PSPDF_EXPORT PSPDFActionOption const PSPDFActionOptionControlsKey;

/// Loop the video.
PSPDF_EXPORT PSPDFActionOption const PSPDFActionOptionLoopKey;

/// Allow fullscreen presentation.
PSPDF_EXPORT PSPDFActionOption const PSPDFActionOptionFullscreenKey;

/// Set video offset.
PSPDF_EXPORT PSPDFActionOption const PSPDFActionOptionOffsetKey;

/// Set modal size.
PSPDF_EXPORT PSPDFActionOption const PSPDFActionOptionSizeKey;

/// Show as popover.
PSPDF_EXPORT PSPDFActionOption const PSPDFActionOptionPopoverKey;

/// Show cover, accepts string path.
PSPDF_EXPORT PSPDFActionOption const PSPDFActionOptionCoverKey;

/// The target page.
PSPDF_EXPORT PSPDFActionOption const PSPDFActionOptionPageKey;

/// Shows a button that activates links.
PSPDF_EXPORT PSPDFActionOption const PSPDFActionOptionButtonKey;

/// Controls if a close button is displayed, when `PSPDFActionOptionButtonKey` is used. Default will be YES.
PSPDF_EXPORT PSPDFActionOption const PSPDFActionOptionCloseButtonKey;

/// Constant to convert `PSPDFActionType` into `NSString` and back.
///
/// @note The transformer is added in the class initialize phase.
/// Requires `PSPDFAnnotation` to be accessed at least once.
PSPDF_EXPORT NSValueTransformerName const PSPDFActionTypeTransformerName NS_SWIFT_NAME(actionType);

/// Defines an action that is defined in the PDF spec, either from an outline or an annotation object.
/// See the Adobe PDF Specification for more about actions and action types.
///
/// @note The PDF spec defines both 'destinations' and 'actions'. PSPDFKit will convert a 'destination' into an equivalent `PSPDFActionTypeGoTo`.
PSPDF_CLASS_SWIFT(Action)
@interface PSPDFAction : PSPDFModel

/// Return the class responsible for `actionType`.
+ (nullable Class)actionClassForType:(PSPDFActionType)actionType;

// MARK: Properties

/// The PDF action type.
@property (nonatomic, readonly) PSPDFActionType type;

/// The actions parent action. Only set if it is a subAction of another action.
/// Automatically set when assigning `subActions` on the parent action.
@property (atomic, weak, readonly) PSPDFAction *parentAction;

/// PDF actions can be chained together. Defines the sub actions.
@property (nonatomic) NSArray<PSPDFAction *> *subActions;

/// If the action contained a pspdfkit:// URL, options between the URL will be parsed and extracted as key/value.
/// Can also be used for generic key/value storage (but remember that `PSPDFActions` usually are regenerated when using any of the convenience setters)
/// Will be persisted externally but not within PDF documents.
@property (nonatomic, readonly, nullable) NSDictionary<PSPDFActionOption, id> *options;

/// Returns the most appropriate description (Like Page 3 or https://www.pspdfkit.com/) for the action.
///
/// @param documentProvider Used to resolve named destinations and page labels. (Optional)
- (NSString *)localizedDescriptionWithDocumentProvider:(nullable PSPDFDocumentProvider *)documentProvider;

/// Returns a user representable string for the action type (Like "Link", "Open File", or "Submit Form").
///
/// @note This is an empty string for the base class, but subclasses might override it.
@property (nonatomic, readonly) NSString *localizedActionType;

@end

NS_ASSUME_NONNULL_END
