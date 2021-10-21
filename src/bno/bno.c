#include "bno.h"
#include "../stm32/f4/i2c/i2c.h"




char *BNO_err_str(const bno_err_t err) {
    switch (err) {
        case BNO_ERR_I2C:
            return "I2C error";
        default:
            return "BNO ok";
    }
}
