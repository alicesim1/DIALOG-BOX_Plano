#include "genesis.h"//[[SGDK]]
/********************************************************************************
*      @Title:  PENGUIN WORLD
*      @Author: Alicia Sanchez Martos "AliceSim1"
***********************************************************************************/
#include "../inc/global.h"

/*
  ASCI: 33 = " (comillas)  usar: \"
  ASCI: 92 = \ (CUIDADO! escape seuence)  usar siempre: \\
*/

//                               10        20        30
//8x2>> 8*4=32, 2*4=8   12345678901234567890123456789012
//--------------------->xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx>xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx>xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx>xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx>
const char dialogo0[]={"El veloz murciélago hindú comía feliz cardillo y kiwi.          La cigüeña tocaba el saxofón    detrás del palenque de paja."};
const char dialogo1[]={" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ "};


const char dialogo2[]={"¡¿ÁÉÍÑÓÚÜáéíñóúü"};//ASCII Extendido
const char dialogo3[]={" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ ¡¿ÁÉÍÑÓÚÜáéíñóúü"};
//---------------------|XXXXXXXXXXXXXXXXXXXXXXXXX0|---------
const char *dialogos[] = {dialogo0,dialogo1,dialogo2,dialogo3};

const u8 ascii_SP[]={129,159,161,169,173,177,179,186,188,193,201,205,209,211,218,220};
/*Message : ¡
Message : letra: 14 >ASCI: 161 >c: 129
Message : ¿
Message : letra: 15 >ASCI: 191 >c: 159
Message : Á
Message : letra: 0 >ASCI: 193 >c: 161
Message : É
Message : letra: 1 >ASCI: 201 >c: 169
Message : Í
Message : letra: 2 >ASCI: 205 >c: 173
Message : Ñ
Message : letra: 5 >ASCI: 209 >c: 177
Message : Ó
Message : letra: 3 >ASCI: 211 >c: 179
Message : Ú
Message : letra: 4 >ASCI: 218 >c: 186
Message : Ü
Message : letra: 6 >ASCI: 220 >c: 188
Message : á
Message : letra: 7 >ASCI: 225 >c: 193
Message : é
Message : letra: 8 >ASCI: 233 >c: 201
Message : í
Message : letra: 9 >ASCI: 237 >c: 205
Message : ñ
Message : letra: 12 >ASCI: 241 >c: 209
Message : ó
Message : letra: 10 >ASCI: 243 >c: 211
Message : ú
Message : letra: 11 >ASCI: 250 >c: 218
Message : ü
Message : letra: 13 >ASCI: 252 >c: 220
*/

static u8 ASCII_EXT(u8 charasci){
	u8 i=0;
	while(ascii_SP[i]!=charasci){
		i++;
	}
	return 96+i;
}

