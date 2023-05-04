//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <PSPDFKit/PSPDFDrawingPoint.h>

#ifdef __cplusplus
bool operator==(const PSPDFDrawingPoint &, const PSPDFDrawingPoint &);

namespace PSPDF {

/**
 Makes drawing points nicer to use in C++.
 It is important that this type has the same memory layout as PSPDFDrawingPoint because
 we pass them around and encode them in NSValue expecting them to be interchangeable.
 */
struct __attribute__((objc_boxable)) DrawingPoint : PSPDFDrawingPoint {
    DrawingPoint(CGPoint point, CGFloat _intensity) {
        location = point;
        intensity = _intensity;
    }

    DrawingPoint(CGPoint point) : DrawingPoint(point, PSPDFDefaultIntensity) {}

    DrawingPoint(CGFloat x, CGFloat y) : DrawingPoint((CGPoint){x, y}) {}

    DrawingPoint(CGFloat x, CGFloat y, CGFloat _intensity) : DrawingPoint((CGPoint){x, y}, _intensity) {}

    DrawingPoint(PSPDFDrawingPoint const &drawingPoint) : DrawingPoint(drawingPoint.location, drawingPoint.intensity) {}

    DrawingPoint(NSString *string) {
        auto const drawingPoint = PSPDFDrawingPointFromString(string);
        location = drawingPoint.location;
        intensity = drawingPoint.intensity;
    }

    DrawingPoint() : DrawingPoint(PSPDFDrawingPointZero) {}

    bool operator==(const PSPDFDrawingPoint &rhs) const { return PSPDFDrawingPointIsEqualToPoint(*this, rhs); }

    operator CGPoint() const { return location; }

    bool isValid() const { return PSPDFDrawingPointIsFinite(*this); }

    NSString *toString() const { return PSPDFDrawingPointToString(*this); }
};
}
#endif
