#ifndef _PLAYERSCONTROL_H_
#define _PLAYERSCONTROL_H_



void updatePlayerScore( u8 num_player, u8 flag );
void updatePlayerGfxUp( u8 num_player, u8 state );
void updatePlayerGfxRight( u8 num_player, u8 state );
void updatePlayerGfxDown( u8 num_player, u8 state );
void updatePlayerGfxLeft( u8 num_player, u8 state );
void playersControl( u8 ticks, u16 state_p1, u16 state_p2, u16 state_p3, u16 state_p4  );
u8 playerCollisionDetection( u8 num_player, u8 direction );
void movePlayer( u8 ticks, u8 player, u8 direction );
void changeFlipPlayer( u8 num_player );
void updateKiPlayer( u8 numPlayer );

#endif
