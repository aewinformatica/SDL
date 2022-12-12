void aoCriar_Fogo(Tobj *o)
{
	o->z = 5;
	o->clock0 = TempoFogo*3;
	o->solido = 1;
}

void aoClock0_Fogo(Tobj *o)
{
	Destrua(o);
}

