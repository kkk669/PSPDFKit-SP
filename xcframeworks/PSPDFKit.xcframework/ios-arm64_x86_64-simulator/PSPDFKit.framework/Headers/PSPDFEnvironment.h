//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

// clang-format off
#if __has_include(<QuartzCore/QuartzCore.h>)
#import <QuartzCore/QuartzCore.h>
#endif
// clang-format on

#if TARGET_OS_OSX
#import <Cocoa/Cocoa.h>
#else
#import <UIKit/UIKit.h>
#endif

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFMacros.h>
#import <PSPDFKit/PSPDFNamespace.h>
#else
#import "PSPDFNamespace.h"
#import "PSPDFMacros.h"
#endif

#define PSPDF_STRINGIZE2(s) #s
#define PSPDF_STRINGIZE(s) PSPDF_STRINGIZE2(s)

#ifndef PSPDF_CUSTOM_PREFIX
#define PSPDF_PREFIX "PSPDF"
#else
#define PSPDF_PREFIX PSPDF_STRINGIZE(PSPDF_CUSTOM_PREFIX) "_PSPDF"
#endif

#ifndef PSPDF_CUSTOM_TYPE_DEFINED
#define PSPDF_CUSTOM_TYPE_DEFINED
    // Swift workaround https://bugs.swift.org/browse/SR-6958 (still unresolved as of Jan 27, 2020)
    // src: https://opensource.apple.com/source/objc4/objc4-706/runtime/NSObjCRuntime.h.auto.html
    #if __LP64__ || (TARGET_OS_EMBEDDED && !TARGET_OS_IPHONE) || TARGET_OS_WIN32 || NS_BUILD_32_LIKE_64
    typedef unsigned long PSPDFPageIndex NS_SWIFT_NAME(PageIndex);
    typedef unsigned long PSPDFPageCount NS_SWIFT_NAME(PageCount);
    typedef unsigned long PSPDFFileIndex NS_SWIFT_NAME(FileIndex);
    #else
    typedef unsigned int PSPDFPageIndex NS_SWIFT_NAME(PageIndex);
    typedef unsigned int PSPDFPageCount NS_SWIFT_NAME(PageCount);
    typedef unsigned int PSPDFFileIndex NS_SWIFT_NAME(FileIndex);
    #endif
#endif

#if TARGET_OS_OSX

#define UIColor NSColor
#define UIImage NSImage
#define UIFont NSFont
#define UIBezierPath NSBezierPath
#define UIFontDescriptor NSFontDescriptor

#define UIFontDescriptorAttributeName NSFontDescriptorAttributeName
#define UIFontDescriptorSymbolicTraits NSFontDescriptorSymbolicTraits
#define UIFontDescriptorTraitBold NSFontDescriptorTraitBold
#define UIFontDescriptorTraitItalic NSFontDescriptorTraitItalic
#define UIFontDescriptorTraitsAttribute NSFontTraitsAttribute
#define UIFontDescriptorNameAttribute NSFontNameAttribute
#define UIFontDescriptorFamilyAttribute NSFontFamilyAttribute
#define UIFontDescriptorSizeAttribute NSFontSizeAttribute

#define NSUnderlineStyle NSInteger

#define NSTextAlignmentToCTTextAlignment PSPDFTextAlignmentToCTTextAlignment
PSPDF_EXPORT CTTextAlignment PSPDFTextAlignmentToCTTextAlignment(NSTextAlignment nsTextAlignment);

#define UIEdgeInsets NSEdgeInsets
#define UIEdgeInsetsZero NSEdgeInsetsZero
#define UIEdgeInsetsMake NSEdgeInsetsMake
#define UIEdgeInsetsEqualToEdgeInsets NSEdgeInsetsEqual

#define UIEdgeInsetsInsetRect PSPDFEdgeInsetInsetRect
#define UIEdgeInsetsFromString PSPDFEdgeInsetFromString
#define NSStringFromUIEdgeInsets NSStringFromPSPDFEdgeInset
PSPDF_EXPORT CGRect PSPDFEdgeInsetInsetRect(CGRect rect, UIEdgeInsets insets);
PSPDF_EXPORT NSString *NSStringFromPSPDFEdgeInset(UIEdgeInsets insets);
PSPDF_EXPORT UIEdgeInsets PSPDFEdgeInsetFromString(NSString *string);

#define NSStringFromCGPoint PSPDF_NSStringFromCGPoint
#define NSStringFromCGSize PSPDF_NSStringFromCGSize
#define NSStringFromCGRect PSPDF_NSStringFromCGRect
#define NSStringFromCGAffineTransform PSPDF_NSStringFromCGAffineTransform

PSPDF_EXPORT NSString *PSPDF_NSStringFromCGPoint(CGPoint point);
PSPDF_EXPORT NSString *PSPDF_NSStringFromCGSize(CGSize size);
PSPDF_EXPORT NSString *PSPDF_NSStringFromCGRect(CGRect rect);
PSPDF_EXPORT NSString *PSPDF_NSStringFromCGAffineTransform(CGAffineTransform transform);

#define CGPointFromString PSPDF_CGPointFromString
#define CGSizeFromString PSPDF_CGSizeFromString
#define CGRectFromString PSPDF_CGRectFromString
#define CGAffineTransformFromString PSPDF_CGAffineTransformFromString

PSPDF_EXPORT CGPoint PSPDF_CGPointFromString(NSString *string);
PSPDF_EXPORT CGSize PSPDF_CGSizeFromString(NSString *string);
PSPDF_EXPORT CGRect PSPDF_CGRectFromString(NSString *string);
PSPDF_EXPORT CGAffineTransform PSPDF_CGAffineTransformFromString(NSString *string);

#define UIApplicationDidReceiveMemoryWarningNotification PSPDFApplicationDidReceiveMemoryWarningNotification
#define UIApplicationWillEnterForegroundNotification NSApplicationWillBecomeActiveNotification
#define UIApplicationDidEnterBackgroundNotification NSApplicationDidHideNotification
#define UIApplicationWillTerminateNotification NSApplicationWillTerminateNotification
#define UIApplicationDidFinishLaunchingNotification NSApplicationDidFinishLaunchingNotification
PSPDF_EXPORT NSNotificationName const PSPDFApplicationDidReceiveMemoryWarningNotification;

#else

#define NSLineCapStyle CGLineCap
#define NSLineJoinStyle CGLineJoin

// Helper to get the shared application object, also for extensions.
PSPDF_EXPORT UIApplication *PSPDFSharedApplication(void) NS_SWIFT_NAME(SharedApplication());

#endif
