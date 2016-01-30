#ifndef _BUFFER_H_INCLUDED_
#define _BUFFER_H_INCLUDED_

class Buff
{
private:

public:
    BITMAP * Buffer_Set_Up(void);
	void Buffer_Clear_To_Color(BITMAP *Buffer);
	void Buffer_Destroy(BITMAP *Buffer);
	void Update_Screen(BITMAP *Buffer);
};
#endif 
