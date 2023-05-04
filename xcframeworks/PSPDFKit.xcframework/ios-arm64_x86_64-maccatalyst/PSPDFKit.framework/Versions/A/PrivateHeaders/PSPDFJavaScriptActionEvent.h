//
//  Copyright © 2013-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment+Private.h>

#import <PSPDFKit/PSPDFDocumentProvider.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_CLOSED_ENUM(NSInteger, PSPDFJavaScriptActionEventName) {
    /// This event occurs whenever a user types a keystroke into a text box or combo box (including cut and paste operations)
    /// or selects an item in a combo box list or list box field. A keystroke script may limit the type of keys allowed.
    /// For example, a numeric field might only allow numeric characters.
    PSPDFJavaScriptActionEventNameKeystroke,
    /// This event is the first event generated for a field after the value has been committed so that a JavaScript can verify
    /// that the value entered was correct.
    /// If the validate event is successful, the next event triggered is the calculate event.
    PSPDFJavaScriptActionEventNameValidate,
    /// This event occurs after the mouse-down event but before the mouse-up after the field gains the focus.
    /// This routine is called regardless of whether a mouse click is used to activate the screen annotation
    /// (for example, the tab key might be used). It is the best place to perform processing that must be done before the
    /// user can interact with the field.
    PSPDFJavaScriptActionEventNameFocus,
    /// This event occurs after all other events, just as the screen annotation loses focus.
    /// This event is generated regardless of whether a mouse click is used to deactivate the screen annotation
    /// (for example, the tab key might be used).
    PSPDFJavaScriptActionEventNameBlur,
    /// This event is triggered once all dependent calculations have been performed.
    /// It allows the attached JavaScript to change the way that the data value appears to a user (also known as its presentation or
    /// appearance). For example, if a data value is a number and the context in which it should be displayed is currency,
    /// the formatting script can add a dollar sign ($) to the front of the value and limit it to two decimal places past
    /// the decimal point.
    PSPDFJavaScriptActionEventNameFormat,
    /// This event is defined when a change in a form requires that all fields that have a calculation script attached to
    /// them be executed. All fields that depend on the value of the changed field will now be recalculated.
    PSPDFJavaScriptActionEventNameCalculate,
    /// This event is triggered when the user clicks a form field and releases the mouse button.
    /// This is the typical place to attach routines such as the submit action of a form.
    /// A mouse-up event will not occur unless a mouse-down event has already occurred.
    PSPDFJavaScriptActionEventNameMouseUp,
    /// This event is triggered when a user starts to click a form field and the mouse button is still down.
    /// A mouse-down event does not occur unless a mouse enter event has already occurred.
    /// It is advised that you perform very little processing during this event (for example, play a short sound).
    PSPDFJavaScriptActionEventNameMouseDown,
    /// This event is triggered when a user moves the pointer inside the rectangle of a field.
    /// This is the typical place to open a text field to display help text, for example.
    PSPDFJavaScriptActionEventNameMouseEnter,
    /// This event occurs when a user moves the mouse pointer outside of the rectangle of a field.
    /// A mouse exit event will not occur unless a mouse enter event has already occurred.
    PSPDFJavaScriptActionEventNameMouseExit,
    /// (Unsupported).
    PSPDFJavaScriptActionEventNameWillPrint,
    /// (Unsupported).
    PSPDFJavaScriptActionEventNameDidPrint,
    /// (Unsupported).
    PSPDFJavaScriptActionEventNameWillSave,
    /// (Unsupported).
    PSPDFJavaScriptActionEventNameDidSave,
    /// (Unsupported).
    PSPDFJavaScriptActionEventNameInit,
    /// (Unsupported).
    PSPDFJavaScriptActionEventNameExec,
    /// (Unsupported).
    PSPDFJavaScriptActionEventNameOpen,
    /// (Unsupported).
    PSPDFJavaScriptActionEventNameClose,
} PSPDF_ENUM_SWIFT(JavaScriptActionEvent.Name);

typedef NS_CLOSED_ENUM(NSInteger, PSPDFJavaScriptActionEventType) {
    /// The JavaScript action comes from a form field.
    PSPDFJavaScriptActionEventTypeField,
    /// (Unsupported).
    PSPDFJavaScriptActionEventTypeBatch,
    /// (Unsupported).
    PSPDFJavaScriptActionEventTypeExternal,
    /// (Unsupported).
    PSPDFJavaScriptActionEventTypeConsole,
    /// (Unsupported).
    PSPDFJavaScriptActionEventTypeBookmark,
    /// (Unsupported).
    PSPDFJavaScriptActionEventTypeApp,
    /// (Unsupported).
    PSPDFJavaScriptActionEventTypeLink,
    /// (Unsupported).
    PSPDFJavaScriptActionEventTypeDoc,
    /// (Unsupported).
    PSPDFJavaScriptActionEventTypePage,
    /// (Unsupported).
    PSPDFJavaScriptActionEventTypeMenu,
} PSPDF_ENUM_SWIFT(JavaScriptActionEvent.Kind);

