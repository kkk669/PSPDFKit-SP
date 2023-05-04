//
//  Copyright © 2017-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFEnvironment.h>
#import <PSPDFKit/PSPDFModelObject.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

@class PSPDFBaseConfigurationBuilder;

/// Used for various configuration options.
///
/// @see PSPDFConfiguration
PSPDF_CLASS_SWIFT(BaseConfiguration)
@interface PSPDFBaseConfiguration<BuilderType : __kindof PSPDFBaseConfigurationBuilder *> : PSPDFModel

PSPDF_EMPTY_INIT_UNAVAILABLE

+ (instancetype)defaultConfiguration;

- (instancetype)initWithBuilder:(BuilderType)builder NS_DESIGNATED_INITIALIZER;

/// Returns a copy of the default configuration.
/// You can provide a `builderBlock` to change the value of properties.
+ (instancetype)configurationWithBuilder:(nullable NS_NOESCAPE void (^)(BuilderType))builderBlock;

/// Copies an existing configuration and all settings + modifies with new changes.
- (instancetype)configurationUpdatedWithBuilder:(NS_NOESCAPE void (^)(BuilderType))builderBlock;

@end

/// Base class for building a configuration object.
PSPDF_CLASS_SWIFT(BaseConfigurationBuilder)
@interface PSPDFBaseConfigurationBuilder : NSObject

PSPDF_EMPTY_INIT_UNAVAILABLE

/// Defines the target class for the readonly configuration object.
@property (nonatomic, class, readonly) Class configurationTargetClass;

/// The actual configuration builder.
@property (nonatomic, readonly) __kindof PSPDFBaseConfiguration *build;

/// Resets all data to the default values. Called at init time.
- (void)reset;

@end

NS_ASSUME_NONNULL_END
