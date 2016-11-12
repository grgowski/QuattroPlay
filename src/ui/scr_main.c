/*
    General UI code
*/

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"
#include "math.h"

#include "../qp.h"
#include "ui.h"
#include "scr_main.h"

    inputstate_t inpstate;

    int displaymode;
    int curr_val;         // Current selected value
    int curr_val_edit;    // Temp value used in editing.
    int curr_val_type;    // Type of current selected value (song request / register)
    int curr_val_offset;  // Offset in song req/register table.
    char tempstring[512];

const char regmatrix_key[] = "+0/8 +1/9 +2/a +3/b +4/c +5/d +6/e +7/f";

void drawreg(int val,int y,int x)
{
    static int blink;

    uint16_t v, a;

    colorsel_t c = COLOR_N_GREY;
    colorsel_t bg= COLOR_D_BLUE;

    if(val < 0x20)
    {
        v = QDrv->SongRequest[val];
    }
    else if(val < 0x120)
    {
        v = QDrv->Register[val-0x20];
    }
    else if(val < 0x140)
    {
        a = val-0x120;
        v=0;
        if(QDrv->Voice[a].TrackNo)
            v = 0x8000|(QDrv->Voice[a].TrackNo-1)<<8|(QDrv->Voice[a].ChannelNo);
        if(QDrv->Voice[a].Enabled)
            v |= 0x80;

        if(QDrv->SoloMask)
        {
            bg = COLOR_D_GREY;
            if(QDrv->SoloMask & 1<<a)
                bg = COLOR_D_BLUE;
        }
        if(QDrv->MuteMask && !(QDrv->SoloMask & 1<<a))
        {
            if(QDrv->MuteMask & 1<<a)
                bg = COLOR_BLACK;
        }

    }
    else
    {
        v = 0;
    }

    if(val == curr_val)
    {
        c = COLOR_WHITE;
        if(inpstate == STATE_SETVALUE)
        {
            v = curr_val_edit;
            blink ^= 1;
            if(blink)
                c = COLOR_N_RED;
        }
    }

    set_color(y,x,1,4,bg,c);
    SCRN(y,x,5,"%04x",v);
}

void drawregkey(int y)
{
    set_color(y,4,1,40,COLOR_BLACK,COLOR_L_GREY);
    SCRN(y,4,40,"%s",regmatrix_key);
}

void drawregrow(int y,int val)
{
    int dispval = val&0x1f;
    int i;
    set_color(y,1,1,2,COLOR_BLACK,COLOR_L_GREY);

    if(val>=0x120)
        dispval = val-0x120;
    else if(val>=0x20)
        dispval = val-0x20;

    SCRN(y,1,40,"%02x",dispval);

    for(i=0;i<8;i++)
    {
        drawreg(val+i,y,4+(i*5));
    }
}

void ui_entry_setvalue(int flag, int type, int offset, int value)
{
    int temp = 0;
    switch(type)
    {
    case ENTRY_SONGREQ:
        Game->PlaylistControl = 0;
        if(flag)
            temp = Q_TRACK_STATUS_START;
        Q_LoopDetectionReset(QDrv);
        QDrv->SongRequest[offset&0x1f] = value | temp;
        break;
    case ENTRY_REGISTER:
        QDrv->Register[offset&0xff] = value;
        break;
    default:
        break;
    }
}

void ui_convert_currval()
{
    if(curr_val < 0x20)
    {
        curr_val_type = ENTRY_SONGREQ;
        curr_val_offset = curr_val;
        curr_val_edit = QDrv->SongRequest[curr_val_offset] & 0x7ff;
    }
    else if(curr_val < 0x120)
    {
        curr_val_type = ENTRY_REGISTER;
        curr_val_offset = curr_val-0x20;
        curr_val_edit = QDrv->Register[curr_val_offset];
    }
    else if(curr_val < 0x140)
    {
        curr_val_type = ENTRY_VOICE;
        curr_val_offset = curr_val-0x120;
    }
}

void ui_bounds_check()
{
    int song_max = QDrv->SongCount-1;

    if(curr_val_edit < 0)
        curr_val_edit=0;

    if(curr_val_type == ENTRY_SONGREQ && curr_val_edit > song_max)
        curr_val_edit=song_max;
    else if(curr_val_edit > 0xffff)
        curr_val_edit=0xffff;
}

