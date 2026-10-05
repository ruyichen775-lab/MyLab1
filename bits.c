/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1<<31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(~(x & ~y) & ~(~x & y));
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  return ~((((1<<31)&x)>>31)&x)+1;
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  return ((0xFF&(x>>(src<<3))) << (dst<<3)) |  (~(0xFF<<(dst<<3)) & x);;
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  return  (~(1<<31>>n<<1)) & (x>>n);
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int a,b,c,d;
  a=0xF;
  b=a+(a<<8);
  c=b+(b<<16);
  d=~c;
  return ((x&c)<<4) | (((x&d)>>4)&(~(1<<31>>3)));

}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
    int a=(x+1)|x;
  return ((a+1)|a)^a;
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x=x^(x>>16);
  x=x^(x>>8);
  x=x^(x>>4);
  x=x^(x>>2);
  x=x^(x>>1);
  return !(x&1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
   int a=(~(1<<31>>n<<1)) & (x>>n);
  int b=x<<1<<(31+~n+1);
  return a|b;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
    int q,r,ex,sm;
  q = x >> n;
  r = (~(1 << 31 >> (32 + ~n))) & x;
  sm = 1 << n >> 1;
  ex = (r & sm) << 1;
  return (q << n) + ex + (~(((!(r ^ sm)) & !(q & 1)) << n) + 1);
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int p1,p2,ex,pd;
  int sx=x>>31,sy=y>>31;
  p1=x>>1;
  p2=y>>1;
  int chk=sx^sy;
  pd=((!chk)&(!((1<<31)&(x+~y+1))))+(chk&(!((1<<31)&(p1+~p2+1))));
  ex=(x&y&1)+(((1&x)^(1&y))&pd);
  return p1+p2+ex;
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
int sx=(x>>31)&1, sa=(a>>31)&1, sb=(b>>31)&1;
  int da=x+~a+1, db=x+~b+1;
  int ca=sx^sa, cb=sx^sb;
  int sda=((ca&sx)|((!ca)&((da>>31)&1)));
  int sdb=((cb&sx)|((!cb)&((db>>31)&1)));
  return !!((sda^sdb)|(!(x^a))|(!(x^b)));
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int y=x<<2;
  int shov=!!(x^(y>>2));
  int z=x+y;
  int ov=(~(x^y))&(x^z);
  int m=(~shov+1)|(ov>>31);
  int sat=(x>>31)^~(1<<31);
  return (z&~m)|(sat&m);

}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
    int sx=x>>31, sy=y>>31;
  int s=x+y, ss=s>>31;
  int po=(~(sx|sy))&ss;
  int ne=sx&sy&~ss;
  int h=(po&1)+(~(ne&1)+1);

  int sz=z>>31;
  int t=s+z, st=t>>31;
  int po2=(~(ss|sz))&st;
  int ne2=ss&sz&~st;
  int k=(po2&1)+(~(ne2&1)+1);

  int H=h+k, sh=H>>31;
  return sh|((!sh)&!!H);
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned s=uf&0x80000000;
  unsigned e=(uf>>23)&0xFF;
  unsigned f=uf&0x7FFFFF;

  if(e==0xFF)
    return uf;

  if(e==0){
    unsigned t=f*3;
    unsigned r=t>>1;

    if((t&1)&&(r&1))
      r++;

    if(r>=0x800000)
      return s|(1<<23)|(r-0x800000);

    return s|r;
  }

  {
    unsigned t=(f|0x800000)*3;
    unsigned r;

    if(t>=0x2000000){
      r=t>>2;
      if((t&3)>2||((t&3)==2&&(r&1)))
        r++;
      e++;
    }
    else{
      r=t>>1;
      if((t&1)&&(r&1))
        r++;
    }

    if(r>=0x1000000){
      r>>=1;
      e++;
    }

    if(e>=0xFF)
      return s|0x7F800000;

    return s|(e<<23)|(r&0x7FFFFF);
  }
}
// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned s=uf&0x80000000;
  unsigned e=(uf>>23)&0xFF;
  unsigned f=uf&0x7FFFFF;
  unsigned sig;
  unsigned sh;
  unsigned q;
  unsigned r;
  unsigned mask;
  unsigned k;

  if(e==0xFF)
    return uf;

  if(e>=150)
    return uf;

  if(e<126)
    return s;

  sig=f|0x800000;
  sh=150-e;
  q=sig>>sh;
  mask=(1<<sh)-1;
  r=sig&mask;

  if(r>(1<<(sh-1))||(r==(1<<(sh-1))&&(q&1)))
    q++;

  if(q==0)
    return s;

  k=0;
  while((q>>(k+1))!=0)
    k++;

  return s|((k+127)<<23)|((q<<(23-k))&0x7FFFFF);
}
// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  unsigned s=0,a,e=0,f,r,sh;

  if(x==0)
    return 0;

  if(x<0){
    s=0x80000000;
    a=~x+1;
  }
  else
    a=x;

  f=a;

  while(a>>1){
    a>>=1;
    e++;
  }

  if(e<=23){
    f=(f<<(23-e))&0x7FFFFF;
    return s|((e+127)<<23)|f;
  }

  sh=e-23;
  r=f&((1<<sh)-1);
  f=(f>>sh)&0x7FFFFF;

  if(r>(1<<(sh-1))||(r==(1<<(sh-1))&&(f&1))){
    f++;
    if(f==0x800000){
      f=0;
      e++;
    }
  }

  return s|((e+127)<<23)|f;
}
// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int m1=0x55,m2=0x33,m3=0xf,m4=0xff,m5=m4+(m4<<8);
  int tmp1,tmp2,tmp3,tmp4;

  m1=m1+(m1<<8);
  m1=m1+(m1<<16);
  tmp1=(x&m1)+((x>>1)&m1);
 
  m2=m2+(m2<<8);
  m2=m2+(m2<<16);
  tmp2=(tmp1&m2)+((tmp1>>2)&m2);

  m3=m3+(m3<<8);
  m3=m3+(m3<<16);
  tmp3=(tmp2&m3)+((tmp2>>4)&m3);

  m4=m4+(m4<<16);
  tmp4=(tmp3&m4)+((tmp3>>8)&m4);

  return (tmp4&m5)+((tmp4>>16)&m5);
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  int m1,m2,m3,m4=0xff+(0xff<<16),m5=0xff+(0xff<<8);
  m3=m4^(m4<<4);
  m2=m3^(m3<<2);
  m1=m2^(m2<<1);

  x=((x>>1)&m1)+((x&m1)<<1);
  x=((x>>2)&m2)+((x&m2)<<2);
  x=((x>>4)&m3)+((x&m3)<<4);
  x=((x>>8)&m4)+((x&m4)<<8);

  return ((x>>16)&m5)+((x<<16));
}
