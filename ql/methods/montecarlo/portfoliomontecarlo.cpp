/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
  Copyright (C) 2006 StatPro Italia srl

  This file is part of QuantLib, a free-software/open-source library
  for financial quantitative analysts and developers - http://quantlib.org/

  QuantLib is free software: you can redistribute it and/or modify it
  under the terms of the QuantLib license.  You should have received a
  copy of the license along with this program; if not, please email
  <quantlib-dev@lists.sf.net>. The license is also available online at
  <http://quantlib.org/license.shtml>.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

// ===========================================================================
// NOTE: The following copyright notice applies to the original code,
//
// Copyright (C) 2002 Peter Jäckel "Monte Carlo Methods in Finance".
// All rights reserved.
//
// Permission to use, copy, modify, and distribute this software is freely
// granted, provided that this notice is preserved.
// ===========================================================================

#include <ql/methods/montecarlo/portfoliomontecarlo.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
 
namespace QuantLib {

    Matrix PortfolioMonteCarlo::simulate(const std::vector<ext::shared_ptr<Instrument>>& securities,
                                         std::vector<RelinkableHandle<Quote>>& handles,
                                         const Matrix& sims) {
        assert (sims.columns() == handles.size());

        Matrix simValues(sims.rows(), securities.size());
        std::cout << "Beginning simulation T=" << sims.rows()
                  << " n_secs=" << securities.size()
                  << " n_handles=" << handles.size() << std::endl;

        for(int t = 0; t < sims.rows(); t++)
            {
                if(t%100 == 0) {
                    std::cout << "t=" << t << std::endl;
                }
                
                QuantLib::ObservableSettings::instance().disableUpdates(true);
                // update handles
                for(int i = 0; i < sims.columns(); i++)
                    {
                        boost::shared_ptr<SimpleQuote> quote(new SimpleQuote(sims[t][i]));
                        handles[i].linkTo(quote);
                    }
                
                QuantLib::ObservableSettings::instance().enableUpdates();
                // calc value of securities
                for(int j = 0; j < securities.size(); j++) {
                    simValues[t][j] = securities[j]->NPV();
                }
            }
        return simValues;
    }
}
