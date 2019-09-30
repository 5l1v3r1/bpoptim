/*
 * File:   Bond.h
 * Author: melichron
 *
 * Created on 10 марта 2019 г., 21:53
 */

#ifndef BOND_H
#define BOND_H

class Bond {

public:
    Bond();
    Bond(std::string bn, float cp, float cr, float ye, float NKD, float dur, int cpy=2, float nom=1000, float ys=0);
    Bond(const Bond& orig);

    Bond& operator=(const Bond& other);

    virtual ~Bond();

    //variables
    std::string bondname;
    int coupons_per_year;       // number of coupons at year

    float nominal;          // nominal price
    float current_price;    // price (part of nominal)
    float ytm_simple;             // simple ytm (вообще, это простая доходность, но названа ytm; она не применяется в этой программе, но создана для возможного будущего развития класса)
    float coupon_rate;            // rate of coupon
    float ytm_eff;                // effective ytm
    float NKD;              // nakoplennaya dohodnost' :)

    float duration;
};

#endif /* BOND_H */
