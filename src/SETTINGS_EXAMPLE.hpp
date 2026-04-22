/* Wifi Properties*/
#define WIFI_SSID "ssid"
#define WIFI_PSK "psk"

/* Temperature Sensor Properties */
/**
 * @brief Set the sensor type.
 * SENSOR_DHT_20 for a dht20 and SENSOR_DHT_22 for a dht22 sensor.
 * 
 */
#define SENSOR_DHT_22

/* NTP Server Properties */
/**
 * @brief Offset which should be appended to the retrieved time by the ntp server. 
 * In Seconds.
 * 
 */
#define NTP_OFFSET   0

/**
 * @brief POSIX Timezone String which should contain your current Timezone. In my case, its set to germany. 
 * You can get a list of posix timezone strings from here: https://support.cyberdata.net/portal/en/kb/articles/010d63c0cfce3676151e1f2d5442e311
 * 
 */
#define NTP_POSIX_TIMEZONESTRING "CEST-1CET,M3.2.0/2:00:00,M11.1.0/2:00:00"

/**
 * @brief Interval in which the NTP - Server will be queried
 * 
 * In Milliseconds
 * 
 */
#define NTP_INTERVAL 60000

/**
 * @brief Address of the NTP - Server which should be queried for the time.
 * 
 */
#define NTP_ADDRESS  "de.pool.ntp.org"

#define MQTT_SERVER "123.123.123.123"

#define MQTT_PORT 1883

#define MQTT_ROOT_TOPIC "/mytopic"

#define MQTT_PUBLISH_INTERVAL 60000

#define UPDATE_INTERVAL 5000
