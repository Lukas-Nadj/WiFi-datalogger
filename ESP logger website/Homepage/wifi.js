function addToWifi(value) {
  // Find the div element with id "list"
  const listDiv = document.getElementById("wifi");

  // Create a new div element with the "item" class
  const itemDiv = document.createElement("div");
  itemDiv.className = "item";

  // Get the current number of items in the list
  const itemCount = listDiv.children.length;

  // Set the id of the itemDiv to "item-N", where N is the current item count
  itemDiv.id = `item-${itemCount}`;

  // Create an input element with the specified value
  const inputElem = document.createElement("input");
  inputElem.style.width = "100%";
  inputElem.value = value;

  // Create a "Edit" div element with the "logo vis edit" classes
  const editDiv = document.createElement("div");
  editDiv.className = "logo vis edit";
  editDiv.textContent = "Edit";

  // Create a "Slet" div element with the "logo vis delete" classes
  const deleteDiv = document.createElement("div");
  deleteDiv.className = "logo vis delete";
  const deleteLink = document.createElement("a");
  /*deleteLink.onclick = function () {
    deleteItem(itemCount);
  };*/
  deleteLink.textContent = "Slet";
  deleteDiv.appendChild(deleteLink);

  // Add the input, edit, and delete elements to the itemDiv
  itemDiv.appendChild(inputElem);
  itemDiv.appendChild(editDiv);
  itemDiv.appendChild(deleteDiv);

  // Add the itemDiv to the listDiv
  listDiv.appendChild(itemDiv);
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
  xhr.open("GET", url);
  xhr.onload = function () {
    if (xhr.status === 200) {
      // Split the response into lines
      const lines = xhr.responseText.split("\n");
      // Loop through the lines and add them to the list
      lines.forEach(function (line) {
        if (line.trim() !== "") {
          addToWifi(line.trim());
        }
      });
    } else {
      console.error("Request failed.  Returned status of " + xhr.status);
    }
  };
  xhr.send();
}

function addTowifi(value) {
  // Find the div element with id "list"
  const listDiv = document.getElementById("auto");

  const existingInput = Array.from(listDiv.querySelectorAll("p")).find(
    (p) => p.textContent === value
  );
  // If an input element with the same value already exists, return to skip creating the new div elements
  if (existingInput) {
    return;
  }
  const itemDiv = document.createElement("div");
  itemDiv.className = "item";
  itemDiv.id = `item-${listDiv.children.length}`;

  // Create a <p> element with the specified value and style
  const pElem = document.createElement("p");
  pElem.style.width = "100%";
  pElem.textContent = value;
  itemDiv.style.cursor = "pointer";
  itemDiv.style.backgroundColor = "gray";
  pElem.style.backgroundColor = "gray";
  itemDiv.appendChild(pElem);

  // Create a "Vis" div element with the "logo vis" classes and style
  const visDiv = document.createElement("div");
  visDiv.className = "logo vis";
  visDiv.style.flexDirection = "row";
  visDiv.style.justifyContent = "flex-end";
  visDiv.style.paddingRight = "5px";
  const iElem = document.createElement("i");
  iElem.className = "material-icons";
  iElem.style.fontSize = "15px";
  iElem.innerHTML = "&#xe63e;";
  visDiv.appendChild(iElem);
  itemDiv.appendChild(visDiv);

  // Add the itemDiv to the listDiv
  listDiv.appendChild(itemDiv);
}

setInterval(function () {
  const url = `http://esp8266.local`;
  const xhr = new XMLHttpRequest();
  xhr.open("GET", url);
  xhr.onload = function () {
    if (xhr.status === 200) {
      const trimmedUrl = url.replace(/^http:\/\//i, "");
      addTowifi(trimmedUrl);
      console.log("yessir");
    } else {
      console.log("no sir " + url);
    }
  };
  xhr.send();
  for (let i = 0; i < 10; i++) {
    const url = `http://esp8266-${i}.local`;
    const xhr = new XMLHttpRequest();
    xhr.open("GET", url);
    xhr.onload = function () {
      if (xhr.status === 200) {
        const trimmedUrl = url.replace(/^http:\/\//i, "");
        addTowifi(trimmedUrl);
        console.log("yessir");
      } else {
        console.log("no sir " + url);
      }
    };
    xhr.send();
  }
}, 2000);
