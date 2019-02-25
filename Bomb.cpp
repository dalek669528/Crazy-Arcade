#include "project.h"

Bomb::Bomb()
{
	pow=NULL;
	bang=0;
	set=0;
	t=0;
}
void Bomb::powerptr(int *p)
{
	pow=p;
}
