typedef enum {SFX_CUR,SFX_SEL,SFX_NOP,SFX_UP,SFX_DOWN,SFX_START,SFX_STOP,SFX_CLR} WHICHSOUND;

extern void playsnd(WHICHSOUND sound);
extern void snd_up();
extern void snd_down();
