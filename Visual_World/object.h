#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "macro.h"
#include "type.h"

class Object {
private:
    Pos pos;
    bool detected;

public:
    Object() {}
    void reset(Pos pos);
    bool step_forward(int direction);
    void update();
    Pos get_pos();
    bool detect(Pos uav_pos);
    bool is_detected() { return detected; }
};

#endif
