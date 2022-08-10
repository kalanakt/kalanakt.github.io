nav_parent = document.querySelector('#navigation')
nav_texts = ["home", "about", "services", "contact"]

for text in nav_texts:
    nav_item = document.createElement("li")
    nav_item.textContent = text
    nav_item.className = "nav_element"
    nav_parent.appendChild(nav_item)
