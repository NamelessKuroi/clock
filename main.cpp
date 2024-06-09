#include <bits/stdc++.h>
#include <string.h>
#include <time.h>
#include <windows.h>

using namespace std;

//Function
template <class T >
const T bound( T minValue , T value , T maxValue )
{
    if(minValue <= maxValue)
    return max( minValue , min(value , maxValue) );
    return min( minValue , max(value , maxValue) );
}

//Data
class Codification
{
public:

    static const short MIN_COLOR = 0;
    static const short MAX_COLOR = 15;

    static const short MIN_DECIMAL = 0;
    static const short MAX_DECIMAL = 9;

    static const short MIN_HEXADECIMAL = 10;
    static const short MAX_HEXADECIMAL = 15;


    enum States
    {
        SIDE_ZERO = 15 , SIDE_ONE = 10 , SIDE_TWO = 6 ,
        SIDE_THREE = 5 , SIDE_FOUR = 13 , SIDE_FIVE = 9 ,
        SIDE_SIX = 11 , SIDE_SEVEN = 5 , SIDE_EIGHT = 15 ,
        SIDE_NINE = 13,

        MID_ZERO = 5 , MID_ONE = 0 , MID_TWO = 7 ,
        MID_THREE = 7 , MID_FOUR = 2 , MID_FIVE = 7 ,
        MID_SIX = 7 , MID_SEVEN = 4 , MID_EIGHT = 7 ,
        MID_NINE = 7
    };

    static vector<bool> EncoderNumber( int number , bool side )
    {
        int current = 0;

        vector < bool > code = side ? vector<bool>(4) : vector<bool>(3);

        while(number != 0)
        {
            code[current++] =  number % 2 ;
            number/=2;
        }
        reverse(code.begin(),code.end());
        return code;
    }


    static int DecoderNumber( vector <bool> code )
    {
        int number = 0;
        for(size_t i = 0 ; i < code.size(); i++)
            number = 2 * number + code[i] ;
        return number;
    }

    static char EncodeColor( int tColor , bool background )
    {
        char valid = background ? '0' : 'F';

        if (  MIN_COLOR > tColor || tColor > MAX_COLOR )
            return valid ;

        if ( MIN_DECIMAL <= tColor && tColor <= MAX_DECIMAL)
            valid = tColor + '0';

        if ( MIN_HEXADECIMAL <= tColor && tColor <= MAX_HEXADECIMAL)
            valid = tColor - 10 + 'A';

        return valid;
    }

};

class Time
{
public:

    static const short MIN_HOURS = 0;
    static const short MAX_HOURS = 23;
    static const short MIN_MINUTES = 0;
    static const short MAX_MINUTES = 59;
    static const short MIN_SECONDS = 0;
    static const short MAX_SECONDS = 59;

    Time()
    {
        hours = minutes = seconds = 0;
    }
    Time(short tHours , short tMinutes , short tSeconds)
    {
        validateHours(tHours);
        validateMinutes(tMinutes);
        validateSeconds(tSeconds);
    }

    inline void setHour( short tHours )
    {
        validateHours(tHours);
    }
    inline void setMinutes(short tMinutes)
    {
        validateMinutes(tMinutes);
    }
    inline void setSeconds(short tSeconds)
    {
        validateSeconds(tSeconds);
    }

    inline short getHour()
    {
        return hours ;
    }

    inline short getMinutes()
    {
        return  minutes;
    }

    inline short getSeconds()
    {
        return  seconds;
    }

    static Time getTimeSystem()
    {
        time_t timeSystem = time(0);
        struct tm *p = localtime(&timeSystem);
        //cout<<asctime(p);
        return Time ( p->tm_hour, p->tm_min , p->tm_sec );
    }

    Time & operator=( const Time & other)
    {
        hours = other.hours;
        minutes = other.minutes;
        seconds  = other.seconds;
        return *this;
    }
    Time & operator++(int j)
    {
        seconds++;
        if(seconds > MAX_SECONDS )
        {
            seconds = 0;
            minutes++;
        }
        if(minutes > MAX_MINUTES )
        {
            minutes = 0;
            hours ++ ;
        }
        if( hours > MAX_HOURS ) hours = MIN_HOURS;
        return *this;
    }

