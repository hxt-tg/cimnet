/*
 *  This file contains Mersenne twister pseudorandom number
 *  generator. The authors of this algorithm are Makoto
 *  Matsumoto & Takuji Nishimura.
 *  Wiki: https://en.wikipedia.org/wiki/Mersenne_Twister
 *  (Xintao Hu is not the author of this part of code.
 *   If there is any infringement, please contact via email:
 *   hxt.taoge@gmail.com)
 *
 *  For further usage, check out http://doc.hxtcloud.cn.
 */

#ifndef CIMNET_RANDOM
#define CIMNET_RANDOM

void sgenrand(unsigned long seed);
void lsgenrand(const unsigned long seed_array[]);
double genrand();
double randf();
long randi(unsigned long LIM);


/* Random - Implementation */
#define NN 624
#define MM 397
#define MATRIX_A 0x9908b0df          /* constant vector a */
#define UPPER_MASK 0x80000000        /* most significant w-r bits */
#define LOWER_MASK 0x7fffffff        /* least significant r bits */
#define TEMPERING_MASK_B 0x9d2c5680
#define TEMPERING_MASK_C 0xefc60000
#define NAMEOUT     "K4b075r5Q2"

#define TEMPERING_SHIFT_U(y)  ((y) >> 11)
#define TEMPERING_SHIFT_S(y)  ((y) << 7)
#define TEMPERING_SHIFT_T(y)  ((y) << 15)
#define TEMPERING_SHIFT_L(y)  ((y) >> 18)

static unsigned long mt[NN];        /* the array for the state vector  */
static int mti = NN + 1;            /* mti==NN+1 means mt[NN] is not initialized */

void sgenrand(unsigned long seed){
    int i;
    for (i = 0; i < NN; i++) {
        mt[i] = seed & 0xffff0000; seed = 69069 * seed + 1;
        mt[i] |= (seed & 0xffff0000) >> 16; seed = 69069 * seed + 1;
    }
    mti = NN;
}

void lsgenrand(const unsigned long seed_array[]){
    int i; for (i = 0; i < NN; i++) mt[i] = seed_array[i]; mti = NN;
}

double genrand(){
    unsigned long y;
    static unsigned long mag01[2] = { 0x0, MATRIX_A };
    if (mti >= NN)
    {
        int kk;
        if (mti == NN + 1) sgenrand(4357);
        for (kk = 0; kk < NN - MM; kk++) {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + MM] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        for (; kk < NN - 1; kk++) {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + (MM - NN)] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        y = (mt[NN - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
        mt[NN - 1] = mt[MM - 1] ^ (y >> 1) ^ mag01[y & 0x1];
        mti = 0;
    }
    y = mt[mti++]; y ^= TEMPERING_SHIFT_U(y); y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
    y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C; y ^= TEMPERING_SHIFT_L(y);
    return y;
}

double randf(){
    return ((double)genrand() * 2.3283064370807974e-10);
}

long randi(unsigned long LIM){
    return (long)((unsigned long)genrand() % LIM);
}

#endif
