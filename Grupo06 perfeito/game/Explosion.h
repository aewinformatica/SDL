void aoCriar_Explosion(Tobj *o)
{
	o->z = 9;
	o->solido=1;
}

void aoTerminarAnim_Explosion(Tobj *o)
{
	Destrua(o);
}
