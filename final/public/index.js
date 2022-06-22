(() => {
    const timeTitle = document.querySelector('#time');
    const timeSocket = new WebSocket(`ws://${location.host}/websocket/time`);
    timeSocket.onmessage = (event) => timeTitle.innerText = event.data;

    const personTitle = document.querySelector('#person');
    const personSocket = new WebSocket(`ws://${location.host}/websocket/has_person`);
    personSocket.onmessage = (event) => personTitle.innerText = event.data;
})();