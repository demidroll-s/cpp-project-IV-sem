#include "testing.h"

static bool debug_enabled = false;
 
bool is_debug_enabled()
{
    return debug_enabled;
}
 
void set_debug_enabled(bool enable)
{
    debug_enabled = enable;
}