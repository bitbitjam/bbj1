// External custom code to be run from a script


void change_tile (unsigned char tile, unsigned char color, int count ){
	unsigned char * pointer;
	tile = 64 + (tile << 2);
	pointer = (unsigned char *) &tileset [2048 + tile];
	pointer[0]=color;
	pointer[1]=color;
	if(count>=3){
	pointer[2]=color;
	pointer[3]=7;
	if (count>=4){
	pointer[3]=color;	
	}
}
		
	

}
void change_attribute(unsigned char coor_tile_x,unsigned char coor_tile_y,unsigned char tile_attribute){
	
	  map_attr [coor_tile_x + (coor_tile_y << 4) - coor_tile_y] = tile_attribute;
}


void do_extern_action (unsigned char n) {
	switch(n){
		case 0:
			//cAMBIO EL COLOR DEL PISO Y DE LA LLAVE EN PLANTA BAJA
		    change_tile(32,71, 2);
		    change_tile(27,6, 3);
			
			
			break;
		
		case 1: 
		    //cAMBIO EL COLOR DEL PISO Y DE LA LLAVE EN PLANTA 1
		    change_tile(32,2, 2);
		    change_tile(27,4, 3);
		    
		   
		break;
		
		case 2: 
		    //cAMBIO EL COLOR DEL PISO Y DE LA LLAVE EN PLANTA 2
		    change_tile(32,6, 2);
		    change_tile(27,2,3 );
		    
			
		break;
		
		case 3: 
		    //cAMBIO EL COLOR DEL PISO Y DE LA LLAVE EN PLANTA 3
		    change_tile(32,4, 2);
		    change_tile(27,1,3 );
			
		break;
		
		case 4: 
		    //cAMBIO EL COLOR DEL PISO Y DE LA LLAVE EN PLANTA 4
		    change_tile(32,1, 2);
		    change_tile(27,7,3 );
			
		break;
		
		case 5:
			//Cambio de color ordenador planta 1
			change_tile(35,2,4);
			change_tile(1, 2, 4);
		    change_tile(17, 2, 2);
		    
			
		break;	
		
		case 6:
			//Cambio de color ordenador planta 2
			change_tile(35,6,4);
			change_tile(1, 6, 4);
		    change_tile(17, 6, 2);
		    
			
		break;	
		
		case 7:
			//Cambio de color ordenador planta 3
			change_tile(35,4,4);
			change_tile(1, 4, 4);
		    change_tile(17, 4, 2);
		    
			
		break;
		
		case 8:
			//Cambio de color ordenador planta 4
			change_tile(35,1,4);
			change_tile(1, 1, 4);
		    change_tile(17, 1, 2);
		    
			
		break;	
		case 9:
			//cambio al color de origen
			change_tile(35,71,4);
			change_tile(1, 71, 4);
		    change_tile(17,71, 2);
		
		break;
		
		case 10:
			//cambiamos el comportamiento de un tile en
			change_attribute(0,8,8);
			change_attribute(0,7,8);
		break;   
	    case 100:
	    case 101:
	    case 102:
	    case 103:
	        draw_coloured_tile(12 + ((n - 100) << 1) ,21 , 27 );
	        print_str (9,  2, 79, " TO POLLUO! ");
            break;
		}
}
