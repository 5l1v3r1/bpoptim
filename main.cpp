#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>

#include "alglib/optimization.h"

#include "CSVReader/CSVReader.h"
#include "Bond/Bond.h"
#include "./bpoptim.h"

float target_rate = 1.12; // target rate by default
int csvindex = 1;

int main (int argc, char** argv)
{
    //простенькая проверка аргументов
    if (argc<2) {
      std::cout << "usage: boptim r filename \n" << "where: \n r - целевая ставка в % (например, 12)\n filename - csv-файл с данными" << std::endl;
      return 0;
    }
    else if (argc==3) {
      if(target_rate = std::stoi(argv[1])) {
        target_rate = target_rate/100 + 1;
        csvindex = 2;
      }
      else {std::cout << "invalid parameter of target rate" << '\n'; return 1;}
    }

    std::string csvfile(argv[csvindex]);

    CSVReader reader(csvfile, ";"); // Creating an object of CSVReader
    std::vector<std::vector<std::string> > dataList = reader.getData(); // Get the data from CSV File
    std::vector<Bond> bonds; // create the vector of bonds (objects of class Bond)

    // Filling the vector of bonds
    for(std::vector<std::string> vec : dataList)
    {
        Bond bb = Bond();
        bb.bondname = vec[1];
        bb.coupons_per_year = std::stoi(vec[5], nullptr);       // number of coupons in year
        bb.nominal = 1000;                                      // nominal price
        bb.current_price = std::stof(vec[8], nullptr);           // price (part of nominal)
        bb.ytm_simple = std::stof(vec[11], nullptr);             // simple ytm (в этом расчете не используется, но сохранена для порядка)
        bb.coupon_rate = std::stof(vec[6], nullptr);             // rate of coupon
        bb.ytm_eff = std::stof(vec[11], nullptr);                // effective ytm
        bb.NKD = std::stof(vec[7], nullptr);
        bb.duration = std::stof(vec[4], nullptr);

        bonds.push_back (bb);
    }

    // creating the matrix for optimization problem
    std::vector<float> durations;
    std::vector<float> disfactor; //discount factor (disfactor = ytm+1)
    std::vector<float> durperytm; // duration/disfactor
    for(Bond bb : bonds)
      {
        durations.push_back(bb.duration);
        disfactor.push_back(bb.ytm_eff/100+1);
        durperytm.push_back(bb.duration/(bb.ytm_eff/100+1));
      }

    size_t n = durations.size();

    alglib::real_2d_array qpma; qpma.setlength(n,n); // matrix nxn
    alglib::real_2d_array qpmq; qpmq.setlength(n,n); // matrix nxn

    // filling the matrix
    for(size_t j=0; j < n; j++) //columns
    {
      //rows
      for (size_t i = 0; i < n; i++) qpma(i,j) = durperytm[j]*disfactor[i];  //i,j matrix element
    }

    for(size_t j=0; j < n; j++) //columns
    {
      //rows
      for (size_t i = 0; i < n; i++) qpmq(i,j) = qpma(i,j) + qpma(j,i); // summ with the transponed matrix
    }

    // solver preparation
    alglib::real_1d_array x0; x0.setlength(n); double sp = 1/n; for (size_t i = 0; i < n; i++) x0[i] = sp;  //  start point
    alglib::real_1d_array b; b.setlength(n);  for (size_t i = 0; i < n; i++) b[i] = 0;  //  linear part
    alglib::real_1d_array s; s.setlength(n); for (size_t i = 0; i < n; i++) s[i] = 1;   // scales
    alglib::real_2d_array c; c.setlength(2, n+1); // linear constraints
    for (size_t i = 0; i < n; i++)
      {
        c(0,i) = disfactor[i];
        c(1,i) = 1;
      }
      c(0,n) = target_rate; c(1,n) = 1;
    alglib::integer_1d_array ct = "[0,0]"; // type of relation in linear constraints
    alglib::real_1d_array bndl; bndl.setlength(n); for (size_t i = 0; i < n; i++) bndl[i] = 0.0; // low boundary
    alglib::real_1d_array bndu; bndu.setlength(n); for (size_t i = 0; i < n; i++) bndu[i] = 0.3;// high boundary
    alglib::real_1d_array x;  // result point
    alglib::minqpstate state; // main object
    alglib::minqpreport rep;  // report

    alglib::minqpcreate(n, state);
    alglib::minqpsetalgobleic(state, 0.0, 0.0, 0.0, 0);
    alglib::minqpsetquadraticterm(state, qpmq);
    alglib::minqpsetstartingpoint(state, x0);
    alglib::minqpsetlinearterm(state, b);
    alglib::minqpsetlc(state, c, ct);
    alglib::minqpsetbc(state, bndl, bndu);
    alglib::minqpsetscale(state, s);

    alglib::minqpoptimize(state);
    alglib::minqpresults(state, x, rep);

    alglib::ae_int_t tt = rep.terminationtype;
    if (tt>=0)
    {
      std::cout << "Веса облигаций в портфеле:" << '\n';
      for(size_t i = 0; i < n; i++)
      {
        std::cout << (i+1) << ".\t" << bonds[i].bondname << ":\t\t\t " << (x(i)*100) << "\%" << std::endl;
      }

      for (size_t i = 0; i < n; i++)
      {
        for (size_t j = 0; j < n; j++)
        {
          qpmq(i,j) /= 2;
        }
      }

      double result = VecProd(x, MxVecProd(qpma, x));
      std::cout << "Расчетная дюрация: \t" << result << " Дней" << std::endl;

    }
    else
    {
      std::cout << "completion code: " << tt << '\n';
    }

  return 0;
}
