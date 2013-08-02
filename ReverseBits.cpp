#include <iostream>
#include <string>
#include <chrono>

using namespace std;

// Compiler: Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012)
// Based on http://corner.squareup.com/2013/07/reversing-bits-on-arm.html

// Trivial solution O(n)
unsigned char ReverseBitsObvious(unsigned char v)
{
  unsigned char r = v;
  int s = sizeof(v) * CHAR_BIT - 1;
  for (v >>= 1; v; v >>= 1) {
      r <<= 1; r |= v & 1; s--;
  }
  return r << s;
}

// Lookup table O(1)
// Leverages cache locality but requires extra storage
#define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64
#define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )

static const unsigned char BitReverseTable256[256] =
{
    R6(0), R6(2), R6(1), R6(3)
};

unsigned char ReverseBitsLookupTable(unsigned char v)
{
  return BitReverseTable256[v];
}

// 3 operations (O(1))
// 64bit multiply + 64-bit modulo (non power of two)
unsigned char ReverseBits3ops64bit(unsigned char v)
{
  return (v * 0x0202020202ULL & 0x010884422010ULL) % 1023;
}

// 4 operations (O(1))  
// 64-bit multiply
unsigned char ReverseBits4ops64bit(unsigned char v)
{
  return ((v * 0x80200802ULL) & 0x0884422110ULL) * 0x0101010101ULL >> 32;
}

// 7 operations (O(1))
// 32-bit multiply
unsigned char ReverseBits7ops32bit(unsigned char v)
{
  return ((v * 0x0802LU & 0x22110LU) | 
          (v * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;
}

// Parallel bitwise approach (O(5log(N)) where N is the number of bits):
unsigned char ReverseBits5logNOps(unsigned char v)
{
  v = ((v >> 1) & 0x55) | ((v & 0x55) << 1);
  v = ((v >> 2) & 0x33) | ((v & 0x33) << 2);
  v = ((v >> 4) & 0x0F) | ((v & 0x0F) << 4);
  return v;
}

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds milliseconds;

#define OPERATIONS 5000000

void bench ( unsigned char (*f)(unsigned char), std::string name, unsigned char v) {
  
  Clock::time_point t0 = Clock::now();

  for(int i = 0; i < OPERATIONS; ++i){
      (*f)(v);
  }
        
  Clock::time_point t1 = Clock::now();

  milliseconds ms = std::chrono::duration_cast<milliseconds>(t1 - t0);
  long throughput = (OPERATIONS) / ms.count();

  std::cout << std::endl << name << " time: " << ms.count() << " ms, throughput:" << throughput << " calls / ms" << std::endl;
}

int main(){

    bench(ReverseBitsLookupTable, "ReverseBitsLookupTable O(1)", 'C');
    bench(ReverseBits7ops32bit, "ReverseBits7ops32bit O(1)", 'C');
    bench(ReverseBits5logNOps, "ReverseBits5logNOps O(5log(N)", 'C');
    bench(ReverseBits4ops64bit, "ReverseBits4ops64bit O(1)", 'C');
    bench(ReverseBits3ops64bit, "ReverseBits3ops64bit O(1)", 'C');
    bench(ReverseBitsObvious, "ReverseBitsObvious O(N)", 'C');

    return 0;
}