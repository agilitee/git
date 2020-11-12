#include <iostream>
using namespace std;

#define WALL 8888
#define PTERO -1
#define FOOD 0
#define CLEAR 6000

struct koor {int row; int col;};

int main()
{
    int rows,cols,k;
    int lab[50][50];
    int i, j;
    char inputc;
    int step;
    int counter=0, way=0, perfoway = 0, shorter;
    bool processing;
    koor food, ptero, destroy;

    food.row = 0;
    food.col = 0;
    ptero.row = 0;
    ptero.col = 0;
    destroy.col = 0;
    destroy.row = 0;
    cin >> cols >>rows;
    cin.get();
    i = 0;
    j = 0;
    for (j = 0; j< rows; j++) 
    {
        for (i = 0; i<cols; i++)
        {
            inputc = cin.get();
            if (inputc==' ') lab [j][i] = CLEAR;
            else if (inputc=='#') lab [j][i] = WALL;
            else if (inputc=='@') {
                lab [j][i] = PTERO;
                ptero.row = j;
                ptero.col = i;
            }
            else if (inputc=='*') {
                lab [j][i] = FOOD;
                food.row = j;
                food.col = i;
            }    
        } 
        cin.get();
    } 
//                      проход лабиринта от еды
    step = 1;
    processing = true;
    if ((food.row+1<=rows) && (lab[food.row+1][food.col]==CLEAR)) lab[food.row+1][food.col] = step;
    else if (lab[food.row+1][food.col]==PTERO) processing = false;
    
    if ((food.row-1>=0) && (lab[food.row-1][food.col]==CLEAR)) lab[food.row-1][food.col] = step;
    else if (lab[food.row-1][food.col]==PTERO) processing = false;
    
    if ((food.col+1<=cols) && (lab[food.row][food.col+1]==CLEAR)) lab[food.row][food.col+1] = step;
    else if (lab[food.row][food.col+1]==PTERO) processing = false;
    
    if ((food.col-1>=0) && (lab[food.row][food.col-1]==CLEAR)) lab[food.row][food.col-1] = step;
    else if (lab[food.row][food.col-1]==PTERO) processing = false;
    
    if (!processing) way = 1;
 //   step++;

    while (processing && (step < (rows*cols)-2))
    {   
        step++;
        for (j = 0; j< rows; j++)
        {
            for (i = 0;i<cols;i++)
            {
                if (lab[j][i]==step-1)
                {
                    if ((j+1<rows) && (lab[j+1][i]==CLEAR)) 
                    {   lab[j+1][i] = step;
                        counter++;
                    }
                    else if (lab[j+1][i]==PTERO) 
                    {
                        processing = false;
                        way = step;
                    }

                    if ((j-1>=0) && (lab[j-1][i]==CLEAR)) 
                    {
                        lab[j-1][i] = step;
                        counter++;
                    }    
                    else if (lab[j-1][i]==PTERO)
                    {
                        processing = false;
                        way = step;
                    }
    
                    if ((i+1<cols) && (lab[j][i+1]==CLEAR)) 
                    {
                        lab[j][i+1] = step;
                        counter++;
                    }    
                    else if (lab[j][i+1]==PTERO) 
                    {
                        processing = false;
                        way = step;
                    }
    
                    if ((i-1>=0) && (lab[j][i-1])==CLEAR) 
                    {
                        lab[j][i-1] = step;
                        counter++;
                    }
                    else if (lab[j][i-1]==PTERO) 
                    {
                        processing = false;
                        way = step;
                    }
                } 
            }
        }
        if (counter) counter = 0;  // если ячейки помечены, пойдет следующая волна
        else processing = false;  // если не помечены - прерываем процесс
    }    
    
 //   if (way) cout <<"Way founded " << way << "steps"<<endl;
//    else cout <<"I need perforator"<<endl;
//    cout <<"Maded " << step << "steps"<<endl;

//                 проход лабиринта от перфораптора
    
    counter = 0;
    if ((ptero.row+1<=rows) && (lab[ptero.row+1][ptero.col]==CLEAR)) 
        {lab[ptero.row+1][ptero.col] = -2; counter++;}
    if ((ptero.row-1>=0) && (lab[ptero.row-1][ptero.col]==CLEAR)) 
        {lab[ptero.row-1][ptero.col] = -2; counter++;}
    if ((ptero.col+1<=cols) && (lab[ptero.row][ptero.col+1]==CLEAR)) 
        { lab[ptero.row][ptero.col+1] = -2; counter++;}
    if ((ptero.col-1>=0) && (lab[ptero.row][ptero.col-1]==CLEAR)) 
        {lab[ptero.row][ptero.col-1] = -2; counter++;}
    if (counter>0)
    {
        step = -2;
        processing = true;
        counter = 0;
    }    
 
    while (processing && ((-1*step) < (rows*cols)-2))
    {   
        step--;
        for (j = 0; j< rows; j++)
        {
            for (i = 0;i<cols;i++)
            {
                if (lab[j][i]==step+1)
                {
                    if ((j+1<rows) && (lab[j+1][i]==CLEAR)) 
                    {   lab[j+1][i] = step;
                        counter++;
                    }
                    if ((j-1>=0) && (lab[j-1][i]==CLEAR)) 
                    {
                        lab[j-1][i] = step;
                        counter++;
                    }    
                    if ((i+1<cols) && (lab[j][i+1]==CLEAR)) 
                    {
                        lab[j][i+1] = step;
                        counter++;
                    }    
                    if ((i-1>=0) && (lab[j][i-1])==CLEAR) 
                    {
                        lab[j][i-1] = step;
                        counter++;
                    }
                } 
            }
        }
        if (counter) counter = 0;  // если ячейки помечены, пойдет следующая волна
        else processing = false;  // если не помечены - прерываем процесс
    }    
 //   cout <<"Maded " << step << "steps"<<endl;


 //     проверяем короткий путь через стену
    //if (way==0) way = rows*cols;
    perfoway = rows*cols;
    shorter = perfoway;
 //   if (way!=0) lab[ptero.row][ptero.col]=0;
 //   else lab[ptero.row][ptero.col]=-PTERO;
    for (j=0; j<rows;j++)
    {
        for(i=0; i<cols;i++)
        {
            if (lab[j][i]==WALL)  //ищем стену и "удаляем" её для сравнения нового пути
            {
                if (((j>0)&&(j<rows-1))&&(lab[j-1][i]!=WALL)&&(lab[j+1][i]!=WALL)) // по строкам (верх-низ)
                {
                    if (lab[j-1][i]*lab[j+1][i] >= 0) 
                        { if (way>0) shorter = way-abs(lab[j-1][i]-lab[j+1][i])+2;}
                    else shorter = abs(lab[j-1][i]-lab[j+1][i])+1;
                    if (shorter<perfoway)
                    {
                        destroy.col=i;
                        destroy.row=j;
                        perfoway = shorter;
                    }
                }
                if (((i>0)&&(i<cols-1))&&(lab[j][i-1]!=WALL)&&(lab[j][i+1]!=WALL)) // по столбцам (право-лево)
                {
                    if (lab[j][i-1]*lab[j][i+1] >= 0) 
                        { if (way>0) shorter = way-abs(lab[j][i-1]-lab[j][i+1])+2;}
                    else shorter = abs(lab[j][i-1]-lab[j][i+1])+1;
                    if (shorter<perfoway)
                    {
                        destroy.col=i;
                        destroy.row=j;
                        perfoway = shorter;
                    }
                }
               /* if ((i>0&&i<cols-1)&&(j<rows-1)&&(lab[j][i-1]!=WALL)&&(lab[j+1][i]!=WALL)) // по диагонали вперед-вниз
                {
                    if (lab[j][i-1]*lab[j+1][i] > 0) 
                        { if (way!=0) shorter = way-abs(lab[j][i-1]-lab[j+1][i])+2;}
                    else shorter = abs(lab[j][i-1]-lab[j+1][i])+1;
                    if (shorter<perfoway)
                    {
                        destroy.col=i;
                        destroy.row=j;
                        perfoway = shorter;
                    }
                }*/
             /*  if ((i>0&&i<cols-1)&&(j<rows-1)&&(lab[j][i+1]!=WALL)&&(lab[j+1][i]!=WALL)) // по диагонали назад-вниз
                {
                    if (lab[j][i+1]*lab[j+1][i] > 0) 
                        { if (way!=0) shorter = way-abs(lab[j][i+1]-lab[j+1][i])+2;}
                    else shorter = abs(lab[j][i+1]-lab[j+1][i])+1;
                    if (shorter<perfoway)
                    {
                        destroy.col=i;
                        destroy.row=j;
                        perfoway = shorter;
                    }
                }*/
            }
        }
    }
//    cout << "perfoway="<<perfoway<<" way="<<way;
//    cout << " will be destroyed " << destroy.col<<","<<destroy.row<<endl; 

    
   // lab[ptero.row][ptero.col]=PTERO;
// обнуляемся, рисуем дырку и ищем маршрут   
    if ((perfoway < way)||(way==0))
    {
        lab[destroy.row][destroy.col]=CLEAR;
        for (j=0; j<rows;j++) 
            for(i=0; i<cols;i++)
                if ((lab[j][i]!=WALL)&&(lab[j][i]!=PTERO)&&(lab[j][i]!=FOOD))lab[j][i]=CLEAR;
        way = 0;
        step = 1;
        processing = true;
    }
    if ((food.row+1<=rows) && (lab[food.row+1][food.col]==CLEAR)) lab[food.row+1][food.col] = step;
    else if (lab[food.row+1][food.col]==PTERO) processing = false;
    
    if ((food.row-1>=0) && (lab[food.row-1][food.col]==CLEAR)) lab[food.row-1][food.col] = step;
    else if (lab[food.row-1][food.col]==PTERO) processing = false;
    
    if ((food.col+1<=cols) && (lab[food.row][food.col+1]==CLEAR)) lab[food.row][food.col+1] = step;
    else if (lab[food.row][food.col+1]==PTERO) processing = false;
    
    if ((food.col-1>=0) && (lab[food.row][food.col-1]==CLEAR)) lab[food.row][food.col-1] = step;
    else if (lab[food.row][food.col-1]==PTERO) processing = false;
    
 //   if (!processing) way = 1;
 //   step++;

    while (processing && (step < (rows*cols)-2))
    {   
        step++;
        for (j = 0; j< rows; j++)
        {
            for (i = 0;i<cols;i++)
            {
                if (lab[j][i]==step-1)
                {
                    if ((j+1<rows) && (lab[j+1][i]==CLEAR)) 
                    {   lab[j+1][i] = step;
                        counter++;
                    }
                    else if (lab[j+1][i]==PTERO) 
                    {
                        processing = false;
                        way = step;
                    }

                    if ((j-1>=0) && (lab[j-1][i]==CLEAR)) 
                    {
                        lab[j-1][i] = step;
                        counter++;
                    }    
                    else if (lab[j-1][i]==PTERO)
                    {
                        processing = false;
                        way = step;
                    }
    
                    if ((i+1<cols) && (lab[j][i+1]==CLEAR)) 
                    {
                        lab[j][i+1] = step;
                        counter++;
                    }    
                    else if (lab[j][i+1]==PTERO) 
                    {
                        processing = false;
                        way = step;
                    }
    
                    if ((i-1>=0) && (lab[j][i-1])==CLEAR) 
                    {
                        lab[j][i-1] = step;
                        counter++;
                    }
                    else if (lab[j][i-1]==PTERO) 
                    {
                        processing = false;
                        way = step;
                    }
                } 
            }
        }
        if (counter) counter = 0;  // если ячейки помечены, пойдет следующая волна
        else processing = false;  // если не помечены - прерываем процесс
    }    
    
 //   if (way) cout <<"Way founded " << way << "steps"<<endl;
 //   else cout <<"I need MORE perforator"<<endl;
 //   cout <<"Maded " << step << "steps"<<endl;
    

// численная визуализация лабиринта    
/*    for (j = 0; j< rows; j++) 
    {
        for (i = 0; i<cols; i++) cout << lab [j][i];
        cout <<endl;
    }*/
    
//     вывод пути                         
    for (k=way-1; k>=0; k--)
    {
        if (lab[ptero.row+1][ptero.col] == k) 
        { cout <<"down ";
          ptero.row++;
        }  
        else if (lab[ptero.row-1][ptero.col] == k) 
        { cout <<"up ";
          ptero.row--;
        }
        else if (lab[ptero.row][ptero.col-1] == k) 
        { cout <<"left ";
            ptero.col--;
        }    
        else if (lab[ptero.row][ptero.col+1] == k)
        { cout <<"right ";
            ptero.col++;
        }    
        


    }


    return 0;
}