    Time & operator--(int j)
    {
        seconds--;
        if(seconds < MIN_SECONDS )
        {
            seconds = MAX_SECONDS;
            minutes--;
        }
        if(minutes < MIN_MINUTES )
        {
            minutes = MAX_MINUTES;
            hours -- ;
        }
        if(hours < MIN_HOURS ) hours = MAX_HOURS;
        return *this;
    }

    friend Time  operator - ( Time current , short tSeconds )
    {
        current.seconds -= tSeconds;
        if(current.seconds < MIN_SECONDS  )
        {
            current.seconds = MAX_SECONDS;
            current.minutes--;
        }
        if(current.minutes < MIN_MINUTES )
        {
            current.minutes = MAX_MINUTES;
            current.hours -- ;
        }
        if(current.hours < MIN_HOURS )
            current.hours = MAX_HOURS;

        return current;
    }

    friend ostream & operator<<(ostream & output , Time & time  )
    {
        output<<time.hours<<':'<<time.minutes<<':'<< time.seconds;
        return output;
    }

    vector<short> getDigits()
    {
        vector < short> digits;
        digits.push_back( hours / 10);
        digits.push_back( hours % 10);
        digits.push_back( minutes / 10);
        digits.push_back( minutes % 10);
        digits.push_back( seconds / 10);
        digits.push_back(seconds % 10);
        return digits;
    }

private :
    short hours , minutes , seconds;

    inline void validateHours(short  tHours )
    {
        hours = bound( MIN_HOURS , tHours , MAX_HOURS);
    }

    inline void validateMinutes(short  tMinutes )
    {
        minutes = bound( MIN_MINUTES , tMinutes , MAX_MINUTES);
    }

    inline void validateSeconds(short  tSeconds )
    {
            seconds = bound( MIN_SECONDS , tSeconds , MAX_SECONDS);
    }
};

class Clock
{
public:
    enum Color
    {
        BLACK = 0 , BLUE , GREEN , CYAN , RED ,
        PURPLE , YELLOW , WHITE ,

        BRIGHT_BLACK , BRIGHT_BLUE , BRIGHT_GREEN , BRIGHT_CYAN , BRIGHT_RED ,
        BRIGHT_PURPLE , BRIGHT_YELLOW , BRIGHT_WHITE
    };


    static const short MIN_COLOR = 0;
    static const short MAX_COLOR = 15;

    static const short MIN_POSITION = 2;
    static const short MAX_POSITION = 20;

    static const short STOP_RATE = -1;
    static const short MIN_RATE = 1000;
    static const short RATE_BY_TEN = 100;
    static const short RATE_BY_HUNDRED = 10;
    static const short MAX_RATE = 0;

    static const bool STOPED = true;
    static const bool RUNNING = false;

    static const short MIN_WIDTH_NUMBER = 3;
    static const short MAX_WIDTH_NUMBER = 5;

    static const short MIN_HEIGHT_NUMBER = 3;
    static const short MAX_HEIGHT_NUMBER = 10;


    static const short MIN_SPACING_NUMBER = 2;
    static const short MAX_SPACING_NUMBER = 5;

    static const short MIN_SPACING_SIGN = 2;
    static const short MAX_SPACING_SIGN = 4;


    Clock()
    {
        //Constant
        SetConsoleTitleA("Clock");
        CreateStateNumbers();
        currentTime = Time::getTimeSystem();
        screen = GetStdHandle(STD_OUTPUT_HANDLE);
        widthSign = 1;

        //Modificable
        colorBackground = Color::BLACK;
        colorNumber = Color::BRIGHT_WHITE;
        //system("color F0");
        // colorBackground = Color::Bright_White;
        //colorNumber = Color::Black;

        validateClockPosition({20,3});
        validateRate( MIN_RATE );
        validateWidthNumber(MIN_WIDTH_NUMBER);
        validateHeightNumber(MAX_HEIGHT_NUMBER);
        validateSpacingNumber(MIN_SPACING_NUMBER);
        validateSpacingSign(MAX_SPACING_SIGN);

    }

    void setColorBackground( short tColorBackground )
    {
       colorBackground = bound(MIN_COLOR , tColorBackground , MAX_COLOR);

        char tColorB = Codification::EncodeColor(colorBackground,BACKGROUND);
        char tColorN = Codification::EncodeColor(colorNumber,NUMBER);

        string commmad = "color " ;
        commmad+= tColorB;
        commmad+= tColorN;
        system(commmad.c_str());
    }

