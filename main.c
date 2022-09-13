#include<Wire.h>
#include<LiquidCrystal.h>
#include"DHT.h"
#include "RTClib.h"
#define y 4
#define x 2
#define pres 3
#define D 49  // relate to the temperature and humidity

#define touch 5 // the touch pin is 5
#define light_r 1 // the light sensitive resistor output the data

#define bkl 24 

//  rtc.adjust(DateTime(year, mon, day, hour, minute,sec)); // put this line in the setup when adjusting the time

int Start, Stop = 0;
int Cursor = 16; // for the rolling screen

const int back_light=8;
const int rs=23, en=27, d4=31, d5=35, d6=39, d7=43;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);  //initialisation of the lcd display
DHT dht(D,DHT11); // initialize the DHT11 sensor and relate it to the pin 28 digital input
RTC_DS3231 rtc;   //define the name of the time module

void accu_time_display(){
  DateTime now = rtc.now(); // obtain the current time
  lcd.clear();

    if(now.month()<10 && now.day()<10){
      lcd.setCursor(4,0);  lcd.print(now.year()); lcd.print("-"); lcd.print(now.month()); lcd.print("-"); lcd.print(now.day());
    }
    if(now.month()>=10 && now.day()<10){
      lcd.setCursor(3,0);  lcd.print(now.year()); lcd.print("--"); lcd.print(now.month()); lcd.print("-"); lcd.print(now.day());
    }
    if(now.month()<10 && now.day()>=10){
      lcd.setCursor(3,0);  lcd.print(now.year()); lcd.print("--"); lcd.print(now.month()); lcd.print("-"); lcd.print(now.day());
    }
    if(now.month()>=10 && now.day()>=10){
      lcd.setCursor(3,0);  lcd.print(now.year()); lcd.print("-"); lcd.print(now.month()); lcd.print("-"); lcd.print(now.day());
    }

    
    if(now.hour()<10 && now.minute()<10 && now.second()<10){
      lcd.setCursor(5,1);lcd.print(":"); lcd.print(now.hour()); lcd.print(":"); lcd.print(now.minute()); lcd.print(":"); lcd.print(now.second());
    }
    
    if(now.hour()>=10 && now.minute()<10 && now.second()<10){
      lcd.setCursor(5,1); lcd.print(now.hour()); lcd.print(":"); lcd.print(now.minute()); lcd.print(":"); lcd.print(now.second());
    }
    if(now.hour()<10 && now.minute()>=10 && now.second()<10){
      lcd.setCursor(5,1); lcd.print(now.hour()); lcd.print(":"); lcd.print(now.minute()); lcd.print(":"); lcd.print(now.second());
    }
    if(now.hour()<10 && now.minute()<10 && now.second()>=10){
      lcd.setCursor(5,1); lcd.print(now.hour()); lcd.print(":"); lcd.print(now.minute()); lcd.print(":"); lcd.print(now.second());
    }

    
    if(now.hour()<10 && now.minute()>=10 && now.second()>=10){
      lcd.setCursor(4,1); lcd.print(":");  lcd.print(now.hour()); lcd.print(":"); lcd.print(now.minute()); lcd.print(":"); lcd.print(now.second());
    }
    if(now.hour()>=10 && now.minute()<10 && now.second()>=10){
      lcd.setCursor(4,1); lcd.print(":");  lcd.print(now.hour()); lcd.print(":"); lcd.print(now.minute()); lcd.print(":"); lcd.print(now.second());
    }
    if(now.hour()>=10 && now.minute()>=10 && now.second()<10){
      lcd.setCursor(4,1); lcd.print(":");  lcd.print(now.hour()); lcd.print(":"); lcd.print(now.minute()); lcd.print(":"); lcd.print(now.second());
    }

    if(now.hour()>=10 && now.minute()>=10 && now.second()>=10){
      lcd.setCursor(4,1); lcd.print(now.hour()); lcd.print(":"); lcd.print(now.minute()); lcd.print(":"); lcd.print(now.second());
    }
    
  delay(500); // get the time and print it once in the lcd
}

//  lcd.setCursor(5,1); lcd.print("Set Hour"); lcd.setCursor(0,0); lcd.print((hm-hm%100)/100); lcd.print("-h-"); lcd.print(hm%100);; lcd.print("-m");




int set_timer(){
  int hm=0;
  int accumulate_counter;
  int exit_counter=0;  
//  lcd.clear();lcd.setCursor(0,0); lcd.print("Set Timer (^-^)");
 lcd.clear();lcd.setCursor(4,1); lcd.print("Set-Hour");lcd.setCursor(4,0); lcd.print((hm-hm%100)/100); lcd.print("-h-"); lcd.print(hm%100);; lcd.print("-m");
  do{
    if(analogRead(x)>=900){hm=0;  goto  End;}
    if(analogRead(y)<=200){
      do{
         if(analogRead(y)>400 && analogRead(y)<700){
            
            if(accumulate_counter>=30){accumulate_counter=0;break;}
            accumulate_counter=0;
            if(accumulate_counter<30){hm+=100; accumulate_counter=0; lcd.clear();lcd.setCursor(4,1); lcd.print("Set-Hour");lcd.setCursor(4,0); lcd.print((hm-hm%100)/100); lcd.print("-h-"); lcd.print(hm%100);; lcd.print("-m"); break;}
         }            
         if(analogRead(y)<=200){
            accumulate_counter+=1;
            delay(25);
            if(accumulate_counter>=30 && accumulate_counter%30==0){hm+=500; lcd.clear();lcd.setCursor(4,1); lcd.print("Set-Hour");lcd.setCursor(4,0); lcd.print((hm-hm%100)/100); lcd.print("-h-"); lcd.print(hm%100);; lcd.print("-m");}
         }
      }while(1);
    }    // this block is used to perefrom the add on function  small push and add by one if  long push, consecutively add on 2 ever 750ms
 
/////////////////////////////////////////////////////////////////////////////////////////////////    
    
    if(analogRead(y)>=700){
      do{
         if(analogRead(y)>400 && analogRead(y)<700){
            
            if(accumulate_counter>=30){accumulate_counter=0;break;}
            accumulate_counter=0;
            if(accumulate_counter<30){
              if(hm>=100){hm-=100; accumulate_counter=0; lcd.clear();lcd.setCursor(4,1); lcd.print("Set-Hour");lcd.setCursor(4,0); lcd.print((hm-hm%100)/100); lcd.print("-h-"); lcd.print(hm%100);; lcd.print("-m");  break;}
              if(hm<100){break;}  // save the last two digits
            }
         }      
         if(analogRead(y)>=700){
            accumulate_counter+=1;
            delay(25);
            if(accumulate_counter>=30 && accumulate_counter%30==0){
              if(hm>=500){hm-=500; lcd.clear(); lcd.setCursor(4,1); lcd.print("Set-Hour");lcd.setCursor(4,0); lcd.print((hm-hm%100)/100); lcd.print("-h-"); lcd.print(hm%100);; lcd.print("-m");};
              if(hm<500 && hm>=100){hm=hm%100; lcd.clear();lcd.setCursor(4,1); lcd.print("Set-Hour");lcd.setCursor(4,0); lcd.print((hm-hm%100)/100); lcd.print("-h-"); lcd.print(hm%100);; lcd.print("-m");};
              if(hm<100){};
            }
         }
      }while(1);
    }
    
///////////////////////////////////////////////////////////////////////////////////// minute setting
       if(analogRead(touch)>900){
            do{
                exit_counter+=1;
                delay(10);
                if(exit_counter>=300){goto exterior;}                
                if(analogRead(touch)<200){ exit_counter=0;  lcd.clear();lcd.setCursor(3,1); lcd.print("Set-Minute"); lcd.setCursor(4,0); lcd.print((hm-hm%100)/100); lcd.print("-h-"); lcd.print(hm%100);; lcd.print("-m");//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    do{       
                              if(analogRead(x)>=900){hm=0;  goto  End;}
                              if(analogRead(y)<=200){
                                do{
                                   if(analogRead(y)>400 && analogRead(y)<700){
                                      
                                      if(accumulate_counter>=30){accumulate_counter=0;break;}
                                      accumulate_counter=0;
                                      if(accumulate_counter<30){accumulate_counter=0; if(hm%100<=58){hm+=1;} if(hm%100>=60){hm=59;} lcd.clear();lcd.setCursor(3,1); lcd.print("Set-Minute"); lcd.setCursor(4,0); lcd.print((hm-hm%100)/100); lcd.print("-h-"); lcd.print(hm%100);; lcd.print("-m");break;}
                                   }            
                                   if(analogRead(y)<=200){
                                      accumulate_counter+=1;
                                      delay(25);
                                      if(accumulate_counter>=30 && accumulate_counter%30==0){if(hm%100<=54){hm+=5;} if(hm%100>=55){hm=hm-hm%100+59;}lcd.clear();lcd.setCursor(3,1); lcd.print("Set-Minute");lcd.setCursor(4,0); lcd.print((hm-hm%100)/100); lcd.print("-h-"); lcd.print(hm%100);; lcd.print("-m");}
                                   }
                                }while(1); // minute add on the same principla of the hour case
                              } // add on calculation
///////////////////////////////////////////////////////////////////////////////////////////////
                              if(analogRead(y)>=700){
                                do{
                                   if(analogRead(y)>400 && analogRead(y)<700){
                                      
                                      if(accumulate_counter>=30){accumulate_counter=0;break;}
                                      accumulate_counter=0;
                                      if(accumulate_counter<30){
                                        if(hm%100>=1){hm-=1; accumulate_counter=0; lcd.clear();lcd.setCursor(3,1); lcd.print("Set-Minute");lcd.setCursor(4,0); lcd.print((hm-hm%100)/100); lcd.print("-h-"); lcd.print(hm%100);; lcd.print("-m"); break;}
                                        if(hm%100<1){accumulate_counter=0; break;}  // save the last two digits
                                      }
                                   }            
                                   if(analogRead(y)>=700){
                                      accumulate_counter+=1;
                                      delay(25);
                                      if(accumulate_counter>=30 && accumulate_counter%30==0){
                                        if(hm%100>=5){hm-=5; lcd.clear(); lcd.setCursor(3,1); lcd.print("Set-Minute"); lcd.setCursor(4,0); lcd.print((hm-hm%100)/100); lcd.print("-h-"); lcd.print(hm%100);; lcd.print("-m");};
                                        if(hm%100<5 && hm%100>=1){hm=hm-(hm%100);lcd.clear(); lcd.setCursor(3,1); lcd.print("Set-Minute"); lcd.setCursor(3,0); lcd.print((hm-hm%100)/100); lcd.print("-h-"); lcd.print(hm%100);; lcd.print("-m");};
                                        if(hm<1){};
                                      }
                                   }
                                }while(1);
                              }    
                              Serial.print("changed minute final value==");
                              Serial.println(hm); 
                              if(analogRead(touch)>900){ 
                                  do{  exit_counter+=1;
                                       delay(10);
                                       if(exit_counter>=300){goto exterior;}   
                                if(analogRead(touch)<200){ lcd.clear();lcd.setCursor(4,1); lcd.print("Set-Hour");lcd.setCursor(4,0); lcd.print((hm-hm%100)/100); lcd.print("-h-"); lcd.print(hm%100);; lcd.print("-m"); exit_counter=0; // clear the value if release the button with out the time condition
                                    goto door;        // exit the minute stage                           
                                }
                            }while(1);          
                        }
                    }while(1);
                }
            }while(1);
        } door:; 
 //////////////////////////////////////////////////////////////////////////////////////////  
         Serial.print("changed hour final value==");
         Serial.println(hm); 
 }while(1); exterior:;
 lcd.clear(); lcd.setCursor(0,0); lcd.print("Release Nob(^_^)");
 delay(1500);
 End:;
 return hm;
}