/// Information needed by the "source" and "target" properties.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(JSEventSourceTargetInfo) PSPDF_OBJC_DIRECT_MEMBERS_EXCEPT_TESTS
@interface PSPDFJSEventSourceTargetInfo : NSObject

- (nonnull instancetype)initWithDocumentProvider:(nullable PSPDFDocumentProvider *)documentProvider
                                             fqn:(nullable NSString *)fqn;

@property (nonatomic, readonly, nullable) PSPDFDocumentProvider *documentProvider;
@property (nonatomic, readonly, nullable) NSString *fqn;

@end


/// The kind of values that can be part of JS event.
PSPDF_CLASS_SUBCLASSING_RESTRICTED_SWIFT(JSEventValue) PSPDF_OBJC_DIRECT_MEMBERS_EXCEPT_TESTS
@interface PSPDFJSEventValue : NSObject

- (nonnull instancetype)initWithNumberValue:(nullable NSNumber *)numberValue
                                stringValue:(nullable NSString *)stringValue;

/// A JavaScript event value represented as a floating point number.
@property (nonatomic, readonly, nullable) NSNumber *numberValue;

/// A JavaScript event value represented as a string.
@property (nonatomic, readonly, nullable) NSString *stringValue;

//// Synthesized properties.
// TODO: These methods will probably go away when we port all the field JS functions to Core.
@property (nonatomic, copy, readonly, nullable) NSString *valueAsString;
@property (nonatomic, readonly, nullable) NSNumber *valueAsNumber;

@end

/// A class that models a JavaScript action event.
///
/// All JavaScript scripts are executed as the result of a particular event. For each of these events, JavaScript creates an event object.
/// During the occurrence of each event, you can access this object to get and possibly manipulate information about the current
/// state of the event.
/// Each event has a type and a name property that uniquely identify the event. This section describes all the events,
/// listed as type/name pairs, and indicates which additional properties, if any, they define.
/// The rc property of an event is its return code. The description for each event describes whether it listens to
/// (is affected by) the return code.
///
/// It is important for JavaScript writers to know when these events occur and in what order they are processed.
/// Some methods or properties can only be accessed during certain events.
PSPDF_TEST_CLASS_SUBCLASSING_RESTRICTED_SWIFT(JavaScriptActionEvent)
@interface PSPDFJavaScriptActionEvent : NSObject

#if !defined(PSPDF_UI_TESTS) && !defined(TESTING)
PSPDF_EMPTY_INIT_UNAVAILABLE
#endif

/// The type of the current event. The type and name together uniquely
/// identify the event.
@property (nonatomic, readonly) PSPDFJavaScriptActionEventType type;

/// The name of the current event as a text string. The type and name
/// together uniquely identify the event.
@property (nonatomic, readonly) PSPDFJavaScriptActionEventName name;

/// This property has different meanings for different field events:
///
/// - For the Field/Validate event, it is the value that the field
///   contains when it is committed. For a combo box, it is the face
///   value, not the export value
///
/// - For a Field/Calculate event, JavaScript should set this property. It
///   is the value that the field should take upon completion of the
///   event.
///
/// - For a Field/Format event, JavaScript should set this property. It is
///   the value used when generating the appearance for the field. By
///   default, it contains the value that the user has committed. For a
///   combo box, this is the face value, not the export value.
///
/// - For a Field/Keystroke event, it is the current value of the
///   field. If modifying a text field, for example, this is the text in
///   the text field before the keystroke is applied.
///
/// - For Field/Blur and Field/Focus events, it is the current value of
///   the field. During these two events, event.value is read only. That is,
///   the field value cannot be changed by setting event.value.  Beginning
///   with Acrobat 5.0, for a list box that allows multiple selections (see
///   field.multipleSelection), the following behavior occurs. If the field
///   value is an array (that is, multiple items are selected), event.value
///   returns an empty string when getting, and does not accept setting.
@property (nonatomic, nullable) PSPDFJSEventValue *value;

/// This property mirrors the richValue property of the Field object
/// and the event.value property for each event.
@property (nonatomic, copy) NSArray *richValue;

/// The Field object that triggered the calculation event. This object
/// is usually different from the target of the event, which is the
/// field that is being calculated.
@property (nonatomic, readonly, nullable) PSPDFJSEventSourceTargetInfo *source;

/// The target object that triggered the event. In all mouse, focus, blur,
/// calculate, validate, and format events, it is the Field object that
/// triggered the event. In other events, such as page open and close, it
/// is the Doc or this object.
@property (nonatomic, readonly, nullable) PSPDFJSEventSourceTargetInfo *target;

/// Tries to return the name of the JavaScript being executed. Can
/// be used for debugging purposes to help identify the code causing
/// exceptions to be thrown. Common values of targetName include:
/// - The folder-level script file name for App/Init events
/// - The document-level script name forDoc/Open events
/// - The PDF file name being processed for Batch/Exec events
/// - The field name for Field events
/// - The menu item name for Menu/Exec events
/// - The screen annotation name for Screen events (multimedia events)
/// When an exception is thrown, targetName is reported if there is an identifiable name.
@property (nonatomic, copy, readonly) NSString *targetName;

