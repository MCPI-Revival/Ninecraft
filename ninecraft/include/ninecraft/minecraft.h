#ifndef NINECRAFT_MINECRAFT_H
#define NINECRAFT_MINECRAFT_H

#include <stdint.h>
#include <stdbool.h>
#include <ninecraft/android/android_string.h>
#include <ninecraft/app_context.h>

#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_5_0 0x2d8
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_5_0_J 0x170
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_6_0 0x2d8
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_6_1 0x2d8
#if defined(__i386__) || defined(_M_IX86)

#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_7_0 0xdcc
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_7_1 0xdcc
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_7_2 0xdd8
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_7_3 0xc38
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_7_4 0xc38
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_7_5 0xc38
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_7_6 0xc38
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_8_0 0xc50
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_8_1 0xc60
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_9_0 0xc88
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_9_1 0xc88
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_9_2 0xc88
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_9_3 0xc88
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_9_4 0xc88
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_9_5 0xc74

#else
#if defined(__arm__) || defined(_M_ARM)

#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_7_0 0xdd0
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_7_1 0xdd0
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_7_2 0xde0
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_7_3 0xc40
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_7_4 0xc40
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_7_5 0xc40
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_7_6 0xc40
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_8_0 0xc58
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_8_1 0xc68
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_9_0 0xc90
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_9_1 0xc90
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_9_2 0xc90
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_9_3 0xc90
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_9_4 0xc90
#define MINECRAFT_LOCAL_PLAYER_OFFSET_0_9_5 0xc78

#endif
#endif

#define PLAYER_INVENTORY_OFFSET_0_5_0 0xc00
#define PLAYER_INVENTORY_OFFSET_0_5_0_J 0xbd8
#define PLAYER_INVENTORY_OFFSET_0_6_0 0xc08
#define PLAYER_INVENTORY_OFFSET_0_6_1 0xc08
#if defined(__i386__) || defined(_M_IX86)

#define PLAYER_INVENTORY_OFFSET_0_7_0 0xc78
#define PLAYER_INVENTORY_OFFSET_0_7_1 0xc78
#define PLAYER_INVENTORY_OFFSET_0_7_2 0xc7c
#define PLAYER_INVENTORY_OFFSET_0_7_3 0xc2c
#define PLAYER_INVENTORY_OFFSET_0_7_4 0xc2c
#define PLAYER_INVENTORY_OFFSET_0_7_5 0xc2c
#define PLAYER_INVENTORY_OFFSET_0_7_6 0xc30
#define PLAYER_INVENTORY_OFFSET_0_8_0 0xcac
#define PLAYER_INVENTORY_OFFSET_0_8_1 0xcac
#define PLAYER_INVENTORY_OFFSET_0_9_0 0xc88
#define PLAYER_INVENTORY_OFFSET_0_9_1 0xc88
#define PLAYER_INVENTORY_OFFSET_0_9_2 0xc88
#define PLAYER_INVENTORY_OFFSET_0_9_3 0xc88
#define PLAYER_INVENTORY_OFFSET_0_9_4 0xc88
#define PLAYER_INVENTORY_OFFSET_0_9_5 0xc88
#define PLAYER_INVENTORY_OFFSET_0_10_0 0xc88
#define PLAYER_INVENTORY_OFFSET_0_10_1 0xc88
#define PLAYER_INVENTORY_OFFSET_0_10_2 0xc88
#define PLAYER_INVENTORY_OFFSET_0_10_3 0xc88
#define PLAYER_INVENTORY_OFFSET_0_10_4 0xc88
#define PLAYER_INVENTORY_OFFSET_0_10_5 0xc88

#else
#if defined(__arm__) || defined(_M_ARM)

#define PLAYER_INVENTORY_OFFSET_0_7_0 0xc7c
#define PLAYER_INVENTORY_OFFSET_0_7_1 0xc7c
#define PLAYER_INVENTORY_OFFSET_0_7_2 0xc84
#define PLAYER_INVENTORY_OFFSET_0_7_3 0xc30
#define PLAYER_INVENTORY_OFFSET_0_7_4 0xc30
#define PLAYER_INVENTORY_OFFSET_0_7_5 0xc30
#define PLAYER_INVENTORY_OFFSET_0_7_6 0xc34
#define PLAYER_INVENTORY_OFFSET_0_8_0 0xcb4
#define PLAYER_INVENTORY_OFFSET_0_8_1 0xcb4
#define PLAYER_INVENTORY_OFFSET_0_9_0 0xc8c
#define PLAYER_INVENTORY_OFFSET_0_9_1 0xc8c
#define PLAYER_INVENTORY_OFFSET_0_9_2 0xc8c
#define PLAYER_INVENTORY_OFFSET_0_9_3 0xc8c
#define PLAYER_INVENTORY_OFFSET_0_9_4 0xc8c
#define PLAYER_INVENTORY_OFFSET_0_9_5 0xc8c
#define PLAYER_INVENTORY_OFFSET_0_10_0 0xc8c
#define PLAYER_INVENTORY_OFFSET_0_10_1 0xc8c
#define PLAYER_INVENTORY_OFFSET_0_10_2 0xc8c
#define PLAYER_INVENTORY_OFFSET_0_10_3 0xc8c
#define PLAYER_INVENTORY_OFFSET_0_10_4 0xc8c
#define PLAYER_INVENTORY_OFFSET_0_10_5 0xc8c