void timer_down(int h, int m){ //m<=59 h is not limited
   
    int hint_location;
    int sec=60;
    int current_sec_1;
    int exit_counter=0;
    if(h==0 && m==0){ lcd.clear(); goto ending;}
  do{  DateTime now = rtc.now();
       current_sec_1=now.second();
       delay(985);     //990 is good
       if(DateTime now = rtc.now(); current_sec_1!=now.second()){
          sec+=1; // if the second changed the second added by 1
       }
       if(sec>=60 && m!=0){
          m=m-1;
          sec=0;
       }
       if(sec>=60 && m==0 && h!=0){
          m=59;
          sec=0;
          h=h-1;
       }
       if(sec>=60 && m==0 && h==0){ sec=0; break;} // the count down finished
      
       if(analogRead(touch)>900){ 
            do{
                if(analogRead(touch)<200){ 
                         lcd.clear();
                         lcd.setCursor(0,0);
                         lcd.print(h);
                         lcd.print("h-");
                         lcd.print(m);
                         lcd.print("min-");
                         lcd.print("Paused");
                    do{                       
                         if(analogRead(touch)>900){ 
                            do{
                                exit_counter+=1;
                                delay(10);
                                if(exit_counter>=150){goto Exit;} 
                                if(analogRead(touch)<200){exit_counter=0;
                                    goto door;                                   
                                }
                            }while(1);          
                        }
                    }while(1);
                }
            }while(1);
        } door:; 
        
       lcd.clear();
       lcd.setCursor(3,0);
       lcd.print(h);
       lcd.print("h-");
       lcd.print(m);
       lcd.print("min");
       hint_location=15*(sec+1)/60;
       lcd.setCursor(0,1);
       for(int i=0; i<=hint_location; i++){lcd.print("=");}
     
       Serial.print(current_sec_1);
       Serial.print("==");
       Serial.println(sec);

  }while(1);
        Exit:;
        sec=0;
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("Time is up!");
          do{
                  lcd.setCursor(3,0);
                  lcd.print("Time is up!");
                  delay(400);
                  lcd.clear();
                  delay(400);
          }while(analogRead(touch)<200);
   
        lcd.clear();
        ending:;
}



//lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.print(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);



