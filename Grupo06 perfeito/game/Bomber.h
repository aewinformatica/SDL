void aoDestruir_Bomber(Tobj *o)
{
	Crie("BomberBurn", o->x, o->y);
}

void AlinharGrade(Tobj *o)
{
	if ((int)o->x%32 <= o->speed/2)
		o->x -= (int)o->x%32;
	if ((int)o->x%32 >= 32-o->speed/2)
		o->x += 32-(int)o->x%32;
	if ((int)o->y%32 <= o->speed/2)
		o->y -= (int)o->y%32;
	if ((int)o->y%32 >= 32-o->speed/2)
		o->y += 32-(int)o->y%32;
}

void Colisoes_Bomber(Tobj *o)
{
	int other;
	for (other=0;other<nobj;other++)
	{
		//Colisao entre Bomber e ItemFire
		if (!strcmp(obj[other].nome,"ItemFire") && ColisaoS2(o, &obj[other], 9))
		{
			Destrua(&obj[other]);
			FirePower++;
			if (FirePower>9)
				FirePower=9;
			score+=50;
		}
		
		//Colisao entre Bomber e ItemBomba
		if (!strcmp(obj[other].nome,"ItemBomba") && ColisaoS2(o, &obj[other], 9))
		{
			Destrua(&obj[other]);
			MaxBombs++;
			if (MaxBombs>9)
				MaxBombs=9;
			score+=50;
		}
		
		//Colisao entre Bomber e ItemLife
		if (!strcmp(obj[other].nome,"ItemLife") && ColisaoS2(o, &obj[other], 9))
		{
			Destrua(&obj[other]);
			vidas++;
			score+=100;
			PlaySom("sLife");
		}
		
		//Colisao entre Bomber e ItemPatins
		if (!strcmp(obj[other].nome,"ItemPatins") && ColisaoS2(o, &obj[other], 9))
		{
			Destrua(&obj[other]);
			o->speed+=0.5;
			if (o->speed > 5)
				o->speed = 5;
			
			o->x = ((int)o->x/o->speed)*o->speed;
			o->y = ((int)o->y/o->speed)*o->speed;
			
			score+=50;
		}
		
		//Colisao entre Bomber e Caveira1
		if (!strcmp(obj[other].nome,"Caveira1") && ColisaoS2(o, &obj[other], 9))
		{
			Destrua(o);
		}
		
		//Colisao entre Bomber e Dog
		if (!strcmp(obj[other].nome,"Dog") && ColisaoS2(o, &obj[other], 9))
		{
			Destrua(o);
		}
		
		//Colisao entre Bomber e a chama da explosao da bomba
		if ((!strcmp(obj[other].nome,"FireS") || !strcmp(obj[other].nome,"FireN") || !strcmp(obj[other].nome,"FireL") || !strcmp(obj[other].nome,"FireO") || !strcmp(obj[other].nome,"FireNS") || !strcmp(obj[other].nome,"FireLO") || !strcmp(obj[other].nome,"FireM")) && ColisaoS2(o, &obj[other], 8))
		{
			Destrua(o);
		}
	}
}

void aoCriar_Bomber(Tobj *o)
{
	DefPic(o, "iBomberDown");
	o->z = 10;
	o->speed = 3;
}

void Movimentar_Bomber(Tobj *o)
{
	int other;
	
	if (kleft)
	{	
		other = Colidindo(o,o->x-1,o->y);
	
		if (!other)
		{
			o->x-=o->speed;
			DefPic(o,"iBomberMoveLeft");
		}
		else
		{
			if (!kup && !kdown)
			{
				other--;
				if (o->y+16-12 < obj[other].y)
				{
					o->y-=o->speed;
					DefPic(o,"iBomberMoveUp");
				}
				else
				if (o->y+16+12 > obj[other].y+obj[other].h)
				{
					o->y+=o->speed;
					DefPic(o,"iBomberMoveDown");
				}
				else
					DefPic(o,"iBomberLeft");
			}
		}
		
		AlinharGrade(o);
	}

	if (kright)
	{
		other = Colidindo(o,o->x+1,o->y);
	
		if (!other)
		{
			o->x+=o->speed;
			DefPic(o,"iBomberMoveRight");
		}
		else
		{
			if (!kup && !kdown)
			{
				other--;
				if (o->y+16-12 < obj[other].y)
				{
					o->y-=o->speed;
					DefPic(o,"iBomberMoveUp");
				}
				else
				if (o->y+16+12 > obj[other].y+obj[other].h)
				{
					o->y+=o->speed;
					DefPic(o,"iBomberMoveDown");
				}
				else
					DefPic(o,"iBomberRight");
			}
		}
		
		AlinharGrade(o);
	}	

	if (kup)
	{
		other = Colidindo(o,o->x,o->y-1);
	
		if (!other)
		{
			o->y-=o->speed;
			DefPic(o,"iBomberMoveUp");
		}
		else
		{
			if (!kleft && !kright)
			{
				other--;
				if (o->x+16-12 < obj[other].x)
				{
					o->x-=o->speed;
					DefPic(o,"iBomberMoveLeft");
				}
				else
				if (o->x+16+12 > obj[other].x+obj[other].w)
				{
					o->x+=o->speed;
					DefPic(o,"iBomberMoveRight");
				}
				else
					DefPic(o,"iBomberUp");
			}
		}
		
		AlinharGrade(o);
	}
	
	if (kdown)
	{
		other = Colidindo(o,o->x,o->y+1);
	
		if (!other)
		{
			o->y+=o->speed;
			DefPic(o,"iBomberMoveDown");
		}
		else
		{
			if (!kleft && !kright)
			{
				other--;
				if (o->x+16-12 < obj[other].x)
				{
					o->x-=o->speed;
					DefPic(o,"iBomberMoveLeft");
				}
				else
				if (o->x+16+12 > obj[other].x+obj[other].w)
				{
					o->x+=o->speed;
					DefPic(o,"iBomberMoveRight");
				}
				else
					DefPic(o,"iBomberDown");
			}
		}
		
		AlinharGrade(o);
	}
	
	if (!kleft && !kright && !kup && !kdown)
	{
		if (!strcmp(o->pic,"iBomberMoveLeft"))
			DefPic(o,"iBomberLeft");
		if (!strcmp(o->pic,"iBomberMoveRight"))
			DefPic(o,"iBomberRight");
		if (!strcmp(o->pic,"iBomberMoveUp"))
			DefPic(o,"iBomberUp");
		if (!strcmp(o->pic,"iBomberMoveDown"))
			DefPic(o,"iBomberDown");
	}
	
	if (kspace==2 && Bombs < MaxBombs)
	{
		Crie("Bomba",
		((int) (o->x + ((int) o->x)%32)/32)*32,
		((int) (o->y + ((int) o->y)%32)/32)*32);
		kspace=1;
	}
}

