//
// Created by ztk on 2021-06-13.
// TODO much
//

#ifndef SAUERKRAUT_ANIMINFO_H
#define SAUERKRAUT_ANIMINFO_H

#define MAXANIMPARTS 3

#define ANIM_ALL         0x7F
#define ANIM_INDEX       0x7F
#define ANIM_LOOP        (1<<7)
#define ANIM_START       (1<<8)
#define ANIM_END         (1<<9)
#define ANIM_REVERSE     (1<<10)
#define ANIM_CLAMP       (ANIM_START|ANIM_END)
#define ANIM_DIR         0x780
#define ANIM_SECONDARY   11
#define ANIM_NOSKIN      (1<<22)
#define ANIM_SETTIME     (1<<23)
#define ANIM_FULLBRIGHT  (1<<24)
#define ANIM_REUSE       (1<<25)
#define ANIM_NORENDER    (1<<26)
#define ANIM_RAGDOLL     (1<<27)
#define ANIM_SETSPEED    (1<<28)
#define ANIM_NOPITCH     (1<<29)
#define ANIM_GHOST       (1<<30)
#define ANIM_FLAGS       (0x1FF<<22)

struct animinfo // description of a character's animation
{
    int anim, frame, range, basetime;
    float speed;
    uint varseed;

    animinfo() : anim(0), frame(0), range(0), basetime(0), speed(100.0f), varseed(0) {}

    bool operator==(const animinfo &o) const { return frame == o.frame && range == o.range &&
                                                      (anim & (ANIM_SETTIME | ANIM_DIR)) ==
                                                      (o.anim & (ANIM_SETTIME | ANIM_DIR)) &&
                                                      (anim & ANIM_SETTIME || basetime == o.basetime) &&
                                                      speed == o.speed;
    }

    bool operator!=(const animinfo &o) const { return frame != o.frame || range != o.range ||
                                                      (anim & (ANIM_SETTIME | ANIM_DIR)) !=
                                                      (o.anim & (ANIM_SETTIME | ANIM_DIR)) ||
                                                      (!(anim & ANIM_SETTIME) && basetime != o.basetime) ||
                                                      speed != o.speed;
    }
};

struct animinterpinfo // used for animation blending of animated characters
{
    animinfo prev, cur;
    int lastswitch;
    void *lastmodel;

    animinterpinfo() : lastswitch(-1), lastmodel(nullptr) {}

    void reset() { lastswitch = -1; }
};

#endif //SAUERKRAUT_ANIMINFO_H
