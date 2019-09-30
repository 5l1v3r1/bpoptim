#include <string>

#include "Bond/Bond.h"

Bond::Bond ()
{
  bondname = "bondname";
  coupons_per_year = 2;       // number of coupons in year

  nominal = 1000;    // nominal price
  current_price = 1000;    // price (part of nominal)
  ytm_simple = 0;             // simple ytm
  coupon_rate = 0;            // rate of coupon
  ytm_eff = 0;                // effective ytm
  NKD = 0;

  duration = 0;
}
Bond::Bond (std::string bn, float cp, float cr, float ye, float NKD, float dur, int cpy, float nom, float ys):
		bondname(bn), coupons_per_year(cpy), nominal(nom), current_price(cp), ytm_simple(ys), coupon_rate(cr), ytm_eff(ye), NKD(NKD), duration(dur)
{ }

Bond::Bond (const Bond& orig)
{
  bondname = orig.bondname;
  coupons_per_year = orig.coupons_per_year;       // number of coupons in year

  nominal = orig.nominal;    // nominal price
  current_price = orig.current_price;    // price (part of nominal)
  ytm_simple = orig.ytm_simple;             // simple ytm
  coupon_rate = orig.coupon_rate;            // rate of coupon
  ytm_eff = orig.ytm_eff;                // effective ytm
  NKD = orig.NKD;

  duration = orig.duration;
}

Bond& Bond::operator = (const Bond& other) //copy assignment
{
    if (this == &other)
        return *this;


    bondname = other.bondname;
    coupons_per_year = other.coupons_per_year;       // number of coupons in year

    nominal = other.nominal;    // nominal price
    current_price = other.current_price;    // price (part of nominal)
    ytm_simple = other.ytm_simple;             // simple ytm
    coupon_rate = other.coupon_rate;            // rate of coupon
    ytm_eff = other.ytm_eff;                // effective ytm
    NKD = other.NKD;

    duration = other.duration;

    return *this;
}

Bond::~Bond () { }