long int set_height_mass(long int HM){
  long int hm; // inital height and mass are 169 and 50
  int accumulate_counter;
  int exit_counter=0;  
  double mass;
  if(HM==0){hm=170500;}
  if(HM!=0){hm=HM;} // if there is one value in the HM then use it otherwise abandon it 
//  lcd.clear();lcd.setCursor(2,0); lcd.print("Please Enter"); lcd.setCursor(0,1); lcd.print("Mass and Height");
 lcd.clear();lcd.setCursor(3,1); lcd.print("Set-Height");lcd.setCursor(1,0); lcd.print((hm-hm%1000)/1000); lcd.print("-cm-"); lcd.print((hm%1000-hm%10)/10);lcd.print("."); lcd.print(hm%10); lcd.print("-kg");
  do{
    if(analogRead(x)<=200){goto End;}
    if(analogRead(x)>=900){hm=0;  goto  End;}
    if(analogRead(y)<=200){
      do{
         if(analogRead(y)>400 && analogRead(y)<700){

            if(accumulate_counter>=30){accumulate_counter=0; break;}
            accumulate_counter=0;
            if(accumulate_counter<30){hm+=1000; accumulate_counter=0; lcd.clear();lcd.setCursor(3,1); lcd.print("Set-Height");lcd.setCursor(1,0); lcd.print((hm-hm%1000)/1000); lcd.print("-cm-"); lcd.print((hm%1000-hm%10)/10);lcd.print("."); lcd.print(hm%10); lcd.print("-kg"); break;}
         }            
         if(analogRead(y)<=200){
            accumulate_counter+=1;
            delay(25);
            if(accumulate_counter>=30 && accumulate_counter%30==0){hm+=5000; lcd.clear();lcd.setCursor(3,1); lcd.print("Set-Height");lcd.setCursor(1,0); lcd.print((hm-hm%1000)/1000); lcd.print("-cm-"); lcd.print((hm%1000-hm%10)/10);lcd.print("."); lcd.print(hm%10); lcd.print("-kg");}
         }
      }while(1);
    }    // this block is used to perefrom the add on function  small push and add by one if  long push, consecutively add on 2 ever 750ms
 
/////////////////////////////////////////////////////////////////////////////////////////////////    
    
    if(analogRead(y)>=700){
      do{
         if(analogRead(y)>400 && analogRead(y)<700){
            
            if(accumulate_counter>=30){accumulate_counter=0;break;}
            accumulate_counter=0;
            if(accumulate_counter<30){
              if(hm>=1000){hm-=1000; accumulate_counter=0; lcd.clear();lcd.setCursor(3,1); lcd.print("Set-Height");lcd.setCursor(1,0); lcd.print((hm-hm%1000)/1000); lcd.print("-cm-"); lcd.print((hm%1000-hm%10)/10);lcd.print("."); lcd.print(hm%10); lcd.print("-kg");  break;}
              if(hm<1000){break;}  // save the last two digits
            }
         }      
         if(analogRead(y)>=700){
            accumulate_counter+=1;
            delay(25);
            if(accumulate_counter>=30 && accumulate_counter%30==0){
              if(hm>=5000){hm-=5000;  lcd.clear();lcd.setCursor(3,1); lcd.print("Set-Height");lcd.setCursor(1,0); lcd.print((hm-hm%1000)/1000); lcd.print("-cm-"); lcd.print((hm%1000-hm%10)/10);lcd.print("."); lcd.print(hm%10); lcd.print("-kg");};
              if(hm<5000 && hm>=1000){hm=hm%1000; lcd.clear();lcd.setCursor(3,1); lcd.print("Set-Height");lcd.setCursor(1,0); lcd.print((hm-hm%1000)/1000); lcd.print("-cm-"); lcd.print((hm%1000-hm%10)/10);lcd.print("."); lcd.print(hm%10); lcd.print("-kg");};
              if(hm<1000){};
            }
         }
      }while(1);
    }
    
///////////////////////////////////////////////////////////////////////////////////// mass setting
       if(analogRead(touch)>900){lcd.clear();lcd.setCursor(4,1); lcd.print("Set-Mass");lcd.setCursor(1,0); lcd.print((hm-hm%1000)/1000); lcd.print("-cm-"); lcd.print((hm%1000-hm%10)/10);lcd.print("."); lcd.print(hm%10); lcd.print("-kg");
            do{             
                if(analogRead(touch)<200){ exit_counter=0;
                    do{       if(analogRead(x)<=200){goto End;} // if the nob turn to right the hm is assigned with proper number and value
                              if(analogRead(x)>=900){hm=0;  goto  End;} // if the nob turn to left, exit  the loop and assign the hmwith 0
                              if(analogRead(y)<=200){
                                do{
                                   if(analogRead(y)>400 && analogRead(y)<700){
                                      
                                      if(accumulate_counter>=30){accumulate_counter=0; break;}
                                      accumulate_counter=0;
                                      if(accumulate_counter<30){accumulate_counter=0; if(hm%1000<=998){hm+=1;} if(hm%1000==999){} lcd.clear();lcd.setCursor(4,1); lcd.print("Set-Mass");lcd.setCursor(1,0); lcd.print((hm-hm%1000)/1000); lcd.print("-cm-"); lcd.print((hm%1000-hm%10)/10);lcd.print("."); lcd.print(hm%10); lcd.print("-kg"); break;}
                                   }            
                                   if(analogRead(y)<=200){
                                      accumulate_counter+=1;
                                      delay(25);
                                      if(accumulate_counter>=30 && accumulate_counter%30==0){if(hm%1000<=989){hm+=10;}lcd.clear();lcd.setCursor(4,1); lcd.print("Set-Mass");lcd.setCursor(1,0); lcd.print((hm-hm%1000)/1000); lcd.print("-cm-"); lcd.print((hm%1000-hm%10)/10);lcd.print("."); lcd.print(hm%10); lcd.print("-kg");}
                                   } // add i kg ever turn long pudh and 0.1 kg ever small push
                                }while(1); // minute add on the same principla of the hour case
                              } // add on calculation
///////////////////////////////////////////////////////////////////////////////////////////////
                              if(analogRead(y)>=700){
                                do{
                                   if(analogRead(y)>400 && analogRead(y)<700){
                                      
                                      if(accumulate_counter>=30){accumulate_counter=0;break;}
                                      accumulate_counter=0;
                                      if(accumulate_counter<30){
                                        if(hm%1000>=1){hm-=1; accumulate_counter=0; lcd.clear();lcd.setCursor(4,1); lcd.print("Set-Mass");lcd.setCursor(1,0); lcd.print((hm-hm%1000)/1000); lcd.print("-cm-"); lcd.print((hm%1000-hm%10)/10);lcd.print("."); lcd.print(hm%10); lcd.print("-kg"); break;}
                                        if(hm%1000<1){accumulate_counter=0; break;}  
                                      }
                                   }            
                                   if(analogRead(y)>=700){
                                      accumulate_counter+=1;
                                      delay(25);
                                      if(accumulate_counter>=30 && accumulate_counter%30==0){
                                        if(hm%1000>=10){hm-=10;lcd.clear();lcd.setCursor(4,1); lcd.print("Set-Mass");lcd.setCursor(1,0); lcd.print((hm-hm%1000)/1000); lcd.print("-cm-"); lcd.print((hm%1000-hm%10)/10);lcd.print("."); lcd.print(hm%10); lcd.print("-kg");};
                                        if(hm%1000<10 && hm%1000>=1){hm=hm-(hm%1000);lcd.clear();lcd.setCursor(4,1); lcd.print("Set-Mass");lcd.setCursor(1,0); lcd.print((hm-hm%1000)/1000); lcd.print("-cm-"); lcd.print((hm%1000-hm%10)/10);lcd.print("."); lcd.print(hm%10); lcd.print("-kg");};
                                        if(hm<1){};
                                      }
                                   }
                                }while(1);
                              }    
                              Serial.print("changed mass final value==");
                              Serial.println(hm); 
                              if(analogRead(touch)>900){ 
                                  do{  
                                if(analogRead(touch)<200){lcd.clear();lcd.setCursor(3,1); lcd.print("Set-Height");lcd.setCursor(1,0); lcd.print((hm-hm%1000)/1000); lcd.print("-cm-"); lcd.print((hm%1000-hm%10)/10);lcd.print("."); lcd.print(hm%10); lcd.print("-kg"); exit_counter=0; // clear the value if release the button with out the time condition
                                    goto door;        // exit the minute stage                           
                                }
                            }while(1);          
                        }
                    }while(1);
                }
            }while(1);
        } door:; 
 //////////////////////////////////////////////////////////////////////////////////////////  
         Serial.print("changed height final value==");
         Serial.println(hm); 
 }while(1); 
 End:;
 return hm;
}




double BMI(double h, double m){
  double bmi;
  bmi=m/(h*h);
  return bmi;
}




void tem_humid(){
      
      float h=dht.readHumidity();
      float t=dht.readTemperature();
      lcd.setCursor(0,0);
      lcd.print("Humid:");
      lcd.setCursor(7,0);
      lcd.print(h);
      lcd.setCursor(12,0);
      lcd.print("%");
      lcd.setCursor(0,1);
      lcd.print("Temp:");
      lcd.setCursor(6,1);
      lcd.print(t);  
      lcd.setCursor(11,1);
      lcd.print(" Cels");  //测量温度与测量湿度
      delay(200);
      lcd.clear();
}




int interrupt_double_click(){
    int itmdtp=0; //intermidiated parameter
    int interrupt_index=0;
    int turn_off_counter=0;
    int differentiate_counter=0;
        if(analogRead(touch)>900){
          do{
            if(analogRead(touch)<200){
              do{itmdtp+=1; delay(10); if(itmdtp>=23){itmdtp=0; goto Stop;} Serial.println("time to show"); // the time elapse should be within 230ms beteween two clicks
                if(analogRead(touch)>900){lcd.clear();
                  do{turn_off_counter+=1; delay(10);if(turn_off_counter>=20){lcd.setCursor(0,0);lcd.print("Disabling...");} if(turn_off_counter>=300){lcd.clear();interrupt_index=2; goto Stop;} // to turn off the index is 2 if the hold time 300ms display the turning off prompt
                  //if this is held for 3000ms turn off is relised 
                    if(analogRead(touch)<200){
                       do{
                          differentiate_counter+=1;
                          delay(10);
                          if(turn_off_counter>=20){lcd.clear(); interrupt_index=0; goto Stop;} // turn off fails does nothing (tried but fail 
                          // if turn off succeed 
                          itmdtp=0; interrupt_index=1;
                          if(differentiate_counter>30){ // if within 1 second the touch isn't activated display the time
                            accu_time_display();
                            delay(1500);
                            lcd.clear();
                            goto Stop;
                          }
                          if(analogRead(touch)>900){
                            do{
                              if(analogRead(touch)<200){
                                do{
                                  accu_time_display();
                                  if(analogRead(touch)>900){
                                    do{
                                      lcd.clear();
                                      if(analogRead(touch)<200){ lcd.clear(); goto Stop;}
                                    }while(1);
                                  }
                                }while(1);
                              }                              
                            }while(1);
                          }
                      }while(1);
                    }
                  }while(1);
                }
              }while(1);
            }
          }while(1);Stop:;
        }
        return interrupt_index;
}



