void aoCriar_BomberBurn(Tobj *o)
{
	o->z = 7;
	o->clock0 = 180;
}

void aoTerminarAnim_BomberBurn(Tobj *o)
{
	DefPic(o,"none");
}

void aoClock0_BomberBurn(Tobj *o)
{
	vidas--;
	if (vidas<0)
		quit = 1;
	else
	{
		Crie("Bomber",32,96);
		FirePower = InitChama;
		MaxBombs = InitBombs;
	}	
	Destrua(o);
}
