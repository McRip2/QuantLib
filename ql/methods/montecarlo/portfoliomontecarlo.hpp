#ifndef quantlib_monte_carlo_hpp
#define quantlib_monte_carlo_hpp

#include <ql/instrument.hpp>
#include <ql/types.hpp>
#include <ql/math/matrix.hpp>
#include <ql/patterns/observable.hpp>
#include <ql/handle.hpp>
#include <ql/quote.hpp>
#include <ql/quotes/simplequote.hpp>
#include <vector>
#include <iostream>

namespace QuantLib {

  class PortfolioMonteCarlo {
  public:
    PortfolioMonteCarlo() {}

    Matrix simulate(const std::vector<ext::shared_ptr<Instrument>>& securities,
                    std::vector<RelinkableHandle<Quote>>& handles,
                    const Matrix& sims);
  };
}

#endif
