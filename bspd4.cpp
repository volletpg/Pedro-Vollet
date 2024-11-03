#include <Arduino.h>
#include <FlexCAN_T4.h>

#define BAUDRATE_CAN 500000
#define BRAKE_SENSOR_PIN A5
#define ENDIANNESS_CYCLE_NUMBER 5
#define BRAKE_CAN_ID 0x123  

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> canBus;

bool endiannessState = false; 
int msgCount = 0;

/**
 * @brief Updates the endianness state
 * @note This function is used to change the endianness state every ENDIANNESS_CYCLE_NUMBER messages sent
 */
void updateEndiannessState() {
    if (msgCount == ENDIANNESS_CYCLE_NUMBER) {
        endiannessState = !endiannessState;
        msgCount = 0;
    }
    msgCount += 1;
}

/**
 * @brief Sets up the CAN Bus communication
 * @note This setup only prepares the CAN Bus to send messages, not to receive them
 */
void canSetup() {
    canBus.begin();
    canBus.setBaudRate(BAUDRATE_CAN);
}

/**
 * @brief Sends the brake sensor value to the CAN Bus
 * @param val The value to be sent to the CAN Bus
 * @note The value is sent in two bytes, switching byte order based on the endianness state
 */
void sendBrakeValue(int val) {
    uint8_t byte1 = (val >> 8) & 0xFF;  // MSB
    uint8_t byte2 = val & 0xFF;         // LSB

    CAN_message_t msg;
    msg.id = BRAKE_CAN_ID;  // Set to 0x123 as specified
    msg.len = 2;
    msg.buf[0] = endiannessState ? byte1 : byte2;
    msg.buf[1] = endiannessState ? byte2 : byte1;

    canBus.write(msg);
}

void setup() {
    pinMode(BRAKE_SENSOR_PIN, INPUT);
    canSetup();
}

void loop() {
    int brakeValue = analogRead(BRAKE_SENSOR_PIN);

    updateEndiannessState();

    sendBrakeValue(brakeValue);
}