#endif
#endif


#define MINECRAFT_GUI_OFFSET_0_5_0 0x2e4
#define MINECRAFT_GUI_OFFSET_0_6_0 0x2e4
#define MINECRAFT_GUI_OFFSET_0_6_1 0x2e4

#define PLAYER_USERNAME_OFFSET_0_5_0 0xc14
#define PLAYER_USERNAME_OFFSET_0_6_0 0xc1c
#define PLAYER_USERNAME_OFFSET_0_6_1 0xc1c

#define CHAT_SCREEN_RENDER_VTABLE_OFFSET_0_5_0 0x04
#define CHAT_SCREEN_RENDER_VTABLE_OFFSET_0_6_0 0x04
#define CHAT_SCREEN_RENDER_VTABLE_OFFSET_0_6_1 0x04

#define SERVERSIDENETWORKHANDLER_CHAT_PACKET_VTABLE_OFFSET_0_5_0 0x32
#define SERVERSIDENETWORKHANDLER_CHAT_PACKET_VTABLE_OFFSET_0_6_0 0x34
#define SERVERSIDENETWORKHANDLER_CHAT_PACKET_VTABLE_OFFSET_0_6_1 0x34

#define CHAT_PACKET_ID_0_5_0 0xb1
#define CHAT_PACKET_ID_0_6_0 0xb4
#define CHAT_PACKET_ID_0_6_1 0xb4

#define MESSAGE_PACKET_ID_0_5_0 0x85
#define MESSAGE_PACKET_ID_0_6_0 0x85
#define MESSAGE_PACKET_ID_0_6_1 0x85

#define MINECRAFT_RAKNET_INSTANCE_OFFSET_0_5_0 0x2bc
#define MINECRAFT_RAKNET_INSTANCE_OFFSET_0_6_0 0x2bc
#define MINECRAFT_RAKNET_INSTANCE_OFFSET_0_6_1 0x2bc

#define MINECRAFT_OPTIONS_OFFSET_0_5_0 0x28
#define MINECRAFT_OPTIONS_OFFSET_0_5_0_J 0x28
#define MINECRAFT_OPTIONS_OFFSET_0_6_0 0x28
#define MINECRAFT_OPTIONS_OFFSET_0_6_1 0x28
#define MINECRAFT_OPTIONS_OFFSET_0_7_0 0x3c
#define MINECRAFT_OPTIONS_OFFSET_0_7_1 0x3c
#define MINECRAFT_OPTIONS_OFFSET_0_7_2 0x3c
#define MINECRAFT_OPTIONS_OFFSET_0_7_3 0x3c
#define MINECRAFT_OPTIONS_OFFSET_0_7_4 0x3c
#define MINECRAFT_OPTIONS_OFFSET_0_7_5 0x3c
#define MINECRAFT_OPTIONS_OFFSET_0_7_6 0x3c
#define MINECRAFT_OPTIONS_OFFSET_0_8_0 0x3c
#define MINECRAFT_OPTIONS_OFFSET_0_8_1 0x3c
#define MINECRAFT_OPTIONS_OFFSET_0_9_0 0x4c
#define MINECRAFT_OPTIONS_OFFSET_0_9_1 0x4c
#define MINECRAFT_OPTIONS_OFFSET_0_9_2 0x4c
#define MINECRAFT_OPTIONS_OFFSET_0_9_3 0x4c
#define MINECRAFT_OPTIONS_OFFSET_0_9_4 0x4c
#define MINECRAFT_OPTIONS_OFFSET_0_9_5 0x38

#define OPTIONS_KEYS_OFFSET_0_5_0 0x1f8
#define OPTIONS_KEYS_OFFSET_0_5_0_J 0xa4
#define OPTIONS_KEYS_OFFSET_0_6_0 0x1f8
#define OPTIONS_KEYS_OFFSET_0_6_1 0x1f8

