#include "genesis.h"//[[SGDK]]
/********************************************************************************
*      @Title:  PENGUIN WORLD
*      @Author: Alicia Sanchez Martos "AliceSim1"
***********************************************************************************/
#include "../inc/global.h"
//-----------------------------------------------------

//Definiciones de las funciones---------------------------------------------------
static void inputHandler(u16,u16,u16);

/////////////////////////////INICIO DE TODO//////////////////////////////////////////////////
void main(){
	
	JOY_setEventHandler(&inputHandler);
	//----------------------------------------------
	
	//VDP_drawText("Total:65536 bytes",20,1);
	//memfreettxt();
	
	//--------------------------------------------------
	gat=TRUE;

    while(1){//LOOP BASICO(NUNCA SE SALE!)
		
		if(!gat){
			
			if(BUTTONS[5]){ gat=TRUE;
				strcpy(dialog_txt,"!Hola Mundo¡");
				dialogo(3,17,32,2,1,PAL1,BG_B);
			}
			if(BUTTONS[6]){ gat=TRUE;
				strcpy(dialog_txt,dialogos[1]);
				dialogo(0,0,16,12,1,PAL1,BG_B);
			}
			if(BUTTONS[7]){ gat=TRUE;
				strcpy(dialog_txt,dialogos[0]);
				dialogo(3,17,32,4,1,PAL1,BG_B);
			}
			if(BUTTONS[8]){ gat=TRUE;
				strcpy(dialog_txt,dialogos[3]);
				dialogo(3,17,32,4,1,PAL1,BG_B);
			}
			
		}else if(!BUTTONS[0]) gat=FALSE;
	
		SYS_doVBlankProcess(); // Renderizamos la pantalla
    }
}


void memfreettxt(){
	/*sprintf(char_salida, "Free: %05u bytes", MEM_getFree());
	VDP_drawText(char_salida, 20, 2);
	sprintf(char_salida, "Used: %05u bytes", 65536 - MEM_getFree());
	VDP_drawText(char_salida, 20, 3);*/
}

/**
 * Manejador de entrada
 * joy-> Indica el mando que ha activado la entrada
 * state -> Indica el estado del mando (boton activo)
 * changed -> indica si ha cambiado (pulsado o solatado)
 * */
void inputHandler(u16 joy, u16 state, u16 changed){
   
    BUTTONS[0]=changed;

	BUTTONS[1]=changed & BUTTON_UP;
	BUTTONS[2]=changed & BUTTON_DOWN;
	BUTTONS[3]=changed & BUTTON_LEFT;
	BUTTONS[4]=changed & BUTTON_RIGHT;
	
	BUTTONS[5]=changed & BUTTON_A;
	BUTTONS[6]=changed & BUTTON_B;
	BUTTONS[7]=changed & BUTTON_C;

	BUTTONS[8]=changed & BUTTON_START;
	
	BUTTONS[9]=changed & BUTTON_X;
	BUTTONS[10]=changed & BUTTON_Y;
	BUTTONS[11]=changed & BUTTON_Z;
	BUTTONS[12]=changed & BUTTON_MODE;
	
}