void scroll(String Text){
 do{
    lcd.setCursor(0,0);
    lcd.print("----FORTUNES----");
    lcd.setCursor(Cursor, 1); 
    lcd.print(Text.substring(Start,Stop));
    delay(500);
      if(Start == 0 && Cursor > 0){
        Cursor--;
        Stop++;
      }else if (Start == Stop){
        Start = Stop = 0;
        Cursor = 16;
      }else if (Stop == Text.length() && Cursor == 0) {
        Start++;
      }else{
        Start++;
        Stop++;
      }
 }while(analogRead(touch)<200);
 lcd.clear();
 Start=0; Stop=0; Cursor=16;
}


void endscroll(String Text){
 do{
    lcd.setCursor(0,0);
    lcd.print("<Happy Birthday>");
    lcd.setCursor(Cursor, 1); 
    lcd.print(Text.substring(Start,Stop));
    delay(400);
      if(Start == 0 && Cursor > 0){
        Cursor--;
        Stop++;
      }else if (Start == Stop){
        Start = Stop = 0;
        Cursor = 16;
      }else if (Stop == Text.length() && Cursor == 0) {
        Start++;
      }else{
        Start++;
        Stop++;
      }
 }while(analogRead(touch)<200);
 lcd.clear();
 Start=0; Stop=0; Cursor=16;
}

void supscroll(String Text){
   do{
    lcd.setCursor(1,0);
    lcd.print("Secret  Letter");
    lcd.setCursor(Cursor, 1); 
    lcd.print(Text.substring(Start,Stop));
    delay(400);
      if(Start == 0 && Cursor > 0){
        Cursor--;
        Stop++;
      }else if (Start == Stop){
        Start = Stop = 0;
        Cursor = 16;
      }else if (Stop == Text.length() && Cursor == 0) {
        Start++;
      }else{
        Start++;
        Stop++;
      }
   }while(analogRead(touch)<200);
   lcd.clear();
   Start=0; Stop=0; Cursor=16;
}




void fortune(){
  int ran;
  int port;
  randomSeed(analogRead(A0));
  port=random(8,16); // select a random analog pin to read in the data 
  randomSeed(analogRead(port));
  ran=random(1,126); // this is the fause random  number damn it 
  switch(ran){
    case 1:{scroll("the grass is greenest where you water it "); break;}
    case 2:{scroll("bitter pills may have blessed effects "); break;}
    case 3:{scroll("find joy in little things "); break;}

    case 4:{scroll("make everyday counts "); break;}
    case 5:{scroll("what the fool does in the end the wise man does at the beginning "); break;}
    case 6:{scroll("celebrate the small wins  "); break;}
    case 7:{scroll("be bold, be brave "); break;}
    case 8:{scroll("do everything with purpose "); break;}
    case 9:{scroll("be a blessing to those you encounter "); break;}
    case 10:{scroll("take it one step at a time "); break;}
    case 11:{scroll("don't lose youself in chaos "); break;}

    case 12:{scroll("be a ray of sunshine in darkness "); break;}
    case 13:{scroll("think outside the box "); break;}
    case 14:{scroll("start each day by being thankful for another opportunity "); break;}
    case 15:{scroll("everything comes with a tradeoff "); break;}
    case 16:{scroll("passionately pursue your purpose "); break;}

    case 17:{scroll("an amateur practices until he gets it right, a professional practices until he can't get it wrong "); break;}
    case 18:{scroll("live like it's your last day "); break;}

    case 19:{scroll("what done is done "); break;}
    case 20:{scroll("after strom ends, the sun shines "); break;}

    case 21:{scroll("it's never too late to make a change "); break;}
    case 22:{scroll("life is a marathon, not a sprint "); break;}
    case 23:{scroll("life is a journey, enjoy the journey "); break;}
    case 24:{scroll("step out of your comfort zone "); break;}
    case 25:{scroll("expect the unexpected "); break;}
    case 26:{scroll("plan the work and work the plan "); break;}

    case 27:{scroll("be initiative and stay sharp "); break;}

    case 28:{scroll("never confuse a single defeat with a final defeat "); break;}


    case 29:{scroll("so what? now what? "); break;}
    case 30:{scroll("establish a habit of success "); break;}
    case 31:{scroll("think twice before taking action "); break;}



    case 32:{scroll("diamonds are produced by pressure "); break;}
    case 33:{scroll("act rather than reacting "); break;}

    case 34:{scroll("progress, not perfection "); break;}


    case 35:{scroll("love others for who they are, not for what they can do for you "); break;}
    case 36:{scroll("never lose the childlike wonder "); break;}

    case 37:{scroll("life is what you make it "); break;}
    case 38:{scroll("live with no regrets "); break;}
    case 39:{scroll("be an inspiration to others "); break;}

    case 40:{scroll("be a leader not a follower "); break;}
    case 41:{scroll("turn obstacles into opportunities "); break;}
    case 42:{scroll("you can't read the next chapter of your life if you keep re-reading the previous chapter "); break;}
    case 43:{scroll("live life to fullest  "); break;}


    case 44:{scroll("remove the word impossible from your vocabulary "); break;}
    case 45:{scroll("breath, let go, smile, repeat! "); break;}
    case 46:{scroll("life is full with endless possibilities "); break;}
    case 47:{scroll("live the life you want, not the life others want "); break;}
    case 48:{scroll("he that live on hope dances without music "); break;}
    case 49:{scroll("never let the things you want make you forget the things you have "); break;}


    case 50:{scroll("be teachable "); break;}
    case 51:{scroll("start each day by believing in yourself "); break;}
    case 52:{scroll("life is too short to waste on what-ifs "); break;}

    case 53:{scroll("let kindness become as instinctive as breathing "); break;}
    case 54:{scroll("surround yourself with positivity! "); break;}


    case 55:{scroll("desperate time, desperate measures "); break;}

    case 56:{scroll("people will make time for who they want to make time for "); break;}
    case 57:{scroll("care and diligence brings luck "); break;}

    case 58:{scroll("don't be bystander in your own story "); break;}

    case 59:{scroll("prepare yourself for the good things you want to happen "); break;}
    case 60:{scroll("let faith guide you "); break;}
    case 61:{scroll("slow and steady wins the race "); break;}
    case 62:{scroll("there is no failure, only feedback "); break;}

    case 63:{scroll("the saddest words are'it might have been' "); break;}
    case 64:{scroll("respect the rules "); break;}


    case 65:{scroll("find magic in the universe by finding magic in yourself "); break;}
    case 66:{scroll("explore the world with curiosity "); break;}
    case 67:{scroll("never settle for good enough "); break;}
    case 68:{scroll("coming event cast their shadow before "); break;}
    case 69:{scroll("every saint has a past and every sinner has a future "); break;}

    case 70:{scroll("prepare for the unexpected "); break;}


    case 71:{scroll("do what's right, even when no one is watching "); break;}
    case 72:{scroll("nothing is particularly hard when you divide them into small tasks "); break;}

    case 73:{scroll("luck is what happens when preparation meets opportunity "); break;}

    case 74:{scroll("if you can't explain it simply, you don't understand it well enough "); break;}
    case 75:{scroll("love the one who loves you "); break;}


    case 76:{scroll("tradition without reason is but ancient error "); break;}
    case 77:{scroll("measure twice and cut once "); break;}


    case 78:{scroll("don't live the same year 75 times and call it a life "); break;}

    


    
    case 79:{scroll("all progress occurs outside of the comfort zone "); break;}




    
    case 80:{scroll("A smooth sea never made a skilled sailor ");break;}
    case 81:{scroll("fight fire with fire ");break;}
    case 82:{scroll("time and tide wait for no man ");break;}
    case 83:{scroll("action speak louder than words ");break;}
    case 84:{scroll("where there is a will, there is a way ");break;}
    case 85:{scroll("experience is better than teacher ");break;}
    case 86:{scroll("an idle youth, a needy age ");break;}
    case 87:{scroll("fortune knocks once at least at every man's door ");break;}
    case 88:{scroll("the definition of insanity is doing the same thing over and over again a dn expect differernt results ");break;}
    case 90:{scroll("fortune favour the bold ");break;}
    case 91:{scroll("haste makes wastes");break;}
    case 92:{scroll("he that promises too much means nothing ");break;}
    case 93:{scroll("the best time to plant a tree was twenty years ago, the seond-best is right now ");break;}
    case 94:{scroll("yesterday will not be called again ");break;}
    case 95:{scroll("keep something for a rainy day ");break;}
    case 96:{scroll("man proposes, God disopses ");break;}
    case 97:{scroll("determined efforts are more reliable than miracles ");break;}
    case 98:{scroll("one who had seen the ocean thinks nothing of mere water ");break;}
    case 99:{scroll("Rome is not built in one day ");break;}
    case 100:{scroll("one today is worth two tomorrows ");break;}
    case 101:{scroll("we are all in gutter, but some of us are looking at the stars ");break;}
    case 102:{scroll("A friend is best found in adversity ");break;}
    case 103:{scroll("what is done cannot be undone ");break;}
    case 104:{scroll("success belongs to the perseverings ");break;}
    case 105:{scroll("A strong man will struggle with the storm of fate ");break;}
    case 106:{scroll("nothing venture. nothing have ");break;}
    case 107:{scroll("the master has failed more times than beginners has even tried ");break;}
    case 108:{scroll("the secret to success is constancy to purpose ");break;}
    case 109:{scroll("better master one than engage ten ");break;}
    case 110:{scroll("there is no shortcuts to any place worth going ");break;}
    case 111:{scroll("you are unique and nothing can replace ");break;}
    case 112:{scroll("the first wealth is health ");break;}
    case 113:{scroll("sweat is the lubricant of success ");break;}
    case 114:{scroll("each man is the architect of his own fate ");break;}
    case 115:{scroll("try not, do or do not ");break;}
    case 116:{scroll("the further backwards you can look, the further forwards you will see ");break;}
    case 117:{scroll("with foxes, we must play the fox ");break;}
    case 118:{scroll("every man is poet when he is in love ");break;}
    case 119:{scroll("do not change the horse in mid-stream ");break;}
    case 120:{scroll("bad times make a good man ");break;}
    case 121:{scroll("there is no royal path to learning ");break;}
    case 122:{scroll("doubt is the key to knowledge ");break;}
    case 123:{scroll("the greatest test of courage is to bear defeat without losing heart ");break;}
    case 124:{scroll("sharp tools make good works ");break;}
    case 125:{scroll("a bosom friend afar brings a distant land near ");break;}
    case 126:{scroll("all time is no time when it is past ");break;}
  }
}