#define MINECRAFT_COMMANDSERVER_OFFSET_0_6_0 0xe5c
#define MINECRAFT_COMMANDSERVER_OFFSET_0_6_1 0xe5c
#if defined(__i386__) || defined(_M_IX86)
#define MINECRAFT_COMMANDSERVER_OFFSET_0_7_0 0xebc
#define MINECRAFT_COMMANDSERVER_OFFSET_0_7_1 0xebc
#define MINECRAFT_COMMANDSERVER_OFFSET_0_7_2 0xec8
#define MINECRAFT_COMMANDSERVER_OFFSET_0_7_3 0xcf0
#define MINECRAFT_COMMANDSERVER_OFFSET_0_7_4 0xcf8
#define MINECRAFT_COMMANDSERVER_OFFSET_0_7_5 0xcf8
#define MINECRAFT_COMMANDSERVER_OFFSET_0_7_6 0xcf8
#define MINECRAFT_COMMANDSERVER_OFFSET_0_8_0 0xd14
#define MINECRAFT_COMMANDSERVER_OFFSET_0_8_1 0xd24
#else
#if defined(__arm__) || defined(_M_ARM)
#define MINECRAFT_COMMANDSERVER_OFFSET_0_7_0 0xec0
#define MINECRAFT_COMMANDSERVER_OFFSET_0_7_1 0xec0
#define MINECRAFT_COMMANDSERVER_OFFSET_0_7_2 0xed0
#define MINECRAFT_COMMANDSERVER_OFFSET_0_7_3 0xcf8
#define MINECRAFT_COMMANDSERVER_OFFSET_0_7_4 0xd00
#define MINECRAFT_COMMANDSERVER_OFFSET_0_7_5 0xd00
#define MINECRAFT_COMMANDSERVER_OFFSET_0_7_6 0xd00
#define MINECRAFT_COMMANDSERVER_OFFSET_0_8_0 0xd1c
#define MINECRAFT_COMMANDSERVER_OFFSET_0_8_1 0xd2c
#endif
#endif

#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_1_0 0xd58
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_1_0_TOUCH 0xd68
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_1_1 0xd70
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_1_1_J 0xd70
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_1_2 0xd70
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_1_2_J 0xd70
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_1_3 0xd80
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_1_3_J 0xd80
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_2_0 0xbf4
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_2_0_J 0xbf4
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_2_1 0xc28
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_2_1_J 0xc28
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_2_2 0xda4
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_3_0 0xdc8
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_3_0_J 0xc38
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_3_2 0xdc8
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_3_2_J 0xc38
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_3_3 0xdd0
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_3_3 0xde8
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_3_3_J 0xc40
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_3_3_J 0xc44
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_4_0 0xdd4
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_4_0 0xdec
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_4_0_J 0xc44
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_4_0_J 0xc48
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_5_0 0xdd8
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_5_0 0xdf0
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_5_0_J 0xc48
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_5_0_J 0xc4c
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_6_0 0xdd8
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_6_0 0xdf0
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_6_1 0xdd8
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_6_1 0xdf0
#if defined(__i386__) || defined(_M_IX86)
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_7_0 0xe20
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_7_0 0xe38
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_7_1 0xe20
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_7_1 0xe38
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_7_2 0xe2c
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_7_2 0xe44
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_7_3 0xc90
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_7_3 0xc94
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_7_4 0xc90
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_7_4 0xc94
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_7_5 0xc90
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_7_5 0xc94
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_7_6 0xc90
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_7_6 0xc94
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_8_0 0xca8
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_8_0 0xcac
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_8_1 0xcb8
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_8_1 0xcbc
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_9_0 0xcb0
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_9_0 0xcb4
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_9_1 0xcb0
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_9_1 0xcb4
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_9_2 0xcb0
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_9_2 0xcb4
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_9_3 0xcb0
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_9_3 0xcb4
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_9_4 0xcb0
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_9_4 0xcb4
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_9_5 0xc9c
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_9_5 0xca0
#else
#if defined(__arm__) || defined(_M_ARM)
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_7_0 0xe24
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_7_0 0xe3c
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_7_1 0xe24
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_7_1 0xe3c
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_7_2 0xe34
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_7_2 0xe4c
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_7_3 0xc98
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_7_3 0xc9c
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_7_4 0xc98
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_7_4 0xc9c
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_7_5 0xc98
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_7_5 0xc9c
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_7_6 0xc98
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_7_6 0xc9c
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_8_0 0xcb0
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_8_0 0xcb4
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_8_1 0xcc0
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_8_1 0xcc4
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_9_0 0xcb8
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_9_0 0xcbc
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_9_1 0xcb8
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_9_1 0xcbc
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_9_2 0xcb8
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_9_2 0xcbc
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_9_3 0xcb8
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_9_3 0xcbc
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_9_4 0xcb8
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_9_4 0xcbc
#define NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_9_5 0xca0
#define NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_9_5 0xca4
#endif
#endif
#define MINECRAFTCLIENT_INTERNAL_STORAGE_OFFSET_0_10_0 0x78
#define MINECRAFTCLIENT_EXTERNAL_STORAGE_OFFSET_0_10_0 0x7c
#define MINECRAFTCLIENT_INTERNAL_STORAGE_OFFSET_0_10_1 0x78
#define MINECRAFTCLIENT_EXTERNAL_STORAGE_OFFSET_0_10_1 0x7c
#define MINECRAFTCLIENT_INTERNAL_STORAGE_OFFSET_0_10_2 0x78
#define MINECRAFTCLIENT_EXTERNAL_STORAGE_OFFSET_0_10_2 0x7c
#define MINECRAFTCLIENT_INTERNAL_STORAGE_OFFSET_0_10_3 0x78
#define MINECRAFTCLIENT_EXTERNAL_STORAGE_OFFSET_0_10_3 0x7c
#define MINECRAFTCLIENT_INTERNAL_STORAGE_OFFSET_0_10_4 0x78
#define MINECRAFTCLIENT_EXTERNAL_STORAGE_OFFSET_0_10_4 0x7c
#define MINECRAFTCLIENT_INTERNAL_STORAGE_OFFSET_0_10_5 0x78
#define MINECRAFTCLIENT_EXTERNAL_STORAGE_OFFSET_0_10_5 0x7c

