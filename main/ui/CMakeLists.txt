SET(SOURCES screens/ui_ScreenSetting.c
    screens/ui_ScreenCn.c
    screens/ui_ScreenCb.c
    screens/ui_ScreenStandby.c
    screens/ui_ScreenHome.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_028_png.c
    images/ui_img_house_png.c
    images/ui_img_settings_png.c
    images/ui_img_1470730272.c
    images/ui_img_nensang_png.c
    images/ui_img_wifi_png.c
    images/ui_img_62997641.c
    images/ui_img_117366239.c
    images/ui_img_1676977835.c
    images/ui_img_lightbulb_png.c
    images/ui_img_may180_png.c
    images/ui_img_set190_png.c
    images/ui_img_2034138760.c
    images/ui_img_mua180_png.c
    images/ui_img_dem180_png.c
    images/ui_img_muto180_png.c
    images/ui_img_754235436.c
    fonts/ui_font_Tiengviet14.c
    fonts/ui_font_Tiengviet16.c
    fonts/ui_font_Tiengviet30.c)

add_library(ui ${SOURCES})