/// A string specifying the change in value that the user has just
/// typed. A JavaScript may replace part or all of this string with
/// different characters. The change may take the form of an
/// individual keystroke or a string of characters (for example, if
/// a paste into the field is performed).
@property (nonatomic, copy) NSString *change;

/// Contains the export value of the change and is available only
/// during a Field/Keystroke event for list boxes and combo boxes.
/// For the list box, the keystroke script, if any, is entered under
/// the Selection Change tab in the properties dialog box.
/// For the combo box, changeEx is only available if the pop-up list
/// is used—that is, a selection (with the mouse or the keyboard) is being
/// made from the list. If the combo is editable and the user types in an
/// entry, the Field/Keystroke event behaves as for a text field (that is,
/// there are no changeEx or keyDown event properties).  Beginning with
/// Acrobat 6.0, event.changeEx is defined for text fields. When
/// event.fieldFull is true, changeEx is set to the entire text string the
/// user attempted to enter and event.change is the text string cropped to
/// what fits within the field. Use event.richChangeEx (and
/// event.richChange) to handle rich text fields.
@property (nonatomic, readonly) id changeEx;

/// The starting position of the current text selection during a
/// keystroke event.
@property (nonatomic) int32_t selStart;

/// The ending position of the current text selection during a
/// keystroke event.
@property (nonatomic) int32_t selEnd;

/// Specifies the change in value that the user has just typed. The
/// richChange property is only defined for rich text fields and mirrors
/// the behavior of the event.change property. The value of richChange is
/// an array of Span objects that specify both the text entered into the
/// field and the formatting. Keystrokes are represented as single member
/// arrays, while rich text pasted into a field is represented as an array
/// of arbitrary length.  When event.fieldFull is true, richChangeEx is
/// set to the entire rich formatted text string the user attempted to
/// enter and event.richChange is the rich formatted text string cropped
/// to what fits within the field. Use event.changeEx (and event.change)
/// to handle (plain) text fields.
@property (nonatomic, copy) NSArray *richChange;

/// This property is only defined for rich text fields. It mirrors the
/// behavior of the event.changeEx property for text fields. Its value is
/// an array of Span objects that specify both the text entered into the
/// field and the formatting. Keystrokes are represented as single member
/// arrays, while rich text pasted into a field is represented as an array
/// of arbitrary length.  If event.fieldFull is true, richChangeEx is set
/// to the entire rich formatted text string the user attempted to enter
/// and event.richChange is the rich formatted text string cropped to what
/// fits within the field. Use event.changeEx (and event.change) to handle
/// (plain) text fields.
@property (nonatomic, copy) NSArray *richChangeEx;

/// Determines how a form field will lose focus. Values are:
/// 0 — Value was not committed (for example, escape key was pressed).
/// 1 — Value was committed because of a click outside the field using the mouse.
/// 2 — Value was committed because of pressing the Enter key.
/// 3 — Value was committed by tabbing to a new field.
@property (nonatomic, readonly) int32_t commitKey;

/// Set to true when the user attempts to enter text that does not fit
/// in the field due to either a space limitation (the Field object
/// property doNotScroll is set to true) or the maximum character limit
/// (the Field object property charLimit is set to a positive
/// value). When fieldFull is true, event.changeEx is set to the entire
/// text string the user attempted to enter and event.change is the text
/// string cropped to what fits within the field.  Only available in
/// keystroke events for text fields.
@property (nonatomic, readonly) BOOL fieldFull;

/// Available only during a keystroke event for list box and combo
/// box. For a list box or the pop-up part of a combo box, the value is
/// true if the arrow keys were used to make a selection, false otherwise.
/// For the combo box, keyDown is only available if the pop-up part of it
/// is used, that is, a selection (with the mouse or the keyboard) is
/// being made from the pop-up. If the combo is editable and the user
/// types in an entry, the Field/Keystroke event behaves as for a text
/// field (that is, there are no changeEx or keyDown event properties).
@property (nonatomic, readonly) BOOL keyDown;

/// Specifies whether the modifier key is down during a particular
/// event. The modifier key on the Microsoft Windows platform is
/// Control and on the Mac OS platform is Option or Command. This
/// property is not supported on UNIX.
@property (nonatomic, readonly) BOOL modifier;

/// Used for validation. Indicates whether a particular event in the
/// event chain should succeed. Set to false to prevent a change
/// from occurring or a value from committing. The default is true.
@property (nonatomic) BOOL rc;

/// true if the shift key is down during a particular event, false
/// otherwise.
@property (nonatomic, readonly) BOOL shift;

/// Verifies the current keystroke event before the data is
/// committed. It can be used to check target form field values to
/// verify, for example, whether character data was entered instead of
/// numeric data. JavaScript sets this property to true after the last
/// keystroke event and before the field is validated.
@property (nonatomic, readonly) BOOL willCommit;

@end

NS_ASSUME_NONNULL_END