#if defined(__i386__) || defined(_M_IX86)
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_10_5 0xac
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_10_4 0xac
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_10_3 0xac
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_10_2 0xac
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_10_1 0xac
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_10_0 0xac
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_9_5 0x198
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_9_4 0x1ac
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_9_3 0x1ac
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_9_2 0x1ac
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_9_1 0x1ac
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_9_0 0x1ac
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_8_1 0x194
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_8_0 0x184
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_7_6 0x184
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_7_5 0x184
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_7_4 0x184
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_7_3 0x184
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_7_2 0x2fc
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_7_1 0x2f0
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_7_0 0x2f0
#else
#if defined(__arm__) || defined(_M_ARM)
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_10_5 0xb0
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_10_4 0xb0
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_10_3 0xb0
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_10_2 0xb0
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_10_1 0xb0
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_10_0 0xb0
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_9_5 0x198
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_9_4 0x1ac
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_9_3 0x1ac
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_9_2 0x1ac
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_9_1 0x1ac
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_9_0 0x1ac
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_8_1 0x194
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_8_0 0x184
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_7_6 0x184
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_7_5 0x184
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_7_4 0x184
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_7_3 0x184
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_7_2 0x2fc
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_7_1 0x2f0
#define MINECRAFT_SCREENCHOOSER_OFFSET_0_7_0 0x2f0
#endif
#endif

#define MINECRAFTCLIENT_SCREEN_OFFSET_0_10_5 0x6c
#define MINECRAFTCLIENT_SCREEN_OFFSET_0_10_4 0x6c
#define MINECRAFTCLIENT_SCREEN_OFFSET_0_10_3 0x6c
#define MINECRAFTCLIENT_SCREEN_OFFSET_0_10_2 0x6c
#define MINECRAFTCLIENT_SCREEN_OFFSET_0_10_1 0x6c
#define MINECRAFTCLIENT_SCREEN_OFFSET_0_10_0 0x6c

