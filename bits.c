/* 
 * CS:APP Data Lab 
 * 
 * <徐木紫 25303050009>
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
  return 1 << 31;
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
	return ~(~x & ~y) & ~(x & y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x) {
  int sign = x >> 31;
  return (~x + 1) & sign;
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
    int srcByte = (x >> (src << 3)) & 0xFF;

    //  将源字节移动到目标位置
    int movedSrc = srcByte << (dst << 3);

    // 构造掩码
    int mask = ~(0xFF << (dst << 3));
    int clearedX = x & mask;
    return clearedX | movedSrc;
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
    // 算术右移
    int shifted = x >> n;
    // 构造掩码
    int mask = ~(((1 << 31) >> n) << 1);
    // 用掩码清除高 n 位
    return shifted & mask;
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
    int m = 0x0F | (0x0F << 8);
    m = m | (m << 16);
    return ((x >> 4) & m) | ((x & m) << 4);
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
    int nx = ~x;
    int low = nx & (~nx + 1);
    int rest = nx ^ low;
    return rest & (~rest + 1);
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
    // 通过逐层折半异或，把所有位的奇偶性压缩到最低位
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    // 此时最低位为 0 表示 1 的个数为奇数，为 1 表示偶数；取反得到奇校验位
    return (x & 1) ^ 1;
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
    // 处理 n=0 的情况，避免移位 32 位导致未定义行为
    int isZero = !n;
    // 计算 32 - n，用 ~n + 1 代替 -n
    int shift = 32 + (~n + 1);
    // 右移 n 位得到高半部分，左移 (32-n) 位得到低半部分，合并即为循环右移
    int rightPart = (x >> n) & ~(~0 << shift);
    int leftPart = x << shift;
    // n=0 时返回原值，否则返回合并结果
    return (isZero & x) | (~isZero & (rightPart | leftPart));
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
    //  half = 2^(n-1)
    int mask = (1 << n) + ~0;
    int half = 1 << (n + ~0);
    // 获取第 n 位的值
    int bit = (x >> n) & 1;
    // 若第 n 位为 1，则加上 2^n，确保向上取整
    return (x + half + bit + ~0) & ~mask;
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

    int sum = (x & y) + ((x ^ y) >> 1);
    int odd = (x ^ y) & 1;

    int sx = x >> 31;
    int sy = y >> 31;
    int diff = sx ^ sy;
    int gtSame = ~((x + ~y + 1) >> 31);
    int xgty = (diff & ~sx) | (~diff & gtSame);

    return sum + (odd & xgty);
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
    // x >= a && x <= b  <=>  (x - a) >= 0 && (b - x) >= 0
    int sx = x >> 31;
    int sa = a >> 31;
    int sb = b >> 31;
    int nsx = ~sx;
    int nsax = ~(sx ^ sa);
    int nsbx = ~(sx ^ sb);
    int xa = (x + ~a + 1) >> 31;
    int xb = (x + ~b + 1) >> 31;
    int ax = (a + ~x + 1) >> 31;
    int bx = (b + ~x + 1) >> 31;
    int lxa = (sx & ~sa) | (nsax & xa);
    int lxb = (sx & ~sb) | (nsbx & xb);
    int lax = (sa & nsx) | (nsax & ax);
    int lbx = (sb & nsx) | (nsbx & bx);
    return !((lxa & lxb) | (lax & lbx));
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
    int P = (0x19 << 24) + (0x99 << 16) + (0x99 << 8) + 0x99;
    int mul5 = (x << 2) + x;
    // x > P  <=> x - P - 1 >= 0   
    int d = x + ~P;
    int gtPm = ~(d >> 31);
    // x < -P <=> x + P < 0
    int ltN = (x + P) >> 31;
    int over = gtPm | ltN;
    int sx = x >> 31;
    int intMin = 1 << 31;
    int intMax = ~intMin;
    int sat = (sx & intMin) | (~sx & intMax);
    return (~over & mul5) | (over & sat);
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

    int ab = x + y;
    int s = ab + z;

    int c1 = (((x & y) | ((x | y) & ~ab)) >> 31) & 1;
    int c2 = (((ab & z) | ((ab | z) & ~s)) >> 31) & 1;
    int C = c1 + c2;
    int sx = ((x >> 31) & 1) + ((y >> 31) & 1) + ((z >> 31) & 1);
    int d = C + ~sx + 1;
    int su = (s >> 31) & 1;
    // d >= 1
    int ge1 = !((d + ~1 + 1) >> 31);
    // d <= -2
    int dltm1 = (d + 1) >> 31;
    int dneg = (d >> 31) & 1;
    int isNeg1 = dneg & !dltm1;
    int hi = ge1 | ((!d) & su);
    int lo = dltm1 | (isNeg1 & ~su);
    return (hi & 1) | (((lo & 1) << 31) >> 31);
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
    unsigned sign = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;
    unsigned t, r;

    if (exp == 0xFF) return uf;

    if (exp == 0) {
        if (frac == 0) return uf;
        t = (frac << 1) + frac;
        r = (t >> 1) + ((t & 1) & ((t >> 1) & 1));
        return sign | r; 
    }

 
    t = (frac << 1) + frac + 0x1800000; 
    if (t < 0x2000000) {
        r = (t >> 1) + ((t & 1) & ((t >> 1) & 1));
        if (r >= 0x1000000) return sign | ((exp + 1) << 23);
        return sign | (exp << 23) | (r - 0x800000);
    }

    if (exp >= 0xFE) return sign | 0x7F800000;
    r = (t >> 2) + (((t >> 1) & 1) & ((t & 1) | ((t >> 2) & 1)));
    return sign | ((exp + 1) << 23) | (r - 0x800000);
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
    unsigned sign = uf & 0x80000000;
    unsigned exp  = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;
    int E, drop;
    unsigned intPart, dropBits, half;

    if (exp == 0xFF) return uf;          
    if (exp < 126) return sign;          
    if (exp == 126) {                   
        if (frac == 0) return sign;     
        return sign | 0x3F800000;        
    }

    E = exp - 127;
    if (E >= 23) return uf;              

    drop = 23 - E;                       
    intPart  = frac >> drop;
    dropBits = frac & ((1 << drop) - 1);
    half     = 1 << (drop - 1);

    if (dropBits > half ||
        (dropBits == half && ((E ? (intPart & 1) : (~intPart & 1))))) {
        intPart++;
        if (intPart >> E) return sign | ((exp + 1) << 23); 
        return sign | (exp << 23) | (intPart << drop);
    }
    return sign | (exp << 23) | (intPart << drop);
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
    unsigned sign = 0;
    unsigned ax;
    int h, exp, r;
    unsigned keep, gt, rest, mant;

    if (x == 0) return 0;
    if (x == 0x80000000) return 0xCF000000; 
    if (x < 0) { sign = 0x80000000; ax = -x; } else { ax = x; }

 
    h = 0;
    unsigned t = ax;
    while (t >>= 1) h++;
    exp = 127 + h;

    if (h > 23) {
 
        r = h - 23;
        keep = ax >> r;
        gt = (ax >> (r - 1)) & 1;
        rest = ax & ((1 << (r - 1)) - 1);
        mant = keep + (gt & (!!rest | (keep & 1)));
        if (mant >> 24) { mant >>= 1; exp++; } 
    } else {
        mant = ax << (23 - h);
    }
    return sign | (exp << 23) | (mant & 0x7FFFFF);
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
    // 构造掩码
    int m1 = 0x55 | (0x55 << 8);
    m1 = m1 | (m1 << 16);
    int m2 = 0x33 | (0x33 << 8);
    m2 = m2 | (m2 << 16);
    int m4 = 0x0F | (0x0F << 8);
    m4 = m4 | (m4 << 16);
    int m8 = 0xFF | (0xFF << 16);

    // 逐层折半求和
    x = (x & m1) + ((x >> 1) & m1);
    x = (x & m2) + ((x >> 2) & m2);
    x = (x & m4) + ((x >> 4) & m4);
    x = (x + (x >> 8)) & m8;   
    x = (x + (x >> 16)) & 0xFF;
    return x;
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
int bitReverse(int x) {
    int m1 = 0x55 | (0x55 << 8);
    m1 = m1 | (m1 << 16);            /* 0x55555555 */
    int m2 = 0x33 | (0x33 << 8);
    m2 = m2 | (m2 << 16);            /* 0x33333333 */
    int m4 = 0x0F | (0x0F << 8);
    m4 = m4 | (m4 << 16);            /* 0x0F0F0F0F */
    int m8 = 0xFF | (0xFF << 16);    /* 0x00FF00FF */
    int t  = 0xFF | (0xFF << 8);     /* 0x0000FFFF */

    x = ((x >> 1) & m1) | ((x & m1) << 1);
    x = ((x >> 2) & m2) | ((x & m2) << 2);
    x = ((x >> 4) & m4) | ((x & m4) << 4);
    x = ((x >> 8) & m8) | ((x & m8) << 8);
    x = ((x >> 16) & t) | (x << 16);
    return x;
}
