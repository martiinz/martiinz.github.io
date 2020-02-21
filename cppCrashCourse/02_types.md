# Types
## Integer (32)
To enforce guaranteed integer sizes use int8_t , int16_t, ... see \<cstdint\>

## FloatingPoint (35)
- float (single precision)
- double (double precision)
- long double (extended precicion)

## Character Types (36)
- char (1 byte, eg ASCII)
- char16_t (2 byte, eg UTF-16)
- char32_t (4 byte, eg UTF-32)
- wchar_t (large enough to contain largest character, eg UNICODE)


## boolean/int conversion (38)
bool <--> int  
true --> 1  
false --> 0  
true <-- != 0  
false <-- 0 

## std::byte
raw memory access, defined in \<cstddef\>

## size_t 
encodes size of object, gua