#if defined(__i386__) || defined(_M_IX86)
#define NINECRAFTAPP_SCREEN_OFFSET_0_9_5 0xc80
#define NINECRAFTAPP_SCREEN_OFFSET_0_9_4 0xc94
#define NINECRAFTAPP_SCREEN_OFFSET_0_9_3 0xc94
#define NINECRAFTAPP_SCREEN_OFFSET_0_9_2 0xc94
#define NINECRAFTAPP_SCREEN_OFFSET_0_9_1 0xc94
#define NINECRAFTAPP_SCREEN_OFFSET_0_9_0 0xc94
#define NINECRAFTAPP_SCREEN_OFFSET_0_8_1 0xc70
#define NINECRAFTAPP_SCREEN_OFFSET_0_8_0 0xc60
#define NINECRAFTAPP_SCREEN_OFFSET_0_7_6 0xc48
#define NINECRAFTAPP_SCREEN_OFFSET_0_7_5 0xc48
#define NINECRAFTAPP_SCREEN_OFFSET_0_7_4 0xc48
#define NINECRAFTAPP_SCREEN_OFFSET_0_7_3 0xc48
#define NINECRAFTAPP_SCREEN_OFFSET_0_7_2 0xde8
#define NINECRAFTAPP_SCREEN_OFFSET_0_7_1 0xddc
#define NINECRAFTAPP_SCREEN_OFFSET_0_7_0 0xddc
#else
#if defined(__arm__) || defined(_M_ARM)
#define NINECRAFTAPP_SCREEN_OFFSET_0_9_5 0xc84
#define NINECRAFTAPP_SCREEN_OFFSET_0_9_4 0xc9c
#define NINECRAFTAPP_SCREEN_OFFSET_0_9_3 0xc9c
#define NINECRAFTAPP_SCREEN_OFFSET_0_9_2 0xc9c
#define NINECRAFTAPP_SCREEN_OFFSET_0_9_1 0xc9c
#define NINECRAFTAPP_SCREEN_OFFSET_0_9_0 0xc9c
#define NINECRAFTAPP_SCREEN_OFFSET_0_8_1 0xc78
#define NINECRAFTAPP_SCREEN_OFFSET_0_8_0 0xc68
#define NINECRAFTAPP_SCREEN_OFFSET_0_7_6 0xc50
#define NINECRAFTAPP_SCREEN_OFFSET_0_7_5 0xc50
#define NINECRAFTAPP_SCREEN_OFFSET_0_7_4 0xc50
#define NINECRAFTAPP_SCREEN_OFFSET_0_7_3 0xc50
#define NINECRAFTAPP_SCREEN_OFFSET_0_7_2 0xdf0
#define NINECRAFTAPP_SCREEN_OFFSET_0_7_1 0xde0
#define NINECRAFTAPP_SCREEN_OFFSET_0_7_0 0xde0
#endif
#endif

#if defined(__i386__) || defined(_M_IX86)
#define MINECRAFTCLIENT_SIZE_0_10_5 0x12c
#define MINECRAFTCLIENT_SIZE_0_10_4 0x12c
#define MINECRAFTCLIENT_SIZE_0_10_3 0x12c
#define MINECRAFTCLIENT_SIZE_0_10_2 0x12c
#define MINECRAFTCLIENT_SIZE_0_10_1 0x12c
#define MINECRAFTCLIENT_SIZE_0_10_0 0x12c
#else
#if defined(__arm__) || defined(_M_ARM) 
#define MINECRAFTCLIENT_SIZE_0_10_5 0x130
#define MINECRAFTCLIENT_SIZE_0_10_4 0x130
#define MINECRAFTCLIENT_SIZE_0_10_3 0x130
#define MINECRAFTCLIENT_SIZE_0_10_2 0x130
#define MINECRAFTCLIENT_SIZE_0_10_1 0x130
#define MINECRAFTCLIENT_SIZE_0_10_0 0x130
#endif
#endif

