#ifndef NINECRAFT_INPUT_MINECRAFT_KEYS_H
#define NINECRAFT_INPUT_MINECRAFT_KEYS_H

/*
    key.forward - MCKEY_FORWARD
    key.left - MCKEY_LEFT
    key.back - MCKEY_BACK
    key.right - MCKEY_RIGHT
    key.jump - MCKEY_JUMP
    key.inventory - MCKEY_INVENTORY
    key.crafting - MCKEY_CRAFTING
    key.drop
    key.chat
    key.fog
    key.sneak
    key.destroy - MCKEY_DESTROY
    key.use - MCKEY_USE
    key.menu.next - MCKEY_MENU_NEXT
    key.menu.previous - MCKEY_MENU_PREVIOUS
    key.menu.cancel - MCKEY_MENU_CANCEL
*/

#define MCKEY_FORWARD 19
#define MCKEY_LEFT 21
#define MCKEY_BACK 20
#define MCKEY_RIGHT 22
#define MCKEY_JUMP 23
#define MCKEY_INVENTORY 100
#define MCKEY_CRAFTING 109
#define MCKEY_DROP 45
#define MCKEY_SNEAK 59
#define MCKEY_DESTROY 102
#define MCKEY_USE 103
#define MCKEY_MENU_NEXT 4
#define MCKEY_MENU_PREVIOUS 99
#define MCKEY_MENU_CANCEL 27

#define MCKEY_PAUSE 82
#define MCKEY_SIGN_BACKSPACE 8
#define MCKEY_SIGN_ENTER 13

typedef enum {
    MCKEY_ID_FORWARD,
    MCKEY_ID_LEFT,
    MCKEY_ID_BACK,
    MCKEY_ID_RIGHT,
    MCKEY_ID_JUMP,
    MCKEY_ID_SNEAK,
    MCKEY_ID_DROP,
    MCKEY_ID_INVENTORY,
    MCKEY_ID_CHAT,
    MCKEY_ID_FOG,
    MCKEY_ID_DESTROY,
    MCKEY_ID_USE,
    MCKEY_ID_MENU_NEXT,
    MCKEY_ID_MENU_PREVIOUS,
    MCKEY_ID_MENU_OK,
    MCKEY_ID_MENU_CANCEL
} mckey_id_t;

#endif