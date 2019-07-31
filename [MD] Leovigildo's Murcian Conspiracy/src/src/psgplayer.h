#ifndef _PSGCONTROL_H_
#define _PSGCONTROL_H_

typedef struct
{
	u8  title[16];
	u8 *data;
	u8  num;
}
PSG;

void   psgFxPlay      ( u16 psg );
void   psgFxFrame     ( void );
u16    psgfx_nb_tracks ( );
PSG   *psgfx_get_track ( u16 num );

#define sfx_select_size     51
extern const u8 sfx_select_data[sfx_select_size];

#define sfx_confirm_size    68
extern const u8 sfx_confirm_data[sfx_confirm_size];

#define sfx_cancel_size     75
extern const u8 sfx_cancel_data[sfx_cancel_size];

#define sfx_start_size     200
extern const u8 sfx_start_data[sfx_start_size];

#define sfx_error_size     147
extern const u8 sfx_error_data[sfx_error_size];

#define CONFIRM_SFX     0
#define SELECT_SFX      1
#define CANCEL_SFX      2
#define START_SFX       3
#define ERROR_SFX       4

#endif
