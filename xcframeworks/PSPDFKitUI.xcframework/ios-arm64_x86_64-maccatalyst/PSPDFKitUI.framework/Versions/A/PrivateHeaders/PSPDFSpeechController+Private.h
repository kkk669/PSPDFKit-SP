//
//  Copyright © 2020-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKitUI/PSPDFSpeechController.h>

NS_ASSUME_NONNULL_BEGIN

@interface PSPDFSpeechController()

/// Exported for testing. Returns a full language identifier (e.g. de-DE or en-US), not just the BCP-47 language tag.
+ (NSString *)autodetectedLanguageForString:(NSString *)string availableLanguageCodes:(NSArray<NSString *> *)languageCodes;

@end

NS_ASSUME_NONNULL_END
