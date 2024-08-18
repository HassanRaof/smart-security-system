/*
 * smart security project.c
 *
 * Created: 11/12/2023 10:28:14 ã
 * Author: Hassan Raof
           Mohanad Hesham
           Mohamed Younes
           Ahmed Mostafa
           Mohamed Alaa
 */





#include <mega16.h>
#include <delay.h>
#include <alcd.h>

//main functions declaration
void EEPROM_Write (int  Address , int Data) ;
int EEPROM_Read (int Address);
char enter_id ();
void enter_PC (int id);
char keypad();
void names (char id);
void enter_PC2(int id);
void enter_PC3 (int id);
void Buzzer ();
void Motor ();

//ID variables
const char Prof_id = 111;
const char Ahmed_id = 126;
const char Amr_id = 128;
const char Adel_id = 130;
const char Omar_id = 132;
//...........................






void main(void)
{

#asm ("sei")
    MCUCR |= 0b00001111;    //raising Edge case
    GICR  |= 0b11000000;    //Specific interrupt enable

    lcd_init(16); 
    lcd_printfxy(5,0,"Welcome");
    lcd_printfxy(2,6,"To LAB.");
    delay_ms(2000);
    lcd_clear();
    


    //EEPROM Data set
    EEPROM_Write (Prof_id , 203) ;      // prof ID and PC
    EEPROM_Write (Ahmed_id , 129) ;     // Ahmed ID and PC
    EEPROM_Write (Amr_id , 325) ;       // Ola ID and PC
    EEPROM_Write (Adel_id , 426) ;      // Omar ID and PC
    EEPROM_Write (Omar_id , 79) ;       // Ali ID and PC

    DDRA  = 0b00000111;                //KeyPad
    PORTA = 0b11111000;                //Pullup resistance
    DDRD.2 = 0;                        //Interrupt 0
    DDRD.3 = 0;                        // interrupt 1
    PORTD.2 = 1;
    PORTD.3 = 1;
    DDRD.1 = 1;
    DDRD.0 = 1;                       //door motor
    DDRD.5 = 1;                       //buzzer
                        

    


    while (1)
        {
        int x;
        lcd_printfxy(0,0,"press * to enter ");
        x = keypad();
        if (x == '*')
          enter_PC(enter_id()); 
             lcd_printf("%c", x);


        }
}

void EEPROM_Write (int Address , int Data)
{
 
        while (EECR.1 == 1);    // wait until ready
        EEAR = Address;
        EEDR = Data;
          EECR.2= 1;            // Enable Master Enable Write
        EECR.1= 1 ;          // Enable Enable write
        EECR.0= 0 ;          // disable Enable Read
      while (EECR.1 == 1);    // wait until ready
        EEAR = Address + 1;
        EEDR = Data >> 8;
          EECR.2= 1;            // Enable Master Enable Write
        EECR.1= 1 ;          // Enable Enable write
        EECR.0= 0 ;          // disable Enable Read

}
int EEPROM_Read(int Address)
{
 int data = 0;
        while (EECR.1 == 1);        // wait until ready
        EEAR = Address + 1 ;
        EECR.0 = 1 ;               // Enable Read
        EECR.1 = 0 ;               // Disable Enable write
data = EEDR;
while (EECR.1 == 1);        // wait until ready
        EEAR = Address;
        EECR.0 = 1 ;               // Enable Read
        EECR.1 = 0 ;               // Disable Enable write
data = (data << 8) | EEDR ;
        return data ;
}
char keypad()
{
    while(1)
        {
        PORTA.0 = 0;    //Col 1 is activated by 0
        PORTA.1 = 1;    //Col 2 is inactive by 1
        PORTA.2 = 1;    //Col 3 is inactive by 1
        switch (PINA)
            {
            case 0b11110110 :
                while ( PINA.3 == 0 ); 
                return 1;
                break;

            case 0b11101110 :
                while ( PINA.4 == 0 );
                return 4;
                break;

            case 0b11011110 :
                while ( PINA.5 == 0 );
                return 7;
                break;

            case 0b10111110 :
                while ( PINA.6 == 0 );
                return '*';
                break;


            }
        PORTA.0 = 1;    //Col 1 is inactive by 1
        PORTA.1 = 0;    //Col 2 is active by 0
        PORTA.2 = 1;    //Col 3 is inactive by 1
        switch (PINA)
            {
            case 0b11110101 :
                while ( PINA.3 == 0 );
                return 2;
                break;

            case 0b11101101 :
                while ( PINA.4 == 0 );
                return 5;
                break;

            case 0b11011101 :
                while ( PINA.5 == 0 );
                return 8;
                break;

            case 0b10111101 :
                while ( PINA.6 == 0 );
                return 0;
                break;


            }
        PORTA.0 = 1;    //Col 1 is inactive by 1
        PORTA.1 = 1;    //Col 2 is inactive by 1
        PORTA.2 = 0;    //Col 3 is active by 0
        switch (PINA)
            {
            case 0b11110011 :
                while ( PINA.3 == 0 );
                return 3;
                break;

            case 0b11101011 :
                while ( PINA.4 == 0 );
                return 6;
                break;

            case 0b11011011 :
                while ( PINA.5 == 0 );
                return 9;
                break;

            case 0b10111011 :
                while ( PINA.6 == 0 );
                return '#';
                break;
          

            } 
        }
}

