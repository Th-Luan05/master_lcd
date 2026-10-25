
#include "ui/ui.h"
#include "esp_lvgl_port.h"
#include "giaodien.h"





void init_display(void)
{
    if (lvgl_port_lock(0)) {
        ui_init();
        lvgl_port_unlock();
    }
}