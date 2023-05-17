function answer(element, color, q) {
    let ques = document.querySelectorAll("." + element.classList[0]);
    if (element.classList[1] !== "answered") {
      element.style.backgroundColor = color;
      if (color == "red") {
        document.querySelector("." + q).innerHTML = "Incorrect Answer!";
      } else if (color == "greenyellow") {
        document.querySelector("." + q).innerHTML = "Correct Answer!";
      }
      ques.forEach((i) => {
        i.classList.add("answered");
      });
    } else {
      return false;
    }
  }

  function answer1(form, q, a) {
    let useranswer = form.answerbox.value;
    if (document.querySelector("input." + q).classList[1] !== "answered") {
      if (a == useranswer.toLowerCase()) {
        document.querySelector("input." + q).style.backgroundColor =
          "greenyellow";
        document.querySelector("span." + q).innerHTML = "Correct Answer!";
        document.querySelector("input." + q).classList.add("answered");
      } else {
        document.querySelector("input." + q).style.backgroundColor = "red";
        document.querySelector("input." + q).style.color = "white";
        document.querySelector("span." + q).innerHTML = "Incorrect Answer!";
        document.querySelector("input." + q).classList.add("answered");
      }
    } else {
      return false;
    }
  }
