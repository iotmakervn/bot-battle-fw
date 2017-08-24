#include <events/mbed_events.h>
#include <mbed.h>
#include "ble/BLE.h"
#include "ble/services/DFUService.h"
#include "Bot.h"

Serial pc(p10, p11);

static const uint16_t CONTROL_SERVICE_UUID = 0xA000;    //UUID Service 16bit
static const uint16_t COMMAND_CHAR_UUID = 0xA001;       //UUID Characteristic 16bit
static const char     DEVICE_NAME[] = "BOT-GAREN";
static const uint16_t uuid16_list[] = {CONTROL_SERVICE_UUID};
static EventQueue eventQueue(/* event count */ 10 * EVENTS_EVENT_SIZE);

ReadWriteGattCharacteristic<uint8_t> charCommand(COMMAND_CHAR_UUID, 0);
GattCharacteristic *charTable[] = {&charCommand};
static DFUService *dfuPtr;


Bot Battle(p7, p28, p25, p24, p23, p22, p21);

void disconnectionCallback(const Gap::DisconnectionCallbackParams_t *params)
{
    (void) params;
    BLE::Instance().gap().startAdvertising();
    Battle.disconnect();
    pc.printf("\n\r Disconnection \n\r");
}

void connectionCallback(const Gap::ConnectionCallbackParams_t *params)
{
    Battle.connect();
    pc.printf("\n\r Connected\n\r Ready!");
}

void onDataWrittenCallback(const GattWriteCallbackParams *params) {
    if((params->handle == charCommand.getValueHandle()) && (params->len == 1)) {
        Battle.process(params->data[0]);
    }
    pc.printf("received value:%d \n\r", params->data[0]);
}

/**
 * This function is called when the ble initialization process has failled
 */
void onBleInitError(BLE &ble, ble_error_t error)
{
    /* Initialization error handling should go here */
}

/**
 * Callback triggered when the ble initialization process has finished
 */
void bleInitComplete(BLE::InitializationCompleteCallbackContext *params)
{
    BLE&        ble   = params->ble;
    ble_error_t error = params->error;

    if(error != BLE_ERROR_NONE) {
        /* In case of error, forward the error handling to onBleInitError */
        onBleInitError(ble, error);
        return;
    }

    /* Ensure that it is the default instance of BLE */
    if(ble.getInstanceID() != BLE::DEFAULT_INSTANCE) {
        return;
    }

    ble.gap().onDisconnection(disconnectionCallback);
    ble.gap().onConnection(connectionCallback);
    ble.gattServer().onDataWritten(onDataWrittenCallback);

    GattService controlService(CONTROL_SERVICE_UUID, charTable, sizeof(charTable) / sizeof(GattCharacteristic *));
    ble.addService(controlService);

    dfuPtr = new DFUService(ble);
    /* setup advertising */
    ble.gap().accumulateAdvertisingPayload(GapAdvertisingData::BREDR_NOT_SUPPORTED | GapAdvertisingData::LE_GENERAL_DISCOVERABLE);
    ble.gap().accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LIST_16BIT_SERVICE_IDS, (uint8_t *)uuid16_list, sizeof(uuid16_list));
    ble.gap().accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LOCAL_NAME, (uint8_t *)DEVICE_NAME, sizeof(DEVICE_NAME));
    ble.gap().setAdvertisingType(GapAdvertisingParams::ADV_CONNECTABLE_UNDIRECTED);
    ble.gap().setAdvertisingInterval(1000); /* 1000ms. */
    ble.gap().startAdvertising();
}

void scheduleBleEventsProcessing(BLE::OnEventsToProcessCallbackContext* context) {
    BLE &ble = BLE::Instance();
    eventQueue.call(Callback<void()>(&ble, &BLE::processEvents));
}

int main()
{
    pc.baud(115200);
    BLE &ble = BLE::Instance();
    ble.onEventsToProcess(scheduleBleEventsProcessing);
    ble.init(bleInitComplete);
    pc.printf("\n\rGAREN\n\r");
    eventQueue.dispatch_forever();
    return 0;
}