    inline void setColorNumber( short tColorNumber )
    {
        colorNumber = bound( MIN_COLOR , tColorNumber , MAX_COLOR);
    }

    inline void setClockPosition(COORD tClockPosition )
    {
        validateClockPosition(tClockPosition);
    }

    inline void setClockPosition(short x , short y )
    {
        validateClockPosition({x,y});
    }

    inline void setRate(int tRate)
    {
        validateRate(tRate);
    }

    inline void setWidthNumber ( short tWidthNumber )
    {
        validateWidthNumber(tWidthNumber);
    }
    inline void setHeightNumber( short tHeightNumber )
    {
        validateHeightNumber(tHeightNumber);
    }
    inline void setSpacingNumber( short tSpacingNumber )
    {
        validateSpacingNumber(tSpacingNumber);
    }

    inline void setSpacingSign ( short tSpacingSign )
    {
        validateSpacingSign(tSpacingSign);
    }
    inline short getColorBackgorund()
    {
        return  colorBackground;
    }
    inline short getColorNumber()
    {
        return colorNumber;
    }
    inline int getRate()
    {
        return rate ;
    }

    inline short getWidthNumber ( )
    {
        return widthNumber;
    }
    inline short getHeightNumber( )
    {
        return  heightNumber;
    }
    inline short getSpacingNumber( )
    {
        return spacingNumber;
    }
    inline short getSpacingSign ( )
    {
        return spacingSign;
    }


    void PaintNumber( COORD position , short number )
    {
        PaintSideNumber(position , Codification::EncoderNumber(SideState[number],SIDE) );
        PaintMidNumber( position , Codification::EncoderNumber(MidState[number],MID) );
    }

    void PaintTimer( COORD position , bool init )
    {
        Time prevTime = currentTime - 1;
        vector < bool > state;
        vector < short> cNumber  = currentTime.getDigits() ,
                        pNumber  = prevTime.getDigits();

        if(init)
            state = vector<bool>( QUANTITY_DIGIT,true);
        else
            for(int i = 0 ; i < QUANTITY_DIGIT ; i++)
             state.push_back( detectChange(cNumber[i],pNumber[i]) );

        //Number 1:
        if(state[0])
        {
            EraseNumber(position,pNumber[0]);
            PaintNumber(position ,cNumber[0]);
        }

        //Number 2:
        position.X += widthNumber + spacingNumber;
        if(state[1])
        {
            EraseNumber(position,pNumber[1]);
            PaintNumber(position , cNumber[1]);

        }

        //Sign
        position.X += widthNumber  + spacingSign  ;
        PaintSign(position);

        //Number 3:
        position.X +=  widthSign + spacingSign ;
        if(state[2])
        {
            EraseNumber(position,pNumber[2]);
            PaintNumber(position, cNumber[2]);
        }

        //Number 4:
        position.X += widthNumber + spacingNumber;
        if(state[3])
        {
            EraseNumber(position,pNumber[3]);
            PaintNumber(position, cNumber[3]);
        }

        //Sign
        position.X += widthNumber + spacingSign;
        PaintSign(position);

        //Number 5:
        position.X += widthSign + spacingSign;
        if(state[4])
        {
            EraseNumber(position,pNumber[4]);
            PaintNumber(position, cNumber[4]);
        }

        //Number 6:
        position.X += widthNumber + spacingNumber;
        if(state[5])
        {
            EraseNumber(position,pNumber[5]);
            PaintNumber(position, cNumber[5]);
        }
    }

    void show(bool stateRate = RUNNING)
    {
        if(stateRate)
            rate = STOP_RATE;
        PaintTimer(clockPosition,true);
        while(true)
        {
            Sleep(rate);
            currentTime++;
            PaintTimer(clockPosition,false);
        }
    }
private:
    static const short QUANTITY_DIGIT = 6;

    static const bool SIDE = true;
    static const bool MID = false;

    static const bool BACKGROUND = true;
    static const bool NUMBER = false;

    int rate;
    short widthNumber ,  heightNumber ,  spacingNumber ,
          widthSign , spacingSign ;
    short colorNumber , colorBackground;
    vector<int> SideState ,MidState;
    HANDLE  screen;
    COORD clockPosition;
    Time currentTime;