int* time_adjust(){
  int settle_counter=0;
  int accumulate_counter;
  int exit_counter=0;  
  static int a[6]; 
  a[0]=2022; 
  a[1]=5; 
  a[2]=9; 
  a[3]=18; 
  a[4]=0; 
  a[5]=0;
  // first adjust the year 
  lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(12,1); lcd.print("year");
  
  do{
        
        do{page1:;
          if(analogRead(x)>900){
            do{
              if(analogRead(x)>400 &&analogRead(x)<600){goto outmost;}
            }while(1);
          }
          
          if(analogRead(touch)>900){
            do{
              if(analogRead(touch)<200){lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(11,1); lcd.print("month");goto page2;} 
            }while(1);
          }

          while(analogRead(pres)<200){
            lcd.clear();
            lcd.print("Confirming");
            settle_counter+=1;
            delay(50);
            if(settle_counter>=60){goto EXIT;}
          } settle_counter=0;

          
          if(analogRead(y)<=200){
            do{
               if(analogRead(y)>400 && analogRead(y)<700){
      
                  if(accumulate_counter>=30){accumulate_counter=0; break;}
                  accumulate_counter=0;
                  if(accumulate_counter<30){a[0]+=1; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(12,1); lcd.print("year"); accumulate_counter=0; break;}
               }            
               if(analogRead(y)<=200){
                  accumulate_counter+=1;
                  delay(25);
                  if(accumulate_counter>=30 && accumulate_counter%30==0){a[0]+=5;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);lcd.setCursor(12,1); lcd.print("year");}
               }
            }while(1);
          }  
          
          if(analogRead(y)>=700){
            do{
               if(analogRead(y)>400 && analogRead(y)<700){                  
                  if(accumulate_counter>=30){accumulate_counter=0;break;}
                  accumulate_counter=0;
                  if(accumulate_counter<30){
                    if(a[0]>=1){a[0]-=1; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(12,1); lcd.print("year"); accumulate_counter=0; break;}
                  }
               }      
               if(analogRead(y)>=700){
                  accumulate_counter+=1;
                  delay(25);
                  if(accumulate_counter>=30 && accumulate_counter%30==0){
                    if(a[0]>=5){a[0]-=5;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(12,1); lcd.print("year");};
                    if(a[0]<5 && a[0]>=1){a[0]=0;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(12,1); lcd.print("year");};
                  }
               }
            }while(1);
          }
        }while(1);

        
       


       
         do{ page2:;

          if(analogRead(x)>900){
            do{
              if(analogRead(x)>400 &&analogRead(x)<600){goto outmost;}
            }while(1);
          }
          
            if(analogRead(touch)>900){
              do{
                if(analogRead(touch)<200){lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(13,1); lcd.print("day"); goto page3;} 
              }while(1);
          }

          while(analogRead(pres)<200){
            lcd.clear();
            lcd.print("Confirming");
            settle_counter+=1;
            delay(50);
            if(settle_counter>=60){goto EXIT;}
          } settle_counter=0;
          
          if(analogRead(y)<=200){
            do{
               if(analogRead(y)>400 && analogRead(y)<700){      
                  if(accumulate_counter>=30){accumulate_counter=0; break;}
                  accumulate_counter=0;
                  if(accumulate_counter<30){
                    if(a[1]<=11){a[1]+=1;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(11,1); lcd.print("month");}
                    if(a[1]>11){a[1]=12;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(11,1); lcd.print("month");}
                    accumulate_counter=0; 
                    break;}
               }            
               if(analogRead(y)<=200){
                  accumulate_counter+=1;
                  delay(25);
                  if(accumulate_counter>=30 && accumulate_counter%30==0){
                    if(a[1]<=9){a[1]+=3;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(11,1); lcd.print("month");} 
                    if(a[1]>9){a[1]=12;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(11,1); lcd.print("month");}
                  }
               }
            }while(1);
          }  
          
          if(analogRead(y)>=700){
            do{
               if(analogRead(y)>400 && analogRead(y)<700){                  
                  if(accumulate_counter>=30){accumulate_counter=0;break;}
                  accumulate_counter=0;
                  if(accumulate_counter<30){
                    if(a[1]>=2){a[1]-=1;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);  lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(11,1); lcd.print("month");}
                    if(a[1]==1){a[1]=1;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);  lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(11,1); lcd.print("month");}
                    accumulate_counter=0; break;
                  }
                  
               }      
               if(analogRead(y)>=700){
                  accumulate_counter+=1;
                  delay(25);
                  if(accumulate_counter>=30 && accumulate_counter%30==0){
                    if(a[1]>=4){a[1]-=3;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(11,1); lcd.print("month");};
                    if(a[1]<5 && a[1]>=1){a[1]=1;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);  lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(11,1); lcd.print("month");};
                  }
               }
            }while(1);
          }
        }while(1);

        


        
          do{page3:;

          if(analogRead(x)>900){
            do{
              if(analogRead(x)>400 &&analogRead(x)<600){goto outmost;}
            }while(1);
          }

          
            if(analogRead(touch)>900){
              do{
                if(analogRead(touch)<200){lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(12,1); lcd.print("hour"); goto page4;} 
              }while(1);
          }

          while(analogRead(pres)<200){
            lcd.clear();
            lcd.print("Confirming");
            settle_counter+=1;
            delay(50);
            if(settle_counter>=60){goto EXIT;}
          } settle_counter=0;

          
          if(analogRead(y)<=200){
            do{
               if(analogRead(y)>400 && analogRead(y)<700){      
                  if(accumulate_counter>=30){accumulate_counter=0; break;}
                  accumulate_counter=0;
                  if(accumulate_counter<30){
                    if(a[1]==1 || a[1]==3  || a[1]==5 || a[1]==7 || a[1]==8 || a[1]==10 || a[1]==12){
                      if(a[2]<=30){a[2]+=1;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(13,1); lcd.print("day");}
                      if(a[2]>30){a[2]=31;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);}
                    }
                    if(a[1]==2 && a[0]%4==0){
                      if(a[2]<=28){a[2]+=1;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(13,1); lcd.print("day");}
                      if(a[2]>28){a[2]=29;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(13,1); lcd.print("day");}
                    }
                    if(a[1]==2 && a[0]%4!=0){
                      if(a[2]<=27){a[2]+=1;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(13,1); lcd.print("day");}
                      if(a[2]>27){a[2]=28;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(13,1); lcd.print("day");}
                    }
                    if(a[1]==4 || a[1]==6 || a[1]==9 || a[1]==11){
                      if(a[2]<=29){a[2]+=1;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(13,1); lcd.print("day");}
                      if(a[2]>29){a[2]=30;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(13,1); lcd.print("day");}
                    }
                    accumulate_counter=0; 
                    break;}
               }            
               if(analogRead(y)<=200){
                  accumulate_counter+=1;
                  delay(25);
                  if(accumulate_counter>=30 && accumulate_counter%30==0){
                      if(a[1]==1 || a[1]==3  || a[1]==5 || a[1]==7 || a[1]==8 || a[1]==10 || a[1]==12){
                          if(a[2]<=26){a[2]+=5;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(13,1); lcd.print("day");}
                          if(a[2]>26 &&a[2]<=31){a[2]=31;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(13,1); lcd.print("day");}
                        }
                        if(a[1]==2 && a[0]%4==0){
                          if(a[2]<=24){a[2]+=5;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(13,1); lcd.print("day");}
                          if(a[2]>24 && a[2]<=29){a[2]=29;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(13,1); lcd.print("day");} // the max is 29
                        }
                        if(a[1]==2 && a[0]%4!=0){
                          if(a[2]<=23){a[2]+=5;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(13,1); lcd.print("day");}
                          if(a[2]>23 && a[2]<=28){a[2]=28;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(13,1); lcd.print("day");}
                        }
                        if(a[1]==4 || a[1]==6 || a[1]==9 || a[1]==11){
                          if(a[2]<=25){a[2]+=5;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(13,1); lcd.print("day");}
                          if(a[2]>25 && a[2]<=30){a[2]=30;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(13,1); lcd.print("day");}
                        }
                  }
               }
            }while(1);
          }  
          
          if(analogRead(y)>=700){
            do{
               if(analogRead(y)>400 && analogRead(y)<700){                  
                  if(accumulate_counter>=30){accumulate_counter=0;break;}
                  accumulate_counter=0;
                  if(accumulate_counter<30){
                    if(a[2]>=2){a[2]-=1; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(13,1); lcd.print("day"); accumulate_counter=0; break;}
                  }
               }      
               if(analogRead(y)>=700){
                  accumulate_counter+=1;
                  delay(25);
                  if(accumulate_counter>=30 && accumulate_counter%30==0){
                    if(a[2]>=4){a[2]-=3;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(13,1); lcd.print("day"); };
                    if(a[2]<5 && a[2]>=1){a[2]=1;lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(13,1); lcd.print("day"); };
                  }
               }
            }while(1);
          }
        }while(1);


        



       
        do{page4:;

          if(analogRead(x)>900){
            do{
              if(analogRead(x)>400 &&analogRead(x)<600){goto outmost;}
            }while(1);
          }

          
          if(analogRead(touch)>900){
            do{
              if(analogRead(touch)<200){ lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(13,1); lcd.print("min"); goto page5;} 
            }while(1);
          }

          while(analogRead(pres)<200){
            lcd.clear();
            lcd.print("Confirming");
            settle_counter+=1;
            delay(50);
            if(settle_counter>=60){goto EXIT;}
          } settle_counter=0;

          
          if(analogRead(y)<=200){
            do{
               if(analogRead(y)>400 && analogRead(y)<700){
      
                  if(accumulate_counter>=30){accumulate_counter=0; break;}
                  accumulate_counter=0;
                  if(accumulate_counter<30){
                    if(a[3]<=22){a[3]+=1; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(12,1); lcd.print("hour");}
                    if(a[3]>22){a[3]=23; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);  lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(12,1); lcd.print("hour");}
                    accumulate_counter=0; break;}
               }            
               if(analogRead(y)<=200){
                  accumulate_counter+=1;
                  delay(25);
                  if(accumulate_counter>=30 && accumulate_counter%30==0){
                    if(a[3]<=18){a[3]+=5; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(12,1); lcd.print("hour");}
                    if(a[3]>18 && a[3]<=23){a[3]=23; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(12,1); lcd.print("hour");}
                  }
               }
            }while(1);
          }  
          
          if(analogRead(y)>=700){
            do{
               if(analogRead(y)>400 && analogRead(y)<700){                  
                  if(accumulate_counter>=30){accumulate_counter=0;break;}
                  accumulate_counter=0;
                  if(accumulate_counter<30){
                    if(a[3]>=1){a[3]-=1; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(12,1); lcd.print("hour");}
                    if(a[3]<1){a[3]=0; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(12,1); lcd.print("hour");}
                    accumulate_counter=0; break;
                  }                  
               }      
               if(analogRead(y)>=700){
                  accumulate_counter+=1;
                  delay(25);
                  if(accumulate_counter>=30 && accumulate_counter%30==0){
                    if(a[3]>=5){a[3]-=5; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);  lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(12,1); lcd.print("hour");};
                    if(a[3]<5 && a[3]>=0){a[3]=0; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(12,1); lcd.print("hour");};
                  }
               }
            }while(1);
          }
        }while(1);


       



        
        do{ page5:;

          if(analogRead(x)>900){
            do{
              if(analogRead(x)>400 &&analogRead(x)<600){goto outmost;}
            }while(1);
          }

          
          if(analogRead(touch)>900){
            do{
              if(analogRead(touch)<200){ lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(13,1); lcd.print("sec"); goto page6;} 
            }while(1);
          }

          
          while(analogRead(pres)<200){
            lcd.clear();
            lcd.print("Confirming");
            settle_counter+=1;
            delay(50);
            if(settle_counter>=60){goto EXIT;}
          } settle_counter=0;

          
          if(analogRead(y)<=200){
            do{
               if(analogRead(y)>400 && analogRead(y)<700){
      
                  if(accumulate_counter>=30){accumulate_counter=0; break;}
                  accumulate_counter=0;
                  if(accumulate_counter<30){
                    if(a[4]<=58){a[4]+=1; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]); lcd.setCursor(13,1); lcd.print("min");}
                    if(a[4]>58){a[4]=59; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);  lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(13,1); lcd.print("min");}
                    accumulate_counter=0; break;}
               }            
               if(analogRead(y)<=200){
                  accumulate_counter+=1;
                  delay(25);
                  if(accumulate_counter>=30 && accumulate_counter%30==0){
                    if(a[4]<=54){a[4]+=5; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);  lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);   lcd.setCursor(13,1); lcd.print("min");}
                    if(a[4]>54 && a[4]<=59){a[4]=59; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(13,1); lcd.print("min");}
                  }
               }
            }while(1);
          }  
          
          if(analogRead(y)>=700){
            do{
               if(analogRead(y)>400 && analogRead(y)<700){                  
                  if(accumulate_counter>=30){accumulate_counter=0;break;}
                  accumulate_counter=0;
                  if(accumulate_counter<30){
                    if(a[4]>=1){a[4]-=1; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(13,1); lcd.print("min");}
                    if(a[4]<1){a[4]=0; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(13,1); lcd.print("min");}
                    accumulate_counter=0; break;
                  }                  
               }      
               if(analogRead(y)>=700){
                  accumulate_counter+=1;
                  delay(25);
                  if(accumulate_counter>=30 && accumulate_counter%30==0){
                    if(a[4]>=5){a[4]-=5; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);   lcd.setCursor(13,1); lcd.print("min");};
                    if(a[4]<5 && a[4]>=0){a[4]=0; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);   lcd.setCursor(13,1); lcd.print("min");};
                  }
               }
            }while(1);
          }
        }while(1);


        



        
        do{page6:;

         if(analogRead(x)>900){
            do{
              if(analogRead(x)>400 &&analogRead(x)<600){goto outmost;}
            }while(1);
          }

          
          if(analogRead(touch)>900){
            do{
              if(analogRead(touch)<200){lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);   lcd.setCursor(12,1); lcd.print("year"); goto page1;} 
            }while(1);
          }

          while(analogRead(pres)<200){
            lcd.clear();
            lcd.print("Confirming");
            settle_counter+=1;
            delay(50);
            if(settle_counter>=60){goto EXIT;}
          } settle_counter=0;


          
          if(analogRead(y)<=200){
            do{
               if(analogRead(y)>400 && analogRead(y)<700){
      
                  if(accumulate_counter>=30){accumulate_counter=0; break;}
                  accumulate_counter=0;
                  if(accumulate_counter<30){
                    if(a[5]<=58){a[5]+=1; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);  lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(13,1); lcd.print("sec"); }
                    if(a[5]>58){a[5]=59; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(13,1); lcd.print("sec"); }
                    accumulate_counter=0; break;}
               }            
               if(analogRead(y)<=200){
                  accumulate_counter+=1;
                  delay(25);
                  if(accumulate_counter>=30 && accumulate_counter%30==0){
                    if(a[5]<=54){a[5]+=5; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(13,1); lcd.print("sec"); }
                    if(a[5]>54 && a[5]<=59){a[5]=59; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(13,1); lcd.print("sec"); }
                  }
               }
            }while(1);
          }  
          
          if(analogRead(y)>=700){
            do{
               if(analogRead(y)>400 && analogRead(y)<700){                  
                  if(accumulate_counter>=30){accumulate_counter=0;break;}
                  accumulate_counter=0;
                  if(accumulate_counter<30){
                    if(a[5]>=1){a[5]-=1; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(13,1); lcd.print("sec"); }
                    if(a[5]<1){a[5]=0; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(13,1); lcd.print("sec"); }
                    accumulate_counter=0; break;
                  }                  
               }      
               if(analogRead(y)>=700){
                  accumulate_counter+=1;
                  delay(25);
                  if(accumulate_counter>=30 && accumulate_counter%30==0){
                    if(a[5]>=5){a[5]-=5; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(13,1); lcd.print("sec"); };
                    if(a[5]<5 && a[5]>=0){a[5]=0; lcd.clear(); lcd.setCursor(0,0); lcd.print(a[0]); lcd.print("-"); lcd.print(a[1]); lcd.print("-"); lcd.print(a[2]);   lcd.setCursor(0,1); lcd.print(a[3]); lcd.print("-"); lcd.print(a[4]); lcd.print("-"); lcd.print(a[5]);  lcd.setCursor(13,1); lcd.print("sec"); };
                  }
               }
            }while(1);
          }
        }while(1);
     }while(1);
   EXIT:;
   
   if(a[0]==2014 && a[1]==9 && a[2]==1 && a[3]==19 && a[4]==0 && a[5]==0){ // 2014 9 1 19:00:00
    lcd.clear();
    
     supscroll(" the second easter egg");

   }
   else{rtc.adjust(DateTime(a[0], a[1], a[2], a[3], a[4],a[5]));};   
   lcd.clear(); lcd.setCursor(0,0); lcd.print("time adjusted!!!"); delay(1500);
   outmost:;
}