#if defined(__i386__) || defined(_M_IX86)
#define NINECRAFTAPP_SIZE_0_9_5 0xd60
#define NINECRAFTAPP_SIZE_0_9_4 0xd74
#define NINECRAFTAPP_SIZE_0_9_3 0xd74
#define NINECRAFTAPP_SIZE_0_9_2 0xd74
#define NINECRAFTAPP_SIZE_0_9_1 0xd74
#define NINECRAFTAPP_SIZE_0_9_0 0xd74
#define NINECRAFTAPP_SIZE_0_8_1 0xd64
#define NINECRAFTAPP_SIZE_0_8_0 0xd54
#define NINECRAFTAPP_SIZE_0_7_6 0xd20
#define NINECRAFTAPP_SIZE_0_7_5 0xd20
#define NINECRAFTAPP_SIZE_0_7_4 0xd20
#define NINECRAFTAPP_SIZE_0_7_3 0xd14
#define NINECRAFTAPP_SIZE_0_7_2 0xeec
#define NINECRAFTAPP_SIZE_0_7_1 0xee0
#define NINECRAFTAPP_SIZE_0_7_0 0xee0
#else
#if defined(__arm__) || defined(_M_ARM) 
#define NINECRAFTAPP_SIZE_0_9_5 0xd68
#define NINECRAFTAPP_SIZE_0_9_4 0xd80
#define NINECRAFTAPP_SIZE_0_9_3 0xd80
#define NINECRAFTAPP_SIZE_0_9_2 0xd80
#define NINECRAFTAPP_SIZE_0_9_1 0xd80
#define NINECRAFTAPP_SIZE_0_9_0 0xd80
#define NINECRAFTAPP_SIZE_0_8_1 0xd70
#define NINECRAFTAPP_SIZE_0_8_0 0xD60
#define NINECRAFTAPP_SIZE_0_7_6 0xd30
#define NINECRAFTAPP_SIZE_0_7_5 0xd30
#define NINECRAFTAPP_SIZE_0_7_4 0xd30
#define NINECRAFTAPP_SIZE_0_7_3 0xd20
#define NINECRAFTAPP_SIZE_0_7_2 0xef8
#define NINECRAFTAPP_SIZE_0_7_1 0xee8
#define NINECRAFTAPP_SIZE_0_7_0 0xee8
#endif
#endif
#define NINECRAFTAPP_SIZE_0_6_1 0xe6c
#define NINECRAFTAPP_SIZE_0_6_0 0xe6c
#define NINECRAFTAPP_SIZE_0_5_0 0xe68
#define NINECRAFTAPP_SIZE_0_5_0_J 0xcb0
#define NINECRAFTAPP_SIZE_0_4_0 0xe64
#define NINECRAFTAPP_SIZE_0_4_0_J 0xcac
#define NINECRAFTAPP_SIZE_0_3_3 0xe64
#define NINECRAFTAPP_SIZE_0_3_3_J 0xcac
#define NINECRAFTAPP_SIZE_0_3_2 0xe44
#define NINECRAFTAPP_SIZE_0_3_2_J 0xca0
#define NINECRAFTAPP_SIZE_0_3_0 0xe44
#define NINECRAFTAPP_SIZE_0_3_0_J 0xca0
#define NINECRAFTAPP_SIZE_0_2_2 0xe20
#define NINECRAFTAPP_SIZE_0_2_1 0xc90
#define NINECRAFTAPP_SIZE_0_2_1_J 0xc90
#define NINECRAFTAPP_SIZE_0_2_0 0xc5c
#define NINECRAFTAPP_SIZE_0_2_0_J 0xc5c
#define NINECRAFTAPP_SIZE_0_1_3 0xdf4
#define NINECRAFTAPP_SIZE_0_1_3_J 0xdf4
#define NINECRAFTAPP_SIZE_0_1_2 0xde4
#define NINECRAFTAPP_SIZE_0_1_2_J 0xde4
#define NINECRAFTAPP_SIZE_0_1_1 0xde4
#define NINECRAFTAPP_SIZE_0_1_1_J 0xde4
#define NINECRAFTAPP_SIZE_0_1_0_TOUCH 0xddc
#define NINECRAFTAPP_SIZE_0_1_0 0xdc8

#define MINECRAFTCLIENT_ISGRABBED_OFFSET_0_10_5 0x74
#define MINECRAFTCLIENT_ISGRABBED_OFFSET_0_10_4 0x74
#define MINECRAFTCLIENT_ISGRABBED_OFFSET_0_10_3 0x74
#define MINECRAFTCLIENT_ISGRABBED_OFFSET_0_10_2 0x74
#define MINECRAFTCLIENT_ISGRABBED_OFFSET_0_10_1 0x74
#define MINECRAFTCLIENT_ISGRABBED_OFFSET_0_10_0 0x74

