function displayNavigation(response) {
    new Typewriter("#ai", {
      strings: response.data.answer,
      autoStart: true,
      delay: 3,
      cursor: "",
    });
  }

  function generateNavigation(event) {
    event.preventDefault();

    let stationSelect = document.querySelector("#station");
    let apiKey = "6f64aatd0b0oe3cc63e4fb944c32303a";
    let prompt = `User selected or inputed instructions: Generate ${stationSelect.value} `;
    let context =
      "You are London underground step-free access expert. Your mission is to write short 4 line information. Make sure to follow user input. If user wrote incorrect London underground station name, correct user input and say do you mean and type correct station name. Do not include a title a name of chosen station. Sign </br> </br> <strong>Step-free Navigator AI</strong> at the end.";
    let apiUrl = `https://api.shecodes.io/ai/v1/generate?prompt=${prompt}&context=${context}&key=${apiKey}`;

    let aiElement = document.querySelector("#ai");
    aiElement.classList.remove("hidden");
    aiElement.innerHTML = `<div id="loading"></div>  Generating ${stationSelect.value} station information `;

    axios.get(apiUrl).then(displayNavigation);
  }

  let stationFormatElement = document.querySelector("#station-navigator");
  stationFormatElement.addEventListener("submit", generateNavigation);