void scr_main_input()
{
    got_input=0;

    const uint8_t * kbd;
    int increment;

    kbd = SDL_GetKeyboardState(NULL);

    switch(keycode)
    {
    case SDLK_0:
        GameDoAction(Game,0);
        break;
    case SDLK_1:
        GameDoAction(Game,1);
        break;
    case SDLK_2:
        GameDoAction(Game,2);
        break;
    case SDLK_3:
        GameDoAction(Game,3);
        break;
    case SDLK_4:
        GameDoAction(Game,4);
        break;
    case SDLK_5:
        GameDoAction(Game,5);
        break;
    case SDLK_6:
        GameDoAction(Game,6);
        break;
    case SDLK_7:
        GameDoAction(Game,7);
        break;
    case SDLK_8:
        GameDoAction(Game,8);
        break;
    case SDLK_9:
        GameDoAction(Game,9);
        break;
    case SDLK_ESCAPE:
        if(inpstate == STATE_SETVALUE)
            inpstate=STATE_MAIN;
        break;
    case SDLK_c:
        curr_val_edit=0;
        if(inpstate != STATE_SETVALUE)
        {
            ui_convert_currval();
            curr_val_edit=0;
            ui_entry_setvalue(0,curr_val_type,curr_val_offset,curr_val_edit);
        }
        break;
    case SDLK_i:
    case SDLK_d:
        increment = keycode==SDLK_i ? 1 : -1;
        curr_val_edit+=increment;
        ui_bounds_check();
        if(inpstate != STATE_SETVALUE)
        {
            Game->PlaylistControl = 0;
            ui_convert_currval();
            curr_val_edit+=increment;
            ui_bounds_check();
            ui_entry_setvalue(1,curr_val_type,curr_val_offset,curr_val_edit);
        }
        break;
    case SDLK_a:
        if(inpstate != STATE_SETVALUE)
        {
            ui_convert_currval();
            if(curr_val_type == ENTRY_SONGREQ)
            {
                QDrv->SongRequest[curr_val_offset] ^= Q_TRACK_STATUS_ATTENUATE;
            }
        }
        break;
    case SDLK_f:
    case SDLK_s:
        if(inpstate != STATE_SETVALUE)
        {
            ui_convert_currval();
            if(curr_val_type == ENTRY_SONGREQ)
            {
                Game->PlaylistControl = 0;
                Q_LoopDetectionReset(QDrv);
                if(keycode==SDLK_f)
                    QDrv->SongRequest[curr_val_offset] |= Q_TRACK_STATUS_FADE;
                if(keycode==SDLK_s)
                    QDrv->SongRequest[curr_val_offset] &= ~(Q_TRACK_STATUS_BUSY);
            }
            if(curr_val_type == ENTRY_VOICE)
            {
                QDrv->SoloMask ^= 1<<curr_val_offset;
                Q_UpdateMuteMask(QDrv);
            }
        }
        break;
    case SDLK_m:
        if(inpstate != STATE_SETVALUE)
        {
            ui_convert_currval();
            if(curr_val_type == ENTRY_VOICE)
            {
                QDrv->MuteMask ^= 1<<curr_val_offset;
                Q_UpdateMuteMask(QDrv);
            }
        }
        break;
    case SDLK_r:
        if(inpstate != STATE_SETVALUE)
        {
            ui_convert_currval();

            if(curr_val_type == ENTRY_VOICE)
            {
                QDrv->MuteMask=0;
                QDrv->SoloMask=0;
                Q_UpdateMuteMask(QDrv);
            }
            else
                ui_entry_setvalue(1,curr_val_type,curr_val_offset,curr_val_edit);
        }
        break;
    case SDLK_l:
        displaysection++;
        break;
    case SDLK_RETURN:
        switch(inpstate)
        {
        case STATE_MAIN:
            curr_val_type=ENTRY_UNSUPPORTED;
            ui_convert_currval();
            if(curr_val_type == ENTRY_VOICE)
                displaysection++;
            else if(curr_val_type != ENTRY_UNSUPPORTED)
                inpstate=STATE_SETVALUE;

            break;
        case STATE_SETVALUE:
            ui_entry_setvalue(1,curr_val_type,curr_val_offset,curr_val_edit);
        default:
            inpstate=STATE_MAIN;
            break;
        }
        break;
    case SDLK_LEFT:
    case SDLK_RIGHT:
    case SDLK_UP:
    case SDLK_DOWN:
        switch(inpstate)
        {
        case STATE_MAIN:

            increment = 1;

            if(keycode == SDLK_UP || keycode == SDLK_DOWN)
                increment *= 8;
            if(keycode == SDLK_LEFT || keycode == SDLK_UP)
                increment *= -1;
            curr_val+=increment;

            if(curr_val < 0)
                curr_val+=0x140;
            if(curr_val >= 0x140)
                curr_val-=0x140;
            break;
        case STATE_SETVALUE:

            increment = kbd[SDL_SCANCODE_RSHIFT] ? 256 : 1;

            if(keycode == SDLK_UP || keycode == SDLK_DOWN)
                increment *= 16;
            if(keycode == SDLK_LEFT || keycode == SDLK_DOWN)
                increment *= -1;
            curr_val_edit+=increment;

            ui_bounds_check();
        }
        break;
    default:
        got_input=1;
        break;
    }
}

