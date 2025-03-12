// ble.h

void bt_main(void);
struct bt_type{
  uint8_t packet[80];
  uint16_t length;};

void bt_get_latest(struct bt_type *dst);
