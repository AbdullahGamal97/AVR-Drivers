
#ifndef UTILITES_BIT_MATH_H_
#define UTILITES_BIT_MATH_H_

#define SET_BIT(REG,BITNO) (REG) |=  (1 << (BITNO))
#define CLR_BIT(REG,BITNO) (REG) &= ~(1 << (BITNO))
#define TOG_BIT(REG,BITNO) (REG) ^=  (1 << (BITNO))
#define GET_BIT(REG,BITNO) (((REG) >> (BITNO)) & 0x01)


#endif /* UTILITES_BIT_MATH_H_ */