/*
numdiag=numero dialogo, 
x,y - coordenadas tile plano
ancho tiles(8x8px),alto(x fila de texto 16px/2 tiles)  
coordenadas VRAM 0=Background, 1=>
paleta:0,1,2,3
*/
void dialogo(u16 x,u16 y,u8 ancho, u8 alto, u16 diag_ind,u8 diag_pal,u8 planoAB){

	/*
	------------------------------
	calculo de consumo Tiles de VRAM:
	barra esquinas= 1
	barra horizontal= 1
	barra vertical= 1
	lienzo= 1+(ancho*alto*16)
	
	*/
	/*KLog("----START DIALOG-BOX----");
	
	KLog_U2("ancho: ",ancho," X alto: ",alto);
	
	KLog_U1("VRAM Start pos: ",diag_ind);
	KLog_U1("VRAM Tiles: ",4+(ancho*alto));
	KLog_U1("VRAM Final pos: ",diag_ind+4+(ancho*alto));
	
	u8 dig_long=strlen(dialog_txt);
	KLog_U1("Caracteres: ",dig_long);	
	KLog(dialog_txt);*/
	
	u8 dig_long=strlen(dialog_txt);
	
	char cadena_org[dig_long];//tipo cadena completa ""(se auto añade al final \0)
	strcpy(cadena_org,dialog_txt);
	
	PAL_setColors(diag_pal<<4,dig_marcoP.data,8,CPU);
	
	
	VDP_loadTileSet(&dig_marco,diag_ind,CPU);
	
	//descomprimimos TilSet
	TileSet *t = unpackTileSet(&font16, NULL);
	//KLog_U1("t->numTile: ",t->numTile);//numTile:384
	u16 Tilelienzo = diag_ind+3;
	DMA_queueDmaFast(DMA_VRAM,(void *)t->tiles,Tilelienzo<<5,16,2);
	//DMA_queueDmaFast(DMA_VRAM,(void *)font16.tiles,Tilelienzo<<5,16,2);
	
	//--------Marco Esquinas---------------------------------------------------------
	
	VDP_setTileMapXY(planoAB,TILE_ATTR_FULL(diag_pal,TRUE, FALSE, FALSE, diag_ind),x,y);
	VDP_setTileMapXY(planoAB,TILE_ATTR_FULL(diag_pal,TRUE, FALSE, TRUE, diag_ind),x+1+ancho,y);
	VDP_setTileMapXY(planoAB,TILE_ATTR_FULL(diag_pal,TRUE, TRUE, FALSE, diag_ind),x,y+1+(alto*2));
	VDP_setTileMapXY(planoAB,TILE_ATTR_FULL(diag_pal,TRUE, TRUE, TRUE, diag_ind),x+1+ancho,y+1+(alto*2));
	SYS_doVBlankProcess();
	
	u8 i;
	u8 cancho=ancho+1;
	//-------Marco horizontales----------------------
	for(i=0;i<cancho;i+=2){
		VDP_fillTileMapRect(planoAB,TILE_ATTR_FULL(diag_pal,TRUE, FALSE, FALSE, diag_ind+1),x+1,y,i,1);
		VDP_fillTileMapRect(planoAB,TILE_ATTR_FULL(diag_pal,TRUE, TRUE, FALSE, diag_ind+1),x+1+(cancho-1-i),y+1+(alto*2),i,1);
		SYS_doVBlankProcess();
	}
	//-------Marco verticales-----------------------
	cancho=(alto*2)+1;
	for(i=0;i<cancho;i+=2){
		VDP_fillTileMapRect(planoAB,TILE_ATTR_FULL(diag_pal,TRUE, FALSE, FALSE, diag_ind+2),x,y+1+(cancho-1-i),1,i);
		VDP_fillTileMapRect(planoAB,TILE_ATTR_FULL(diag_pal,TRUE, FALSE, TRUE, diag_ind+2),x+1+ancho,y+1,1,i);
		SYS_doVBlankProcess();
	}
	//Lienzo 32x32---------------------------------------------------
	
	for(i=0;i<cancho;i++){
		VDP_fillTileMapRect(planoAB,TILE_ATTR_FULL(diag_pal,TRUE, FALSE, FALSE, Tilelienzo),x+1,y+1,ancho,i);
		SYS_doVBlankProcess();
	
	}
	
	//Lienzo 32x32---------------------------------------------------
	
	u16 ind=Tilelienzo+1;
	
	
	
	u16 c;//valor indice de Tileset de la tabla ASCII grafico! 8x16
	u8 ct;//valor caracter ASCII 0(32)=" "
	
	char cadena_temp[1];//[0] caracter, [1]=\0
	
	u8 letra=0;//numero de posicion de caracteres de la frase
	u8 vel_letra=4;
	cancho=0;
	u8 dig_fila=0;
	
	//KLog_U4("ancho:",ancho,"-tcancho:",tcancho,">ind:",Start_ind," -top_ind:",top_ind);
	
	bool skip=FALSE;
	do{
		
		cadena_temp[0]=cadena_org[letra];
		cadena_temp[1]='\0';// [0] = H > ASCII:72
		
		//KLog(cadena_temp);
		
		ct=cadena_temp[0];//32-255
		c=ct-32;//32>0 ASCII valor
		
		if(c>128){ c=ASCII_EXT(c); }
		
		//KLog_U3("letra: ",letra," >ASCI: ",ct," >c: ",c);
		
		//KLog_U1(">ind:",ind);
		if(c>0){//0=Espacio,1=!,2=...
			
			if(c>15){//calcular +16 X cada > 16 caracteres ASCII
				ct=c/16;
				ct=16*ct;//necesario para saltar a la siguiente linea tabla ASCII
				c+=ct;
				//KLog_U2("/16> ",ct," *16= ",c);
			}
			//Insertar Caracteres 8x16 en el lienzo VRAM
			//Tails8521
			//----No se puede comprimir----Dirección del búfer de origen., Dirección de destino VRAM / CRAM / VSRAM.
			//DMA_queueDma(DMA_VRAM, (void *)yourtileset.tiles + yourtileindexinthetileset * 32, yourvramtileindex * 32, 16, 2);
			
			//DMA_queueDmaFast(DMA_VRAM,(void *)font16.tiles+ c    *32,ind<<5,16,2);ind++;//0>1    (2>3)
			//ancho> 128/8= 16 tiles | situamos el origen segunda fila de tiles 8x8, parte inferior de chara 8x16
			//DMA_queueDmaFast(DMA_VRAM,(void *)font16.tiles+(c+16)*32,ind<<5,16,2);ind++;//1>2... (3>4...)
			
			DMA_queueDmaFast(DMA_VRAM,(void *)t->tiles+ c    *32,ind<<5,16,2);ind++;//0>1    (2>3)
			//ancho> 128/8= 16 tiles | situamos el origen segunda fila de tiles 8x8, parte inferior de chara 8x16
			DMA_queueDmaFast(DMA_VRAM,(void *)t->tiles+(c+16)*32,ind<<5,16,2);ind++;//1>2... (3>4...)
			
			SYS_doVBlankProcess();

			VDP_setTileMapXY(planoAB,TILE_ATTR_FULL(diag_pal,TRUE, FALSE, FALSE, ind-2),x+1+cancho,y+1+(dig_fila*2));
			VDP_setTileMapXY(planoAB,TILE_ATTR_FULL(diag_pal,TRUE, FALSE, FALSE, ind-1),x+1+cancho,y+2+(dig_fila*2));
			
		}
		
		cancho++;
		//KLog_U2("cancho:",cancho,"==tcancho:",tcancho);
		if(cancho==ancho){
			cancho=0;
			dig_fila++;//pasamos a la siguiente fila (siguiente fila de Sprites)
		}
		
		letra++;
		if(!skip && vel_letra>0 && c>0){
			for(i=0;i<vel_letra;i++){
				if(!gat){
					if(BUTTONS[6]) { skip=TRUE; break;}//salimos del FOR
				}
				else if(!BUTTONS[6]) gat=FALSE;
				SYS_doVBlankProcess();
				//memfreettxt();
			}
		}
		
		//JOY_waitPressTime(JOY_ALL,BUTTON_B,1000);
	} while(dig_fila<alto && letra<dig_long);
	
	
	//liberamos el TileSet de la fuente 8x16 ASCII de la RAM
	MEM_free(t);
	
	
	gat=TRUE;
	
	//KLog("----ESPERA DIALOG-BOX----");
	
	//memfreettxt();
	
	do{
		
		if(gat && !BUTTONS[6]) gat=FALSE;
		
		SYS_doVBlankProcess();
	}while(!BUTTONS[6] || gat);	gat=TRUE;
	
	VDP_clearTileMapRect(planoAB,x,y,ancho+2,(alto*2)+2);

	//KLog("----END DIALOG-BOX----");
}
