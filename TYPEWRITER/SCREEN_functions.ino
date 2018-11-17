void print_page(String pathtext)
{ 
  int posizione = YPAG*XRES;
  int place;
  int saving = -1;
  copy_file(pathtext,PATHTEMP);
  ASCII_file(PATHTEMP, "/Settings/ASCII.txt");
  File texto = SD.open(PATHTEMP, FILE_READ);
  count_lines(texto); // LINEE e LINEE_LUNG
  char car;
  while (true)
  {
    lcd.clear();
    posizione = 0;
    for(int z = 0; z<YPAG;z++)
    {
      posizione = posizione + abs(LINEE[z]); 
    }
    texto.seek(posizione);
    ASCII_file(PATHTEMP, "/Settings/ASCII.txt");
    for(int j = 0; j<YRES;j++)
    {
      for (int i = 0; i<XRES;i++)
      {
        Webserver_loop();
        car = (char)(texto.read());
        //ASCII 10 - line feed (una linea avanti) - il testo finisce con \r\n, salto l'"\r", poi scalo avanti ed esco dal ciclo
        if(car == '\n') 
        {   lcd.setCursor(i,j);
            car = byte(0);
            lcd.print(car);
            i = XRES;}
 
          //ASCII 13 - carriage return (vado ad inizio linea)
          else if(car != '\r')
          {
            lcd.setCursor(i,j);
            
            if((int)(car) == 255 or (int)(car) == 0) {car = ' ';}
            else if (CRYPTO == 1) {car = '*';}
            lcd.print(car);          
          }
          else
          {
            
            i--;
          }
        
      }
    }
    
  while(Tastiera.available() == 0)
    {
      Webserver_loop();
       if(FLAG_ESC == 1)
       {     texto.close();
             saving = choose_page(2,SAVE_MENU);
             if(saving == 0)
             {
              copy_file(PATHTEMP,pathtext);
              char pathtext_char[pathtext.length()];
              pathtext.toCharArray(pathtext_char,pathtext.length()+1);
              cursor_file_save(pathtext_char);
              ASCII_file(PATHTEMP, "/Settings/ASCII.txt");
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.noBlink();
              lcd.print("SAVED!");
              delay(2500);
              lcd.blink();
             }
             CHOSEN = 1;
             LEVEL = LAST_LEVEL;
             lcd.clear();
             FLAG_ESC = 0;             
             return;
       }
       lcd.setCursor(XCUR,YCUR);
       lcd.blink();
    }
    
    if (Tastiera.available() > 0) 
 {
      ANSWER = keyboard_loop();
       if (ANSWER == "[Up]") //arrow up
      { 
        if(YCUR>0)
        {YCUR--; 
        if(XCUR>abs(LINEE[YPAG+YCUR])+(-2-2*sgn(LINEE[YPAG+YCUR]))/2)
        {XCUR = abs(LINEE[YPAG+YCUR])+(-2-2*sgn(LINEE[YPAG+YCUR]))/2;}
        }
        else if(YPAG>0)
        {YPAG--;
         YCUR = YRES-1;  
         if(XCUR>abs(LINEE[YPAG+YCUR])+(-2-2*sgn(LINEE[YPAG+YCUR]))/2)
         {XCUR = abs(LINEE[YPAG+YCUR])+(-2-2*sgn(LINEE[YPAG+YCUR]))/2;}
         }      
          FLAG_ESC = 0; 
        }
        
      else if (ANSWER == "[Down]") //arrow down
      { 
        if(YCUR<YRES-1)
          {YCUR++;
           if(XCUR>abs(LINEE[YPAG+YCUR])+(-2-2*sgn(LINEE[YPAG+YCUR]))/2)
           {XCUR = abs(LINEE[YPAG+YCUR])+(-2-2*sgn(LINEE[YPAG+YCUR]))/2;} 
           }
        else if (abs(LINEE[YPAG+YCUR+1])+(-1-1*sgn(LINEE[YPAG+YCUR+1]))/2>0 and YPAG<MAXLINES) 
        {
          YPAG++;
          YCUR = 0;   
         }              
        FLAG_ESC = 0; 
      }
      else if (ANSWER == "[Right]") 
      { 
        if(XCUR<abs(LINEE[YPAG+YCUR])+(-1-1*sgn(LINEE[YPAG+YCUR]))/2 -1)
          {XCUR++;}
        else
        { 
          if(YCUR<YRES-1)
          {YCUR++; XCUR = 0;} 
          else if (abs(LINEE[YPAG+YCUR+1])+(-1-1*sgn(LINEE[YPAG+YCUR+1]))/2>0 and YPAG<MAXLINES)
          {YPAG++;   
           XCUR = 0;}        
        }
        FLAG_ESC = 0; }
      else if (ANSWER == "[Left]") 
      { if(XCUR>0){XCUR--;}
        else
        {
          if(YCUR>0){YCUR--; XCUR = abs(LINEE[YPAG+YCUR])+(-1-1*sgn(LINEE[YPAG+YCUR]))/2-1;}
          else if(YPAG>0)
          {YPAG--;  
           XCUR = abs(LINEE[YPAG+YCUR])+(-1-1*sgn(LINEE[YPAG+YCUR]))/2-1;} 
        }
        FLAG_ESC = 0; }
      else if (ANSWER == "[Esc]")
      { FLAG_ESC = 1; }
      else if (ANSWER == "[Enter]")
      { FLAG_ESC = 0;
        texto.close();
        place = posizione + (abs(LINEE[YPAG]))*YCUR + XCUR; 
        inserisciCarattere(PATHTEMP,'\n', place);
        inserisciCarattere(PATHTEMP,'\r', place);
        XCUR = 0;
        texto = SD.open(PATHTEMP, FILE_READ);
        count_lines(texto);
        if(YCUR<YRES-1){YCUR++;}
        else if (YPAG<MAXLINES)
        {YPAG++; YCUR = 1;}     
      }
      else if (ANSWER == "[Del]")
      { FLAG_ESC = 0; 
        texto.close();
        place = posizione + (abs(LINEE[YPAG]))*YCUR + XCUR; 
        cancellaCarattere(PATHTEMP,place);
        ASCII_file(PATHTEMP, "/Settings/ASCII.txt");
        texto = SD.open(PATHTEMP, FILE_READ);
        count_lines(texto);
        }  
        
       else if (ANSWER == "Control-S")
      { FLAG_ESC = 0; 
        texto.close();
        copy_file(PATHTEMP,pathtext);
        char pathtext_char[pathtext.length()];
        pathtext.toCharArray(pathtext_char,pathtext.length()+1);
        cursor_file_save(pathtext_char);
        ASCII_file(PATHTEMP, "/Settings/ASCII.txt");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.noBlink();
        lcd.print("SAVED!");
        delay(2500);
        lcd.blink();
        texto = SD.open(PATHTEMP, FILE_READ);
        count_lines(texto);
        }  
        else if (ANSWER == "Control-P")
      { FLAG_ESC = 0;
        CRYPTO = -CRYPTO;
      }
        
       else if (ANSWER == "Backspace")
      { //FLAG_ESC = 0;
       if(XCUR>0 or YCUR+YPAG>0)
       {
        texto.close();
        place = posizione + (abs(LINEE[YPAG]))*YCUR + XCUR-1; 
        cancellaCarattere(PATHTEMP,place);
        ASCII_file(PATHTEMP, "/Settings/ASCII.txt");
        texto = SD.open(PATHTEMP, FILE_READ);
        if(XCUR>0){XCUR--;}
        else
        {
          if(YCUR>0){YCUR--; XCUR = abs(LINEE[YPAG+YCUR])+(-2-2*sgn(LINEE[YPAG+YCUR]))/2;} 
          else if(YPAG>0)
          {YPAG--;
           XCUR = abs(LINEE[YPAG+YCUR])+(-2-2*sgn(LINEE[YPAG+YCUR]))/2;} 
        }
        count_lines(texto);
       }
        }  
        
      else if ((int)(ANSWER[0]) != 10)
      {
        FLAG_ESC = 0;
        count_lines(texto);
        texto.close();
        place = posizione + (abs(LINEE[YPAG]))*YCUR + XCUR;  //occhio quando vado a capo senza invio
        inserisciCarattere(PATHTEMP, ANSWER[0], place);
        if(XCUR<abs(LINEE[YPAG+YCUR])+(-1-1*sgn(LINEE[YPAG+YCUR]))/2 and XCUR<XRES-1) //se XCUR è meno del limite************
        { XCUR++; Serial.println(XCUR);}
        else
        { if(YCUR<YRES-1){YCUR++; XCUR = 0;}
          else if (abs(LINEE[YPAG+YCUR+1])+(-1-1*sgn(LINEE[YPAG+YCUR]))/2>0 and YPAG<MAXLINES)
          {YPAG++; 
           XCUR = 0;}        
        }
        ASCII_file(PATHTEMP, "/Settings/ASCII.txt");
        texto = SD.open(PATHTEMP, FILE_READ);
        
        count_lines(texto);
      }
        
  }
    
  } 
  texto.close();
}

///////////////////////////////////////////////////////////////////////////////////////////////

