//
// Created by Culring on 2018-01-04.
//

#ifndef LEVEL5AUTONOMOUS_DRIVING_TRACK_H
#define LEVEL5AUTONOMOUS_DRIVING_TRACK_H

#include <vector>
#include "ViewSegment.h"

class ViewTrack {
    std::vector<ViewSegment> m_segments;

public:
    void addSegment(ViewSegment segment);
};

#endif //LEVEL5AUTONOMOUS_DRIVING_TRACK_H
