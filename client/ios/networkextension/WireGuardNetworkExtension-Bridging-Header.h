#include "wireguard-go-version.h"
#include "3rd/awg-apple/Sources/WireGuardKitGo/wireguard.h"
#include "3rd/awg-apple/Sources/WireGuardKitC/WireGuardKitC.h"

#include <stdbool.h>
#include <stdint.h>

#define WG_KEY_LEN (32)
#define WG_KEY_LEN_BASE64 (45)
#define WG_KEY_LEN_HEX (65)

void key_to_base64(char base64[WG_KEY_LEN_BASE64],
                   const uint8_t key[WG_KEY_LEN]);
bool key_from_base64(uint8_t key[WG_KEY_LEN], const char* base64);

void key_to_hex(char hex[WG_KEY_LEN_HEX], const uint8_t key[WG_KEY_LEN]);
bool key_from_hex(uint8_t key[WG_KEY_LEN], const char* hex);

bool key_eq(const uint8_t key1[WG_KEY_LEN], const uint8_t key2[WG_KEY_LEN]);

void write_msg_to_log(const char* tag, const char* msg);
