# Logger

## Supported types

|          Type          | Specifier |         Output         |
|:----------------------:|:---------:|:----------------------:|
|          char          |     %c    |          ASCII         |
|                        |           |                        |
|      signed short      |    %hi    |     Decimal output     |
|     unsigned short     |    %hu    |     Decimal output     |
|       signed int       |     %i    |     Decimal output     |
|      unsigned int      |     %u    |     Decimal output     |
|     signed long int    |    %li    |     Decimal output     |
|    unsigned long int   |    %lu    |     Decimal output     |
|  signed long long int  |    %lli   |     Decimal output     |
| unsigned long long int |    %llu   |     Decimal output     |
|                        |           |                        |
|          float         |     %f    | Floating point decimal |
|         double         |    %lf    | Floating point decimal |
|       long double      |    %llf   | Floating point decimal |
|                        |           |                        |
|         uint8_t        |    %u8    |     Decimal output     |
|        uint16_t        |    %u16   |     Decimal output     |
|        uint32_t        |    %u32   |     Decimal output     |
|        uint64_t        |    %u64   |     Decimal output     |
|                        |           |                        |
|         int8_t         |    %i8    |     Decimal output     |
|         int16_t        |    %i16   |     Decimal output     |
|         int32_t        |    %i32   |     Decimal output     |
|         int64_t        |    %i64   |     Decimal output     |
|                        |           |                        |
|          *char         |     %s    |          ASCII         |
|         char[N]        |   %s[N]   |          ASCII         |

## Modifier
x - Output as hex ie. %xi64
b - Output as binary
