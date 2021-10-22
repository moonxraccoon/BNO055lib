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


bno_err_t BNO_set_pwr_mode(const bno_t bno, const bno_pwr_t pwr) {
    if (I2C_write(bno._i2c, BNO_ADDR, BNO_PWR_MODE, pwr) != I2C_OK) {
        return BNO_ERR_I2C;
    }
    return BNO_OK;
}

bno_err_t BNO_set_page(const bno_t bno, const bno_page_t page) {
    if (I2C_write(bno._i2c, BNO_ADDR, BNO_PAGE_ID, page) != I2C_OK) {
        return BNO_ERR_I2C;
    }
    return BNO_OK;
}