void acknowledge(){
 endscroll("This device is dedicatedly crafted to celebrated the 20th birthday of Miss.Li and hoping this gift brings you joy, convenience and excitement, stay happy stay high and everything will just be what you expect !!!   (Crafted by:Zhengxi Yan ^_^) smile~  ");
}




void title_scroll(String Text){
   do{
    lcd.setCursor(0,0);
    lcd.print("!Happy Birthday!");
    lcd.setCursor(Cursor, 1); 
    lcd.print(Text.substring(Start,Stop));
    delay(400);
      if(Start == 0 && Cursor > 0){
        Cursor--;
        Stop++;
      }else if (Start == Stop){
        Start = Stop = 0;
        Cursor = 16;
      }else if (Stop == Text.length() && Cursor == 0) {
        Start++;
      }else{
        Start++;
        Stop++;
      }
   }while(analogRead(touch)<200);
   lcd.clear();
   Start=0; Stop=0; Cursor=16;
}



void setup(){
  
  Serial.begin(9600);
  pinMode(y,INPUT);
  pinMode(pres,INPUT);
  pinMode(x,INPUT);
  pinMode(D,INPUT); //set the sensor pin as digital input to collect electric data
  pinMode(back_light,OUTPUT); // control the intensity of the back lght

  lcd.begin(16,2);
  dht.begin(); // activate the dht sensor
  lcd.clear();
  lcd.setCursor(2,0);
   Serial.println("enenable");
  lcd.print("Hello Miss.Li");
  delay(2000);
  lcd.clear();
  rtc.begin();

  DateTime now = rtc.now();
}



