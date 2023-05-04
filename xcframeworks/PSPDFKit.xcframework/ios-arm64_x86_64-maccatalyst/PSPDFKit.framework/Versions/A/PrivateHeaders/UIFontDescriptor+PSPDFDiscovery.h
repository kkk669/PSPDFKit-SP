//
//  Copyright © 2014-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFFontDownloader.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIFontDescriptor (PSPDFDiscovery)

/// Returns a list of fonts that can be downloaded from Apple.
///
/// @warning This method might block (network request)
+ (NSArray<UIFontDescriptor *> *)pspdf_downloadableFontDescriptors;

/// Get all fonts or a specific family.
+ (NSArray<UIFontDescriptor *> *)pspdf_fontFamilies;
+ (NSArray<UIFontDescriptor *> *)pspdf_fontDescriptorsForFamilyName:(NSString *)familyName;

/// Like `[UIFont fontNamesForFamilyName:]`, but with an improved sort order that matches Apple's Pages app.
@property (nonatomic, readonly) NSArray<UIFontDescriptor *> *pspdf_fontDescriptorsForFamily;

/// Shortcut for pspdf_fontName.
@property (nonatomic, readonly) NSString *pspdf_fontName;

/// Shortcut for pspdf_fontFamilyName. Will create an UIFont if the attribute is missing.
@property (nonatomic, readonly) NSString *pspdf_fontFamilyName;

/// Indicates whether the font needs to be downloaded first.
@property (nonatomic, readonly) BOOL pspdf_requiresDownloading;

@end

@interface UIFontDescriptor (PSPDFFontListPrivate)

/// By default certain less commonly used fonts are blocked automatically.
/// Array expects a list of regular expression strings.
+ (void)setPSPDFDefaultBlacklist:(NSArray *)defaultBlacklist;
+ (NSArray<NSString *> *)pspdf_defaultBlacklist;

/// Filters a list of `UIFontDescriptor` objects using the `pspdf_defaultBlocklist`.
+ (NSArray<UIFontDescriptor *> *)pspdf_filterFontDescriptors:(NSArray<UIFontDescriptor *> *)fontDescriptors;

/// Default list of filtered font descriptors.
+ (NSArray<UIFontDescriptor *> *)pspdf_defaultFilteredFontDescriptors;

@end

NS_ASSUME_NONNULL_END
