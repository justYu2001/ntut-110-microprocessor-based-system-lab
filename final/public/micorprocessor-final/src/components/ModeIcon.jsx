import React, { useState, useEffect } from "react";
import daytimeIcon from "../assets/images/daytime.png";
import nightIcon from "../assets/images/night.png";

const ModeIcon = () => {
    const [websocket, setWebsocket] = useState(null);

    useEffect(() => {
        const connectWebsocket = () => {
            let websocketURL = "";

            if (process.env.NODE_ENV === "development") {
                websocketURL = `ws://localhost:8000/websocket/time`;
            } else {
                websocketURL = `ws://${window.location.host}/websocket/time`;
            }
    
            setWebsocket(new WebSocket(websocketURL));
        };

        connectWebsocket();
    }, []);

    const [mode, setMode] = useState();

    useEffect(() => {
        if (websocket) {
            websocket.onmessage = (event) => setMode(event.data);
        }
    }, [websocket]);

    return (
        <img src={mode === "night" ? nightIcon : daytimeIcon} alt="mode icon" className="w-20 h-20" />
    );
};

export default ModeIcon;