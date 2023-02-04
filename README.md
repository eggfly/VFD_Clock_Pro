# VFD_Clock_Pro

## IO Pins

| Function | IO Pin | 备注 |
| -- | -- | -- |
| RTC_Interrupt | IO5 | PCF8563 |
| 光敏电阻_ADC | IO6 |  |
| Button_1 | IO7 |  |
| Button_2 (Boot) | IO0 | 启动模式选择 |
| Button_3 (EN) | N/A | ESP32_RESET |
| Buzzer | IO8 | 蜂鸣器 |
| VFD_DIN (MOSI) | IO9 |  |
| VFD_CLK | IO10 |  |
| VFD_CS | IO11 |  |
| VFD_RESET | IO12 |  |
| VFD_EN | IO13 | 需要拉高，拉高后给 VFD 供电 |
| RGB_LED (WS2812) | IO14 | 彩灯 |
| 拨码开关_左 | IO15 |  |
| 拨码开关_右 | IO16 |  |
| 拨码开关_下 | IO17 |  |
| 旋转编码器_A | IO38 |  |
| 旋转编码器_B | IO39 |  |
| 旋转编码器_S | IO40 |  |
| I2C_SDA | IO41 | 见下面 I2C 设备列表 |
| I2C_SCL | IO42 | 见下面 I2C 设备列表 |

## I2C Addresses



| Device | Address | 备注 |
| -- | -- | -- |
| SHT30 | 68 (0x44) | 温度/湿度传感器 |
| PCF8563 | 81 (0x51) | RTC |
| BMP280 | 118 (0x76)| 气压/温度传感器 |
