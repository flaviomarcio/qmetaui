import QtQuick 2.14
import QtCharts 2.3

ChartView {

    Item {
        id: pvt
    }

    function setJson(jsonData) {
/*
        // Clear previous values
        maxTempSeries.clear();
        minTempSeries.clear();
        weatherImageModel.clear();

        // Loop through the parsed JSON
        for (var i in jsonData.data.weather) {
            var charObject = jsonData.data.weather[i];

            // Store temperature values, rainfall and weather icon.
            // The temperature values begin from 0.5 instead of 0.0 to make the start from the
            // middle of the rainfall bars. This makes the temperature lines visually better
            // synchronized with the rainfall bars.
            maxTempSeries.append(Number(i) + 0.5, charObject.tempMaxC);
            minTempSeries.append(Number(i) + 0.5, charObject.tempMinC);
            rainfallSet.append(i, charObject.precipMM);
            weatherImageModel.append({"imageSource":charObject.weatherIconUrl[0].value});

            // Update scale of the chart
            valueAxisY.max = Math.max(chartView.axisY().max,charObject.tempMaxC);
            valueAxisX.min = 0;
            valueAxisX.max = Number(i) + 1;

            // Set the x-axis labels to the dates of the forecast
            var xLabels = barCategoriesAxis.categories;
            xLabels[Number(i)] = charObject.date.substring(5, 10);
            barCategoriesAxis.categories = xLabels;
            barCategoriesAxis.visible = true;
            barCategoriesAxis.min = 0;
            barCategoriesAxis.max = xLabels.length - 1;
        }
*/
    }

}
