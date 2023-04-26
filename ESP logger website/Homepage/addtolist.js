
  function addToList(value) {
    // Find the div element with id "list"
    const listDiv = document.getElementById("list");
    
    // Create a new div element with the "item" class
    const itemDiv = document.createElement("div");
    itemDiv.className = "item";
  
    // Get the current number of items in the list
    const itemCount = listDiv.children.length;
  
    // Set the id of the itemDiv to "item-N", where N is the current item count
    itemDiv.id = `item-${itemCount}`;
  
    // Create an input element with the specified value
    const inputElem = document.createElement("p");
    inputElem.style.width = "100%";
    inputElem.innerHTML = value;
  
    // Create a "Edit" div element with the "logo vis edit" classes
    const editDiv = document.createElement("div");
    editDiv.className = "logo vis edit";
    editDiv.textContent = "Edit";
  
    // Create a "Slet" div element with the "logo vis delete" classes
    const deleteDiv = document.createElement("div");
    deleteDiv.className = "logo vis delete";
    const deleteLink = document.createElement("a");
    deleteLink.onclick = function() {
      deleteItem(itemCount);
    };
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
  
  