#if defined(__i386__) || defined(_M_IX86)
#define MINECRAFT_ISGRABBED_OFFSET_0_9_5 0xc88
#define MINECRAFT_ISGRABBED_OFFSET_0_9_4 0xc9c
#define MINECRAFT_ISGRABBED_OFFSET_0_9_3 0xc9c
#define MINECRAFT_ISGRABBED_OFFSET_0_9_2 0xc9c
#define MINECRAFT_ISGRABBED_OFFSET_0_9_1 0xc9c
#define MINECRAFT_ISGRABBED_OFFSET_0_9_0 0xc9c
#define MINECRAFT_ISGRABBED_OFFSET_0_8_1 0xc78
#define MINECRAFT_ISGRABBED_OFFSET_0_8_0 0xc68
#define MINECRAFT_ISGRABBED_OFFSET_0_7_6 0xc50
#define MINECRAFT_ISGRABBED_OFFSET_0_7_5 0xc50
#define MINECRAFT_ISGRABBED_OFFSET_0_7_4 0xc50
#define MINECRAFT_ISGRABBED_OFFSET_0_7_3 0xc50
#define MINECRAFT_ISGRABBED_OFFSET_0_7_2 0xdec
#define MINECRAFT_ISGRABBED_OFFSET_0_7_1 0xde0
#define MINECRAFT_ISGRABBED_OFFSET_0_7_0 0xde0
#else
#if defined(__arm__) || defined(_M_ARM) 
#define MINECRAFT_ISGRABBED_OFFSET_0_9_5 0xc8c
#define MINECRAFT_ISGRABBED_OFFSET_0_9_4 0xca4
#define MINECRAFT_ISGRABBED_OFFSET_0_9_3 0xca4
#define MINECRAFT_ISGRABBED_OFFSET_0_9_2 0xca4
#define MINECRAFT_ISGRABBED_OFFSET_0_9_1 0xca4
#define MINECRAFT_ISGRABBED_OFFSET_0_9_0 0xca4
#define MINECRAFT_ISGRABBED_OFFSET_0_8_1 0xc80
#define MINECRAFT_ISGRABBED_OFFSET_0_8_0 0xc70
#define MINECRAFT_ISGRABBED_OFFSET_0_7_6 0xc58
#define MINECRAFT_ISGRABBED_OFFSET_0_7_5 0xc58
#define MINECRAFT_ISGRABBED_OFFSET_0_7_4 0xc58
#define MINECRAFT_ISGRABBED_OFFSET_0_7_3 0xc58
#define MINECRAFT_ISGRABBED_OFFSET_0_7_2 0xdf4
#define MINECRAFT_ISGRABBED_OFFSET_0_7_1 0xde4
#define MINECRAFT_ISGRABBED_OFFSET_0_7_0 0xde4
#endif
#endif
#define MINECRAFT_ISGRABBED_OFFSET_0_6_1 0xd98
#define MINECRAFT_ISGRABBED_OFFSET_0_6_0 0xd98
#define MINECRAFT_ISGRABBED_OFFSET_0_5_0 0xd98
#define MINECRAFT_ISGRABBED_OFFSET_0_5_0_J 0xc08
#define MINECRAFT_ISGRABBED_OFFSET_0_4_0 0xd94
#define MINECRAFT_ISGRABBED_OFFSET_0_4_0_J 0xc04
#define MINECRAFT_ISGRABBED_OFFSET_0_3_3 0xd90
#define MINECRAFT_ISGRABBED_OFFSET_0_3_3_J 0xc00
#define MINECRAFT_ISGRABBED_OFFSET_0_3_2 0xd88
#define MINECRAFT_ISGRABBED_OFFSET_0_3_2_J 0xbf8
#define MINECRAFT_ISGRABBED_OFFSET_0_3_0 0xd88
#define MINECRAFT_ISGRABBED_OFFSET_0_3_0_J 0xbf8
#define MINECRAFT_ISGRABBED_OFFSET_0_2_2 0xd64
#define MINECRAFT_ISGRABBED_OFFSET_0_2_1 0xbe8
#define MINECRAFT_ISGRABBED_OFFSET_0_2_1_J 0xbe8
#define MINECRAFT_ISGRABBED_OFFSET_0_2_0 0xbb4
#define MINECRAFT_ISGRABBED_OFFSET_0_2_0_J 0xbb4
#define MINECRAFT_ISGRABBED_OFFSET_0_1_3 0xd40
#define MINECRAFT_ISGRABBED_OFFSET_0_1_3_J 0xd40
#define MINECRAFT_ISGRABBED_OFFSET_0_1_2 0xd40
#define MINECRAFT_ISGRABBED_OFFSET_0_1_2_J 0xd40
#define MINECRAFT_ISGRABBED_OFFSET_0_1_1 0xd40
#define MINECRAFT_ISGRABBED_OFFSET_0_1_1_J 0xd40
#define MINECRAFT_ISGRABBED_OFFSET_0_1_0_TOUCH 0xd38
#define MINECRAFT_ISGRABBED_OFFSET_0_1_0 0xd28

extern void gui_component_draw_rect(void *gui_component, int x1, int y1, int x2, int y2, int color, int thickness);

extern void *minecraft_get_options(void *minecraft, int version_id);

extern uintptr_t get_ninecraftapp_external_storage_offset(int version_id);

extern uintptr_t get_ninecraftapp_internal_storage_offset(int version_id);

typedef void (*minecraft_level_generated_t)(void *minecraft);

extern minecraft_level_generated_t minecraft_level_generated;

typedef void (*minecraft_tick_t)(void *minecraft, uint32_t param_1, uint32_t param_2);

extern minecraft_tick_t minecraft_tick;

typedef int (*minecraft_is_level_generated_t)(void *minecraft);

extern minecraft_is_level_generated_t minecraft_is_level_generated;

typedef void (*command_server_deconstruct_t)(void *command_server);

extern command_server_deconstruct_t command_server_deconstruct;

typedef void (*command_server_construct_t)(void *command_server, void *minecraft);

extern command_server_construct_t command_server_construct;

typedef void (*command_server_init_t)(void *command_server, uint16_t port);

extern command_server_init_t command_server_init;

typedef void (*start_menu_screen_construct_t)(void *start_menu_screen);

extern start_menu_screen_construct_t start_menu_screen_construct;

typedef void (*player_renderer_render_name_t)(void *player_renderer, void *mob, float x, float y, float z);

extern player_renderer_render_name_t player_renderer_render_name;

typedef void (*textures_load_and_bind_texture_t)(void *textures, android_string_t *path);

