#include <Arduino.h>
#include "driver/rmt.h"

#define DATA_PIN        GPIO_NUM_13
#define RMT_CHANNEL_TX  RMT_CHANNEL_0

void setup() {
    Serial.begin(115200);

    rmt_config_t rmtConfig;

    rmtConfig.rmt_mode      = RMT_MODE_TX;
    rmtConfig.channel       = RMT_CHANNEL_TX;
    rmtConfig.clk_div       = 4; // 50ns
    rmtConfig.gpio_num      = DATA_PIN;
    rmtConfig.mem_block_num = 8;

    rmt_config(&rmtConfig);
    rmt_driver_install(rmtConfig.channel, 0, 0);
}

// UCS5603, UCS5603B, SJ1221 Protocol
// https://github.com/FastLED/FastLED/files/1865669/SJ1221.control.protocol.pdf
// 0 (HIGH 350us -> LOW 900us)
// 1 (HIGH 700us -> LOW 550us)

rmt_item32_t rmtReset[1] = {
    // Reset 250us
    2500, 0, 2500, 0,
};

rmt_item32_t rmtWorkCode[61] = {
    // 1 (0b111111111111)
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    // 2 (0b111111111111)
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    // 3 (0b111111111111)
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    // 4 (0b111111111111)
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    // 5 (0b000000000001)
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    14, 1, 11, 0,

    // Wait Time (low for ~15us)
    150, 0, 150, 0,
};


rmt_item32_t rmtCurrentSetting[12] = {
    // 18mA for RGB (0b101110111011)
    14, 1, 11, 0,
    7, 1, 18, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    7, 1, 18, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    7, 1, 18, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
};

rmt_item32_t rmtWhite[36] = {
    // G
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    // R
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    // B
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
};

rmt_item32_t rmtRed[36] = {
    // G
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    // R
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    14, 1, 11, 0,
    // B
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
    7, 1, 18, 0,
};

void loop() {
    // RESET -> WORK CODE -> CURRENT SETTING -> RGB 36BIT 1st -> ... -> RGB 36BIT Nth 
    rmt_write_items(RMT_CHANNEL_TX, rmtReset, 1, false);
    rmt_write_items(RMT_CHANNEL_TX, rmtWorkCode, 61, false);
    rmt_write_items(RMT_CHANNEL_TX, rmtCurrentSetting, 12, false);
    rmt_write_items(RMT_CHANNEL_TX, rmtWhite, 36, false);
    rmt_write_items(RMT_CHANNEL_TX, rmtWhite, 36, false);
    rmt_write_items(RMT_CHANNEL_TX, rmtWhite, 36, false);
    rmt_write_items(RMT_CHANNEL_TX, rmtWhite, 36, false);
    rmt_write_items(RMT_CHANNEL_TX, rmtWhite, 36, false);
    rmt_write_items(RMT_CHANNEL_TX, rmtWhite, 36, false);
    rmt_write_items(RMT_CHANNEL_TX, rmtWhite, 36, false);
    rmt_write_items(RMT_CHANNEL_TX, rmtWhite, 36, false);
    rmt_write_items(RMT_CHANNEL_TX, rmtWhite, 36, false);
    rmt_write_items(RMT_CHANNEL_TX, rmtWhite, 36, false);
    rmt_write_items(RMT_CHANNEL_TX, rmtWhite, 36, true);
}