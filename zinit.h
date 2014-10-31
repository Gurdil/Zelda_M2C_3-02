#ifndef ZINIT_H
#define ZINIT_H

namespace ZInit
{
     enum Constante
     {
          frameRate = 17,
     };

     enum KeyInfo
     {
         up = 1,
         down = up << 1,
         right = down << 1,
         left = right << 1
     };
}

#endif // ZINIT_H
