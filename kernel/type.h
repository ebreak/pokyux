#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned long
#define u64 unsigned long long

#define i8 char
#define i16 short
#define i32 long
#define i64 long long

#ifdef RV32
#define usize long
#else
#define usize long long
#endif

#define true 1
#define false 0