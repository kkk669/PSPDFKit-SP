// swift-tools-version: 5.7

import PackageDescription

let package = Package(
    name: "PSPDFKit",
    platforms: [
        .iOS(.v14),
        .macCatalyst(.v14)
    ],
    products: [
        .library(
            name: "PSPDFKit",
            targets: ["PSPDFKit", "PSPDFKitUI"]),
    ],
    targets: [
        .binaryTarget(
            name: "PSPDFKit",
            path: "xcframeworks/PSPDFKit.xcframework"),
        .binaryTarget(
            name: "PSPDFKitUI",
            path: "xcframeworks/PSPDFKitUI.xcframework"),
    ]
)
