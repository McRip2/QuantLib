#ifndef quantlib_monte_carlo_hpp
#define quantlib_monte_carlo_hpp

#include <ql/instrument.hpp>
#include <ql/types.hpp>
#include <ql/math/matrix.hpp>
#include <vector>


namespace QuantLib {

  class PortfolioMonteCarlo {
  public:
    PortfolioMonteCarlo() {}

    Matrix simulate(const std::vector<ext::shared_ptr<Instrument>>& securities,
                    std::vector<RelinkableHandle<Quote>>& handles,
                    const Matrix& field_sims) {

      assert (field_sims.columns() == handles.size());
      Matrix simValues(field_sims.rows(), securities.size());
      std::cout << "Beginning simulation n=" << field_sims.rows() << "m=" << field_sims.columns() << std::endl;

      for(int t = 0; t < field_sims.rows(); t++)
        {
          // update handles
          for(int i = 0; i < field_sims.columns(); i++)
            {
              boost::shared_ptr<SimpleQuote> quote(new SimpleQuote(field_sims[t][i]));
              handles[i].linkTo(quote);
            }

          // calc value of securities
          for(int j = 0; j < securities.size(); j++) {
            simValues[t][j] = securities[j]->NPV();
          }
        }
      return simValues;
    }
  };

  // class TTTest {
  // public:
  //   void test(const std::vector<ext::shared_ptr<Instrument>>& securities) {

  //     for(int i = 0; i < securities.size(); i++) {
  //    std::cout << securities[i]->NPV() << std::endl;
  //     }
  //     return;
  //   };
}


#endif
