int choose_page(int num, char choices[][XRES-2]) //choice menu 
{
  lcd.clear();
  int arrow = 0;
  int ypage = 0;
  int FLAG_ESC = 0;
  CHOSEN = 0;
  while (CHOSEN == 0)
  {
    Webserver_loop();
  for (int i = 0; i<YRES;i++)
  {
    lcd.setCursor(0,i);    
    for(int j = 0; j<strlen(choices[i+ypage]);j++)
    {
    lcd.print(choices[i+ypage][j]);
        }
    lcd.setCursor(XRES-2,arrow);
    lcd.write('<');
    lcd.setCursor(XRES-1,arrow);
    lcd.write('-');
  }

  if (Tastiera.available() > 0) {
      ANSWER = keyboard_loop();
      if (ANSWER == "[Enter]")
      {
        CHOSEN = 1;
        lcd.clear();
        break;
        
      }
      else if (ANSWER == "[Up]") //arrow up
      {
        FLAG_ESC = 0;
        if(arrow > 0) {arrow--;}
        else if (ypage > 0) {ypage--;}
      }
      else if (ANSWER == "[Down]") //arrow down
      {
        FLAG_ESC = 0;
        if(arrow < 1) {arrow++;}
        else if (ypage < num-2) {ypage++;}
      }
      else if (ANSWER == "[Right]") 
      { FLAG_ESC = 0; }
      else if (ANSWER == "[Left]") 
      { FLAG_ESC = 0; }
      
      else if (ANSWER == "[Esc]")
      {
         FLAG_ESC = 1;      
        
      }
      lcd.clear();
  }
  else if(FLAG_ESC == 1)
        {                }
  }
  return ypage+arrow;  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int open_file(String tpath,int* nem,char choices[][XRES-2]) //choice of the file
{
  getDirectory(tpath, nem, choices);
  int num = *nem;
  int ypage = 0;
  lcd.clear();
  int arrow = 0;
  int FLAG_ESC = 0;
  String pit;
  CHOSEN = 0;
  while (CHOSEN == 0)
  {
    Webserver_loop();
  for (int i = 0; i<YRES;i++)
  {
    lcd.setCursor(0,i);
    for(int j = 0; j<strlen(choices[i+ypage]);j++)
    {
    lcd.print(choices[i+ypage][j]);
        }
    lcd.setCursor(XRES-2,arrow);
    lcd.write('<');
    lcd.setCursor(XRES-1,arrow);
    lcd.write('-');
  }

  if (Tastiera.available() > 0) {
      ANSWER = keyboard_loop();
      if (ANSWER == "[Up]") //arrow up
      {
        FLAG_ESC = 0;
        if(arrow > 0) {arrow--;}
        else if (ypage > 0) {ypage--;}
      }
      else if (ANSWER == "[Down]") //arrow down
      {
        FLAG_ESC = 0;
        if(arrow < 1) {arrow++;}
        else if (ypage < num-2) {ypage++;}
      }
      else if (ANSWER == "[Right]") 
      { FLAG_ESC = 0; }
      else if (ANSWER == "[Left]") 
      { FLAG_ESC = 0; }
      else if (ANSWER == "[Enter]")
      {
       
        if(LISTA[ypage+arrow][0]=='/')
        {
          PREV_LOC = tpath;
          pit = tpath+(String)(LISTA[ypage+arrow]);
          null_array(ArrayCount(LISTA), LISTA);
          LEVEL++;
          open_file(pit,&LENG,LISTA);
          return ypage+arrow;
        }

        else
        { LAST_LEVEL = LEVEL;
          LEVEL = 500;
          CHOSEN = 0;
          lcd.clear();
          return ypage+arrow; }
        
      }
      else if (ANSWER == "[Esc]")
      {
         FLAG_ESC = 1;      
        
      }
      lcd.clear();
  }
  else if(FLAG_ESC == 1)
        {
          if (LEVEL>100)
          { FLAG_ESC = 0;
            lcd.clear();
            LEVEL--;
            null_array(ArrayCount(LISTA), LISTA);
            open_file(PREV_LOC,&LENG,LISTA);
            return ypage+arrow;
          }
                    
          else 
          { CHOSEN = 0;
            //if (LEVEL>0)  {LEVEL--;}
            LEVEL = 0;
            lcd.clear();
            FLAG_ESC = 0;
            return ypage+arrow; }
        }
  }  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getDirectory(String funpath, int* lung, char list [][XRES-2]) //show the directory
{
File dir;
dir = SD.open(funpath);
dir.rewindDirectory();  
int files = 0;
int lex;
int slash;
while(true) {
Webserver_loop();
File entry = dir.openNextFile();
slash = 0;
if (! entry) {
// no more files
*lung = files;
dir.close();
break;
}

if (entry.isDirectory ())
{
  for (int j = strlen(entry.name())-1; j>-1; j--)
  {
    if(entry.name()[j]=='/')
    {
      slash = j;
      j = -1;
    }
  }
    if (strlen(entry.name())-slash < (XRES-2)) {lex = strlen(entry.name());}
    else                             {lex = slash+(XRES-2);}
     for(int i = slash; i<lex; i++)
   {
    list[files][i-(slash)] = entry.name()[i];
   }
    files++;
 }
 else
{
  for (int j = strlen(entry.name())-1; j>-1; j--)
  {
    if(entry.name()[j]=='/')
    {
      slash = j+1;
      j = -1;
    }
  }
  if (strlen(entry.name())-slash < (XRES-2)) {lex = strlen(entry.name());}
  else                             {lex = slash+(XRES-2);}
     for(int i = slash; i<lex; i++)
   {
    list[files][i-slash] = entry.name()[i];
         
   }
   
   
    files++;
 }


entry.close();
}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int insert_name(char* entry) //make you insert the new file name
{
  XCUR = 0;
  YCUR = 1;
  FLAG_ESC = 0;
  bool ent = false;
  int rap = 0; 
  int svuotabuffer = Tastiera.available();
  for(int i = 0; i<XRES;i++)
  {
    entry[i] = ' ';
  }
  while(ent == false)
  {
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Insert name:");
     for (int i = 0; i<XRES-1;i++)
     {
      lcd.setCursor(i,YCUR);
      lcd.print(entry[i]);
      
     }
     lcd.blink();
     lcd.setCursor(XCUR,YCUR);
    
    while(Tastiera.available() == 0)
    {
      Webserver_loop();
       if(FLAG_ESC == 1)
       {    
          FLAG_ESC = 0;
          LEVEL = 0;
          ent = true;
          XCUR = 0;
          YCUR = 0;
          return rap;  
        }
    }

      if (Tastiera.available() > 0)
      {
        ANSWER = keyboard_loop();
        if (ANSWER == "[Up]") //arrow up
        { FLAG_ESC = 0; }
        else if (ANSWER == "[Down]") //arrow down
        { FLAG_ESC = 0; }
        else if (ANSWER == "[Left]") 
        { 
          if(XCUR>0) {XCUR--;}
          FLAG_ESC = 0; 
                }
        else if (ANSWER == "[Right]") 
        { 
          if(XCUR<XRES-1) {XCUR++;}
          FLAG_ESC = 0; 
                }
        else if (ANSWER == "[Esc]")
        { FLAG_ESC = 1;}
        else if (ANSWER == "[Enter]")
        { FLAG_ESC = 0;
          ent = true;
          XCUR = 0;
          YCUR = 0;
          LEVEL = 500;
          return rap;     
        }
        else if (ANSWER == "[Del]")
        { 
          FLAG_ESC = 0;
          for(int i = XCUR; i<XRES-1;i++)
          {
            entry[i] = entry[i+1];
          }
          entry[XRES-1] = ' ';
          if (rap>0) {rap--;}
         }  
        else if (ANSWER == "Backspace")
        { 
          if(XCUR>0)
          {
          for(int i = XCUR-1; i<XRES-1;i++)
          {
            entry[i] = entry[i+1];
            if((int)(entry[i]) == 0)
            {
             
            }
          }
          entry[XRES-1] = ' ';
          if (rap>0) {rap--;}
          if(XCUR>0) {XCUR--;}
          }
          }  
        
        else if ((int)(ANSWER[0]) != 10)
        {
          FLAG_ESC = 0;
          entry[XCUR] = ANSWER[0];
          if(XCUR<XRES-1) {XCUR++;}
          if(rap<XRES-1) {rap++;}
                }

         
  }
 
  

  }


  
}








