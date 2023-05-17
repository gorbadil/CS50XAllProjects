document.addEventListener("mousemove", (e) => {
    setPosition(e);
  });

  document.addEventListener("touchmove", (e) => {
    setPosition(e);
  });

  let spark = document.querySelector("div.spark");
  let root = document.documentElement;
  function setPosition(e) {
    spark.style.top = e.pageY - 10 + "px";
    spark.style.left = e.pageX - 10 + "px";
    root.style.setProperty("--mx", e.pageX + "px");
    root.style.setProperty("--my", e.pageY + "px");
  }

  setInterval(() => {
    var i = document.querySelector(".start");
    if (i.style.visibility == "hidden") {
      i.style.visibility = "visible";
    } else {
      i.style.visibility = "hidden";
    }
  }, 1000);

  setInterval(() => {
    var i = document.querySelector(".end");
    if (i.style.visibility == "visible") {
      i.style.visibility = "hidden";
    } else {
      i.style.visibility = "visible";
    }
  }, 1000);