    bool detectChange(short cNumber, short pNumber )
    {
        return abs( cNumber - pNumber )  != 0 ? true : false ;
    }
    void placerCursor( COORD position )
    {
        SetConsoleCursorPosition(screen, position);
    }

    void CreateStateNumbers()
    {
        SideState =
        {
            Codification::SIDE_ZERO , Codification::SIDE_ONE ,
            Codification::SIDE_TWO , Codification::SIDE_THREE ,
            Codification::SIDE_FOUR , Codification::SIDE_FIVE ,
            Codification::SIDE_SIX , Codification::SIDE_SEVEN ,
            Codification::SIDE_EIGHT , Codification::SIDE_NINE
        };

        MidState =
        {
            Codification::MID_ZERO , Codification::MID_ONE ,
            Codification::MID_TWO , Codification::MID_THREE ,
            Codification::MID_FOUR , Codification::MID_FIVE ,
            Codification::MID_SIX , Codification::MID_SEVEN ,
            Codification::MID_EIGHT , Codification::MID_NINE
        };
    }

    void PaintSideNumber( COORD position ,vector<bool> state )
    {
        if(state[0])
            PaintVertical(position,heightNumber);
        position.X+=widthNumber;
        if(state[1])
            PaintVertical(position,heightNumber);
        position.X-=widthNumber;
        position.Y+=heightNumber;
        if(state[2])
            PaintVertical(position,heightNumber);
        position.X+=widthNumber;
        if(state[3])
            PaintVertical(position,heightNumber);
    }
    void PaintMidNumber(COORD position ,vector<bool> state )
    {
        if(state[0])
            PaintLine(position,widthNumber + 1);
        position.Y+= heightNumber;
        if(state[1])
            PaintLine(position,widthNumber+ 1);
        position.Y+= heightNumber-1;
        if(state[2])
            PaintLine(position,widthNumber+ 1);
    }

    void PaintLine( COORD position , short length  )
    {
        SetConsoleCursorPosition(screen,position);
        for(int i = 0 ; i < length ; i++ )
            cout<<'*';
    }
    void PaintVertical( COORD position , short length  )
    {
        SetConsoleCursorPosition(screen,position);
        for(int i = 0 ; i < length ; i++ )
        {
            cout<<'*';
            position.Y++;
            SetConsoleCursorPosition(screen,position);
        }
    }

    void PaintSign( COORD position )
    {
        position.Y+= heightNumber - 1;
        placerCursor(position );
        cout<<'*';
        position.Y++;
        placerCursor(position );
        cout<<'*';
    }

    void EraseNumber(COORD  position , short number )
    {
        SetConsoleTextAttribute(screen,colorBackground);
        PaintNumber(position,number);
        SetConsoleTextAttribute(screen,colorNumber);
    }

    inline void validateSpacingNumber( short tSpacingNumber )
    {
       spacingNumber = bound ( MIN_SPACING_NUMBER ,
                              tSpacingNumber , MAX_SPACING_NUMBER );
    }

     inline void validateSpacingSign( short tSpacingSign )
    {
        spacingSign = bound ( MIN_SPACING_SIGN ,
                             tSpacingSign , MAX_SPACING_SIGN);
    }

    void validateClockPosition(COORD tClockPosition)
    {
       tClockPosition.X = bound(MIN_POSITION ,tClockPosition.X ,
                           MAX_POSITION);
       tClockPosition.Y = bound(MIN_POSITION ,tClockPosition.Y ,
                           MAX_POSITION);
        clockPosition = tClockPosition;
    }
    inline void validateRate(short tRate)
    {
            rate = bound ( MIN_RATE , tRate ,MAX_RATE );
    }
    inline void validateWidthNumber(short tWidthNumber)
    {
            widthNumber = bound ( MIN_WIDTH_NUMBER ,
                                 tWidthNumber , MAX_WIDTH_NUMBER);
    }
     inline void validateHeightNumber(short tHeightNumber)
    {
       heightNumber = bound ( MIN_HEIGHT_NUMBER ,
                                  tHeightNumber , MAX_HEIGHT_NUMBER);
    }

};

/*
    To resolve problem
    with function setColorBackground
    search in Google as last option
*/
int main()
{
    Clock clock;
    clock.setColorNumber(2);
    clock.show();

    return 0;
}

