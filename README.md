# samp-drp
A client/server Discord Rich Presence plugin for SA-MP. 

Versions supported: 0.3.7-R1, 0.3.7-R2 & 0.3.DL-R1

### Client

On the first initialization, a file called "samp-drp.ini" is created where the plugin is located. 

```C
[Settings]
ConnectToServer=1
```

By default, the plugin will try to connect to the server. If the server doesn't use the plugin or if this option is turned off, the default application ID will be initialized and the plugin will work independently, showing this information: Player name, server ip, server port, if the server is locked, player count and max players. An example of how it looks:

![img](https://i.imgur.com/3Ka5BDc.png)</br>
![img](https://i.imgur.com/yQdJvb9.png)

If connected to a server, the information shown will be different and controlled by it.

### Server

#### Function list
```Pawn
native DRP_InitializeDiscordPlugin(const application_id[], const details[], const drp_state[], const large_image[], const large_image_text[], const small_image[], const small_image_text[]);
native DRP_IsPlayerUsingClientPlugin(const playerid);
native DRP_GetPlayerDetails(const playerid, details[], const length);
native DRP_GetPlayerLargeImageKey(const playerid, large_imagekey[], const length);
native DRP_GetPlayerSmallImageKey(const playerid, small_imagekey[], const length);
native DRP_GetPlayerSmallImageText(const playerid, small_image_text[], const length);
native DRP_GetPlayerLargeImageText(const playerid, large_image_text[], const length);
native DRP_GetPlayerState(const playerid, drp_state[], const length);
native DRP_SetPlayerDetails(const playerid, const details[]);
native DRP_SetPlayerLargeImageKey(const playerid, const large_image_key[]);
native DRP_SetPlayerLargeImageText(const playerid, const large_image_text[]);
native DRP_SetPlayerSmallImageKey(const playerid, const small_image_key[]);
native DRP_SetPlayerSmallImageText(const playerid, const small_image_text[]);
native DRP_SetPlayerState(const playerid, const drp_state[]);
```
