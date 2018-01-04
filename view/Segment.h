//
// Created by Culring on 2018-01-04.
//

#ifndef LEVEL5AUTONOMOUS_DRIVING_SEGMENT_H
#define LEVEL5AUTONOMOUS_DRIVING_SEGMENT_H

namespace view
{
    enum SegmentType{
        ANGLE_30,
        ANGLE_45,
        ANGLE_60,
        ANGLE_90
    };

    class Segment {
        SegmentType segmentType;
    };
}

#endif //LEVEL5AUTONOMOUS_DRIVING_SEGMENT_H