char enter_id()
{

    int y, z, id;
    int x;

    lcd_clear();
    lcd_gotoxy(4, 0);
    lcd_puts("Enter ID");

    x = 100 * keypad();
    lcd_gotoxy(4, 1);
    lcd_printf("%u", x / 100);
    y = 10 * keypad();
    lcd_gotoxy(5, 1);
    lcd_printf("%u", y / 10);
    z = keypad() ;
    lcd_gotoxy(6, 1);
    lcd_printf("%u", z);
    delay_ms(50);
    id = x + y + z ;

    switch (id)
        {
        case Prof_id :
            return Prof_id;
            break;


        case Ahmed_id :
            return Ahmed_id;
            break;

        case Amr_id :
            return Amr_id;
            break;

        case Omar_id :
            return Omar_id;
            break;

        case Adel_id :
            return Adel_id;
            break;

        default:
            return 0 ;
            break;

        }
}
void enter_PC (int id)
{

    if (id == 0)
        {
        lcd_clear();
        lcd_gotoxy(0, 0);
        lcd_puts("Wrong ID");
        Buzzer();
        Buzzer();
        }
    else
        {
        int y, z, pc;
        int x;
        lcd_clear();
        lcd_gotoxy(4, 0);
        lcd_puts("Enter PC");
        x = 100 * keypad();
        lcd_gotoxy(4, 1);
        lcd_printf("%u", x / 100);
        y = 10 * keypad();
        lcd_gotoxy(5, 1);
        lcd_printf("%u", y / 10);
        z = keypad() ;
        lcd_gotoxy(6, 1);
        lcd_printf("%u", z);
        delay_ms(50);
        pc = x + y + z ;
        lcd_clear();
        if ( pc ==  EEPROM_Read(id) )
            {
            names (id);
            Motor();
            }
        else
            {
            lcd_gotoxy(0, 0);
            lcd_puts("Sorry, Wrong PC"); 
            Buzzer();
            }
        }



}
void enter_PC2 (int id)
{

    if (id == 0)
        {
        lcd_clear();
        lcd_gotoxy(0, 0);
        lcd_puts("Wrong ID");
        Buzzer();
        Buzzer();
        }
    else
        {
        int y, z, pc, y1, z1, pc1;
        int x, x1;
        lcd_clear();
        lcd_gotoxy(4, 0);
        lcd_puts("Enter Old PC");
        x = 100 * keypad();
        lcd_gotoxy(4, 1);
        lcd_printf("%u", x / 100);
        y = 10 * keypad();
        lcd_gotoxy(5, 1);
        lcd_printf("%u", y / 10);
        z = keypad() ;
        lcd_gotoxy(6, 1);
        lcd_printf("%u", z);
        delay_ms(50);
        pc = x + y + z ;
        lcd_clear();
        if ( pc ==  EEPROM_Read(id) )
            {
            lcd_gotoxy(2, 0);
            lcd_puts("Enter new PC");
            x1 = 100 * keypad();
            lcd_gotoxy(4, 1);
            lcd_printf("%u", x1 / 100);
            y1 = 10 * keypad();
            lcd_gotoxy(5, 1);
            lcd_printf("%u", y1 / 10);
            z1 = keypad() ;
            lcd_gotoxy(6, 1);
            lcd_printf("%u", z1);
            delay_ms(50);
            pc1 = x1 + y1 + z1 ;
            EEPROM_Write(id, pc1);
            lcd_clear();
            lcd_gotoxy(2, 0);
            lcd_puts("PC is stored");

            }
        else
            {
            lcd_gotoxy(1, 0);
            lcd_puts("Contact Admin!"); 
            Buzzer();
        Buzzer();
            }
        }



}
   
