var chartT = new Highcharts.Chart({
  chart: {
    renderTo: "chart-temperature",
    zoomType: "xy",
    panning: {
      enabled: true,
      type: "xy",
    },
    panKey: "shift",
  },
  boost: {
    useGPUTranslations: true,
    // Chart-level boost when there are more than 5 series in the chart
    seriesThreshold: 5,
  },
  title: { text: "DataGraf" },

  series: [
    {
      boostThreshold: 10,
      showInLegend: true,
      name: "Voltage",
      lineColor: "#A4A519",
      data: [],
    },
    {
      boostThreshold: 10,
      showInLegend: true,
      name: "Amperes",
      lineColor: "#FF3B25",
      data: [],
    },
  ],
  plotOptions: {
    line: { animation: false, dataLabels: { enabled: true } },
    series: { color: "#059e8a" },
  },
  xAxis: { type: "datetime", dateTimeLabelFormats: { second: "%H:%M:%S" } },
  yAxis: {
    title: { text: "Voltage" + " " + "Amperes" },
    min: 0,
    minRange: 0.5,
    //title: { text: 'Temperature (Fahrenheit)' }
  },
  credits: { enabled: false },
});

let queryString = window.location.search; // "?param1=value1&param2=value2"
let params = new URLSearchParams(queryString);
let Frekvens = params.get("Frekvens"); // "value1"
let Punkter = params.get("Punkter"); // "value1"
setInterval(function () {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var x = new Date().getTime(),
        y = parseFloat(this.responseText);

      //console.log(this.responseText);
      if (chartT.series[0].data.length > Punkter) {
        chartT.series[0].addPoint([x, y], true, true, true);
      } else {
        chartT.series[0].addPoint([x, y], true, false, true);
      }
      if (chartT.series[1].data.length > Punkter) {
        chartT.series[1].addPoint([x, y], true, true, true);
      } else {
        chartT.series[1].addPoint([x, y], true, false, true);
      }
      let a = document.getElementById("frekvens").value;
      let b = document.getElementById("punkter").value;
      document.getElementById("tid").innerHTML =
        parseInt(((1.0 / a) * b) / 60.0) +
        " minutter og " +
        (parseInt(1.0 * (1.0 / a) * b) % 60) +
        " sekunder";
      document.getElementById("remain").innerHTML =
        parseInt((1.0 * (1.0 / a) * (b - chartT.series[0].data.length)) / 60) +
        " minutter og " +
        (parseInt(1.0 * (1.0 / a) * (b - chartT.series[0].data.length)) % 60) +
        " sekunder";
    }
  };
  //xhttp.open("GET", "http://"+window.location.hostname+"/temperature", true);
  xhttp.open(
    "GET",
    "http://" + document.getElementById("source").value + "/voltage",
    true
  );
  xhttp.send();
}, (1.0 / Frekvens) * 1000);
document.getElementById("download").addEventListener("click", function () {
  download(chartT.getCSV());
});
function download(data) {
  // Creating a Blob for having a csv file format
  // and passing the data with type
  const blob = new Blob([data], { type: "text/csv" });

  // Creating an object for downloading url
  const url = window.URL.createObjectURL(blob);

  // Creating an anchor(a) tag of HTML
  const a = document.createElement("a");

  // Passing the blob downloading url
  a.setAttribute("href", url);

  // Setting the anchor tag attribute for downloading
  // and passing the download file name
  a.setAttribute("download", "download.csv");

  // Performing a download with click
  a.click();
}