void loop() {

  double hor;
  double ver;
  double but;
  int page_turn;
  int decimal_hour_minute;
  int sleep_counter=0;
  int off_counter=0;
  int enable_counter=0;
  long int hei_mas_hyb=0;
  double height_cm;
  double height_m;
  double mass_nodecimal;
  double mass;
  double bmi=0;
  int interrupt_index;
  float distance;
  int adjust_counter=0;
  int bullet_counter=0;



//Serial.print("x=");
//Serial.print(analogRead(x));
//Serial.print(" y=");
//Serial.print(analogRead(y));
//Serial.print(" touch=");
//Serial.print(analogRead(touch));
//Serial.print(" pres=");
//Serial.println(analogRead(pres));
//
//lcd.setCursor(0,0);
//lcd.print(analogRead(x));
//lcd.setCursor(4,0);
//lcd.print(analogRead(y));
//lcd.setCursor(0,1);
//lcd.print(analogRead(touch));
//lcd.setCursor(4,1);
//lcd.println(analogRead(pres));
//delay(200);
//lcd.clear();
//lcd.setCursor(0,0);
//lcd.print("hello world");
  


  head:; lcd.clear();
    do{}while(analogRead(touch)>900); // only in the release state can enter the turn on state
      do{
//        analogWrite(back_light,0);
        
        DateTime now = rtc.now();
        if(now.month()==8 && now.day()==8){
          title_scroll("wish you a wonderful birthday!! Stay Happy evey second, evey minute and every day!! remember my blessing !! ");
          enable_counter=0;
        }
        if(now.hour()>=6 && now.hour()<=11){
          lcd.setCursor(2,0); lcd.print("Good Morning!");
          lcd.setCursor(0,1); lcd.print("Have a Nice Day!!");
        }
        if(now.hour()>=12 && now.hour()<=14){
          lcd.setCursor(3,0); lcd.print("Take a Nap");
          lcd.setCursor(5,1); lcd.print("(^-^)");
        }
        if(now.hour()>=15 && now.hour()<=18){
          lcd.setCursor(3,0); lcd.print("Study Hard");
          lcd.setCursor(3,1); lcd.print("Play--Hard");
        }
        if(now.hour()>=19 && now.hour()<=23){
          lcd.setCursor(0,0); lcd.print("How is Your Day?");
          lcd.setCursor(0,1); lcd.print("Reflect && Relax");
        }
        if(now.hour()>=0 && now.hour()<=5){
          lcd.setCursor(4,0); lcd.print("Wish You");
          lcd.setCursor(0,1); lcd.print("a Sound Sleep.....");
        }
    
        while(analogRead(touch)>900){ 
//          analogWrite(back_light,255);
          lcd.setCursor(0,0); lcd.print("Enabling...");
          enable_counter+=1;
          delay(50);
          lcd.clear();
          if(enable_counter>30){goto Begin;}
        }
   
        enable_counter=0;
      }while(1);

  Begin:; lcd.clear(); lcd.setCursor(1,0); lcd.print("Machine is ON"); delay(1500);lcd.clear();

 do{ // consecutive reepeate in this loop the actual void loop function  

  
//  analogWrite(back_light,255);
  do{
    interrupt_index=interrupt_double_click(); // if entered the interrputed clock the sleep counter must set to zero
    if(interrupt_index==1){sleep_counter=0; interrupt_index=0;}
    if(interrupt_index==2){ lcd.print("Machine is OFF"); delay(1500); lcd.clear(); goto head;}
/////////////////////////////////////////////////
    delay(1);
    sleep_counter+=1;
    if(sleep_counter>=2500){sleep_counter=0; do{accu_time_display(); if(analogRead(touch)>900){ lcd.clear(); break;}}while(analogRead(y)>500 && analogRead(y)<600);}
    lcd.setCursor(0,0);
    lcd.print("=>");
    lcd.setCursor(3,0);
    lcd.print("1.Tem & Humid");
    lcd.setCursor(3,1);
    lcd.print("2.Timer");
/////////////////////////////////////////////////
    while(analogRead(pres)<200){
     lcd.clear();lcd.setCursor(0,0); lcd.print("Disabling...");
      off_counter+=1;
      delay(50);
      if(off_counter>=60){lcd.clear(); lcd.setCursor(1,0); lcd.print("Machine is OFF"); delay(1500); lcd.clear(); goto head;}
    }if(off_counter!=0){ off_counter=0;  lcd.clear();}; // turn off the machine
////////////////////////////////////////////////    
    if(analogRead(x)<200){
      do{tem_humid();}while(analogRead(x)<579);
    }
  }while(analogRead(y)>500 && analogRead(y)<600); sleep_counter=0; // the first page if the rob gose up, go to the previous page other wise gose to the next page
  if(ver=analogRead(y)<500){goto page_4;}

  
 
  page_23:;
  do{lcd.clear();ver=analogRead(y);}while(ver>600 || ver<500); //only if the rob returned to the origin, leaves the page

  

  do{
    interrupt_index=interrupt_double_click(); // if entered the interrputed clock the sleep counter must set to zero
    if(interrupt_index==1){sleep_counter=0; interrupt_index=0;}
    if(interrupt_index==2){ lcd.print("Machine is OFF"); delay(1500); lcd.clear(); goto head;}
////////////////////////////////////////////////////
     delay(1);
     sleep_counter+=1;
     if(sleep_counter>=2500){sleep_counter=0; do{accu_time_display(); if(analogRead(touch)>900){ lcd.clear(); break;} }while(analogRead(y)>500 && analogRead(y)<600);}
     lcd.setCursor(0,0);
     lcd.print("=>");
     lcd.setCursor(3,0);
     lcd.print("2.Timer");
     lcd.setCursor(3,1);
     lcd.print("3.BMI calc");
//////////////////////////////////////////////////
//    while(analogRead(pres)==0){
//      lcd.clear();lcd.setCursor(0,0); lcd.print("Disabling...");
//      off_counter+=1;
//      delay(50);
//      if(off_counter>=60){lcd.clear(); lcd.setCursor(1,0); lcd.print("Machine is OFF"); delay(1500); lcd.clear(); goto head;}
//    }if(off_counter!=0){ off_counter=0;  lcd.clear();};
/////////////////////////////////////////////////////////      
     if(analogRead(x)<200){
        decimal_hour_minute = set_timer();
        timer_down((decimal_hour_minute-decimal_hour_minute%100)/100,decimal_hour_minute%100);
     }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    while(analogRead(pres)<200){
           lcd.clear();lcd.setCursor(0,0); lcd.print("Adjusting...");
           adjust_counter+=1;
           delay(50);
           if(adjust_counter>=60){lcd.clear(); lcd.setCursor(0,0); lcd.print("Release the rocker"); delay(1500); time_adjust();}
    }if(adjust_counter!=0){adjust_counter=0; lcd.clear();}

  }while(analogRead(y)>500 & analogRead(y)<600); sleep_counter=0;


  
  
  if(analogRead(y)<500){goto page_12;}
  page_34:;
  do{lcd.clear();}while(analogRead(y)>600 || analogRead(y)<500); //only if the rob returned to the origin, leaves the page 
  // if the nob isn't in the position, always clear the display.



  

  do{
    interrupt_index=interrupt_double_click(); // if entered the interrputed clock the sleep counter must set to zero
    if(interrupt_index==1){sleep_counter=0; interrupt_index=0;}
    if(interrupt_index==2){ lcd.print("Machine is OFF"); delay(1500); lcd.clear(); goto head;}
//////////////////////////////////////
    delay(1);
    sleep_counter+=1;
    if(sleep_counter>=2500){sleep_counter=0; do{accu_time_display(); if(analogRead(touch)>900){ lcd.clear(); break;} }while(analogRead(y)>500 && analogRead(y)<600);}
    lcd.setCursor(0,0);
    lcd.print("=>");
    lcd.setCursor(3,0);
    lcd.print("3.BMI calc");
    lcd.setCursor(3,1);
    lcd.print("4.Fortune");   
/////////////////////////////////////////////////
    while(analogRead(pres)<200){
      lcd.clear();lcd.setCursor(0,0); lcd.print("Disabling...");
      off_counter+=1;
      delay(50);
      if(off_counter>=60){lcd.clear(); lcd.setCursor(1,0); lcd.print("Machine is OFF"); delay(1500); lcd.clear(); goto head;}
    }if(off_counter!=0){ off_counter=0;  lcd.clear();}; 
////////////////////////////////////////////////    
  if(analogRead(x)<200){
    do{
      if(analogRead(x)<700 && analogRead(x)>400){
        re_set:;
        lcd.clear();
        hei_mas_hyb=set_height_mass(hei_mas_hyb);
        if(hei_mas_hyb!=0){
            height_cm=hei_mas_hyb/1000;
            height_m=height_cm/100;
            mass_nodecimal=(hei_mas_hyb%1000);
            mass=mass_nodecimal/10;
            bmi=BMI(height_m,mass);
            lcd.clear();
              if(bmi<=18.4){lcd.setCursor(0,1); lcd.print("<18.5 UnderWeight");}
              if(bmi>18.4 && bmi<=23.9){lcd.setCursor(0,1); lcd.print("18.5-23.9 Proper");}
              if(bmi>23.9){lcd.setCursor(0,1); lcd.print(">23.9 Overweight");}
            do{
              lcd.setCursor(3,0);lcd.print("BMI="); lcd.print(bmi);
              if(analogRead(x)>700){
                do{
                  if(analogRead(x)>500 && analogRead(x)<600){
                    goto re_set;
                  }
                }while(1);
               } // back to the previous page 
              if(analogRead(touch)>900){
                do{
                  if(analogRead(touch)<200){lcd.clear(); goto small_exit;}
                }while(1);
              }
            }while(1);
        }
        if(hei_mas_hyb==0){lcd.clear(); goto small_exit; };
      }
    }while(1);small_exit:; hei_mas_hyb=0; 
 }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}while(analogRead(y)>500 & analogRead(y)<600); sleep_counter=0;



  
  if(analogRead(y)<500){goto page_23;}  
  page_4:;
  do{lcd.clear();}while(analogRead(y)>600 || analogRead(y)<500); //only if the rob returned to the origin, leaves the page


  

  
  do{
    interrupt_index=interrupt_double_click(); // if entered the interrputed clock the sleep counter must set to zero
    if(interrupt_index==1){sleep_counter=0; interrupt_index=0;}
    if(interrupt_index==2){ lcd.print("Machine is OFF"); delay(1500); lcd.clear(); goto head;}
/////////////////////////////////////////////////////
    delay(1);
    sleep_counter+=1;
    if(sleep_counter>=2500){sleep_counter=0; do{accu_time_display(); if(analogRead(touch)>900){lcd.clear();break;} }while(analogRead(y)>500 && analogRead(y)<600);}
    ver=analogRead(y);
    lcd.setCursor(0,0);
    lcd.print("=>");
    lcd.setCursor(3,0);
    lcd.print("4.Fortune");  
/////////////////////////////////////////////////
    while(analogRead(pres)<200){
      lcd.clear();lcd.setCursor(0,0); lcd.print("Disabling...");
      off_counter+=1;
      delay(50);
      if(off_counter>=60){lcd.clear(); lcd.setCursor(1,0); lcd.print("Machine is OFF"); delay(1500); lcd.clear(); goto head;}
    }if(off_counter!=0){ off_counter=0;  lcd.clear();}; 
////////////////////////////////////////////////    
    if(analogRead(x)<200){
      lcd.clear();
    
      fortune();
    }
  }while(analogRead(y)>500 & analogRead(y)<600); sleep_counter=0;
  
  if(analogRead(y)<500){goto page_34;}
  page_12:;
  do{
    lcd.clear();
    bullet_counter+=1;
    delay(50);
    if(bullet_counter>=60){acknowledge(); lcd.clear();}
  }while(analogRead(y)>600 || analogRead(y)<500); //only if the rob returned to the origin, leaves the page
  bullet_counter=0;
 }while(1);
}
