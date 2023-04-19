document.getElementById("source").value+"/data"
function clearList() {
    var listDiv = document.getElementById("list");
    listDiv.innerHTML = "";
  }
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
  }
  
  function addLinesToList() {
    clearList();
    var url = "http://"+document.getElementById("source").value+"/data";
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