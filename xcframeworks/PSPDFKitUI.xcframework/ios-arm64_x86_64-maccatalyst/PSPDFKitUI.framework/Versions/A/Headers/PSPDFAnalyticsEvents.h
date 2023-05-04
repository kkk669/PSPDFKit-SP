//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFAnalytics.h>

// MARK: - Analytics Event Names

/// Prefix used for all analytics events. "pspdf".
/// A underscore (`_`) is added after this prefix to all analytics events as well.
PSPDF_EXPORT NSString *const PSPDFAnalyticsEventPrefix;

// MARK: Document

/// Document load event. This event signifies that the user has loaded a document.
///
/// Attributes:
///
/// - Key: `PSPDFAnalyticsEventAttributeNameDocumentType`. Value: `PSPDFAnalyticsEventAttributeValueDocumentTypeImage` for `PSPDFImageDocument`, `PSPDFAnalyticsEventAttributeValueDocumentTypeStandard` for other documents.

PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameDocumentLoad;

/// Spread change event. This signifies that the spread was changed.
///
/// Attributes:
///
/// - Key: `PSPDFAnalyticsEventAttributeValuePreviousSpreadIndex`. Value: integer spread index before the spread change.
/// - Key: `PSPDFAnalyticsEventAttributeValueNewSpreadIndex`. Value: integer spread index after the spread change.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameSpreadChange;

// MARK: Annotation Creation

/// Enter annotation creation mode event. This event signifies that the user opened the annotation toolbar. No attributes.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameAnnotationCreationModeEnter;
/// Exit annotation creation mode event. This event signifies that the user closed the annotation toolbar. No attributes.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameAnnotationCreationModeExit;

// MARK: Annotation Author

/// Show annotation creator dialog event. This signifies that the annotation creator dialog was shown to the user. No attributes.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameAnnotationCreatorDialogShow;
/// Cancel annotation creator dialog event. Signifies that the annotation creator dialog was cancelled by the user. No attributes.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameAnnotationCreatorDialogCancel;
/// Set annotation creator event. Signifies that the annotation creator dialog was confirmed by the user, setting a creator name. No attributes.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameAnnotationCreatorSet;

// MARK: Annotation Editing

/// Select annotation event. This signifies that the user selected an annotation, either by tapping it or by any other option (for example using the annotation list).
///
/// Attributes:
///
/// - Key: `PSPDFAnalyticsEventAttributeNameAnnotationType`. Value: `PSPDFAnnotationString` of the selected annotation.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameAnnotationSelect;
/// Create annotation event. This signifies that the user created an annotation and added it to the document.
///
/// Attributes:
///
/// - Key: `PSPDFAnalyticsEventAttributeNameAnnotationType`. Value: `PSPDFAnnotationString` of the created annotation.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameAnnotationCreate;
/// Delete annotation event. This signifies that the user deleted an annotation from the document.
///
/// Attributes:
///
/// - Key: `PSPDFAnalyticsEventAttributeNameAnnotationType`. Value: `PSPDFAnnotationString` of the deleted annotation.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameAnnotationDelete;

// MARK: Annotation Inspector

/// Show annotation inspector event. This signifies that the user has opened the annotation inspector for editing annotation properties, either via the annotation toolbar or by editing an existing annotation. No attributes.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameAnnotationInspectorShow;

// MARK: Text Selection

/// Select text event. This signifies that the user has selected text on the document. No attributes.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameTextSelect;

// MARK: Outline

/// Open outline event. This signifies that the user opened the outline containing the document outline, annotations, and bookmarks. No attributes.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameOutlineOpen;
/// Tap outline element in outline view event. This signifies that the user tapped an outline element in the outline view. No attributes.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameOutlineElementSelect;
/// Tap annotation in outline view event. This signifies that the user tapped an annotation in the outline view.
///
/// Attributes:
///
/// - Key: `PSPDFAnalyticsEventAttributeNameAnnotationType`. Value: `PSPDFAnnotationString` of the selected annotation.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameOutlineAnnotationSelect;

// MARK: Thumbnail Grid

/// Open thumbnail grid event. This signifies that the user opened the thumbnail grid view. No attributes.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameThumbnailGridOpen;

// MARK: Document Editor

/// Open document editor event. This signifies that the user opened the document editor. No attributes.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameDocumentEditorOpen;
/// Perform document editor action event. This signifies that the user performed an action inside the document editor.
///
/// Attributes:
///
/// - Key: `PSPDFAnalyticsEventAttributeNameAction`. Value: `PSPDFAnalyticsEventAttributeValueAction` the user performed in the document editor (like `PSPDFAnalyticsEventAttributeValueActionInsertNewPage`)
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameDocumentEditorAction;

