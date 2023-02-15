#include <stdint.h>
#include <stdatomic.h>

static int j = 47;
int inc(int i)
{
  i++;
  return i;
}

uint32_t get_PRIMASK(void)
{
  uint32_t res;

  __asm__ __volatile__(
    "mrs %0, PRIMASK"
    : "=r" (res) 
    ://no input
    ://No clobber
  );
  return res;
}

uint32_t get_BASEPRI(void)
{
  uint32_t ret;

  __asm__ __volatile__(
    "mrs %0, BASEPRI \n\t"
    : "=r" (ret)
    : //No input
    : // No clobber
  );
  return ret;
}

uint32_t get_FAULTMASK(void)
{
  uint32_t ret;

  __asm__ __volatile__(
    "mrs %0, FAULTMASK \n\t"
    : "=r" (ret)
    : //No input
    : // No clobber
  );
  return ret;
}

uint32_t get_CONTROL(void)
{
  uint32_t res;

  __asm__ __volatile__ (
    "mrs %0, control \n\t"
    : "=r" (res)
    : // No input
    : // No clobber
  );
  return res;
}

uint32_t get_msr(void)
{
  // Note that the bits 26-24 and bits 15-10 (ICI/IT and T bits) always
  // reads as zero with the mrs instruction. 
  uint32_t sr;
  __asm__("mrs %[result], xpsr"
      :[result]"=r" (sr)
      : /* No input */
      : /* No clobber */
      );
  __asm__("nop");
  __asm__("nop.w");
  return sr;
}

unsigned long ByteSwap(unsigned long val)
{
__asm__ __volatile__ (
        "eor     r3, %1, %1, ror #16\n\t"
        "bic     r3, r3, #0x00FF0000\n\t"
        "mov     %0, %1, ror #8\n\t"
        "eor     %0, %0, r3, lsr #8"
        : "=r" (val)
        : "0"(val)
        : "r3"
);
return val;
}

uint32_t leso(uint32_t val)
{
  uint32_t result;

  __asm__ __volatile__ (
      "mov %0, %1 \n\t"
      "add %0, %1 \n\t"
      : "=r" (result)
      : "r"  (val)
      : //No clobber
      );
  return result;
}

uint32_t add_args(uint32_t val1, uint32_t val2)
{
  uint32_t result;

  __asm__ __volatile__ (
      "add %0, %1, %2 \n\t"
      : "=r" (result)
      : "r"  (val1) ,"r" (val2)
      : //No clobber
      );
  return result;
}

uint32_t add_args2(uint32_t val1, uint32_t val2)
{
  uint32_t result;

  __asm__ __volatile__ (
      "mov r5, %1 \n\t"
      "mov r6, %2 \n\t"
      "add %0, r5, r6 \n\t"
      : "=r" (result)
      : "r"  (val1) ,"r" (val2)
      : "r5", "r6"
      );
  return result;
}

static void set_PRIMASK(uint32_t val)
{
  __asm__ __volatile__ (
    "msr PRIMASK, %0 \n\t"
    :
    : "r" (val)
    :
    );
}

static void change_primask(void)
{
  uint32_t mask = get_PRIMASK();
  if (mask == 0)
  {
    __asm__ __volatile__("cpsid i \n\t":::);
  }
  else
  {
    __asm__ __volatile__ ("cpsie i \n\t":::);
  }
}

int main()
{

  int i = 34;
  volatile uint32_t x = 0x1;
  volatile uint32_t y;
  volatile uint32_t z;
  volatile uint32_t swap =0x01234567;
  volatile _Atomic(uint8_t) a;

  a = 5;
  
  a++;
  (void)a;
  y = leso(0x23);
  z = add_args(0x10, 0x20);
  y = add_args2(0x10, 0x20);


  __asm__("mov %[result], %[value], ror #1"
      :[result]"=r" (y) /* Rotate result */
      :[value]"r"   (x) /* Rotated value */
      : /*No clobbers*/
  );
  
  y = ByteSwap(swap);

  x = get_msr();

  set_PRIMASK(1);
  change_primask();
  y = get_PRIMASK();



  y = get_BASEPRI();
  y = get_FAULTMASK();
  y = get_CONTROL();

  i = inc(i);
  i = j;
  return 0; 
}
