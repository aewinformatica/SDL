void aoDestruir_Caveira1(Tobj *o)
{
	Crie("Explosion2", o->x, o->y);
}

void Colisoes_Caveira1(Tobj *o)
{
	int other;
	for (other=0;other<nobj;other++)
	{
		//Colisao entre Caveira1 e Chama
		if ((!strcmp(obj[other].nome,"FireS") || !strcmp(obj[other].nome,"FireN") || !strcmp(obj[other].nome,"FireL") || !strcmp(obj[other].nome,"FireO") || !strcmp(obj[other].nome,"FireNS") || !strcmp(obj[other].nome,"FireLO") || !strcmp(obj[other].nome,"FireM")) && ColisaoS2(o, &obj[other], 8))
		{
			Destrua(o);
			score+=100;
		}	
	}

}

void aoCriar_Caveira1(Tobj *o)
{
	PuleAleatorio(o);
	redirect(o);
	o->speed = 1;
	o->z=1000;
}

void aoClock0_Caveira1(Tobj *o)
{
	Mova(o);
	if (NaGrade(o,32))
		redirect(o);
	else
		o->clock0 = 1;
}