// MARK: Bookmarks

/// Add bookmark event. This signifies that the user added a bookmark to the document. No attributes.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameBookmarkAdd;
/// Edit bookmarks event. This signifies that the user has entered bookmark editing mode inside the bookmark list. No attributes.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameBookmarkEdit;
/// Delete bookmark event. This signifies that the user has deleted a bookmark from the document. No attributes.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameBookmarkRemove;
/// Sort bookmark event. This signifies that the user changed moved the order of a bookmark item in the bookmark list. No attributes.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameBookmarkSort;
/// Rename bookmark event. This signifies that the user renamed a bookmark. No attributes.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameBookmarkRename;
/// Select bookmark event. This signifies that the user tapped a bookmark in the bookmark list. No attributes.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameBookmarkSelect;

// MARK: Search

/// Start search event. This signifies that the user started a search in the document by pressing the search icon (or any other way). No attributes.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameSearchStart;
/// Search result select event. This signifies that the user selected a search result after searching the document. No attributes.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameSearchResultSelect;

// MARK: Share

/// Share event. This signifies that the user has shared the document using the share sheet.
///
/// Attributes:
///
/// - Key: `PSPDFAnalyticsEventAttributeNameActivityType`. Value: Activity type the user selected as string.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameShare;

// MARK: Toolbar

/// Move toolbar event. This signifies that the toolbar was moved to a different location.
///
/// Attributes:
///
/// - Key: `PSPDFAnalyticsEventAttributeValueToolbarPosition`. Value: `PSPDFFlexibleToolbarPosition` of the destination.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameToolbarMove;

// MARK: Reader View

/// Reader View was shown. No attributes.
PSPDF_EXPORT PSPDFAnalyticsEventName const PSPDFAnalyticsEventNameReaderViewOpen;

// MARK: - Analytics Event Attributes

PSPDF_EXPORT PSPDFAnalyticsEventAttributeName const PSPDFAnalyticsEventAttributeNameDocumentType;
PSPDF_EXPORT PSPDFAnalyticsEventAttributeName const PSPDFAnalyticsEventAttributeNameAnnotationType;
PSPDF_EXPORT PSPDFAnalyticsEventAttributeName const PSPDFAnalyticsEventAttributeNameAction;
PSPDF_EXPORT PSPDFAnalyticsEventAttributeName const PSPDFAnalyticsEventAttributeNameActivityType;

PSPDF_EXPORT PSPDFAnalyticsEventAttributeValue const PSPDFAnalyticsEventAttributeValueDocumentTypeStandard;
PSPDF_EXPORT PSPDFAnalyticsEventAttributeValue const PSPDFAnalyticsEventAttributeValueDocumentTypeImage;

PSPDF_EXPORT PSPDFAnalyticsEventAttributeValue const PSPDFAnalyticsEventAttributeValueActionInsertNewPage;
PSPDF_EXPORT PSPDFAnalyticsEventAttributeValue const PSPDFAnalyticsEventAttributeValueActionRemoveSelectedPages;
PSPDF_EXPORT PSPDFAnalyticsEventAttributeValue const PSPDFAnalyticsEventAttributeValueActionDuplicateSelectedPages;
PSPDF_EXPORT PSPDFAnalyticsEventAttributeValue const PSPDFAnalyticsEventAttributeValueActionRotateSelectedPages;
PSPDF_EXPORT PSPDFAnalyticsEventAttributeValue const PSPDFAnalyticsEventAttributeValueActionExportSelectedPages;
PSPDF_EXPORT PSPDFAnalyticsEventAttributeValue const PSPDFAnalyticsEventAttributeValueActionSelectAllPages;
PSPDF_EXPORT PSPDFAnalyticsEventAttributeValue const PSPDFAnalyticsEventAttributeValueActionUndo;
PSPDF_EXPORT PSPDFAnalyticsEventAttributeValue const PSPDFAnalyticsEventAttributeValueActionRedo;

PSPDF_EXPORT PSPDFAnalyticsEventAttributeValue const PSPDFAnalyticsEventAttributeValueToolbarPosition;

PSPDF_EXPORT PSPDFAnalyticsEventAttributeValue const PSPDFAnalyticsEventAttributeValuePreviousSpreadIndex;
PSPDF_EXPORT PSPDFAnalyticsEventAttributeValue const PSPDFAnalyticsEventAttributeValueNewSpreadIndex;
