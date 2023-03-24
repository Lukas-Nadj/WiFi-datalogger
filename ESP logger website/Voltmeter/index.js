var chartT = new Highcharts.Chart({
  chart: { renderTo: "chart-temperature" },
  title: { text: "DataGraf" },
  series: [
    {
      showInLegend: true,
      name: "Voltage",
      data: [],
    },
    {
      showInLegend: true,
      name: "Amperes",
      data: [],
    },
  ],
  plotOptions: {
    line: { animation: false, dataLabels: { enabled: true } },
    series: { color: "#059e8a" },
  },
  xAxis: { type: "datetime", dateTimeLabelFormats: { second: "%H:%M:%S" } },
  yAxis: {
    title: { text: "Temperature (Celsius)" },
    //title: { text: 'Temperature (Fahrenheit)' }
  },
  credits: { enabled: false },
});
const queryString = window.location.search; // "?param1=value1&param2=value2"
const params = new URLSearchParams(queryString);
const param1 = params.get("Frekvens"); // "value1"
setInterval(function () {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var x = new Date().getTime(),
        y = parseFloat(this.responseText);
        chartT.series[0].addPoint([x, y], true, false, true);
        chartT.series[1].addPoint([x, y], true, false, true);
      //console.log(this.responseText);
      /*if (chartT.series[0].data.length > 40) {
        chartT.series[0].addPoint([x, y], true, true, true);
      } else {
        chartT.series[0].addPoint([x, y], true, false, true);
      }
      if (chartT.series[1].data.length > 40) {
        chartT.series[1].addPoint([x, y], true, true, true);
      } else {
        chartT.series[1].addPoint([x, y], true, false, true);
      }*/
    }
  };
  //xhttp.open("GET", "http://"+window.location.hostname+"/temperature", true);
  xhttp.open("GET", "http://"+"192.168.181.131" + "/temperature", true);
  xhttp.send();
}, param1);
document.getElementById("download").addEventListener("click", function() {
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
};


