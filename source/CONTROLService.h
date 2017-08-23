#ifndef __BLE_CONTROL_SERVICE_H__
#define __BLE_CONTROL_SERVICE_H__
class control_service {
public:
    const static uint16_t control_service_uuid = 0xA000;  //UUID Service 16bit
    const static uint16_t state_characteristic_uuid = 0xA001;  //UUID Characteristic 16bit
/**
*
* This contructor is declared and initialized Control Service
*/
    control_service(BLEDevice &_ble, bool initialValueForStateCharacteristic) :
        ble(_ble), state(state_characteristic_uuid, &initialValueForStateCharacteristic)
    {
        GattCharacteristic *charTable[] = {&state};
        GattService         control_service(control_service_uuid, charTable, sizeof(charTable) / sizeof(GattCharacteristic *));
        ble.addService(control_service);
    }

    GattAttribute::Handle_t getValueHandle() const
    {
        return state.getValueHandle();
    }

private:
    BLEDevice                         &ble;
    ReadWriteGattCharacteristic<bool> state;
};

#endif /* #ifndef __BLE_CONTROL_SERVICE_H__ */