void scr_main()
{
    if(refresh & R_SCR_MAIN)
    {
        refresh &= ~R_SCR_MAIN;
        displaymode = 0;
        curr_val = 0;
        curr_val_edit = 0;
        curr_val_type = 0;
        curr_val_offset = 0;
    }

    int i, j=0, x=0, y=0;

    SCRN(1,1,FCOLUMNS-2,"%s",QDrv->SongMessage);

    SCRN(0,FCOLUMNS-4,5,"%04x",QDrv->FrameCnt);

    if(got_input)
        scr_main_input();

    int ypos = 5;
    drawregkey(ypos++);
    for(i=0;i<0x20;i+=8)
        drawregrow(ypos++,i);
    drawregkey(ypos++);
    for(i=0x20;i<0x120;i+=8)
        drawregrow(ypos++,i);
    drawregkey(ypos++);
    for(i=0x120;i<0x140;i+=8)
        drawregrow(ypos++,i);

    set_color(1,1,1,FCOLUMNS-2,COLOR_D_BLUE|CFLAG_YSHIFT_50,COLOR_L_GREY);
    set_color(3,1,1,FCOLUMNS-2,COLOR_D_BLUE|CFLAG_YSHIFT_25,COLOR_L_GREY);
    //SCRN(47,1,40,"");


    set_color(49,0,1,FCOLUMNS,COLOR_D_BLUE,COLOR_L_GREY);
    if(curr_val < 0x120)
    {
        x = SCRN(49,1,48,"ENTER: change value, I/D: in-/decrement");
    }
    if(curr_val < 0x20)
    {
        i=curr_val;
        ui_info_track(i,5);
        x += SCRN(49,1+x,48,", R: Restart, S: Stop, F: Fade");
        j += SCRN(3,1,40,"Track %02x = %04x",i,QDrv->SongRequest[i]&0x7ff);

        y += SCRN(3,44+y,40,"%s %2.0f:%02.0f",
                 QDrv->SongRequest[i]&0x8000 ? "Playing" : "Stopped",
                 floor(QDrv->SongTimer[i]/60),floor(fmod(QDrv->SongTimer[i],60)));

        int8_t loopcount = Q_LoopDetectionGetCount(QDrv,curr_val);
        if(loopcount > 0)
            y += SCRN(3,44+y,15,", Loop%3d",loopcount);

    }
    else if(curr_val < 0x120)
    {
        j += SCRN(3,1,40,"Register %02x = %04x",curr_val-0x20,QDrv->Register[curr_val-0x20]);
    }
    else if(curr_val < 0x140)
    {
        i = curr_val-0x120;

        SCRN(49,1,48,"ENTER: display mode, M: Mute, S: Solo, R: Reset");
        ui_info_voice(i,5);
        SCRN(3,1,40,"Voice %02x",i);

        if(QDrv->Voice[i].TrackNo)
            SCRN(3,44,40,"Track %02x, Channel %02x",QDrv->Voice[i].TrackNo-1,QDrv->Voice[i].ChannelNo);
    }

    if(inpstate == STATE_SETVALUE)
    {
        SCRN(3,4+j,16," (Edit: %04x)",curr_val_edit);
    }
}
