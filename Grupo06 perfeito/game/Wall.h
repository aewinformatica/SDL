void aoCriar_Wall(Tobj *o)
{
	o->solido = 1;
	
	if (o->y==64)
		DefPic(o,"iWallUp");
	
	if (o->x==0)
		DefPic(o,"iWallLeft");
	
	if (o->x==screen_w-32)
		DefPic(o,"iWallRight");
	
	if (o->y==screen_h-32)
		DefPic(o,"iWallDown");
	
	if ((o->x==0 || o->x==screen_w-32) && o->y==screen_h-32)
		DefPic(o,"iWallBorderDown");
	
	if (o->x > 0 && o->x < screen_w-32 && o->y > 64 && o->y < screen_h-32)
		DefPic(o,"iWallMiddle");
}
