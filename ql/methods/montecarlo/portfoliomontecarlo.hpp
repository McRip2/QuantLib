#ifndef quantlib_monte_carlo_hpp
#define quantlib_monte_carlo_hpp

#include <ql/instrument.hpp>
#include <ql/types.hpp>
#include <ql/math/matrix.hpp>
#include <ql/patterns/observable.hpp>
#include <vector>


namespace QuantLib {

  class PortfolioMonteCarlo {
  public:
    PortfolioMonteCarlo() {}

    Matrix simulate(const std::vector<ext::shared_ptr<Instrument>>& securities,
                    std::vector<RelinkableHandle<Quote>>& handles,
                    const Matrix& sims) {

      assert (sims.columns() == handles.size());
      
      Matrix simValues(sims.rows(), securities.size());
      std::cout << "Beginning simulation n=" << sims.rows() << " " << "m=" << sims.columns() << std::endl;

      for(int t = 0; t < sims.rows(); t++)
        {
	  if(t%100 == 0) {
	    std::cout << "t=" << t << std::endl;
	  }

	  ObservableSettings::instance().disableUpdates(true);
          // update handles
          for(int i = 0; i < sims.columns(); i++)
            {
              boost::shared_ptr<SimpleQuote> quote(new SimpleQuote(sims[t][i]));
              handles[i].linkTo(quote);
            }
	  
          // calc value of securities
	  ObservableSettings::instance().enableUpdates();	  
          for(int j = 0; j < securities.size(); j++) {
            simValues[t][j] = securities[j]->NPV();
          }
        }
      return simValues;
    }
  };
}


#endif
