file(GLOB_RECURSE SRC_UI
    "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.c"
)

idf_component_register(
    SRCS
        "main.c"
        "LCD.c"
        "giaodien.c"
        "app_config.c"
        "tien_ich.c"
        "node_comm.c"
        "automation.c"
        "ota_app.c"
        "mqtt_app.c"
        "giaodien.c"
        "wifi_mgr.c"
        ${SRC_UI}
    INCLUDE_DIRS
        "."
        "ui"
    PRIV_REQUIRES nvs_flash esp_wifi esp_event mqtt json esp_http_client esp_https_ota app_update bt esp_timer esp_netif lwip
)