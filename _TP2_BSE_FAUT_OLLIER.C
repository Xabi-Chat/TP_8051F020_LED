//-----------------------------------------------------------------------------
// TP1_BSE.c
//-----------------------------------------------------------------------------
// AUTH: XF + DO
// DATE: 
//
// Target: C8051F02x
// Tool chain: KEIL Microvision 4
//
//-----------------------------------------------------------------------------
#include <C8051F020.h>

//sfr P1 = 0x80; /**On place le port P1 dans le registre sfr qui est compris entre 80 et FF**/
//sfr P3 = 0x88;

sbit LED = P1^6; /**Led connectée au bit 6 du port P1**/
sbit BOUTON = P3^7; /**Bouton poussoir connecté au bit 7 du port P3**/
sbit SIG_OUT = P1^5;

// Prototypes de Fonctions
void Init_Device(void);
void Phase_Demarrage(void);
void Phase_Usage(void);
void Delay(unsigned long int delais_ms);

//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------
void main (void) {
        P1MDOUT=0x40; //mode pushpull
	      Init_Device();
	      // Inserer ici des fonctions de configuration
        Phase_Demarrage();
	       EA=1; //autoriser les interruptions
        while(1)
        {
           Phase_Usage();		
        }						               	
}
//-----------------------------------------------------------------------------
// Init_Device Routine - Code  de configuration du 8051F020
//-----------------------------------------------------------------------------
void Init_Device(void)
{
// Ne pas enlever, modifier ces 3 lignes de code qui suivent. 
// Leur compréhension n'est pas l'objet du premier TP
	  WDTCN = 0xDE;   
    WDTCN = 0xAD;	
	  XBR2  |= 0x40;
//  Code de configuration globale a inserer	
	
	IE |= 0x20; //IE.5 = 1; autoriser interruption5
	TR2=1; //enable and start the timer
	T2CON &= 0x01; //selection du auto_reload (CP/RL2=T2CON.0) xxxx.xxx0
	CKCON |= 0x20; //pas besoin de diviser par 12 (T2M=CKCON.5) xx1x.xxxx
	T2CON &= 0x02; //on utilise sysclk (C/T2=T2CON.1) xxxx.xx0x
	RCAP2H = 0xFD; //RCAP2H=1111.1101;
	RCAP2L = 0x8F; //RCAP2L=1000.1111;
	//si TF2 == 1 alors interruption.
}
//-----------------------------------------------------------------------------
// Phase_Demarrage Routine 
//-----------------------------------------------------------------------------
void Phase_Demarrage(void)
{
//  Code à inserer	
	while (BOUTON==1){
		LED = 1; // Led allumée cycle 1
		Delay(500);
		LED = 0; // Led éteinte cycle 1
		Delay(500);
	}
}
//-----------------------------------------------------------------------------
// Phase_Usage Routine 
//-----------------------------------------------------------------------------
void Phase_Usage(void)
{
//  Code à inserer	
	
}
//-----------------------------------------------------------------------------
// Fonction délais
//-----------------------------------------------------------------------------
void Delay(unsigned long int delais_ms)
{
unsigned long int k = 0;
delais_ms = delais_ms*25; /** En testant plusieurs valeurs de coefficients
multiplicatifs, on remarque que multiplier par 25 nous permet bien
d'avoir 5% de précision en temps. **/
for (k=0;k<delais_ms;k++){
}
return;
}
//-----------------------------------------------------------------------------
// Interruption
//-----------------------------------------------------------------------------
void InterruptionT2 (void) interrupt 5{
	P5 |= 0x40; //P5.6 = 1 témoin
	SIG_OUT = !SIG_OUT;
	
	T2CON &= 0x7F; //(TF2=T2CON.7) 0xxx.xxxx
	P5 &= 0xBF; //P5.6 = 0
}