void enter_PC3 (int id)
{

    if (id == 0)
        {
        lcd_clear();
        lcd_gotoxy(0, 0);
        lcd_puts("Wrong ID");
        Buzzer();
        Buzzer();
        }
    else
        {
        int y, z, pc, y1, z1, pc1, y2, z2, pc2;
        int x, x1, x2;
        lcd_clear();
        lcd_gotoxy(2, 0);
        lcd_puts("Enter old PC");
        x = 100 * keypad();
        lcd_gotoxy(4, 1);
        lcd_printf("%u", x / 100);
        y = 10 * keypad();
        lcd_gotoxy(5, 1);
        lcd_printf("%u", y / 10);
        z = keypad() ;
        lcd_gotoxy(6, 1);
        lcd_printf("%u", z);
        delay_ms(50);
        pc = x + y + z ;
        lcd_clear();
        if ( pc ==  EEPROM_Read(id) )
            {
            lcd_gotoxy(2, 0);
            lcd_puts("Enter new PC");
            x1 = 100 * keypad();
            lcd_gotoxy(4, 1);
            lcd_printf("%u", x1 / 100);
            y1 = 10 * keypad();
            lcd_gotoxy(5, 1);
            lcd_printf("%u", y1 / 10);
            z1 = keypad() ;
            lcd_gotoxy(6, 1);
            lcd_printf("%u", z1);
            delay_ms(50);
            pc1 = x1 + y1 + z1 ;
            lcd_clear();
            lcd_gotoxy(0, 0);
            lcd_puts("Re-enter new PC");
            x2 = 100 * keypad();
            lcd_gotoxy(4, 1);
            lcd_printf("%u", x2 / 100);
            y2 = 10 * keypad();
            lcd_gotoxy(5, 1);
            lcd_printf("%u", y2 / 10);
            z2 = keypad() ;
            lcd_gotoxy(6, 1);
            lcd_printf("%u", z2);
            delay_ms(50);
            pc2 = x2 + y2 + z2 ;
            if (pc2 == pc1)
                {
                EEPROM_Write(id, pc1);
                lcd_clear();
                lcd_gotoxy(1, 0);
                lcd_puts("New PC stored");
                }
            else
                {
                lcd_clear();
                lcd_gotoxy(1, 0);
                lcd_puts("Contact admin!");
                Buzzer();
                Buzzer();
                }
            }
        else
            {
            lcd_gotoxy(1, 0);
            lcd_puts("Contact Admin!");
            Buzzer();
            Buzzer();
            }
        }



}
void names (char id)
{
    switch (id)
        {

        case Prof_id :
            lcd_clear();
            lcd_gotoxy(0, 0);
            lcd_puts("Welcome, Prof"); 
            delay_ms(2000);
             lcd_clear();
            break;

        case Ahmed_id :
            lcd_clear();
            lcd_gotoxy(0, 0);
            lcd_puts("Welcome, Ahmed");
             delay_ms(2000);
             lcd_clear();
            break;

        case Amr_id :
            lcd_clear();
            lcd_gotoxy(0, 0);
            lcd_puts("Welcome, Amr"); 
             delay_ms(2000);
             lcd_clear();
            break;

        case Omar_id :
            lcd_clear();
            lcd_gotoxy(0, 0);
            lcd_puts("Welcome, Omar");
             delay_ms(2000);
             lcd_clear();
            break;

        case Adel_id :
            lcd_clear();
            lcd_gotoxy(0, 0);
            lcd_puts("Welcome, Adel") ;
             delay_ms(2000);
             lcd_clear();
            break;

        }
}
void Buzzer ()
    {
        PORTD.5 = 1;
        delay_ms(500);
        PORTD.5 = 0;
        delay_ms(500);
        }      
        
 void Motor()
    {
        PORTD.1 = 1;
        delay_ms(1000);
         PORTD.1 = 0;
        delay_ms(1000);  
         PORTD.0 = 1;
        delay_ms(1000);
         PORTD.0 = 0;
         
        }  

        

interrupt [2] void Admin (void)
{
    int y, z, pc;
    int x;
    lcd_clear();
    lcd_gotoxy(1, 0);
    lcd_puts("Enter Prof  PC");
    x = 100 * keypad();
    lcd_gotoxy(4, 1);
    lcd_printf("%u", x / 100);
    y = 10 * keypad();
    lcd_gotoxy(5, 1);
    lcd_printf("%u", y / 10);
    z = keypad() ;
    lcd_gotoxy(6, 1);
    lcd_printf("%u", z);
    delay_ms(50);
    pc = x + y + z ;
    lcd_clear();
    if ( pc ==  EEPROM_Read(Prof_id) )
        enter_PC2(enter_id());


    else
        {
        lcd_gotoxy(0, 0);
        lcd_puts("Sorry, Wrong PC");
        Buzzer();
        Buzzer();
        }
}
interrupt [3] void student (void)
{
    enter_PC3(enter_id());
}


