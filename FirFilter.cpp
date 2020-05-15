#include "FirFilter.h"

# include <Eigen/Dense>

// Apply FIR filter on the raw signal
Eigen::VectorXd filteredDataArray(rawSignal.dataArray.size());
for (size_t iRaw = 0; iRaw < numSample; ++iRaw) {
    double filteredData{0.0};  // initialize the value of the filtered data
    for (size_t iConv = 0; iConv < filterOrder; iConv++) {
        double rawData{std::numeric_limits<double>::quiet_NaN()};
         /**
          * if iRaw >= iConv, the raw data is from the incoming signal, otherwise, the raw data
          * is from the patch
          */
        iRaw >= iConv ? rawData = rawSignal.dataArray(iRaw - iConv)
                      : rawData = noisePatch(patchSize + iRaw - iConv);
        filteredData += lidarParams.rfAdcSettings.firZero(iConv) * rawData;
    }
        filteredDataArray(iRaw) = filteredData;
}