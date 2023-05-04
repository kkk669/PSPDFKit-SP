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

@class PSPDFRedactionAnnotation;
@protocol PSPDFRedactionTrackerDelegate;

/// Used to keep track of loaded and added redaction in a document.
/// Can be used as an alternative for parsing the whole document to look for annotations.
///
/// @note Uses `uuidForReplies` instead of the redaction annotation instances to keep track of the redactions.
@interface PSPDFRedactionTracker : NSObject

/// The currently tracked redactions.
@property (nonatomic, readonly) NSSet<NSString *> *trackedRedactions;

/// Delegate for callbacks when the tracked redactions are changing.
@property (nonatomic, weak) id<PSPDFRedactionTrackerDelegate> delegate;

/// Add tracked redactions.
- (void)addTrackedRedactions:(NSArray<PSPDFRedactionAnnotation *> *)redactionAnnotations;

/// Remove tracked redactions.
- (void)removeTrackedRedactions:(NSArray<PSPDFRedactionAnnotation *> *)redactionAnnotations;

/// Removes all tracked redactions.
- (void)resetAllTrackedRedactions;

@end

/// Delegate for the redaction tracker, informing about changes in tracked redactions.
@protocol PSPDFRedactionTrackerDelegate

/// Called when the redaction tracker changes its tracked redactions.
- (void)redactionTrackerDidChangeTrackedRedactions:(PSPDFRedactionTracker *)redactionTracker;

@end

NS_ASSUME_NONNULL_END
