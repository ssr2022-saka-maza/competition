#include "ps4operation/Log.hpp"

void ps4operation::Log::operate(const ssr::PS4Value & value) {
    char log[256] = "";
    sprintf_P(
        log,
        PSTR("(%#x %#x) (%#x %#x) [%d %d %d %d] [%d %d %d %d] [%d %d %d] [%d %#x %d] [%d %#x %d]\n"),
        value.lstick.x, value.lstick.y,
        value.rstick.x, value.rstick.y,
        value.up, value.right, value.down, value.left,
        value.triangle, value.circle, value.cross, value.square,
        value.ps, value.share, value.options,
        value.l1, value.l2, value.l3,
        value.r1, value.r2, value.r3
    );
    Serial.print(log);
}
