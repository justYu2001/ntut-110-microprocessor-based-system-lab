(() => {
    const timeTitle = document.querySelector('#time');
    const timeSocket = new WebSocket(`ws://${location.host}/websocket/time`);
    timeSocket.onmessage = (event) => timeTitle.innerText = event.data;
})();