void aoCriar_Minerva(Tobj *o)
{
	o->opac = 0;
	o->clock0=1;
}

void aoClock0_Minerva(Tobj *o)
{
	if (o->opac<200)
	{
		o->opac++;
		o->clock0=1;
	}
	else
	{
		o->clock1=120;
	}
}

void aoClock1_Minerva(Tobj *o)
{
	if (o->opac>0)
	{
		o->opac--;
		o->clock1=1;
	}
	else
	{
		quit=1;
		Destrua(o);
	}
}

