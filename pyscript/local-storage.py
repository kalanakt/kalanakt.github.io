from js import localStorage


def save_comment(e):
    text = Element("comment").value
    localStorage.setItem("comment", text)


if localStorage.getItem("comment"):
    text_area = Element("comment")
    text_area.write(localStorage.getItem("comment"))