extern textures_load_and_bind_texture_t textures_load_and_bind_texture;

typedef void (*gui_component_blit_t)(void *gui_component, int32_t x_dest, int32_t y_dest, int32_t x_src, int32_t y_src, int32_t width_dest, int32_t height_dest, int32_t width_src, int32_t height_src);

extern gui_component_blit_t gui_component_blit;

typedef void (*screen_render_dirt_background_t)(void *screen, int32_t param_1);

extern screen_render_dirt_background_t screen_render_dirt_background;

typedef void (*ninecraft_app_construct_t)(void *ninecraft_app);

extern ninecraft_app_construct_t ninecraft_app_construct;

typedef void (*ninecraft_app_construct_2_t)(void *ninecraft_app, int argc, char **argv);

extern ninecraft_app_construct_2_t ninecraft_app_construct_2;

typedef void (*ninecraft_app_init_t)(void *ninecraft_app);

extern ninecraft_app_init_t ninecraft_app_init;

typedef void (*app_init_t)(void *app, app_context_0_9_0_t *context);

extern app_init_t app_init;

typedef void (*minecraft_set_size_t)(void *minecraft, uint32_t width, uint32_t height);

extern minecraft_set_size_t minecraft_set_size;

typedef void (*ninecraft_app_update_t)(void *ninecraft_app);

extern ninecraft_app_update_t ninecraft_app_update;

typedef void (*ninecraft_app_handle_back_t)(void *ninecraft_app, bool keep_screen);

extern ninecraft_app_handle_back_t ninecraft_app_handle_back;

typedef void (*minecraft_client_set_size_t)(void *minecraft_client, uint32_t width, uint32_t height, float px);

extern minecraft_client_set_size_t minecraft_client_set_size;

typedef void (*minecraft_client_handle_back_t)(void *minecraft_client, bool keep_screen);

extern minecraft_client_handle_back_t minecraft_client_handle_back;

typedef void (*minecraft_update_t)(void *minecraft);

extern minecraft_update_t minecraft_update;

typedef void (*minecraft_client_construct_t)(void *minecraft_client, int argc, char **argv);

extern minecraft_client_construct_t minecraft_client_construct;

typedef void (*minecraft_client_init_t)(void *minecraft_client);

extern minecraft_client_init_t minecraft_client_init;

typedef void (*app_platform_construct_t)(void *app_platform);

extern app_platform_construct_t app_platform_construct;

typedef void (*screen_construct_t)(void *screen);

extern screen_construct_t screen_construct;

typedef void (*minecraft_set_screen_t)(void *minecraft, void *screen);

extern minecraft_set_screen_t minecraft_set_screen;

typedef int (*raknet_instance_send_packet_t)(void *raknet_instance, void *packet);

extern raknet_instance_send_packet_t raknet_instance_send_packet;

typedef int (*raknet_rakstring_assign_t)(void *raknet_rakstring, char *str);

extern raknet_rakstring_assign_t raknet_rakstring_assign;

typedef void *(*minecraft_packets_create_packet_t)(int packet_id);

extern minecraft_packets_create_packet_t minecraft_packets_create_packet;

typedef void *(*server_side_network_handler_get_player_t)(void *server_side_network_handler, void *raknet_guid);

extern server_side_network_handler_get_player_t server_side_network_handler_get_player;

typedef void *(*server_side_network_handler_redistribute_packet_t)(void *server_side_network_handler, void *packet, void *raknet_guid);

extern server_side_network_handler_redistribute_packet_t server_side_network_handler_redistribute_packet;

typedef void *(*chat_packet_deconstruct_t)(void *chat_packet);

extern chat_packet_deconstruct_t chat_packet_deconstruct;

typedef void *(*message_packet_deconstruct_t)(void *message_packet);

extern message_packet_deconstruct_t message_packet_deconstruct;

typedef void *(*raknet_instance_is_server_t)(void *raknet_instance);

extern raknet_instance_is_server_t raknet_instance_is_server;

typedef void *(*gui_add_message_t)(void *gui, android_string_t *message);

extern gui_add_message_t gui_add_message;

typedef void (*options_set_key_t)(void *options, int key, int value);

extern options_set_key_t options_set_key;

typedef void *(*minecraft_client_get_options_t)(void *minecraft_client);

extern minecraft_client_get_options_t minecraft_client_get_options;

typedef void *(*minecraft_client_get_local_player_t)(void *minecraft_client);

extern minecraft_client_get_local_player_t minecraft_client_get_local_player;

typedef void (*gui_component_fill_t)(void *gui_component, int x1, int y1, int x2, int y2, int color);
extern gui_component_fill_t gui_component_fill;

extern void minecraft_setup_hooks(void *handle);

#endif