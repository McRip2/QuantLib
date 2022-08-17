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
		    std::vector<RelinkableHandle<Quote>>& vol_shift_handles,
                    const Matrix& field_sims,
		    const Matrix& vol_shifts) {

      assert (field_sims.columns() == handles.size());
      assert (field_sims.columns() == vol_shifts.columns());
      assert (field_sims.rows() == vol_shifts.rows());
      
      Matrix simValues(field_sims.rows(), securities.size());
      std::cout << "Beginning simulation n=" << field_sims.rows() << " " << "m=" << field_sims.columns() << std::endl;

      for(int t = 0; t < field_sims.rows(); t++)
        {
          // update handles
          for(int i = 0; i < field_sims.columns(); i++)
            {
              boost::shared_ptr<SimpleQuote> quote(new SimpleQuote(field_sims[t][i]));
	      boost::shared_ptr<SimpleQuote> vol_shift(new SimpleQuote(vol_shifts[t][i]));
              handles[i].linkTo(quote);
	      vol_shift_handles[i].linkTo(vol_shift);
            }

          // calc value of securities
          for(int j = 0; j < securities.size(); j++) {
            simValues[t][j] = securities[j]->NPV();
          }
        }
      return simValues;
    }
  };
}


#endif
