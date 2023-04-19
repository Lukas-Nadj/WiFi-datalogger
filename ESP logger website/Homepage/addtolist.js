function addToList() {
    // Create new div with class "item"
    var newItem = document.createElement("div");
    newItem.classList.add("item");

    // Create new input element with style "width:100%"
    var newInput = document.createElement("input");
    newInput.style.width = "100%";
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