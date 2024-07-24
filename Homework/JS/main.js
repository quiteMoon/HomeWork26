const apiKey = 'ff9ab98ece314de3a86160746242407';

async function getWeather() {
    const city = document.getElementById('cityInput').value;
    if (!city) {
        alert('Please enter a city');
        return;
    }

    const response = await fetch(`https://api.weatherapi.com/v1/current.json?key=${apiKey}&q=${city}`);
    if (!response.ok) {
        alert('Error fetching weather data');
        return;
    }

    const data = await response.json();
    displayWeather(data);
}

function displayWeather(data) {
    const weatherInfoDiv = document.getElementById('weatherInfo');
    weatherInfoDiv.innerHTML = `
        <p><strong>City:</strong> ${data.location.name}</p>
        <p><strong>Country:</strong> ${data.location.country}</p>
        <p><strong>Temperature:</strong> ${data.current.temp_c}°C</p>
        <p><strong>Wind Speed:</strong> ${data.current.wind_kph} kph</p>
        <p><strong>Wind Direction:</strong> ${data.current.wind_dir}</p>
        <p><strong>Cloudiness:</strong> <img src="${data.current.condition.icon}" alt="Cloudiness Icon"> ${data.current.condition.text}</p>
    `;
}
