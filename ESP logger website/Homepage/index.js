
/*function addToList(value) {
  // Create new div with class "item"
  var newItem = document.createElement("div");
  newItem.classList.add("item");

  // Create new input element with style "width:100%" and set its value to the input string
  var newInput = document.createElement("input");
  newInput.style.width = "100%";
  newInput.value = value;
  newItem.appendChild(newInput);

  // Create new div with class "logo vis edit" and text "Edit"
  var newEdit = document.createElement("div");
  newEdit.classList.add("logo", "vis", "edit");
  newEdit.textContent = "Edit";
  newItem.appendChild(newEdit);

  // Create new div with class "logo vis delete" and a child anchor tag with text "Slet"
  var newDelete = document.createElement("div");
  newDelete.classList.add("logo", "vis", "delete");
  var deleteLink = document.createElement("a");
  deleteLink.textContent = "Slet";
  newDelete.appendChild(deleteLink);
  newItem.appendChild(newDelete);

  // Add the new div as a child of the div with id "list"
  var listDiv = document.getElementById("list");
  listDiv.appendChild(newItem);
}*/
function addToList(value) {
  // Create new div with class "item"
  var newItem = document.createElement("div");
  newItem.classList.add("item");

  // Create new input element with style "width:100%" and set its value to the input string
  var newInput = document.createElement("input");
  newInput.style.width = "100%";
  newInput.value = value;
  newItem.appendChild(newInput);

  // Create new div with class "logo vis edit" and text "Edit"
  var newEdit = document.createElement("div");
  newEdit.classList.add("logo", "vis", "edit");
  newEdit.textContent = "Edit";
  // Add an index to the ID of the Edit button
  newEdit.id = "edit-" + (document.getElementsByClassName("item").length + 1);
  newItem.appendChild(newEdit);

  // Create new div with class "logo vis delete" and a child anchor tag with text "Slet"
  var newDelete = document.createElement("div");
  newDelete.classList.add("logo", "vis", "delete");
  var deleteLink = document.createElement("a");
  deleteLink.textContent = "Slet";
  // Add an index to the ID of the Delete button
  deleteLink.id = "delete-" + (document.getElementsByClassName("item").length + 1);
  newDelete.appendChild(deleteLink);
  newItem.appendChild(newDelete);

  // Add the new div as a child of the div with id "list"
  var listDiv = document.getElementById("list");
  listDiv.appendChild(newItem);
}
function deleteItem(index) {
  // Remove the div with the given index from the list
  var itemToDelete = document.getElementById("item-" + index);
  itemToDelete.parentNode.removeChild(itemToDelete);
}
function clearList() {
  var listDiv = document.getElementById("list");
  listDiv.innerHTML = "";
}
function addLinesToList(url) {
  clearList();
  const xhr = new XMLHttpRequest();
  xhr.open('GET', url);
  xhr.onload = function() {
    if (xhr.status === 200) {
      // Split the response into lines
      const lines = xhr.responseText.split('\n');
      // Loop through the lines and add them to the list
      lines.forEach(function(line) {
        if (line.trim() !== '') {
          addToList(line.trim());
        }
      });
    } else {
      console.error('Request failed.  Returned status of ' + xhr.status);
    }
  };
  xhr.send();
}



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
    "http://" + document.getElementById("source").value + "/voltage"+window.location.search,
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
// Add an event listener for the Delete button
document.addEventListener("click", function(event) {
  if (event.target && event.target.id.startsWith("delete-")) {
    // Get the index from the ID of the Delete button
    var index = parseInt(event.target.id.split("-")[1]);
    deleteItem(index);
  }
});

addToList("bruh");
