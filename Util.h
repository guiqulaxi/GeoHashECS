#ifndef UTIL_H
#define UTIL_H

#include<algorithm>
#include <math.h>
template <class T>
T limit(T angle,int base)
{
     if(0<=angle&&angle<=base)
     {
         return angle;
     }
     else if(angle<0)
     {

            angle=(int)(angle)%base+base+abs(angle)-floor(abs(angle));

     }
     else
     {
         angle=(int)(angle)%base+angle-std::floor(angle);
     }
     return angle;
}
template <class T>
T diffAngle(T a,T b)
{
   a=limit(a,(T)360);
   b=limit(b,(T)360);
   if(a>b)
   {
     T diff=a-b;
     if(diff>180)
     {
         return (T)360-diff;
     }else
     {
        return (T)(-1)*diff;
     }

   }
   else
   {
       T diff=b-a;
       if(diff>180)
       {
           return (T)(-1)*((T)360-diff);
       }else
       {
          return diff;
       }

   }

}


#endif // UTIL_H
